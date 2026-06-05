cmake_minimum_required(VERSION 3.20)

if(CONFIG_RAW_HID)
  zephyr_library()
  zephyr_library_sources(src/raw_hid.c)

  target_sources(app PRIVATE src/behavior_rawhidlog.c)
endif()
