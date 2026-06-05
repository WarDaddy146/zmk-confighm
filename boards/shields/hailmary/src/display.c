#include <lvgl.h>

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32

static uint8_t canvas_buf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(DISPLAY_WIDTH, DISPLAY_HEIGHT)];

lv_obj_t *zmk_display_status_screen(void)
{
    lv_obj_t *screen = lv_obj_create(NULL);

    lv_obj_t *canvas = lv_canvas_create(screen);
    lv_canvas_set_buffer(canvas, canvas_buf, DISPLAY_WIDTH, DISPLAY_HEIGHT, LV_IMG_CF_TRUE_COLOR);
    lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_COVER);
    lv_canvas_set_px(canvas, 0, 0, lv_color_black(), LV_OPA_COVER);

    return screen;
}
