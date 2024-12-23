#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

// SENSOR_PINS for Optoelectronics in Car Head
#define SENSOR_1_PIN A1 // Sensor 1 connected to analog pin A1
#define SENSOR_2_PIN A2 // Sensor 2 connected to analog pin A2
#define SENSOR_3_PIN A3 // Sensor 3 connected to analog pin A3

// MOTOR_PIN_LEFT - Left Motor Control Pins
#define MOTOR_LEFT_EN 2    // Left motor enable pin
#define MOTOR_LEFT_A_PIN 5 // Left motor direction A (PWM supported)
#define MOTOR_LEFT_D_PIN 6 // Left motor direction D (PWM supported)

// MOTOR_PIN_RIGHT - Right Motor Control Pins
#define MOTOR_RIGHT_EN 3     // Right motor enable pin
#define MOTOR_RIGHT_D_PIN 9  // Right motor direction D (PWM supported)
#define MOTOR_RIGHT_A_PIN 10 // Right motor direction A (PWM supported)

// PS2X_remote_player_controller - PS2 Controller Pin Definitions
#define PS2_DAT 12 // Data pin of the PS2 controller
#define PS2_CMD 11 // Command pin of the PS2 controller
#define PS2_SEL 7  // Select pin of the PS2 controller
#define PS2_CLK 13 // Clock pin of the PS2 controller

#endif
