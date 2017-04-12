#include "mbed.h"
#include "kinetis_lowpower.h"

// TODO: this should be wrapped and moved into the low power config
// the interrupt pin is needed to setup the gpio for triggering an interrupt
InterruptIn wakeup(PTA4);
DigitalOut modem(PTD7);
DigitalOut rf(PTA18);

/**
 * Example how to power down the board and let it wake up using a pin (button).
 * The code will enable the LED when awake.
 *
 * 30s  - awake, then sleep until button or pin is connected to GND
 * connect pin PTA4 (the button) to GND to wake up again (simply press the button
 */
int main(void) {
    DigitalOut led(LED1);

    // print message on boot (w/ indication of wakeup)
    printf("WAKEUP TEST (%s)\r\n", isLowPowerWakeup() ? "low power wakeup" : "power on reset");

    led = 1;
    wait(30);
    led = 0;

    // disable modem and rf module
    modem = 0;
    rf = 1;

    // wakes up on PTA4 connected to GND
    powerDownWakeupOnPin();

    // the control flow will never arrive here, as the low power enable can only be
    // left by a RESET

    // if the LED blinks a lot, this didn't work
    while (1) {
        led = 1;
        wait_ms(500);
        led = 0;
        wait_ms(500);
    }
}