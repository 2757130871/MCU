/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/
#include <DFRobot_DHT11.h> // 温度库
#include <ESP8266WiFi.h>

#include <ArduinoJson.h>

#define DHT11_PIN 16
DFRobot_DHT11 DHT; // 定义温湿度
float temperature,humidity;


#ifndef STASSID
#define STASSID "overflow"
#define STAPSK "aaaaaaaa"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "www.chenxinrong.xyz";
const uint16_t port = 8080;


void DHT11()
{
  DHT.read(DHT11_PIN);
  temperature = DHT.temperature;
  humidity = DHT.humidity;

}

void setup() {

//  pinMode(16);

  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
//   DHT11();
   
  static bool wait = false;

  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  // This will send a string to the server
  Serial.println("sending data to server");
  while(client.connected())
  {
     DHT11();
    String payloadJson = "{\"temperature\": ";
    payloadJson += "\"";
    payloadJson += String(temperature);  
    payloadJson += "\",";

    payloadJson += "\"humidity: \"";
    payloadJson += String(humidity);
    payloadJson += "\"}";
    
    
//
   client.print(payloadJson);

  //Read
  RecvJson(client);
  
//    client.write("tempe: ");
//    client.print(temperature);
//    client.write("\n");
//  
//    client.write("humidity: ");
//    client.print(humidity);
//    client.write("\n");
//  
//    String line = client.readStringUntil('\n');
//    Serial.print("recv data from server: ");
//    Serial.println(line);

   
    delay(1000);
  }
 
}



// 重点3：解析请求体中的json信息
void RecvJson(WiFiClient client){
  bool d3_bool;          // 建立变量存储客户端开发板按键信息
  String info_name_str;  // 建立变量存储字符串信息
  int analog_pin_a0_int; // 建立变量存储客户端开发板模拟输入引脚读数
  
  const size_t capacity = JSON_OBJECT_SIZE(1) + 3*JSON_OBJECT_SIZE(3) + 140;
  DynamicJsonDocument doc(capacity);
  
  deserializeJson(doc, client);
  
    JsonObject info = doc["info"];
  
   //String str = info["test"].as<String>();
   
    const char* str = info["test"];
    Serial.print("receive: ");
      Serial.println(String(str));
//    const char* info_email = info["email"];
//    info_name_str =  info["name"].as<String>();
//    Serial.print("info_name_str = ");Serial.println(info_name_str);
//    

  
//  JsonObject digital_pin = doc["digital_pin"];
//  if (digital_pin){
//    Serial.println("Server Json has digital_pin: true");
//    const char* digital_pin_d1 = digital_pin["d1"]; 
//    const char* digital_pin_d2 = digital_pin["d2"]; 
//    const char* digital_pin_d3 = digital_pin["d3"];
//    d3_bool = digital_pin["d3"].as<int>();
//    Serial.print("d3_bool = ");Serial.println(d3_bool);
//  } else {
//    Serial.println("Server Json has digital_pin: false");
//  }
//
//  const char* analog_pin_a0 = doc["analog_pin"]["a0"]; 
//  if (analog_pin_a0){
//    Serial.println("Server Json has analog_pin_a0: true");
//    analog_pin_a0_int = doc["analog_pin"]["a0"].as<int>(); 
//    Serial.print("analog_pin_a0 = ");Serial.println(analog_pin_a0);
//  } else {
//    Serial.println("Server Json has analog_pin_a0: false");
//  }
//   
//  // 利用d3引脚读数控制板上LED点亮和熄灭
//  d3_bool == 0 ? digitalWrite(LED_BUILTIN, LOW) : digitalWrite(LED_BUILTIN, HIGH);  
}
