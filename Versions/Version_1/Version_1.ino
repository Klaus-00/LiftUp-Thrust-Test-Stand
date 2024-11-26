#include <Servo.h>
#include "HX711.h"

// Pin per l'ESC
#define ESC_PIN 11

// Pin per la cella di carico thrust
#define DT_THRUST 6
#define SCK_THRUST 7

// Oggetti per il motore e la cella di carico
Servo esc;
HX711 scale_thrust;

// Variabili globali
int pwm_min = 1100;
int pwm_max = 2000;
float calibration_factor_thrust = -214000.0; // Fattore di calibrazione thrust

void setup() {
  Serial.begin(9600);
  Serial.println("Avvio sistema...");

  // Configura ESC
  esc.attach(ESC_PIN);
  esc.writeMicroseconds(1000);
  delay(3000);
  Serial.println("ESC configurato.");

  // Configura la bilancia thrust
  scale_thrust.begin(DT_THRUST, SCK_THRUST);
  while (!scale_thrust.is_ready()) {
    Serial.println("Cella di carico thrust non pronta. Attendi...");
    delay(500);
  }
  scale_thrust.set_scale(calibration_factor_thrust);
  scale_thrust.tare();
  Serial.println("Cella di carico thrust pronta e tarata.");
}

void loop() {
  for (int pwm = pwm_min; pwm <= pwm_max; pwm += 50) {
    esc.writeMicroseconds(pwm);

    if (scale_thrust.is_ready()) {
      float thrust_kg = scale_thrust.get_units();
      float thrust_N = thrust_kg * 9.80665;

      Serial.print("PWM: ");
      Serial.print(pwm);
      Serial.print(" - Thrust: ");
      Serial.print(thrust_kg, 2);
      Serial.print(" kg, ");
      Serial.print(thrust_N, 2);
      Serial.println(" N");
    }

    delay(500);
  }

  Serial.println("Test completato.");
  esc.writeMicroseconds(1000);

  while (true) {
    // Ciclo infinito dopo il test
  }
}