#include "HYPERWISOR_IOT.h"
#include <ArduinoJson.h>

HYPERWISOR_IOT::HYPERWISOR_IOT()
{
    initialized = false;
}

void HYPERWISOR_IOT::init(String apiKey)
{
    _apiKey = apiKey;
    initialized = true;
}

String HYPERWISOR_IOT::sendData(String data)
{
    String startapi = "https://nikolaindustry.wixsite.com/hyperwisor/_functions/updstesensordata?apikey=" + _apiKey + "&" + data;

    HTTPClient http;
    http.begin(startapi);
    int httpPOSTCode = http.POST(startapi);
    String payload = http.getString();

    http.end();
    return payload;
}

String HYPERWISOR_IOT::getsensordata()
{
    String getlink = "https://nikolaindustry.wixsite.com/hyperwisor/_functions/readsensordata?apikey=" + _apiKey;
    HTTPClient http;

    delay(100);
    http.begin(getlink);
    int httpCode = http.GET();

    String response;

    if (httpCode > 0)
    {
        response = http.getString();
    }

    http.end();

    return response;
}


String HYPERWISOR_IOT::update_schema(String data)
{
    String schemaapi = "https://nikolaindustry.wixsite.com/hyperwisor/_functions/updateschema?apikey=" + _apiKey + "&" + data;
    HTTPClient http;
    delay(100);
    http.begin(schemaapi);
    int httpCode = http.GET();

    String response;

    if (httpCode > 0)
    {
        response = http.getString();
    }

    http.end();

    return response;
}

String HYPERWISOR_IOT::get_schema()
{
    String getlink = "https://nikolaindustry.wixsite.com/hyperwisor/_functions/getschema?apikey=" + _apiKey;
    HTTPClient http;

    delay(100);
    http.begin(getlink);
    int httpCode = http.GET();

    String response;

    if (httpCode > 0)
    {
        response = http.getString();
    }

    http.end();

    return response;
}

String HYPERWISOR_IOT::extractor(String data, String key)
{

    char json[1512];
    String payload = data;
    // Serial.println(payload);
    int leng = payload.length();
    String newpayload = payload.substring(1, leng - 1);

    newpayload.replace(" ", "");
    newpayload.replace("\n", "");
    newpayload.trim();
    newpayload.remove(0, 10);
    newpayload.toCharArray(json, 1512);
    // Serial.println(newpayload);
    StaticJsonDocument<1512> jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, newpayload);

    if (error)
    {

        Serial.print("deserializeJson() failed: ");
        String errorr = error.c_str();
        // // Serial.println(error.c_str());
        // // return errorr;
    }
    String value = jsonDoc[key];
    if (value == "null")
    {
        String errorspace = "0";
        return errorspace;
    }
    else
    {
        return value;
    }
}
