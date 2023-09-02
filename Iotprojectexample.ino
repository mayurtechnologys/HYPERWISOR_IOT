#include <WiFi.h>
#include <HYPERWISOR_IOT.h>

const char* ssid = "NIKOLA";        // Replace with your network SSID
const char* password = "12345678";  // Replace with your network password

const String apiKey = "8OGUIrwDojujJye";  // get your APIKEY from www.hyperwisor.com/dashboard
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



  // Check if connected to Wi-Fi before sending data
  if (WiFi.status() == WL_CONNECTED) {

    String jsonobj = httpController.get_schema();
    Serial.println("schima");
    //  Serial.println(chstatus);
    delay(1000);

    String extractedValue = httpController.extractor(jsonobj, "Angle");
    Serial.println(extractedValue);
    delay(1000);




    String sensorData = "HUMIDITY=" + String(readHumidity()) + "&TEMPERATURE=" + String(readTemperature()) + "&PH=" + String(readPH()) + "&DISTANCE=" + String(readDistance());
    String response = httpController.get_schema();
    Serial.println(response);
    delay(1000);
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
