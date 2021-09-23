#pragma once
#include "strlist.h"

typedef struct
{
    unsigned int power_max;
    unsigned int work_speed;
    unsigned int jog_speed;
    float density;
    float offset_x;
    float offset_y;
    float min_x;
    float min_y;
    float max_x;
    float max_y;
    unsigned int img_width_px;
    unsigned int img_height_px;
} Clip;

void Clip_ctor(Clip *this, Clip *conf);
st_strlist *Clip_generator_one_line_gcode(Clip *this, unsigned char *gray_list, unsigned int gray_list_len, unsigned int line_num);
float Clip_normalizer_x(Clip *this, int x);
float Clip_normalizer_y(Clip *this, int y);
int Clip_get_power(Clip *this, unsigned char gray);