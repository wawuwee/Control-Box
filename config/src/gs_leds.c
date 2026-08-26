#include <errno.h>
#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/init.h>

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

static int gs_led_init(void)
{
    if (!device_is_ready(strip)) {
        return -ENODEV;
    }

    /* 20% max brightness */

    /* 1-15: Purple status zone, STATIC for this test */
    fill_range(1, 15,     32,  0, 51);

    /* Fixed color zones */
    fill_range(16, 31,    51, 51, 51); /* White  */
    fill_range(32, 46,    51, 18,  0); /* Orange */
    fill_range(47, 61,    32,  0, 51); /* Purple */
    fill_range(62, 90,    51,  0,  0); /* Red    */
    fill_range(91, 124,    0,  0, 51); /* Blue   */
    fill_range(125, 161,   0, 51,  0); /* Green  */
    fill_range(162, 187,  51, 38,  0); /* Yellow */

    /* ONE LED transfer at startup only */
    return led_strip_update_rgb(strip, pixels, LED_COUNT);
}

SYS_INIT(gs_led_init, APPLICATION, 90);
