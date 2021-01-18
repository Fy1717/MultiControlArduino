#include <LiquidCrystal.h>

int motor1F = A0;
int motor1B = A1;
int motor2F = A4;
int motor2B = A5;
int buttonF = 5;
int buttonB = 4;
int buttonL = 3;
int buttonR = 2;

long duration, cm;

int valF;
int valB;
int valL;
int valR;

int rs = 6;
int en = 7;
int d4 = 8;
int d5 = 9;
int d6 = 10;
int d7 = 11;

int pingPin = 13;

int sensor = A2;
int buzzer = A3;
int velocity;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
    pinMode(buttonF, INPUT);
    pinMode(buttonB, INPUT);
    pinMode(buttonL, INPUT);
    pinMode(buttonF, INPUT);

    pinMode(motor1F, OUTPUT);
    pinMode(motor1B, OUTPUT);

    pinMode(buzzer, OUTPUT);

    pinMode(motor2F, OUTPUT);
    pinMode(motor2B, OUTPUT);

    lcd.begin(16, 2);

    Serial.begin(9600);
}

void loop() {
    valF = digitalRead(buttonF);
    valB = digitalRead(buttonB);
    valL = digitalRead(buttonL);
    valR = digitalRead(buttonR);

    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(5);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin, LOW);

    pinMode(pingPin, INPUT);
    duration = pulseIn(pingPin, HIGH);

    cm = (duration / 29) / 2;

    if (cm < 2) {
        velocity = 0;
    }

    if (valF == 1) {
        Serial.println("---------FORWARD---------");
        velocity = velocity + 20;

        lcd.setCursor(8, 0);
        lcd.print(" DIRCT  ");

        digitalWrite(motor1F, HIGH);
        digitalWrite(motor2B, HIGH);
        delay(300);
        digitalWrite(motor1F, LOW);
        digitalWrite(motor2B, LOW);
        delay(100);
    }

    if (valB == 1) {
        Serial.println("---------STOPPED---------");
        velocity = 0;

        lcd.clear();
        lcd.setCursor(8, 0);
        lcd.print(" STOPPED");

        digitalWrite(motor1B, HIGH);
        digitalWrite(motor2F, HIGH);
        delay(300);
        digitalWrite(motor1B, LOW);
        digitalWrite(motor2F, LOW);
        delay(100);
    }

    if (valL == 1) {
        Serial.println("---------LEFT---------");

        lcd.setCursor(8, 0);
        lcd.print("<-- LEFT");

        digitalWrite(motor1B, HIGH);
        digitalWrite(motor2B, HIGH);
        delay(300);
        digitalWrite(motor1B, LOW);
        digitalWrite(motor2B, LOW);
        delay(100);
    }

    if (valR == 1) {
        Serial.println("---------RIGHT---------");

        lcd.setCursor(8, 0);
        lcd.print("RIGHT-->");

        digitalWrite(motor1F, HIGH);
        digitalWrite(motor2F, HIGH);
        delay(300);
        digitalWrite(motor1F, LOW);
        digitalWrite(motor2F, LOW);
        delay(100);
    }

    if (((valF || valB || valL || valR) == 0) && (velocity != 0)) {
        lcd.setCursor(8, 0);
        lcd.print(" DIRCT  ");
    }

    if (velocity == 0) {
        lcd.setCursor(8, 0);
        lcd.print(" STOPPED");
    } else {
        lcd.setCursor(8, 0);
        lcd.print(" DIRCT  ");

        digitalWrite(motor1F, HIGH);
        digitalWrite(motor2B, HIGH);
        delay(300);
        digitalWrite(motor1F, LOW);
        digitalWrite(motor2B, LOW);
        delay(100);
    }

    // SET DATA TO LCD
    lcd.setCursor(0, 0);
    lcd.print("MOVE:");

    lcd.setCursor(0, 1);
    lcd.print("VEL:");
    lcd.setCursor(4, 1);
    lcd.print(velocity);

    lcd.setCursor(8, 1);
    lcd.print(" D:");
    lcd.print(cm);
    lcd.print("cm");

    // BUZZER CONTROLLER
    if (cm < 10) {
        digitalWrite(buzzer, HIGH);
        delay(100);
        digitalWrite(buzzer, LOW);
        delay(100);
    }
}