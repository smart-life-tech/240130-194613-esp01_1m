#include <ESP8266WiFi.h>
// #include <HTTPClient.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
const char *ssid = "put your wifi ssid here";
const char *password = "put your wifi password here";
const int buttonPin = 2;
const char *server_name = "http://maker.ifttt.com/trigger/sendemail/with/key/EBT913u-Aj1Z-tL0Rs225";

unsigned long last_time = 0;
unsigned long timer_delay = 2000;

void setup()
{
    Serial.begin(115200);
    pinMode(buttonPin, INPUT_PULLUP);
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WIFI…");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.println("After 10 seconds the first set of readings will be displayed");

    // initialize a pseudorandom number
    randomSeed(analogRead(23));
}

void loop()
{
    // Send an HTTP POST request every 10 seconds
    if ((digitalRead(buttonPin) == LOW))
    {
        // Check WiFi connection status
        if (WiFi.status() == WL_CONNECTED)
        {
            HTTPClient http;
            WiFiClient client;
            // http.begin(server_name);
            http.begin(client, server_name);

            // Specify content-type header
            http.addHeader("Content-Type", "application/x-www-form-urlencoded");
            // Data to send with HTTP POST
            // String httpRequestData = "value1=" + String(random(50)) + "&value2=" + String(random(50)) + "&value3=" + String(random(50));
            // Send HTTP POST request
            String httpRequestData = "the button has just been pressed !";
            int httpResponseCode = http.POST(httpRequestData);

            Serial.print("HTTP Response code is: ");
            Serial.println(httpResponseCode);

            http.end();
        }
        else
        {
            Serial.println("WiFi Disconnected");
        }
        last_time = millis();
    }
}