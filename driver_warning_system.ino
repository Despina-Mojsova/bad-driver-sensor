#include "peaches.h"

const int trigPin = 13;
const int echoPin = 12;

const int buzzer = 11;
const int greenLED = 10;
const int yellowLED = 9;
const int redLED = 8;

long duration;
double distance;

double maxDistanceCM = 30;

int melody[] = {
  NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4,
  NOTE_C5, NOTE_A4, NOTE_B4, NOTE_G4,
  NOTE_A4, NOTE_F4, NOTE_G4, NOTE_E4
};
int noteDuration = 150;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  digitalWrite(buzzer, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  digitalWrite(greenLED, distance < maxDistanceCM ? HIGH : LOW);
  digitalWrite(yellowLED, distance < (maxDistanceCM * 0.66) ? HIGH : LOW);

  if (distance < (maxDistanceCM * 0.33)) {
    digitalWrite(redLED, HIGH);
    playMelody();
  } else {
    digitalWrite(redLED, LOW);
    noTone(buzzer);
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void playMelody() {
  for (int i = 0; i < sizeof(melody) / sizeof(int); i++) {
    tone(buzzer, melody[i], noteDuration);
    delay(noteDuration + 30);
  }
}



