int red = 3;

int waterlevel_sensor = A0;

int waterpump = 12; 

int moisture_sensor = A1;
int moisture_value = 0;

//map(analogRead(moisture_value), 0, 1023, 0, 100);
int lembab_rendah;
int lembab_tinggi;

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

  if(moisture_value < lembab_rendah){
    Serial.println("KERING, BUTUH AIR!");
  }else if(moisture_value > lembab_tinggi){
    Serial.println("BASAH, KEBANYAKAN AIR!");
  }else{
    Serial.println("LEMBAB, NICE!^^");
  }
//  delay(3000);
//  if(){
//    
//  }else{
//    
//  }
  //Persediaan Air
  Serial.print("Persediaan Air: ");
  if (waterlevel_sensor > 400) {
    Serial.println("Masih Ada");
    digitalWrite(red,LOW);
    delay(1000);
  }else{
    Serial.println("Habis");
    digitalWrite(red,HIGH);
    delay(1000);
  }
}
