#include             <ESP8266WiFi.h>
#include             <ESP8266HTTPClient.h>
#include             <WiFiClientSecure.h>
#include             <ArduinoJson.h>
#include             <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);

char                password[]            = "HIER WIFI PASSWORT EINGEBEN";
char                ssid[]                = "FRITZ!Box 7560 ML <- DURCH NAMEN DES EIGENEN NETZWERKS ERSETZEN";
int                 status;
const char fingerprint[] PROGMEM = "CF EB 29 32 EE BF 3B FD 7C 77 47 E1 D3 BD D9 9A D8 41 81 93";
const char* host = "kvg-kiel.de";
const int httpsPort = 443;

WiFiClientSecure client;

struct Data { 
    char* dir; 
    char* actualTime;
    int minutes;
    int seconds;
}; 

String get_data(String number) {
  String url = "/internetservice/services/passageInfo/stopPassages/stop?mode=departure&stop=" + number;

  client.setFingerprint(fingerprint);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
  }

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
             "Host: " + host + "\r\n" +
             "User-Agent: Firefox\r\n" +
             "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }

  return client.readString();
}

void setup() {

  lcd.begin(20,4);
  lcd.init();

  lcd.backlight();
  lcd.clear();
  lcd.print("Connecting...");
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.println(WiFi.status());
  }

}

void loop() {

  String stop1 = get_data("1079"); // HIER DIE NUMMER DER EIGENEN HALTESTELLE EINGEBEN
  String stop2 = get_data("1062"); // HIER DIE NUMMER DER EIGENEN HALTESTELLE EINGEBEN

  const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonObject& root1 = jsonBuffer.parseObject(stop1);
  JsonObject& root2 = jsonBuffer.parseObject(stop2);

  int len = root1["actual"].size();
  int len2 = root2["actual"].size();

  int actualRelativeTime1;
  int actualRelativeTime2;
  const char* dir;
  const char* actualTime;
  const char* patternText;

  int minutes;
  int seconds;

  lcd.clear();
  int j = 0;
  int k = 0;
  for (int i = 0; i < len + len2 && i < 4; i ++){
    actualRelativeTime1 = root1["actual"][j]["actualRelativeTime"];
    actualRelativeTime2 = root2["actual"][k]["actualRelativeTime"];

    if (actualRelativeTime1 < actualRelativeTime2) {
      minutes = actualRelativeTime1/60;
      seconds = actualRelativeTime1%60;
      dir = root1["actual"][j]["direction"];
      actualTime = root1["actual"][j]["actualTime"];
      patternText = root1["actual"][j]["patternText"];
      lcd.setCursor(0,i);
      lcd.print(patternText);
      lcd.setCursor(3, i);
      lcd.print(dir);
      lcd.setCursor(18,i);
      lcd.print(minutes);
      j++;
    } else {
      minutes = actualRelativeTime2/60;
      seconds = actualRelativeTime2%60;
      dir = root2["actual"][k]["direction"];
      actualTime = root2["actual"][k]["actualTime"];
      patternText = root2["actual"][k]["patternText"];
      lcd.setCursor(0,i);
      lcd.print(patternText);
      lcd.setCursor(3, i);
      lcd.print(dir);
      lcd.setCursor(18,i);
      lcd.print(minutes);
      k++;
    }
  }

}
