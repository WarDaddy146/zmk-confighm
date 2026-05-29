cmake_minimum_required(VERSION 3.20)

if(CONFIG_RAW_HID)
  zephyr_library()
  zephyr_library_sources(src/raw_hid.c)
endif()

if(CONFIG_RAW_HID AND CONFIG_ZMK_DISPLAY)
  target_sources(app PRIVATE src/raw_hid_display.c)
endif()

if(CONFIG_RAW_HID)
  target_sources(app PRIVATE src/behavior_raw_hid_log.c)
endif()
