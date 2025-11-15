#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

#define LED_VERDE 3
#define LED_VERMELHO 12
#define TRIG 4 
#define ECHO 5
#define MAX 200
#define BUZZER 13

int count = 0;
bool objetoDetectado = false;

LiquidCrystal_I2C lcd(0x27, 16, 2);
NewPing sonar(TRIG, ECHO, MAX);

void setup(){
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Contagem: ");
  lcd.setCursor(0, 1);
  lcd.print(count);

  Serial.begin(9600);
}
void loop(){
  int distancia = sonar.ping_cm();

  if(distancia < 50 == distancia > 0){
    if(objetoDetectado == false){
      objetoDetectado = true;
      count++;

      digitalWrite(LED_VERDE, HIGH);
      delay(200);
      digitalWrite(LED_VERDE, LOW);
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Contagem: ");
      lcd.setCursor(0, 1);
      lcd.print(count);
      delay(1000);
      lcd.print("   ");

      if(count == 12){
        dispararAlarme();
      }
    }
  } else {
    objetoDetectado = false;
  }
  Serial.print(count);
  delay(100);
}
void dispararAlarme(){
  unsigned long inicio = millis();

  while((millis() - inicio) < 5000){
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(BUZZER, HIGG);
    delay(500);
    digitalWrite(BUZZER, LOW);
    delay(500);
    digitalWrite(LED_VERMELHO, LOW);
  }
  digitalWrite(BUZZER, LOW);
}