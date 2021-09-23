#include <stdio.h>
#include <stdlib.h>
#include "clip.h"
#include "strlist.h"
#include "../lib/qdbmp.h"
#include "api.h"

int line_to_line_gcode(char *bmpPath, char *gcodePath, Clip *conf)
{
    BMP *bmp;
    UCHAR r, g, b;
    UINT width, height;
    int x, y;

    bmp = BMP_ReadFile(bmpPath);
    BMP_CHECK_ERROR(stderr, -1);
    width = BMP_GetWidth(bmp);
    height = BMP_GetHeight(bmp);
    unsigned char gray[width];

    Clip clip_1;
    conf->min_x = 0;
    conf->min_y = 0;
    conf->max_x = width;
    conf->max_y = height;
    conf->img_width_px = width;
    conf->img_height_px = height;
    Clip_ctor(&clip_1, conf);

    FILE *fp = NULL;
    fp = fopen(gcodePath, "w+");

    fprintf(fp, "G90\n");
    fprintf(fp, "G1 F%d\n", conf->jog_speed);
    fprintf(fp, "M4\n");

    for (y = height - 1; y >= 0; --y)
    {
        for (x = 0; x < width; ++x)
        {
            /* Get pixel's RGB values */
            BMP_GetPixelRGB(bmp, x, y, &r, &g, &b);
            gray[x] = r;
        }
        /*get one line pixel to generator gcode*/
        st_strlist *oneline_gcode = Clip_generator_one_line_gcode(&clip_1, gray, sizeof(gray), y);
        for (int i = 0; i < oneline_gcode->size; i++)
        {
            fprintf(fp, "%s\n", oneline_gcode->list[i]);
        }
        strlist_free(oneline_gcode);
    }

    fprintf(fp, "M5\n");
    fprintf(fp, "G0 X0 Y0\n");
    fclose(fp);
    BMP_Free(bmp);
    return 0;
}