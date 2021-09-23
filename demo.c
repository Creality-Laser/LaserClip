#include "core/api.h"

int main()
{
    Clip conf;
    conf.power_max = 1 * 1000; /*设置最大功率，按照百分比换算，例如设置50%功率，0.5*1000 */
    conf.work_speed = 1000; /*工作速度 1000mm/min */
    conf.jog_speed = 2000;  /*空驶速度 2000mm/min */
    conf.density = 10; /*雕刻分辨率， line/mm */
    conf.offset_x = 50; /*图片中心位置 X*/
    conf.offset_y = 50; /*图片中心位置 Y*/

    line_to_line_gcode("image.bmp", "test.gcode", &conf);
    return 0;
}