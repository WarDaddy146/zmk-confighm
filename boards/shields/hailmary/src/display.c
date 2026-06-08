#include <lvgl.h>

uint8_t display_cbuf[128 * 32];
static lv_obj_t *display_canvas;

void display_invalidate_canvas(void)
{
    if (display_canvas)
        lv_obj_invalidate(display_canvas);
}

lv_obj_t *zmk_display_status_screen(void)
{
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_white(), LV_PART_MAIN);

    lv_obj_t *canvas = lv_canvas_create(screen);

    memset(display_cbuf, 0xFF, sizeof(display_cbuf));
    lv_canvas_set_buffer(canvas, display_cbuf, 128, 32, LV_COLOR_FORMAT_L8);
    lv_obj_set_pos(canvas, 0, 0);
    display_cbuf[0 * 128 + 0] = 0x00;
    display_cbuf[31 * 128 + 127] = 0x00;
    display_cbuf[0 * 128 + 127] = 0x00;
    display_cbuf[31 * 128 + 0] = 0x00;
    display_cbuf[15 * 128 + 63] = 0x00;
    display_canvas = canvas;
    return screen;
}
