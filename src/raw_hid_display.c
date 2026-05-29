#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <lvgl.h>
#include <zmk/display.h>
#include <zmk/display/status_screen.h>

LOG_MODULE_REGISTER(raw_hid_display, CONFIG_ZMK_LOG_LEVEL);

#define MAX_LINE_LEN 63

static lv_obj_t *line_label[2];

struct display_data {
    uint8_t cmd;
    char line0[MAX_LINE_LEN + 1];
    char line1[MAX_LINE_LEN + 1];
};

static struct display_data data;
static struct k_mutex data_mutex;

static void display_work_handler(struct k_work *work);

K_WORK_DEFINE(display_work, display_work_handler);

static void display_work_handler(struct k_work *work)
{
    k_mutex_lock(&data_mutex, K_FOREVER);

    switch (data.cmd) {
    case 0x01:
        lv_label_set_text(line_label[0], data.line0);
        break;
    case 0x02:
        lv_label_set_text(line_label[1], data.line1);
        break;
    case 0x10:
        lv_label_set_text(line_label[0], "");
        lv_label_set_text(line_label[1], "");
        break;
    }

    data.cmd = 0;
    k_mutex_unlock(&data_mutex);
}

lv_obj_t *zmk_display_status_screen(void)
{
    lv_obj_t *screen = lv_obj_create(NULL);

    for (int i = 0; i < 2; i++) {
        line_label[i] = lv_label_create(screen);
        lv_label_set_text(line_label[i], "");
        lv_obj_set_style_text_align(line_label[i], LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align(line_label[i], i == 0 ? LV_ALIGN_TOP_MID : LV_ALIGN_BOTTOM_MID, 0, 0);
    }

    return screen;
}

void raw_hid_display_process(const uint8_t *buf, uint32_t len)
{
    if (!zmk_display_is_initialized() || len < 1) {
        return;
    }

    k_mutex_lock(&data_mutex, K_FOREVER);

    data.cmd = buf[0];
    uint32_t copy_len = len - 1;

    if (data.cmd == 0x01 || data.cmd == 0x02) {
        char *target = (data.cmd == 0x01) ? data.line0 : data.line1;
        if (copy_len > MAX_LINE_LEN) {
            copy_len = MAX_LINE_LEN;
        }
        memcpy(target, buf + 1, copy_len);
        target[copy_len] = '\0';
    }

    k_mutex_unlock(&data_mutex);
    k_work_submit_to_queue(zmk_display_work_q(), &display_work);
}
