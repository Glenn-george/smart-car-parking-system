#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo gateServo;

int trigPin = 9;
int echoPin = 10;
int ir1 = A0;
int ir2 = A1;
int buzzer = 8;
long duration;
int distance;


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  gateServo.attach(3);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(buzzer, OUTPUT);

  gateServo.write(0); 
  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  delay(3000);
  
}

void loop() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  
  int slot1 = digitalRead(ir1);
  int slot2 = digitalRead(ir2);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Slot1:");
  lcd.print(slot1 == LOW ? "Occupied " : "Free     ");
  lcd.setCursor(0, 1);
  lcd.print("Slot2:");
  lcd.print(slot2 == LOW ? "Occupied " : "Free     ");

  
  if (slot1 == LOW && slot2 == LOW && distance < 10) {
    digitalWrite(buzzer, HIGH);
    delay(2000);
    digitalWrite(buzzer, LOW);
  
  } else{
    digitalWrite(buzzer, LOW);
   
  }

  
  if (distance < 10 && (slot1 == HIGH || slot2 == HIGH)) {
    gateServo.write(90);  
    delay(3000);
        
  }else{
    gateServo.write(0);
  }
   
  delay(500);
}