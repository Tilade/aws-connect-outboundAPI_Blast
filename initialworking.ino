#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>



char ssid[] = "XXXXXXX";  //CHANGE TO YOUR OWN HOTSPOT AND PASSWORD
char password[] = "XXXXXXXX";

char host[] = "YOUR-API-GATEWAY-GET-ENDPOINT"; //CHANGE TO API DEPLOYMENT ROOT PATH";
String URL = "/prod/blast";  //CHANGE TO API GATEWAY RESOURCE PATH
int val;
int loopComplete = 1;
WiFiClientSecure client;

unsigned long previousMillis = 0;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WIFI");
  Serial.println("Please wait...");
  while (WiFi.status() != WL_CONNECTED)
  {
    //;
    Serial.print(".");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(10);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");

  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

void loop() {
  
  loopComplete = 1;
  Serial.println(val);
  val = analogRead(A0);
  if (val > 800)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("CRASH DETECTED!!  Attempting to phone Emergency Resource!");
    Serial.print("A0 Value: ");
    Serial.println(val);
    while (loopComplete >= 1)
    {
      Serial.println("Trying.........");
      if (client.connect(host, 443))
      {
        Serial.println("API Connected!!");
        //Serial.println(URL);
        client.println("GET " + URL + " HTTP/1.1");
        client.print("Host: ");
        client.println(host);
        client.println("User-Agent: arduino/1.0");
        client.println("");

        while (!client.available()) {
          char c = client.read();
          delay(100);
          Serial.print(c);
        }
        Serial.println();
        delay (1000);
        loopComplete = 0;
      }
      else {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("Connection Failed!");
      }
    }
  }
}
