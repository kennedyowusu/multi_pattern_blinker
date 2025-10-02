# Multi-Pattern LED Blinker

A professional ESP32 project demonstrating component-based architecture with a reusable LED controller.

## Overview

This project implements a multi-pattern LED blinker using ESP-IDF and FreeRTOS. The LED controller is built as a reusable component that can be integrated into other projects.

## Features

- **Component-based architecture**: Reusable LED controller module
- **Multiple patterns**: OFF, ON, BLINK_SLOW, BLINK_FAST, PULSE, SOS (Morse code)
- **FreeRTOS task**: Background task handles pattern timing
- **Clean API**: Simple configuration and control interface
- **Configurable**: GPIO pin and polarity can be set at initialization

## Hardware Requirements

- ESP32 development board
- Built-in LED (typically on GPIO 2) or external LED with current-limiting resistor

## Project Structure

multi_pattern_blinker/
├── components/
│   └── led_controller/          # Reusable LED component
│       ├── include/
│       │   └── led_controller.h # Public API
│       ├── led_controller.c     # Implementation
│       └── CMakeLists.txt
├── main/
│   ├── main.c                   # Application entry point
│   └── CMakeLists.txt
├── CMakeLists.txt               # Root build configuration
└── README.md                    # This file

## Component API

### Configuration

```c
typedef struct {
    gpio_num_t gpio_num;    // GPIO pin number
    bool active_high;       // true = LED on when GPIO high
} led_config_t;
Available Patterns
ctypedef enum {
    LED_PATTERN_OFF,         // LED always off
    LED_PATTERN_ON,          // LED always on
    LED_PATTERN_BLINK_SLOW,  // 1 Hz (500ms on/off)
    LED_PATTERN_BLINK_FAST,  // 4 Hz (125ms on/off)
    LED_PATTERN_PULSE,       // Breathing effect
    LED_PATTERN_SOS          // Morse code SOS (···---···)
} led_pattern_t;
Functions
c// Initialize LED controller
esp_err_t led_init(const led_config_t *config);

// Set active pattern
esp_err_t led_set_pattern(led_pattern_t pattern);

// Get current pattern
led_pattern_t led_get_pattern(void);

// Cleanup and deinitialize
void led_deinit(void);
Building and Flashing
Prerequisites

ESP-IDF v5.5.1 or later
ESP32 toolchain installed
USB driver for ESP32 (CP210x or CH340)

Build Commands
bash# Set up ESP-IDF environment (run in each new terminal)
. ~/esp/esp-idf/export.sh

# Configure project (optional - defaults are usually fine)
idf.py menuconfig

# Build the project
idf.py build

# Flash to ESP32
idf.py -p /dev/tty.SLAB_USBtoUART flash

# Monitor serial output
idf.py -p /dev/tty.SLAB_USBtoUART monitor

# Or do all at once
idf.py -p /dev/tty.SLAB_USBtoUART flash monitor
VSCode
With ESP-IDF extension installed:

Select port: Command Palette → "ESP-IDF: Select Port to Use"
Build: Click flame icon in status bar
Flash: Click arrow icon in status bar
Monitor: Click monitor icon in status bar

Usage Example
c#include "led_controller.h"

void app_main(void) {
    // Configure LED
    led_config_t config = {
        .gpio_num = GPIO_NUM_2,
        .active_high = true
    };

    // Initialize
    led_init(&config);

    // Set pattern
    led_set_pattern(LED_PATTERN_BLINK_FAST);

    // Pattern runs automatically in background
}
How It Works

Initialization: Configures GPIO and creates FreeRTOS task
Background Task: Continuously executes the selected pattern
Pattern Changes: Application sets pattern, task switches behavior
Non-blocking: Main application continues while LED blinks

Reusing the Component
To use led_controller in another project:

Copy the components/led_controller/ folder to your new project
Add REQUIRES led_controller to your main CMakeLists.txt
Include the header: #include "led_controller.h"

Learning Objectives
This project demonstrates:

ESP-IDF component architecture
FreeRTOS task creation and management
GPIO control and configuration
Clean API design with configuration structs
Error handling with esp_err_t
Proper resource initialization and cleanup
Separation of concerns (component vs application)

Future Enhancements

 PWM for true brightness control (pulse pattern)
 Add custom pattern via callback
 Multiple LED support
 Configuration via menuconfig
 Power consumption optimization (light sleep between blinks)

License
Public Domain / CC0
Author
Created as part of ESP32/IoT learning journey.

This documentation covers:
- What the project does
- How to build and use it
- API reference
- Architecture explanation
- Reusability instructions
