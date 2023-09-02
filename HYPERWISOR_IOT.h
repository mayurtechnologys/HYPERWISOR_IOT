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
    String get_ch_status();
    String updateCH(String CH_NAME, String CH_VALUE);
    String get_schema();
    String update_schema(String data);
    String extractor(String data,String key);
    

private:
    bool initialized;
    String _apiKey;
};

#endif
