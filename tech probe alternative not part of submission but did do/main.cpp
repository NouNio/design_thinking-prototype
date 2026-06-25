/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the ID/UID, type and any data blocks it can read. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * If your reader supports it, this sketch/program will read all the PICCs presented (that is: multiple tag reading).
 * So if you stack two or more PICCs on top of each other and present them to the reader, it will first output all
 * details of the first and then the next PICC. Note that this may take some time as all data blocks are dumped, so
 * keep the PICCs at reading distance until complete.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
 */
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <WiFiClient.h>


#define RST_PIN 13  // Configurable, see typical pin layout above
#define SS_PIN 5    // Configurable, see typical pin layout above
const char *ssid = "LegotecNET";
const char *password = "Toffie83!";
const char *mqtt_broker = "raspberrypi.local";
//const char *mqtt_broker = "192.168.8.115";
int mode = 0;
int b_mode = 0;
int colours[][3] = {
  { 0, 0, 1 },  //blue
  { 0, 1, 1 },  //cyan
  { 1, 0, 1 },  //magenta
  { 1, 1, 0 }   //yellow
};
long r=0;
int i = 0;
bool parity = 0;
int c_b = 0;
int c_c = 1;
int c_m = 2;
int c_y = 3;
int blink_on_transferring = 0;
int on_on_transferring = 1;
int blink_once_on_success = 2;
const char *pubtopic = "emqx/esp32";
const char *mqtt_username = "rfid_mqtt_1";
const char *mqtt_id = "rfid_mqtt_2";
const char *mqtt_password = "pass_for_esp_00";
const int mqtt_port = 1883;
const unsigned int red = 25;
const unsigned int green = 32;
const unsigned int blue = 27;
const unsigned int led = 12;
int transferred = 0;
bool waiting = false;
WiFiClient client;

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

//*

//*/
void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(red, OUTPUT);
  digitalWrite(red, HIGH);

  pinMode(green, OUTPUT);
  digitalWrite(green, HIGH);

  pinMode(blue, OUTPUT);
  digitalWrite(blue, HIGH);

  Serial.begin(115200);  // Initialize serial communications with the PC
  while (!Serial)
    ;                                 // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();                        // Init SPI bus
  mfrc522.PCD_Init();                 // Init MFRC522
  delay(4);                           // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  WiFi.mode(WIFI_STA);  //Optional
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

  /*
  ssid,
  password,
  mqtt_broker,  // MQTT Broker server ip
  mqtt_username,   // Can be omitted if not needed
  mqtt_password,   // Can be omitted if not needed
  mqtt_id     // Client name that uniquely identify your device
  //mqtt_port   
  */

  //client.setWifiCredentials(ssid, password);
  //client.setMqttClientName(mqtt_id);
  //client.setMqttServer(ip, mqtt_username, mqtt_password, mqtt_port);
  // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).

WiFi.mode(WIFI_STA);  //Optional
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}




// Publish a message to "mytopic/test"

// Execute delayed instructions

void loop() {
  Serial.printf("transferred: %d\n", transferred);
  if (i > 20) {
    digitalWrite(led, HIGH);

  } else {
    digitalWrite(led, LOW);
  }
   if (mfrc522.PICC_IsNewCardPresent() &&mfrc522.PICC_ReadCardSerial()) {
  

  String uid_str = String();
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid_str.concat((mfrc522.uid.uidByte[i] < 0x10 ? " 0" : ""));
    uid_str.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  int uid = std::__cxx11::stoul(uid_str.c_str(), 0, 16);
  switch (uid) {
    case (int)0x3ba99332:
      mode = c_c;
      Serial.println("change_cyan");
      break;

    case (int)0x1b7daa32:
      mode = c_b;
            Serial.println("change_blue");

      break;

    case (int)0x6b44a832:
      mode = c_m;
                  Serial.println("change_magenta");

      break;
    case (int)0x2bdabe32:
      mode = c_y;
                        Serial.println("change_yellow");

      break;

    case (int)0xfb90a832:
      //always on while transferring
                        Serial.println("change_to_on");

      b_mode = 1;
      break;
    case (int)0x6bdcc632:
      //blink  while trasferring
      b_mode = 0;
                              Serial.println("change_to_blink");

      break;
    case (int)0x8b978032:
      //blink on success
      b_mode = 2;
                                    Serial.println("change_to_once");

      break;
    case (int)0x0b4d3fa7:
      i = 0;
      transferred = 0;
      break;
    default:
      Serial.println("unknown card");


      break;
  }
  }
  if(transferred > 6){
    i++;
    delay(1000);
    return;
  }
  if (!WiFi.status()==WL_CONNECTED){
     WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, HIGH);
    Serial.print(".");
    delay(1000);
    i++;
  
  }

  Serial.println("\nreconnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

  }
  //*
  //if(!client.connected()){
  //if(client.connect("debian.local", 29876)){
  if(b_mode==2){{
    if(!waiting){
      //client.printf("package %d\n", transferred);
      //client.flush();
      waiting = true;
      r = random(5,8);
    }
  }
  }
  else{
    if(!waiting){
      //client.printf("package %d\n", transferred);
      //client.flush();
      r = random(3,6);
      waiting = true;
    }
  }
  //if(client.available()>0){
  if (random(9)>7){
   //String s = client.readStringUntil('\r');
   //if(s.endsWith(String(transferred))){
   if (r >0){
    r-=1;}
    if (r==0){
    transferred++;
    waiting = false;
    if (b_mode==2){
        digitalWrite(red, !colours[mode][0]);
      digitalWrite(green, !colours[mode][1]);
      digitalWrite(blue, !colours[mode][2]);
      delay(1000);
         digitalWrite(red, HIGH);
      digitalWrite(green,HIGH);
      digitalWrite(blue, HIGH);
      delay(1000);
      i+=2;
    }
    //if(transferred>6){
      //client.stop();
    //}
   }
  }
//*/
  if (b_mode == 1) {
    digitalWrite(red, !colours[mode][0]);
    digitalWrite(green, !colours[mode][1]);
    digitalWrite(blue, !colours[mode][2]);
  } else if ((b_mode == 0) && parity) {
      digitalWrite(red, !colours[mode][0]);
      digitalWrite(green, !colours[mode][1]);
      digitalWrite(blue, !colours[mode][2]);
  } else {
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, HIGH);
  }
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  
  if (!(b_mode == 2)) {
    delay(1000);
  }
  if (!parity){
  parity = true;}
  else{
     parity = false;
  }
  i++;
}