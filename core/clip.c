#include "clip.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "strlist.h"

void Clip_ctor(Clip *this, Clip *conf)
{
    this->power_max = conf->power_max;
    this->density = 1.0 / conf->density;
    this->offset_x = conf->offset_x;
    this->offset_y = conf->offset_y;
    this->min_x = conf->min_x;
    this->min_y = conf->min_y;
    this->max_x = conf->max_x;
    this->max_y = conf->max_y;
    this->img_width_px = conf->img_width_px;
    this->img_height_px = conf->img_height_px;
}

st_strlist *Clip_generator_one_line_gcode(Clip *this, unsigned char *gray_list, unsigned int gray_list_len, unsigned int line_num)
{
    int is_reverse = (this->img_height_px - line_num) % 2 == 0;
    int is_new_row = 1;
    st_strlist *gcode_list = strlist_malloc();
    int last_power = -1;
    for (int i = is_reverse ? gray_list_len - 1 : 0;
                      is_reverse ? i >= 0 : i < gray_list_len;
                      is_reverse ? i-- : i++)
    {
        int s_power = Clip_get_power(this, gray_list[i]);
        if (is_new_row)
        {
            strlist_push(gcode_list, "G0 X%.3f Y%.3f S0", Clip_normalizer_x(this, i), Clip_normalizer_y(this, line_num));
            strlist_push(gcode_list, "G1 X%.3f S%d", Clip_normalizer_x(this, i), s_power);
            is_new_row = 0;
        }else {
            if (i > 1 && i < gray_list_len-2 && s_power == last_power){
                strlist_removeLast(gcode_list);
            }
            strlist_push(gcode_list, "X%.3f S%d", Clip_normalizer_x(this, i), s_power);
        }
        last_power = s_power;
    }
    return gcode_list;
}

float Clip_normalizer_x(Clip *this, int x)
{
    float res = x;
    float half = (this->min_x + this->max_x) * 0.5;
    res = res - half;
    res = res * this->density;
    res = res + this->offset_x;
    return res;
}

float Clip_normalizer_y(Clip *this, int y)
{
    float res = y;
    float half = (this->min_y + this->max_y) * 0.5;
    res = res - half;
    res = res * this->density;
    res = res + this->offset_y;
    return res;
}

int Clip_get_power(Clip *this, unsigned char gray)
{
    float s_power;
    s_power = (255 - gray) / 255.0 * this->power_max;
    return (int)s_power;
}