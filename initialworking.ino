#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>



char ssid[] = "Canhotspot";
char password[] = "12457800";

char host[] = "cqm83waqe0.execute-api.us-east-1.amazonaws.com"; //xxxxxxx.execute-api.us-east-1.amazonaws.com
//String URL = "/prod/call?DestinationPhoneNumber=%2B16087381977&ContactFlowId=2d213e3d-c6e3-42a3-9ca8-8faf1455ecbf&InstanceId=33de395b-9b5e-4ed2-b4d0-4b2d42fcdc1c&SourcePhoneNumber=%2B13473942645";
String URL = "/prod/blast";
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






  //    while (client.available())
  //    {
  //      char c = client.read();
  //
  //      if (finishedHeaders)
  //      {
  //        body = body + c;
  //      }
  //      else
  //      {
  //        if (currentLineIsBlank && c == '\n')
  //        {
  //          finishedHeaders = true;
  //        }
  //        else
  //        {
  //          headers = headers + c;
  //        }
  //      }
  //
  //      if (c == '\n')
  //      {
  //        currentLineIsBlank = true;
  //      }
  //      else if (c != '\r')
  //      {
  //        currentLineIsBlank = false;
  //      }
  //
  //      gotResponse = true;
  //    }
  //    if (gotResponse)
  //      return body;
  //  }

  //return body;
}

void loop() {
  //  delay(500);
  //  digitalWrite(LED_BUILTIN, LOW);
  //  delay(500);
  //  digitalWrite(LED_BUILTIN, HIGH);

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
