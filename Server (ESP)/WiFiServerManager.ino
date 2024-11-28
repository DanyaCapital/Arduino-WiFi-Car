#include <ESP8266WiFi.h>

class WiFiServerManager {
private:
    const char* _ssid;
    const char* _password;
    WiFiServer _server;

public:
    WiFiServerManager(const char* ssid, const char* password) 
        : _ssid(ssid), _password(password), _server(80) 
    {
    }

    void Begin() 
    {
        Serial.begin(115200);
        WiFi.softAP(_ssid, _password);
        _server.begin();
    }

    void HandleClient() 
    {
        WiFiClient client = _server.available();

        if (client) 
        {
            String currentLine = "";

            while (client.connected()) 
            {
                if (client.available()) 
                {
                    char c = client.read();
                    Serial.write(c);

                    if (c == '\n') 
                    {
                        break;
                    }
                }
            }
            client.stop();
        }
    }
};

WiFiServerManager wifiServer("robot", "12345678");

void setup() 
{
    wifiServer.Begin();
}

void loop() 
{
    wifiServer.HandleClient();
}
