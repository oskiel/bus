#include             <ESP8266WiFi.h>
#include             <ESP8266HTTPClient.h>
#include             <WiFiClientSecure.h>
#include             <ArduinoJson.h>
#include             <LiquidCrystal_I2C.h>
#include <HttpClient.h>
#include <vector>
#include <algorithm>    // std::sort

LiquidCrystal_I2C lcd(0x3F, 20, 4);

char                password[]            = "WIFI PASSWORT"; // Hier WIFI Passwort einfügen
char                ssid[]                = "WIFI NAME"; // Hier WIFI Name einfügen, z.B. FRITZ!BOX 6340 SL
int                 status;
const char fingerprint[] PROGMEM = "CF EB 29 32 EE BF 3B FD 7C 77 47 E1 D3 BD D9 9A D8 41 81 93";
const char* host = "kvg-kiel.de";
const int httpsPort = 443;

WiFiClientSecure client;

struct Data { 
  public:
    const char* dir; 
    int actualRelativeTime;
    const char* stopName;
    const char* patternText;
    int minutes;
    int seconds;
}; 

bool sortFunction (Data i,Data j) { return (i.actualRelativeTime<j.actualRelativeTime); }

void get_data(DynamicJsonBuffer jsonBuffer,String number) {
  String url = "/internetservice/services/passageInfo/stopPassages/stop?mode=departure&stop=" + number;
  HTTPClient http;
  http.begin(host+url, fingerprint);
  http.GET();
  // Get a reference to the stream in HTTPClient
  Stream& response = http.getStream();
  // Deserialize the JSON document in the response
  deserializeJson(jsonBuffer, response);
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

  String stops[] = {"1491", "2652"}; // LISTE DER STOPS ausfuellen. 

  std::vector<Data> data;
  const size_t bufferSize = 8*JSON_ARRAY_SIZE(0) + 7*JSON_ARRAY_SIZE(2) + JSON_ARRAY_SIZE(6) + JSON_ARRAY_SIZE(14) + 6*JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(9) + 2*JSON_OBJECT_SIZE(10) + 14*JSON_OBJECT_SIZE(11) + 9177;
  DynamicJsonBuffer jsonBuffer(bufferSize);
  int numberOfDepartures = 0;
  String jsonString;
  int len;
  
  for (int i = 0; i < sizeof(stops)/sizeof(stops[0]); i++) {
    get_data(jsonBuffer,stops[i]);
    JsonObject& root = jsonBuffer.parseObject(jsonString);
    
    len = root["actual"].size();

    int actualRelativeTime;
    char* dir;
    char* actualTime;
    char* patternText;
    char* stopName;
    Serial.println(len);

    for (int i = 0; i < len; i ++){
      actualRelativeTime = root["actual"][i]["actualRelativeTime"];
      
      Data d;
      d.actualRelativeTime = actualRelativeTime;
      d.dir = root["actual"][i]["direction"];
      d.minutes = actualRelativeTime/60;
      d.stopName = root["stopName"];
      d.patternText = root["actual"][i]["patternText"];

      bool insert = true;

      for(int j = 0; j < numberOfDepartures; j++) {
        if (*d.patternText == *data[j].patternText && *d.stopName != *data[j].stopName) {
          Serial.println("No insert");
          insert = false;
        }
      }

      if (insert) {
         numberOfDepartures++;
         data.push_back(d);
      }
    }

    delay(1000);
  }

  std::sort (data.begin(), data.end(), sortFunction);

  lcd.clear();

  for (int i = 0; i < numberOfDepartures && i < 4; i++) {
    lcd.setCursor(0,i);
    lcd.print(data[i].patternText);
    lcd.setCursor(3, i);
    lcd.print(data[i].dir);
    lcd.setCursor(18,i);
    lcd.print(data[i].minutes);
  }

  delay(5000);

  if (numberOfDepartures > 4) {
    lcd.clear();
    for (int i = 4; i < numberOfDepartures && i < 8; i++) {
      lcd.setCursor(0,i - 4);
      lcd.print(data[i].patternText);
      lcd.setCursor(3, i - 4);
      lcd.print(data[i].dir);
      lcd.setCursor(18,i - 4);
      lcd.print(data[i].minutes);
    }

    delay(5000);
    lcd.clear();
  
    for (int i = 0; i < numberOfDepartures && i < 4; i++) {
      lcd.setCursor(0,i);
      lcd.print(data[i].patternText);
      lcd.setCursor(3, i);
      lcd.print(data[i].dir);
      lcd.setCursor(18,i);
      lcd.print(data[i].minutes);
    }
  }
}
