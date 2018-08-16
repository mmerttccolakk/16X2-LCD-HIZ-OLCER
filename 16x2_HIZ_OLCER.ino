#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//ozel degiskenler
long microSecs;
long freq;
int lastBit;
int nowVal;
long secs;
long maxHz;
long minHz;
long minmax;

//pin bağlantıları
#define hiz_pin A0
//hiz_carpani
double hiz_degiskeni =1.575;
int hiz =0;
int devir =0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(hiz_pin, INPUT);
  lcd.begin(16, 2);
  pinMode(13, OUTPUT);//anot
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  analogWrite(7,30);//v0
  digitalWrite(13, HIGH);
  digitalWrite(8, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("MERHABA, SISTEM");
  lcd.setCursor(0, 1);
  lcd.print("HAZIRLANIYOR....");
  delay(5000);
  lcd.clear();
  microSecs = micros();
  freq = 0;
  lastBit = 0;
  nowVal =0;
  maxHz=0;
  minHz=0;
  minmax=0;
  secs = millis();
}
int x=0;
void loop() {
  if ((microSecs+20)<micros()){
            nowVal=digitalRead(hiz_pin);
       
            if (lastBit!=nowVal) {
              lastBit=nowVal;
              freq=freq+1;
            }
            if (freq>maxHz){
              maxHz=freq;
            }
            if (freq<minHz){
              minHz=freq;
            }
            microSecs = micros();
        }
        if (secs+1000<millis()){
      
          if (minmax+300000<millis())
          {
            minmax=millis();
            minHz=freq;
            maxHz=freq;
            
          }
           hiz=freq*hiz_degiskeni;
           devir=freq*60;
            freq=0;
            secs=millis();
        }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" (KM/S) | (RPM)");
  lcd.setCursor(3, 1);
  lcd.print(hiz);
  lcd.setCursor(12, 1);
  lcd.print(devir);
}

