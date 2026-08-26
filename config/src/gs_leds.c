#include <errno.h>
#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>

#include <zmk/ble.h>
#include <zmk/event_manager.h>
#include <zmk/events/ble_active_profile_changed.h>

#define LED_COUNT 187

static const struct device *strip =
    DEVICE_DT_GET(DT_CHOSEN(zmk_underglow));

static struct led_rgb pixels[LED_COUNT];

static void fill_range(int first, int last,
                       uint8_t r, uint8_t g, uint8_t b)
{
    for (int led = first; led <= last; led++) {
        pixels[led - 1].r = r;
        pixels[led - 1].g = g;
        pixels[led - 1].b = b;
    }
}

static void set_fixed_zones(void)
{
    fill_range(16, 31,    51, 51, 51);
    fill_range(32, 46,    51, 18,  0);
    fill_range(47, 61,    32,  0, 51);
    fill_range(62, 90,    51,  0,  0);
    fill_range(91, 124,    0,  0, 51);
    fill_range(125, 161,   0, 51,  0);
    fill_range(162, 187,  51, 38,  0);
}

static void update_status_leds(void)
{
    if (zmk_ble_active_profile_is_connected()) {
        fill_range(1, 15, 0, 32, 51);
    } else {
        fill_range(1, 15, 32, 0, 51);
    }

    (void)led_strip_update_rgb(strip, pixels, LED_COUNT);
}

static int gs_led_init(void)
{
    if (!device_is_ready(strip)) {
        return -ENODEV;
    }

    set_fixed_zones();
    update_status_leds();
    return 0;
}

SYS_INIT(gs_led_init, APPLICATION, 90);

static int gs_ble_led_listener(const zmk_event_t *eh)
{
    ARG_UNUSED(eh);
    update_status_leds();
    return 0;
}

ZMK_LISTENER(gs_ble_led_listener, gs_ble_led_listener);
ZMK_SUBSCRIPTION(gs_ble_led_listener, zmk_ble_active_profile_changed);
