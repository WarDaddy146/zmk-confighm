cmake_minimum_required(VERSION 3.20)

zephyr_library()

if(CONFIG_RAW_HID)
  zephyr_library_sources(src/raw_hid.c)
endif()

if(CONFIG_RAW_HID AND CONFIG_ZMK_DISPLAY)
  target_sources(app PRIVATE src/raw_hid_display.c)
endif()

zephyr_library_sources_ifdef(CONFIG_RAW_HID src/behavior_raw_hid_log.c)
