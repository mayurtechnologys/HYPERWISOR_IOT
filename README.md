# HYPERWISOR_IOT Arduino Library

The **HYPERWISOR_IOT** library simplifies the integration of IoT capabilities into your Arduino projects, making it easier than ever to communicate with IoT platforms and send sensor data to remote servers. Whether you're working on a home automation system, industrial monitoring, or any IoT application, this library streamlines data transmission and interaction with cloud services.

www.hyperwisor.com/dashboard

## Key Features

- **HTTP Communication:** Seamlessly send and receive data using HTTP requests, enabling smooth interaction with IoT platforms and web services.
- **Sensor Data Management:** Easily read and process sensor data, allowing you to monitor various environmental parameters.
- **Device Status Retrieval:** Fetch device status information from the server for real-time monitoring and diagnostics.
- **Customizable and Expandable:** Adapt and extend the library to meet the specific requirements of your IoT project.

## Getting Started

1. Install the library in your Arduino IDE using the Library Manager or download the ZIP file from the [releases](link-to-releases) section.
2. Include the library in your sketches using `#include <HYPERWISOR_IOT.h>`.
3. Create an instance of the `HYPERWISOR_IOT` class and provide your API key.
4. Utilize the library's functions to send data, retrieve sensor readings, and manage device status.

For detailed documentation and usage examples, visit the [wiki](link-to-wiki) of this repository.

## Example Usage

```cpp
#include <WiFi.h>
#include <HYPERWISOR_IOT.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
const String apiKey = "YourAPIKey";

HYPERWISOR_IOT httpController(apiKey);

void setup() {
  // Initialize WiFi and establish connection
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Read sensor data and send to the server
    String sensorData = // Create sensor data string
    String response = httpController.sendData(sensorData);
    // Process the response
  }
}
```

## Contributing

Contributions are welcome! If you encounter any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.

## License Apache License 2.0

This project is licensed under MIT Licence.

---


