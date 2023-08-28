#include <WiFi.h>
#include <HYPERWISOR_IOT.h>

const char* ssid = "NIKOLA";        // Replace with your network SSID
const char* password = "12345678";  // Replace with your network password

const String apiKey = "39oUmvyoyegY4qg";
HYPERWISOR_IOT httpController(apiKey);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Check if connected to Wi-Fi before sending data
  if (WiFi.status() == WL_CONNECTED) {
    // Read sensor data and prepare a string with data
    String sensorData = "HUMIDITY=" + String(readHumidity()) + "&TEMPERATURE=" + String(readTemperature()) + "&PH=" + String(readPH()) + "&DISTANCE=" + String(readDistance());

    // Call the library to send data
    String response = httpController.sendData(sensorData);
    Serial.println(response);
    delay(1000); 

    String senordata = httpController.getsensordata();
    Serial.println("sensordata:");
    Serial.println(senordata);
    delay(1000); 

    String chstatus = httpController.get_ch_status();
    Serial.println("ch_status:");
    Serial.println(chstatus);
    delay(1000); 

    String updateresponse = httpController.updateCH("ch1", "150");
    Serial.println("updateresponse:");
    Serial.println(updateresponse);

    delay(2000);  // Adjust delay as needed
  } else {
    Serial.println("Not connected to WiFi");
  }
}

float readHumidity() {
  float Humidity = 49.00;
  return Humidity;
}

float readTemperature() {
  float Temperature = 28.5;
  return Temperature;
}

float readPH() {
  // Your pH reading code
  float pHValue = 12.1;
  return pHValue;
}

float readDistance() {
  float Distance = 9.0;
  return Distance;
}
