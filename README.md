# Penugasan NCC Arduino

## Home Alarm with Auto Lamp

Tujuan awal dari proyek ini adalah membuat lampu otomatis yang menyala jika ada gerakan dan keadaan sedang gelap. Fitur plus dari sistem ini juga disertai dengan alarm yang akan berbunyi jika terdeteksi gerakan saat alarm dalam posisi on. Untuk menghidupkan dan mematikan alarmnya digunakan sebuah remote. Sistem ini tersambung ke lampu di rumah yang akan menyala jika ada gerakan dan posisi gelap dan alarm dalam posisi off. Ditambahkan juga display untuk menampilkan informasi dari sistem. Sensor yang digunakan antara lain yaitu PIR Sensor (Motion Sensor), Photoresistor, dan IR Sensor. 

## Alur Penggunaan

1. Menghidupkan Arduino (Posisi awal alarm off)
2. Saat ada gerakan di ruangan dan kondisi cahaya gelap, lampu ruangan akan hidup dan display LCD akan menampilkan "Welcome Home"
3. Saat ada gerakan di ruangan dan kondisi cahaya terang, display LCD akan menampilkan "Welcome Home"
4. Untuk menyalakan Alarm, tekan tombol power di remote, display LCD akan menampilkan "Alarm: On" dan led merah akan terus menyala
5. Untuk mematikan Alarm, tekan tombol power di remota, display LCD akan menampilkan "Alarm: Off" dan led merah akan mati
6. Saat Alarm posisi on dan ada gerakan di ruangan, speaker akan berbunyi, led merah akan berkedip, display LCD menampilkan "Ada Maling!!!!", dan lampu ruangan akan hidup
7. Alarm akan terus berbunyi dan hanya bisa dimatikan dengan menekan tombol di remote


## Rangkaian

![Gambar Rangkaian](/SS__NCC_Aflah.png)

## List Komponen

- Arduino Uno R3
- Breadboard
- IR Remote
- IR Sensor
- PIR Motion Sensor
- Photoresistor
- Light Bulb
- Red LED
- Piezo
- LCD 16x2
- Resistor 10k Ω
- Resistor 220 Ω
- 2 Resistor 100 Ω
- Jumper Cable

## Source Code

```
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
```

## Link Tinkercad

[Link Tinkercad](https://www.tinkercad.com/things/e0A9JvWHUpG)
