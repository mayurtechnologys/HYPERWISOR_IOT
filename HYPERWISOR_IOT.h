#ifndef HYPERWISOR_IOT_h
#define HYPERWISOR_IOT_h

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class HYPERWISOR_IOT
{
public:
    HYPERWISOR_IOT();
    void init(String apiKey);
    String sendData(String data);
    String getsensordata();
    String get_schema();
    String update_schema(String data);
    String extractor(String data, String key);
    String runiftdt();
    String runscheule();

private:
    bool initialized;
    String _apiKey;
    
};

#endif
