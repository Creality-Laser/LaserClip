#include <stdio.h>
#include <stdlib.h>
#include "core/clip.h"
#include "core/strlist.h"
#include "lib/qdbmp.h"

int main()
{
    BMP *bmp;
    UCHAR r, g, b;
    UINT width, height;
    int x, y;

    /* Read an image file */
    bmp = BMP_ReadFile("image.bmp");
    BMP_CHECK_ERROR(stderr, -1); /* If an error has occurred, notify and exit */

    /* Get image's dimensions */
    width = BMP_GetWidth(bmp);
    height = BMP_GetHeight(bmp);

    unsigned char gray[width];
    /*Clip config*/
    Clip conf;
    conf.power_max = 1000;
    conf.density = 10;
    conf.offset_x = 50;
    conf.offset_y = 50;
    conf.min_x = 0;
    conf.min_y = 0;
    conf.max_x = width;
    conf.max_y = height;
    conf.img_width_px = width;
    conf.img_height_px = height;
    Clip clip_1;
    Clip_ctor(&clip_1, &conf);

    FILE *fp = NULL;
    fp = fopen("test.gcode", "w+");
    /* Iterate through all the image's pixels */
    fprintf(fp, "G1 F1000\n");
    fprintf(fp, "M4\n");
    for (y = height - 1; y >= 0 ; --y)
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
        /*strlist_infolog(oneline_gcode);*/
        strlist_free(oneline_gcode);
    }
    fclose(fp);
    /* Free all memory allocated for the image */
    BMP_Free(bmp);
    return 0;
}