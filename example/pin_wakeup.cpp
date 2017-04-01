#include "mbed.h"
#include "kinetis_lowpower.h"

DigitalOut led(LED1);

/**
 * Example how to power down the board and let it wake up using a pin.
 * The code will enable the LED when awake.
 *
 * 5s  - awake
 * connect pin PTC3 to GND to wake up again
 */
int main(void) {
    // print message on boot (w/ indication of wakeup)
    printf("WAKEUP TEST (%s)\r\n", isLowPowerWakeup() ? "low power wakeup" : "power on reset");

    led = 1;
    wait(5);
    led = 0;

    // wakes up on PTC3 connected to GND
    powerDownWakeupOnPin();

    // the control flow will never arrive here, as the low power enable can only be
    // left by a RESET
    
    // if the LED blinks a lot, this didn't work
    while (1) {
        led = !led;
        wait_ms(10);
    }
}