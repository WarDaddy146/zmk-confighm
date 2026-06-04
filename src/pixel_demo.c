#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <lvgl.h>


LOG_MODULE_REGISTER(pixel_demo);

/* Buffer for a 1‑bit 128×32 canvas: (128*32)/8 bytes */
static uint8_t canvas_buf[16384];

static int pixel_demo_init(void)
{
    /* Initialize LVGL – safe to call multiple times */
    lv_init();

    /* Get the default screen */
    lv_obj_t *scr = lv_scr_act();

    /* Create a canvas object */
    lv_obj_t *canvas = lv_canvas_create(scr);
    if (!canvas) {
        LOG_ERR("Failed to create LVGL canvas");
        return -EINVAL;
    }
    lv_canvas_set_buffer(canvas, canvas_buf, 128, 32, 0);
    lv_canvas_fill_bg(canvas, LV_COLOR_BLACK, LV_OPA_COVER);

    /* Draw a single white pixel at (10,10) */
    lv_canvas_set_px(canvas, 10, 10, LV_COLOR_WHITE);

    /* Force a refresh of the canvas */
    lv_obj_invalidate(canvas);

    LOG_INF("LVGL pixel drawn");
    return 0;
}

/* Run after the application subsystem has started */
SYS_INIT(pixel_demo_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
