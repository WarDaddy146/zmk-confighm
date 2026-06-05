cmake_minimum_required(VERSION 3.20)

if(CONFIG_RAW_HID)
  zephyr_library()
  zephyr_library_sources(src/raw_hid.c)
endif()

# Add pixel demo when LVGL support is enabled
if(CONFIG_LVGL)
  target_sources(app PRIVATE src/pixel_demo.c src/lvgl_pixel.c)
endif()

# raw_hid_display.c is optional; omitted because the source file is unavailable
# if(CONFIG_RAW_HID AND CONFIG_ZMK_DISPLAY)

# endif()

if(CONFIG_RAW_HID)
  target_sources(app PRIVATE src/behavior_rawhidlog.c)
endif()
