#include <Servo.h>
#include "HX711.h"

// Pin per l'ESC
#define ESC_PIN 11

// Pin per le celle di carico
#define DT_LEFT 3
#define SCK_LEFT 2
#define DT_RIGHT 4
#define SCK_RIGHT 5

// Oggetti per il motore e le celle di carico
Servo esc;
HX711 scale_left, scale_right;

// Variabili globali
int pwm_min = 1100;
int pwm_max = 2000;
float calibration_factor_left = 217000.0;
float calibration_factor_right = -211000.0;

void setup() {
  Serial.begin(9600);
  Serial.println("Avvio sistema...");

  // Configura ESC
  esc.attach(ESC_PIN);
  esc.writeMicroseconds(1000);
  delay(3000);
  Serial.println("ESC configurato.");

  // Configura le bilance
  scale_left.begin(DT_LEFT, SCK_LEFT);
  scale_right.begin(DT_RIGHT, SCK_RIGHT);

  scale_left.set_scale(calibration_factor_left);
  scale_left.tare();
  scale_right.set_scale(calibration_factor_right);
  scale_right.tare();

  Serial.println("Bilance pronte e tarate.");
}

void loop() {
  for (int pwm = pwm_min; pwm <= pwm_max; pwm += 50) {
    esc.writeMicroseconds(pwm);

    float left_kg = scale_left.get_units();
    float right_kg = scale_right.get_units();
    float torque_kg = right_kg - left_kg;
    float torque_N = torque_kg * 9.80665;

    Serial.print("PWM: ");
    Serial.print(pwm);
    Serial.print(" - Torque: ");
    Serial.print(torque_kg, 2);
    Serial.print(" kg, ");
    Serial.print(torque_N, 2);
    Serial.println(" N");

    delay(500);
  }

  Serial.println("Test completato.");
  esc.writeMicroseconds(1000);

  while (true) {
    // Ciclo infinito dopo il test
  }
}