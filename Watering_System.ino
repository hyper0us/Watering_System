#include <LiquidCrystal.h>
#define A0 A0
#define A4 A4
#define A5 A5
float temperature;
int clicktime = 0;
int lasthumiditytime = -31;
float avrhumidity = 0;
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
void setup() {
  pinMode(A0,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(13,OUTPUT);
  pinMode(12,INPUT);
  pinMode(11,OUTPUT);
  pinMode(10,INPUT);
  digitalWrite(13,LOW);
  pinMode(3,OUTPUT);
  digitalWrite(3,LOW);
  lcd.begin(16, 2);
}
void loop() {
  if(digitalRead(12)==HIGH){
    avrhumidity=((1023-analogRead(A4))+(1023-analogRead(A5)))/20;
  if(avrhumidity<50&&millis()/60000-lasthumiditytime>30 ){
    lcd.noDisplay();
    digitalWrite(13, LOW);
    digitalWrite(3, HIGH);
    delay(5000);
    digitalWrite(3, LOW);
    lasthumiditytime=millis()/60000;
    lcd.display();
    digitalWrite(13, HIGH);
  }
  if(digitalRead(10)==HIGH)clicktime=millis()/1000;
  if(millis()/1000-clicktime<=15){
    lcd.display();
    digitalWrite(13, HIGH);
    temperature = analogRead(A0)* 0.48828125;
    lcd.setCursor(0,0);
    lcd.print(temperature);
    lcd.print(" *C");
    lcd.setCursor(0,1);
    lcd.print("avr. hum. :");
    if(digitalRead(12)==HIGH)
    lcd.print(avrhumidity*1000/1023);
    else lcd.print("unknown");
    lcd.print("% ");
  }
  else {
    digitalWrite(13, LOW);
    lcd.noDisplay();
  }
}
else{
  digitalWrite(13,LOW);
  lcd.noDisplay();
  digitalWrite(3,LOW);
  clicktime=0;
}
delay(1000);
lcd.setCursor(0,0);
lcd.print("                ");
lcd.setCursor(0,1);
lcd.print("                ");
lcd.noCursor();
}
