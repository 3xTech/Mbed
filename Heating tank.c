#include "mbed.h"

#define SPEAKER p21
#define AIN1 p15
#define AIN2 p16
#define RLED p17

// Define the PWM speaker output
PwmOut speaker(SPEAKER);

// Define analog inputs
AnalogIn temp(AIN1);
AnalogIn level(AIN2);
DigitalOut rLED(RLED);

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main() {
    // Define variables
    float temp1;
    float level2;

    while (1) {
        // Read sensor values
        temp1 = temp.read(); // Normalized value (0.0 to 1.0)
        level2 = level.read(); // Normalized value (0.0 to 1.0)

        // Check conditions and generate appropriate tones
        if (level2 >= 0.75) { // Tank is full (three-quarters or more)
            if (temp1 > 0.66) { // Upper third of temperature range
                // Two-tone
                speaker.period(1.0 / 1000); // 1000 Hz
                speaker = 0.5; // 50% duty cycle
                wait_ms(250);
                speaker.period(1.0 / 1500); // 1500 Hz
                speaker = 0.5; // 50% duty cycle
                wait_ms(250);
            } else if (temp1 > 0.33 && temp1 <= 0.66) { // Middle third of temperature range
                // Steady continuous tone
                speaker.period(1.0 / 1000); // 1000 Hz
                speaker = 0.5; // 50% duty cycle
            } else if (temp1 <= 0.33) { // Lower third of temperature range
                // Single beeping tone
                speaker.period(1.0 / 1000); // 1000 Hz
                speaker = 0.5; // 50% duty cycle
                wait_ms(500); // Beep duration
                speaker = 0.0; // Turn off sound
                wait_ms(500); // Silence duration
            }
            rLED = 0; // Turn off LED (not needed in this state)
        } else { // Tank level is too low (less than three-quarters full)
            // Frequency-modulated "warble" tone
            for (float freq = 500; freq <= 1500; freq += 10) {
                speaker.period(1.0 / freq); // Set period for current frequency
                speaker = 0.5; // 50% duty cycle
                wait_ms(10); // Modulation speed
            }
            for (float freq = 1500; freq >= 500; freq -= 10) {
                speaker.period(1.0 / freq); // Set period for current frequency
                speaker = 0.5; // 50% duty cycle
                wait_ms(10); // Modulation speed
            }
            // Flash LED
            rLED = !rLED; // Toggle LED
            wait_ms(250); // Flash speed
        }

        wait_ms(100); // Small delay to avoid excessive CPU usage
    }
}