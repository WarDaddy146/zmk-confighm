/* src/lvgl_pixel.c
 * Minimal LVGL example for CI builds.
 * It creates a canvas, clears it black and lights a single white pixel.
 */

#include <zephyr.h>
#include <logging/log.h>
#include <lvgl.h>

LOG_MODULE_REGISTER(lvgl_pixel, LOG_LEVEL_INF);

/* Dummy driver – just tells LVGL that flushing is finished. */
static void dummy_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    ARG_UNUSED(disp_drv);
    ARG_UNUSED(area);
    ARG_UNUSED(color_p);
    lv_disp_flush_ready(disp_drv);
}

static int lvgl_pixel_init(const struct device *dev)
{
    ARG_UNUSED(dev);

    lv_init();

    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t buf[LV_HOR_RES_MAX * 10];
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, LV_HOR_RES_MAX * 10);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = dummy_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.hor_res = 128;
    disp_drv.ver_res = 64;
    (void)lv_disp_drv_register(&disp_drv);

    static lv_color_t canvas_buf[128 * 64];
    lv_obj_t *canvas = lv_canvas_create(lv_scr_act());
    lv_canvas_set_buffer(canvas, canvas_buf, 128, 64, LV_IMG_CF_TRUE_COLOR);
    lv_canvas_fill_bg(canvas, lv_color_black(), LV_OPA_COVER);
    lv_canvas_set_px(canvas, 10, 10, lv_color_white());

    LOG_INF("LVGL single‑pixel demo drawn");
    return 0;
}

SYS_INIT(lvgl_pixel_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
