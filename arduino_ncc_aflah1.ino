#include <LiquidCrystal.h>
#include <IRremote.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
IRrecv irrecv(6);
decode_results results;
int STATUS_REMOTE = 0;


void setup() 
{
  irrecv.enableIRIn();
  lcd.begin(16, 1);
  pinMode(7, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(8, OUTPUT);
  lcd.print("SYSTEM STARTING");
  delay(100);
  lcd.clear();
}

void loop()
{
  if (STATUS_REMOTE == 0) //status alarm off
  {
    if (digitalRead(7) == HIGH) //input dari pir sensor
    {
      Serial.println(analogRead(A1));
      if (analogRead(A1) < 900) //input dari photoresistor
      {
        digitalWrite(8,HIGH); //output ke lampu bohlam
      }
      lcd.print("WELCOME HOME");
      delay(3000);
      lcd.clear();
    }
    digitalWrite(8,LOW); //output ke lampu bohlam
  }
  
  else if (STATUS_REMOTE == 1) //status alarm on
  {
    if (digitalRead(7) == HIGH) //input dari pir sensor
    {
      while ( ! irrecv.decode(&results)) //loop sampai menerima input remote
      {
        digitalWrite(8,HIGH); //output ke lampu bohlam
        lcd.print("ADA MALING!!!!");
        digitalWrite(9,HIGH); //output ke speaker alarm
        digitalWrite(13,LOW); //output ke lampu led indikator alarm
        delay (100);
        digitalWrite(9,LOW); //output ke speaker alarm
        digitalWrite(13,HIGH); //output ke lampu led indikator alarm
        lcd.clear();
        delay (100);
      }
      digitalWrite(13,LOW); //output ke lampu led indikator alarm
      lcd.print("ALARM: OFF");
      STATUS_REMOTE=0; //status alarm off
      delay(300);
      lcd.clear();
      irrecv.resume(); //meresume penerimaan ir
    }
  }
  
  else
  {
    lcd.print("ERROR!!");
  }
  
  if (irrecv.decode(&results)) //input dari remote
  {
    Serial.println(results.value,DEC);
    if (results.value == 16580863) //input tombol power
    {
      if (STATUS_REMOTE == 0) //status alarm off
      {
        digitalWrite(13,HIGH); //output ke lampu led indikator alarm
        lcd.print("ALARM: ON");
        STATUS_REMOTE=1; //status alarm on
      }
      else //status alarm on
      {
        digitalWrite(13,LOW); //output ke lampu led indikator alarm
        lcd.print("ALARM: OFF");
        STATUS_REMOTE=0; //status alarm off
      }      
     delay(300);
     lcd.clear();
    }
    irrecv.resume(); //meresume penerimaan ir
  }
}