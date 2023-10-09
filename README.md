# Smart Home Project.

This a simple smart home project to get knowledge about big projects and how to handle the difficulty in integrating more than one module or driver.

## Table Of Contents.

1. [Mapping.](#mapping)
2. [Components.](#components)
3. [Requiremets.](#requirements)
	1. [Sound System.](#sound-system)
	2. [Curtains System.](#curtains-system)
	3. [Fire Alarm System.](#fire-alarm-system)
	4. [Lighting System.](#lighting-system)
	5. [Security System.](#security-system)
	6. [General Requirements.](#general-requirements)


## Mapping.

- Curtains 			-> DC Motor + Bluetooth.
- Fire Alarm System	-> Temperature Sensor + LED.
- Sound System		-> Push Buttons + Seven Segment + LED.
- Security System		-> Keypad + LCD.
- Lighting System		-> LDR + LED.

## Components.

- Microcontroller(ATMEGA32).
- 3 Push buttons.
- 3 LEDs.
- Seven Segment.
- DC Motor.
- LCD.
- Keypad.
- Temperature Sensor.
- Bluetooth Module.
- LDR.

## Requirements.

### Sound System.

- The seven segment value should be initialized with 0.
- The maximum value of the seven segment is 9 and the minimum value is 0
- When PB1 is pressed, the seven segment value should be incremented by 1.
- When PB2 is pressed, the seven segment value should be decremented by 1.
- When PB1 is pressed (while the seven segment’s value is the maximum value) the seven segment value shouldn’t be changed and the buzzer should be turned on for 50 ms and then turned off again.
- When PB2 is pressed (while the seven segment’s value is not the minimum value) the seven segment value shouldn’t be changed and the buzzer should be turned on for 50 ms and then turned off again.

### Curtains System.

- The motor is initially stopped.
- When the Bluetooth module receives ‘F’ the motor should moves forward (Clockwise direction).
- When the Bluetooth module receives ‘B’ the motor should moves backward (Anti-clockwise direction).
- When the Bluetooth module receives ‘S’ the motor should be stopped.

### Fire Alarm System.

- When the temperature exceeds 60 Celsius Led1 should be turned on and all the other functionalities of the system should be stopped.
- When the temperature becomes less than 60 Celsius again Led1 should be turned off and the system should be resumed normally.

### Lighting System.

- The LDR value varies from 0% to 100% , When increasing light, the value increases and vice versa.
- The intensity of Led 2 depends on the value of LDR, when the value of LDR increases the intensity of Led 2 increases and vice versa.

### Security System.

- After each reset the system should require to enter the password in order to start the system.
- The password should be entered using the Keypad and the LCD should display the password entered encrypted (i.e. “****”).
- If the password is not correct the LCD should display this
message “Wrong!Try Again.” and the system shouldn’t work until the correct password is entered.

### General Requirements.

- When PB3 is pressed the whole system should reset.
- The LCD should display the current temperature and the current status of the motor if it is forward or backward or stopped.
- The LCD should display “The System is Stopped” when the system is stopped as a result of the Fire Alarm system.
- No polling should be done for checking the push buttons status.

