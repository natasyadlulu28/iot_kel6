#include <SerialESP8266wifi.h>

#define FIREBASE_HOST "iot-6-d28b7-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "R70A6X5QIK1JcduBGYumU2VrryAjZRJb8lUVhHOb"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

#include <RTClib.h>
#include <Time.h>
#include <TimeLib.h>
#include <NTPClient.h>   

int red = 3;

int waterlevel_sensor = A0;

int waterpump = 12; 

int moisture_sensor = A1;
int moisture_value = 0;

int lembab_rendah = 60;
int lembab_tinggi = 75;

//NTPClient timeClient(ntpUDP, "time.nist.gov", 3600, 60000);
char Time[] = "TIME:00:00:00";
char Date[] = "DATE:00/00/2000";
byte last_second, second_, minute_, hour_, day_, month_;
int year_;

void setup () {
  pinMode(red,OUTPUT);
  pinMode(waterpump,OUTPUT);
  Serial.println("Reading From the Sensor ...");
  Serial.begin (9600);
}

void loop() {
  waterlevel_sensor = analogRead(waterlevel_sensor);
  moisture_value = 100 - map(analogRead(moisture_sensor), 0, 1023, 0, 100);
  
  //Kelembaban Tanah
  Serial.print("Kelembaban Tanah: ");
  Serial.print(moisture_value);
  Serial.println("%");
  
  //Persediaan Air
  Serial.print("Persediaan Air: ");
  if (waterlevel_sensor > 300) {
     Serial.println("Masih Ada");
     digitalWrite(red,LOW);
      if(moisture_value < lembab_rendah){
        Serial.println("KERING, BUTUH AIR!");
        digitalWrite(waterpump, LOW); 
        delay(5000);
      }else if(moisture_value > lembab_tinggi){
        digitalWrite(waterpump, HIGH);  
        Serial.println("BASAH, KEBANYAKAN AIR!");
        delay(1000);
      }else{
        digitalWrite(waterpump, HIGH); 
        Serial.println("LEMBAB, NICE!^^");
        delay(1000);
      }
  }else{
    Serial.println("Habis");
    digitalWrite(red,HIGH);
    delay(1000);
  }
}
