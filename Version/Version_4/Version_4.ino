#include <Servo.h>
#include "HX711.h"

// Pin per l'ESC e pulsante
#define ESC_PIN 11
#define BUTTON_PIN 12

// Pin per i LED
#define LED_ARMED 8
#define LED_SAFE 10

// Pin per le celle di carico
#define DT_LEFT 3
#define SCK_LEFT 2
#define DT_RIGHT 4
#define SCK_RIGHT 5
#define DT_THRUST 6
#define SCK_THRUST 7

// Oggetti per il motore e le celle di carico
Servo esc;
HX711 scale_left, scale_right, scale_thrust;

// Variabili globali
int pwm_min = 1100;
int pwm_max = 2000;
bool is_armed = false;
bool is_test_running = false;

// Variabili per il doppio clic
unsigned long last_button_press = 0;
const int double_click_interval = 500;
bool waiting_for_second_click = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Avvio sistema...");

  // Configura i LED
  pinMode(LED_ARMED, OUTPUT);
  pinMode(LED_SAFE, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(LED_ARMED, LOW);
  digitalWrite(LED_SAFE, HIGH);

  // Configura ESC
  esc.attach(ESC_PIN);
  esc.writeMicroseconds(1000);
  delay(3000);
  Serial.println("ESC configurato.");

  // Configura le bilance
  configureScale(scale_left, DT_LEFT, SCK_LEFT, 217000.0, "Sinistra");
  configureScale(scale_right, DT_RIGHT, SCK_RIGHT, -211000.0, "Destra");
  configureScale(scale_thrust, DT_THRUST, SCK_THRUST, -214000.0, "Thrust");
}

void configureScale(HX711 &scale, int dt, int sck, float calibration_factor, const char *label) {
  scale.begin(dt, sck);
  Serial.print("Configurazione della bilancia ");
  Serial.println(label);

  while (!scale.is_ready()) {
    Serial.print("Bilancia ");
    Serial.print(label);
    Serial.println(" non pronta. Attendi...");
    delay(500);
  }

  scale.set_scale(calibration_factor);
  scale.tare();
  Serial.print("Bilancia ");
  Serial.print(label);
  Serial.println(" pronta e azzerata.");
}

void loop() {
  checkButton();

  if (is_test_running) {
    runTest();
    is_test_running = false;
    disarmSystem();
  }

  delay(50);
}

void checkButton() {
  bool button_state = digitalRead(BUTTON_PIN) == LOW;

  if (button_state) {
    unsigned long current_time = millis();

    if (waiting_for_second_click && current_time - last_button_press <= double_click_interval) {
      Serial.println("Doppio clic rilevato: avvio del test.");
      is_test_running = true;
      waiting_for_second_click = false;
    } else {
      waiting_for_second_click = true;
      last_button_press = current_time;

      if (is_armed) {
        Serial.println("Singolo clic: disarmo del sistema.");
        disarmSystem();
      } else {
        Serial.println("Singolo clic: armamento del sistema.");
        armSystem();
      }
    }
  }

  if (waiting_for_second_click && millis() - last_button_press > double_click_interval) {
    waiting_for_second_click = false;
  }
}

void armSystem() {
  is_armed = true;
  digitalWrite(LED_ARMED, HIGH);
  digitalWrite(LED_SAFE, LOW);
  Serial.println("Sistema armato.");
}

void disarmSystem() {
  is_armed = false;
  digitalWrite(LED_ARMED, LOW);
  digitalWrite(LED_SAFE, HIGH);
  Serial.println("Sistema disarmato.");
}

void runTest() {
  Serial.println("Avvio del test...");
  digitalWrite(LED_SAFE, LOW);

  for (int pwm = pwm_min; pwm <= pwm_max; pwm += 50) {
    esc.writeMicroseconds(pwm);

    float left_kg = scale_left.get_units();
    float right_kg = scale_right.get_units();
    float thrust_kg = scale_thrust.get_units();

    float thrust_N = thrust_kg * 9.80665;
    float torque_kg = right_kg - left_kg;
    float torque_N = torque_kg * 9.80665;

    Serial.print("PWM: ");
    Serial.print(pwm);
    Serial.print(" - Thrust: ");
    Serial.print(thrust_kg, 2);
    Serial.print(" kg, ");
    Serial.print(thrust_N, 2);
    Serial.print(" N - Torque: ");
    Serial.print(torque_kg, 2);
    Serial.print(" kg, ");
    Serial.print(torque_N, 2);
    Serial.println(" N");

    delay(500);
  }

  Serial.println("Test completato.");
  esc.writeMicroseconds(1000);
}