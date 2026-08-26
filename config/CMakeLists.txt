if(CONFIG_SHIELD_GS_CONTROL_BOX)
    zephyr_library()

    # Allow this external module to include ZMK headers such as:
    # <zmk/ble.h>, <zmk/event_manager.h>, etc.
    zephyr_library_include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../zmk/app/include
    )

    zephyr_library_sources(src/gs_leds.c)
endif()
