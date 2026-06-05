#include <lvgl.h>

static uint8_t canvas_buf[16384];

lv_obj_t *zmk_display_status_screen(void)
{
    lv_obj_t *screen = lv_obj_create(NULL);

    lv_obj_t *canvas = lv_canvas_create(screen);
    lv_canvas_set_buffer(canvas, canvas_buf, 128, 32, LV_IMG_CF_TRUE_COLOR);
    lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_COVER);
    lv_canvas_set_px(canvas, 0, 0, lv_color_black(), LV_OPA_COVER);

    return screen;
}
