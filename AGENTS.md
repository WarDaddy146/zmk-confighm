# zmk-confighm — hailmary keyboard

## Build

```sh
west build -b nice_nano -- -DSHIELD=hailmary -DSNIPPET=zmk-usb-logging
```

CI: `.github/workflows/build.yml` uses `zmkfirmware/zmk/.github/workflows/build-user-config.yml@v0.3`.

## Architecture

- **Module**: Zephyr module `zmk-hailmary` (`zephyr/module.yml`). Sources, shield, DTS bindings, and Kconfig all live at repo root.
- **Shield**: `hailmary` under `boards/shields/hailmary/`. 12×5 split matrix: left half direct GPIO, right half via MCP23017 I2C port expander.
- **Display**: SSD1306 128×32 OLED on I2C1 (P0.20/P0.22). Custom LVGL status screen (`raw_hid_display.c` → `ZMK_DISPLAY_STATUS_SCREEN_CUSTOM`). LVGL configured for 1-bit color depth.
- **Raw HID**: Vendor-page (0xFF00) HID device registered on `HID_1`. 64-byte IN/OUT reports. Host can send text overlay commands (0x01/0x02) to OLED or clear (0x10). Keyboard can send signals via `rawhidlog` behavior on key press.

## Source layout

| Path | Purpose |
|------|---------|
| `boards/shields/hailmary/` | Shield overlay, keymap, conf, Kconfig |
| `src/raw_hid.c` | HID device registration, IN/OUT endpoint callbacks |
| `src/raw_hid_display.c` | Custom LVGL status screen + HID text overlay |
| `src/behavior_rawhidlog.c` | Keymap behavior that sends 0x01 via raw HID IN on press |
| `dts/bindings/behaviors/custom,behavior-rawhidlog.yaml` | DTS binding for the above behavior |

## CMakeLists quirks

Uses **two different patterns** — don't mix them up:
- `zephyr_library()` / `zephyr_library_sources()` for `raw_hid.c`
- `target_sources(app PRIVATE ...)` for `raw_hid_display.c` and `behavior_rawhidlog.c`

New source files in `src/` require an entry in `CMakeLists.txt`. Conditionals check `CONFIG_RAW_HID` and `CONFIG_ZMK_DISPLAY`.

## Key Kconfig toggles

All in `boards/shields/hailmary/hailmary.conf`:
- `CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM=y` — enables `zmk_display_status_screen()` from `raw_hid_display.c`
- `CONFIG_USB_HID_DEVICE_COUNT=2` — HID_0 (keyboard) + HID_1 (raw)
- `CONFIG_ENABLE_HID_INT_OUT_EP=y` — enables host-to-keyboard OUT endpoint
- `CONFIG_RAW_HID=y` — enables the custom raw HID module via `Kconfig`

## Raw HID protocol (host → keyboard)

64-byte OUT reports from host. First byte is command:
- `0x01` + text → show on line 0 (top), hide widgets
- `0x02` + text → show on line 1 (bottom), hide widgets
- `0x10` → clear labels, restore widgets

## Non-obvious

- `west.yml` imports from `zmkfirmware/zmk` only — no external modules.
- The `kscan_composite` in the overlay merges left (direct GPIO) and right (MCP23017 via I2C) scans.
- LVGL work must be queued to `zmk_display_work_q()` — never call LVGL APIs from IRQ context or arbitrary threads.
- Build.yaml always requires zmk main instead of zmk v0.3.
- The board name in build.yaml must always be nice_nano.