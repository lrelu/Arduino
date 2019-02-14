#include <MFRC522.h >     //RFID
#include <TM1638.h >      //LED
#include "DHT.h"           //온습도 센서
#include <ESP8266WiFi.h >     //WIFI
#include <PubSubClient.h >  //MQTT
#include <stdio.h>     // sprintf 함수가 선언된 헤더 파일

//-----------LED----------------
#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int _temperature;
int _humidity;
int _pre_t;               // 온도가 변했을 경우에만 MQTT, Serial에 출력하기 위해 생성
int _pre_h;               // 습도가 변했을 경우에만 MQTT, Serial에 출력하기 위해 생성

//-----------LED----------------
TM1638 module(D2, D1, D0);
byte _led = 0;
byte _pre_led = 0;

//-----------RFID----------------
constexpr uint8_t RST_PIN = D4; 
constexpr uint8_t SS_PIN = D8;
char* _rfid;   
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 
 
// Init array that will store new NUID 
byte nuidPICC[4];

//----------MQTT-----------------
const char * ssid = "KCCI_STC_S";
const char * password = "kcci098#";

char * topic = "kw/nodemcu";                //수신 Topic
char * server = "broker.mqttdashboard.com"; //MQTT broker address

char message_buff[100]; //initialise storage buffer
WiFiClient wifiClient; //클라이언트로 작동

void callback(char * topic, byte * payload, unsigned int length) {
  int i = 0;
 
  Serial.println("Message arrived: topic: " + String(topic));
  Serial.println("Length: "+ String(length,DEC));
 
  //create character buffer with ending null terminator (string)
  for(i =0; i <length; i ++){
    message_buff[i] = payload[i];
  }
  message_buff[i]= '\0';
 
  String msgString = String(message_buff);
  Serial.println("Payload: "+ msgString);
}

//MQTT 서버, 포트, 메세지 왔을때 콜백함수, 인터넷연결을 포함하여 MQTT client 객체 생성
PubSubClient client(server, 1883, callback, wifiClient);

// 아두이노 셋팅
void setup() {
  Serial.begin(9600);

  //-----------WIFI--------------
  connectWIFI();

  //-----------LED----------------
  module.setDisplayToHexNumber(0x1234ABCD,0x00); //점은 사용하지 않음
  
  //-----------RFID---------------
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  
}

// 실행구간
void loop() {
  client.loop();  //MQTT ready to read
  
  rfidread(); //RFID

  ledkey();   //LED KEY

  temp_humi();//temperature and humidity

  //0.01초 주기로 실행 하도록 설정
  delay(10);
}

void connectWIFI(void){
  //wifi에 연결을 시도한다.
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  //연결되면 접속한 IP가 뭔지 출력한다.
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());
 
  //Connection to broker
  if (client.connect("")){ 
    client.subscribe(topic);
  }
}

void temp_humi(void){
  
  _temperature = dht.readTemperature();
  _humidity = dht.readHumidity();

  if ((_temperature != _pre_t) || (_humidity != _pre_h)){
    Serial.print("Temperature: ");
    Serial.print(_temperature);
    Serial.print(" C");
    Serial.print("Humidity: ");
    Serial.print(_humidity);
    Serial.println(" %\t");

    char sTemp[4];
    char sHumi[4];

    sprintf(sTemp, "%d", _temperature);
    sprintf(sHumi, "%d", _humidity);

    client.publish("kw/nodemcu/temperature", sTemp);
    client.publish("kw/nodemcu/humidity", sHumi);
  }
  
  _pre_t = _temperature;
  _pre_h = _humidity;
}

void ledkey(void){
  _led = module.getButtons();
  module.setLEDs(_led);

  if (_pre_led != _led){
    Serial.print("LED: ");
    Serial.println(_led); //시리얼 모니터로 key값 출력
  }
  
  _pre_led = _led;
}
 
void rfidread(void)
{
    // Look for new cards
  if (rfid.PICC_IsNewCardPresent()) 
  {
      if (rfid.PICC_ReadCardSerial())
      {
          MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
          
          String cardData = String(rfid.uid.uidByte[0], HEX);
          cardData = cardData + String(rfid.uid.uidByte[1], HEX);
          cardData = cardData + String(rfid.uid.uidByte[2], HEX);
          cardData = cardData + String(rfid.uid.uidByte[3], HEX);
          Serial.print("RFID: ");
          Serial.println(cardData);

          char rfidstr[10];
          cardData.toCharArray(rfidstr, 10);
          client.publish("kw/nodemcu/rfid", rfidstr);
          
          // Halt PICC
          rfid.PICC_HaltA();
          
          // Stop encryption on PCD
          rfid.PCD_StopCrypto1();
      }
  }
}
