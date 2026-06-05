#include <lvgl.h>

lv_obj_t *zmk_display_status_screen(void)
{
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_white(), LV_PART_MAIN);

    lv_obj_t *canvas = lv_canvas_create(screen);
    static uint8_t cbuf[128 * 32];

    memset(cbuf, 0x00, sizeof(cbuf));
    lv_canvas_set_buffer(canvas, cbuf, 128, 32, LV_COLOR_FORMAT_L8);
    lv_obj_set_pos(canvas, 0, 0);
    cbuf[0 * 128 + 0]   = 0xFF;

    return screen;
}
