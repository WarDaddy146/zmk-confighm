#include <lvgl.h>

lv_obj_t *zmk_display_status_screen(void)
{
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_white(), LV_PART_MAIN);

    lv_obj_t *canvas = lv_canvas_create(screen);
    static uint8_t cbuf[16];
    lv_canvas_set_buffer(canvas, cbuf, 1, 1, LV_COLOR_FORMAT_L8);
    lv_obj_set_pos(canvas, 0, 0);
    lv_canvas_set_px(canvas, 0, 0, lv_color_black(), LV_OPA_COVER);

    return screen;
}
