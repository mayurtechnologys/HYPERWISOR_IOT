#include <WiFi.h>
#include <HYPERWISOR_IOT.h>
const char* ssid = "NIKOLA";              // Replace with your network SSID
const char* password = "12345678";        // Replace with your network password
const String apiKey = "K2yS60Pl4bILscC";  // get your APIKEY from www.hyperwisor.com/dashboard
HYPERWISOR_IOT httpController;
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  httpController.init(apiKey);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    delay(1000);
  }
  Serial.println("Connected to WiFi");
}
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print(payload);
    String jsonobj = httpController.get_schema();
    Serial.println("schima");
    Serial.println(jsonobj);
    delay(1000);


    String res = httpController.update_schema(String("ch1=0&ch2=255"));
    Serial.println(res);
    delay(1000);


    String extractedValue = httpController.extractor(jsonobj, "ch4");
    Serial.println(extractedValue);
    delay(1000);


    if (extractedValue == "255") {
      Serial.println("ON");
    } else {
      Serial.println("OFF");
    }


    String sensorData = "HUMIDITY=" + String(readHumidity()) + "&TEMPERATURE=" + String(readTemperature()) + "&PH=" + String(readPH()) + "&DISTANCE=" + String(readDistance());
    String response = httpController.sendData(sensorData);
    Serial.println(response);
    delay(1000);


    String senordata = httpController.getsensordata();
    Serial.println("sensordata:");
    Serial.println(senordata);
    
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
