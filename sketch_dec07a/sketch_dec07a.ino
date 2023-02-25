#include<LiquidCrystal.h>
#include <TimeLib.h>
const int rs=10,en=9,d4=4,d5=5,d6=6,d7=7;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
#define soilPin=A1;
#define ldrPin=A2;
#define tempPin=A0;
#define rainPin=8;
int motor=13;
int moisture=0;
void setup() {
  lcd.begin(16,2);
  setTime(4,59,0,30,12,21);  
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(13,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(8,INPUT);
}
void loop() {  
   lcd.clear();
  int soilValue=analogRead(A1);
  int lightValue=analogRead(A2);
  int tempValue=analogRead(A0);
  int rainValue=digitalRead(8);
  float temp=(tempValue*500)/1024;
  int a=(18/100)*1024;
  int b=(20/100)*1024;
  moisture=map(soilValue,1023,150,0,100);
  lcd.setCursor(0,1);
  lcd.print("temp:");
  lcd.setCursor(5,1);
  lcd.print(temp);
  lcd.print("*C");
  Time(lightValue);
  delay(2000);
  lcd.clear();
  delay(2000);
  lcd.setCursor(0,0);
  lcd.print("lightValue=");
  lcd.setCursor(11,0);
  lcd.print(lightValue);
  lcd.setCursor(0,1);
  lcd.print("moisture=");
  lcd.setCursor(9,1);
  lcd.print(moisture);
  lcd.print("%");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  if(rainValue==1){
    lcd.print("there is no rain");
    delay(2000);
  }else{
    lcd.print("there is rain");
    delay(2000);
  } 
  digitalClockDisplay();
  delay(1000); 
  lcd.clear(); 
  //---------------------------------------------------------------------
 //temperature in morning and evening is not high at sunset and morning so we will not depend on temperature.
  if(moisture<20&&moisture>18&&lightValue<600&&lightValue>=400&&rainValue==1)
  {
    digitalWrite(13,LOW);
  }
  //temperature in afternoon is high so we can depend on temperature.
   else if(soilValue<b&&soilValue>a&& lightValue<1023&& temp>=30&&rainValue==1)
  {
    digitalWrite(13,LOW);
  }
  if(rainValue==0){ //there is rain so we don't need water.
    digitalWrite(13,  HIGH);
    }
   if(moisture<18){   //the soil is very dry.
     digitalWrite(13,LOW);
  }
  if(lightValue<=400){  //lights turn on in  the evening.   
    digitalWrite(3,HIGH);
  }else{
    digitalWrite(3,LOW);
  }
}
//---------------------------------
 void Time(int lightValue){
   lcd.setCursor(0,0);
   lcd.print("time:");
  int m=lightValue;
  lcd.setCursor(5,0);
  if(m<=400){
    lcd.print("evening");
  } 
  if(m>400&&m<600){
    lcd.print("morning");
  }else if(m>600&&m<1023){
    lcd.print("afternoon");
  }
}
void digitalClockDisplay()
{ 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(hour());
  printDigits(minute());
  printDigits(second());
  lcd.setCursor(0,1);
  lcd.print(" ");
  lcd.print(day());
  lcd.print(" ");
  lcd.print(month());
  lcd.print(" ");
  lcd.print(year());
  lcd.println();  
  }
void printDigits(int digits)
{
  lcd.print(":");
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);  
}
