#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#define DHTPIN 14  
#define DHTTYPE DHT11    
#define buzz 12
#define LED 13

unsigned long timer = 0;
void delay_100ms()
{
    if ( (unsigned long) (millis() - timer) > 1000 )
    {
       timer = millis();
    }
}
LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(115200);
  pinMode(buzz,OUTPUT);
  pinMode(LED,OUTPUT);
  dht.begin();
  lcd.begin();
  lcd.backlight();
}
void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  int value = analogRead(A0);   //đọc giá trị điện áp ở chân A0 - chân cảm biến
                                //(value luôn nằm trong khoảng 0-1023) 10bit 2^10-1
                                // đọc cảm biến khí gas
  Serial.println(value);
  if(value > 500) 
  {
    Canhbaogas();
    }
  else{
      digitalWrite(buzz,LOW);
      digitalWrite(LED,LOW);
    }
  
  lcd.setCursor(3,0);
  lcd.print("NHOM 11 ");
  lcd.setCursor(0,1);
  lcd.print("T:");
  lcd.print(t);
  lcd.setCursor(9,1);
  lcd.print("H:");
  lcd.setCursor(11,1);
  lcd.print(h);

  Serial.println("TEMP: ");
  Serial.println(t);
  Serial.println("HUM: ");
  Serial.println(h);
  Serial.println("GAS: ");
  Serial.println(value);
}

void Canhbaogas(){
  digitalWrite(buzz,HIGH), delay_100ms();
  digitalWrite(buzz,LOW), delay_100ms();
  digitalWrite(LED,HIGH), delay_100ms();
  digitalWrite(LED,LOW), delay_100ms();
} 
