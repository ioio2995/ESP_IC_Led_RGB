# ESP_IC_Led_RGB

This project is an implementation to control RGB LEDs with an ESP32 microcontroller using the ESP-IDF framework. The project is written in C++ and C.

## Project Structure

- **CMakeLists.txt**: CMake configuration file to compile the project.
- **LICENSE**: Project license.
- **README.md**: Project documentation.
- **ic_led_rgb.cpp**: Main file containing the implementation of functions to control the RGB LEDs.
- **led_encoder.c**: Additional C file for encoding LED data.
- **include/**: Directory containing the header files (.hpp and .h) for the project.


## Configuration

Configuration is done during the initialization of the `IC_Led_RGB` class. The GPIO number and resolution are passed as parameters during the initialization. Additionally, information about the number of LEDs and their colors is provided via an initialized array.

## Usage

This project is an ESP-IDF component and cannot be compiled on its own. It must be added to the `components` directory of your ESP-IDF project.

To use this component, follow these steps:

1. **Install dependencies**: Ensure the ESP-IDF framework is properly installed and configured.
2. **Add Component**: Copy the `ESP_IC_Led_RGB` directory to the `components` directory of your ESP-IDF project.
3. **Build**: Use `idf.py build` to compile your project.
4. **Flash**: Use `idf.py flash` to flash the firmware to your ESP32.
5. **Monitor**: Use `idf.py monitor` to monitor the serial messages sent by the ESP32.

### Using RMT Encoder

The `IC_Led_RGB` component uses the RMT (Remote Control) peripheral of the ESP32 for driving the LED strip. The RMT peripheral is well-suited for generating the precise timing pulses required by various types of LED strips.

The `rmt_encoder` is utilized to encode the LED color data into a format that can be transmitted using the RMT peripheral. This ensures that the color data is accurately sent to the LEDs, resulting in the desired color display.

### Example

Below is a simple example demonstrating how to use the `IC_Led_RGB` class within your project:

```cpp
#include "ic_led_rgb.hpp"
#include <iostream>

// Define the LED strip pixel array
static uint8_t led_strip_pixels[LED_NUMBERS * 3];

void example_usage() {
    // Initialize the IC_Led_RGB class
    IC_Led_RGB LRGB(GPIO_NUM_18, 10000000); // Example GPIO number and resolution

    // Set the color to red
    int red = 50;
    int green = 0;
    int blue = 0;
    led_strip_pixels[0] = red;
    led_strip_pixels[1] = green;
    led_strip_pixels[2] = blue;

    // Apply the color settings to the LED strip
    LRGB.set(led_strip_pixels, sizeof(led_strip_pixels));

    // Example of using the LED strip
    std::cout << "LED color set to red" << std::endl;
}
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributions

Contributions are welcome! Please submit a pull request or open an issue to discuss any changes you wish to make.

## Authors

- [Lionel ORCIL](https://github.com/ioio2995)
