#include <Preferences.h>      //----read and write RAM
#include "BluetoothSerial.h"  //----BT Recive data about setup config
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <HYPERWISOR_IOT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <esp_task_wdt.h>

BluetoothSerial SerialBT;
Preferences preferences;

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);
#define buzz 2


const int lcdColumns = 16;
const int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

String NAME = "Sensorflow DS1B20 2";

String header;
String apikey;
String userid;
String deviceid;
String ssid;
String pass;
String TEMP;
String HUMIDITY;
int restartcpount = 0;
HYPERWISOR_IOT Hyperwisorsensor;

int E_delay;
char buffer[10];

float temperatureC = 0.0;
float temperatureF = 0.0;
void setup() {
  esp_task_wdt_init(10, true);  // Set the watchdog timer to 10 seconds
  Serial.begin(115200);

  // Disable sleep modes
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_ON);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_ON);

  delay(500);
  Wire.begin();

  pinMode(buzz, OUTPUT);
  sensors.begin();
  delay(500);
  // Initialize the LCD
  lcd.begin(lcdColumns, lcdRows);
  // initialize LCD
  lcd.init();
  //delayTime = 1000;

  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Sensorflow");
  lcd.setCursor(0, 1);
  lcd.print("Temprature");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("--Powered by");
  lcd.setCursor(0, 1);
  lcd.print("NIKOLAINDUSTRY");
  delay(3000);



  Serial.println();
  // sensors.begin();
  delay(500);
  preferences.begin("my-app", false);
  delay(500);
  apikey = preferences.getString("apikey");
  userid = preferences.getString("userid");
  deviceid = preferences.getString("deviceid");
  ssid = preferences.getString("ssid");
  pass = preferences.getString("pass");
  Hyperwisorsensor.init(apikey);
  delay(500);
  WiFi.disconnect();
  delay(50);
  Serial.println("connecting...");
  WiFi.setHostname(NAME.c_str());
  WiFi.begin(ssid.c_str(), pass.c_str());
  delay(240000);
  Serial.println("connected to");
  Serial.println(ssid);
  Serial.println(pass);
  Serial.println(WiFi.localIP());
  digitalWrite(buzz, HIGH);
  delay(2000);
  digitalWrite(buzz, LOW);

  lcd.clear();
  delay(100);
}

void loop() {
  esp_task_wdt_reset();  // Reset the watchdog timer

  if ((WiFi.status() == WL_CONNECTED)) {
    Serial.println("Connected");
    showvalue();
    String mysensordata = ("&TempratureC=" + String(temperatureC) + "&TempratureF=" + String(temperatureF));
    String jsonobj = Hyperwisorsensor.sendData(mysensordata);

    String response = Hyperwisorsensor.get_schema();
    String delayvalue = Hyperwisorsensor.extractor(response, "delay");
    int delayint = delayvalue.toInt();
    Serial.println("getschema");
    Serial.println(response);
    Serial.println("send data");
    Serial.println(jsonobj);
    Serial.println("extractor delay");
    Serial.println(delayint);
    digitalWrite(buzz, LOW);


    delay(delayint);

  } else {
    showvalue();
    startBT();
    Serial.println("NOT RECIVED");
    digitalWrite(buzz, HIGH);
    delay(50);
    digitalWrite(buzz, LOW);
    delay(50);
    restartcpount++;
    if (restartcpount == 1500) {
      Serial.println("Restarted");
      ESP.restart();
    }
  }
}


void startBT() {

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
  SerialBT.begin(NAME.c_str());
  if (SerialBT.available()) {
    String btdata = SerialBT.readString();
    Serial.println(btdata);
    StaticJsonDocument<512> jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, btdata);
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }
    String datatype = jsonDoc["Datatype"];
    if (datatype == "wifiupdate") {
      String Nssid = jsonDoc["ssid"];
      String Npass = jsonDoc["pass"];
      preferences.putString("ssid", Nssid);
      preferences.putString("pass", Npass);
      Serial.println("wifiinfoupdated");
      digitalWrite(buzz, HIGH);
      delay(5000);
      digitalWrite(buzz, LOW);
      delay(10);
      ESP.restart();
    } else if (datatype == "wifiinfo") {

      Serial.println("datatype = wifiinfo");
      String apikey = jsonDoc["apikey"];
      String userid = jsonDoc["userid"];
      String deviceid = jsonDoc["deviceid"];
      String ssid = jsonDoc["ssid"];
      String pass = jsonDoc["pass"];

      if (ssid.length() > 0 && pass.length() > 0 && apikey.length() > 0) {
        preferences.putString("apikey", apikey);
        preferences.putString("userid", userid);
        preferences.putString("deviceid", deviceid);
        preferences.putString("ssid", ssid);
        preferences.putString("pass", pass);

        Serial.println(apikey);
        Serial.println(userid);
        Serial.println(ssid);
        Serial.println(pass);
        digitalWrite(buzz, HIGH);
        delay(2000);
        digitalWrite(buzz, LOW);
        delay(1000);
        digitalWrite(buzz, HIGH);
        delay(2000);
        digitalWrite(buzz, LOW);
        delay(1000);
        ESP.restart();
      }
    }
  }
}


void showvalue() {
  sensors.requestTemperatures();
  temperatureC = sensors.getTempCByIndex(0);
  temperatureF = sensors.getTempFByIndex(0);
  delay(100);

  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature ");
  lcd.setCursor(0, 1);
  lcd.print(String(temperatureC) + " C");
  lcd.setCursor(9, 1);
  lcd.print(String(temperatureF) + " F");
}
