#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <lvgl.h>

LOG_MODULE_REGISTER(lvgl_pixel, LOG_LEVEL_INF);

static int lvgl_pixel_init(const struct device *dev)
{
    ARG_UNUSED(dev);

    lv_obj_t *canvas = lv_canvas_create(lv_scr_act());

    static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(128, 32)];
    lv_canvas_set_buffer(canvas, cbuf, 128, 32, LV_IMG_CF_TRUE_COLOR);

    lv_canvas_fill_bg(canvas, lv_color_black(), LV_OPA_COVER);
    lv_canvas_set_px(canvas, 10, 10, lv_color_white(), LV_OPA_COVER);

    LOG_INF("LVGL pixel drawn on OLED");
    return 0;
}

SYS_INIT(lvgl_pixel_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
