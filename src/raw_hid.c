#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(raw_hid, CONFIG_RAW_HID_LOG_LEVEL);

static int raw_hid_init(void)
{
  LOG_INF("Raw HID module initialized");
  return 0;
}

SYS_INIT(raw_hid_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
