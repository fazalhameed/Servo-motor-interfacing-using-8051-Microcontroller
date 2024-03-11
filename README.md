# Servo-motor-interfacing-using-8051-Microcontroller

## OverView:

This project focuses on precise servo motor control using the STC89C52 microcontroller. The implementation leverages timer interrupts to generate a PWM signal, ensuring accurate and smooth movement of the servo motor.

## Key Features:

1. **Timing Accuracy:**
   - Address the timing accuracy problem by utilizing a timer interrupt for PWM signal generation.
   - Configure the timer interrupt to operate significantly faster than 20 ms for enhanced resolution.

2. **Resolution and Pulse Range:**
   - Achieve a resolution of 1 degree for precise control.
   - Define a pulse range of 2000 us for servo movement from 0 to 180 degrees.

3. **User Interaction:**
   - Introduce a variable, `servo_position` (range: 0-180), initialized to zero.
   - Control `servo_position` using keys K1 (decrease angle) and K2 (increase angle).

4. **PWM Signal Generation:**
   - Generate a PWM signal on a GPIO pin based on the user-set `servo_position`.
   - Calculate the required number of timer ticks for GPIO pin high and low to meet the 20 ms (50 Hz) PWM frequency.

5. **Verification and Display:**
   - Utilize a logic analyzer or oscilloscope to validate the generated PWM signal.
   - Display `servo_position` on a seven-segment display or LCD.

## Example Scenario:

Suppose the timer interrupt is configured for 11.11 us, and the user sets `servo_position` to 45 degrees:
   - Number of timer ticks to toggle the pin: 45 (1 tick per degree).
   - Display the servo position on the seven-segment display or LCD.

## Servo Motor Connection:

Ensure proper connection between the generated PWM signal and the servo motor:
   - Supply the PWM signal to the servo motor.
   - Connect the ground of the servo motor to the ground of the STC board.

## Demonstration:

Run the code to showcase servo motor rotation from 0 to 180 degrees using keys K1 and K2. Validate the PWM signal using external tools for precision.

Feel free to customize the code and hardware settings based on your requirements. Contributions are welcome under the [MIT License](LICENSE). Happy servo motor controlling!
