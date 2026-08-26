# GS Control Box — ZMK Stage 1

This package is intentionally **keyboard-only first**.

It moves the controller from CircuitPython to ZMK/Zephyr and preserves the
8×5 matrix and GSPro key map already proven electrically.

## Why the LEDs are not enabled in Stage 1

ZMK can drive WS2812 LEDs through the nRF52840's hardware SPI peripheral,
which is the correct way to avoid the BLE timing problem seen in CircuitPython.
However, ZMK's built-in RGB underglow feature treats the strip as one global
lighting effect/color. Your product needs simultaneous fixed zones:
white, orange, purple, red, blue, green, and yellow.

That zone pattern needs a small custom ZMK/Zephyr LED module. We should first
prove BLE + matrix + shortcuts under ZMK, then add that module.

## Build with GitHub Actions

1. Create a new empty GitHub repository.
2. Upload the entire contents of this folder, preserving folders.
3. Commit/push.
4. Open the repository's **Actions** tab.
5. Run or wait for the `build` workflow.
6. Download the firmware artifact.
7. It should contain:
   - `gs_control_box` UF2 firmware
   - `settings_reset` UF2 firmware

## First flash

Because this board has been running CircuitPython and has previous BLE bonds:

1. Put the nice!nano in bootloader mode.
2. Flash the `settings_reset` UF2 first.
3. Let it reboot.
4. Return to bootloader mode.
5. Flash the `gs_control_box` UF2.
6. On your Mac/GSPro PC, pair with **GS Control Box**.

## Hardware pin map

Rows:
- 031 / P0.31
- 029 / P0.29
- 002 / P0.02
- 115 / P1.15
- 113 / P1.13
- 111 / P1.11
- 010 / P0.10
- 009 / P0.09

Columns:
- 017 / P0.17
- 020 / P0.20
- 022 / P0.22
- 024 / P0.24
- 100 / P1.00

LED data remains physically wired to:
- 011 / P0.11

Stage 1 simply does not drive that LED pin yet.

## Important

Matrix has no diodes. This configuration assumes one button at a time,
matching the intended golf-simulator control-box use case.
