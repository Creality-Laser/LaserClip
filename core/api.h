#pragma once
#include "clip.h"

/* Line to line scanning algorithm 
    char *bmpPath  Bmp image file path
    char *gcodePath Save gcode file path
    Clip *conf Set the parameters
*/
int line_to_line_gcode(char *bmpPath, char *gcodePath, Clip *conf);