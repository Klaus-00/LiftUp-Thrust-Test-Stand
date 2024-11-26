#include <Servo.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include "HX711.h"

// Pin per i LED
#define LED_ARMED 8
#define LED_SAFE 10

// Pin per il pulsante
#define BUTTON_PIN 12

// Pin per l'ESC
#define ESC_PIN 11

// Pin per le celle di carico
#define DT_LEFT 3
#define SCK_LEFT 2
#define DT_RIGHT 4
#define SCK_RIGHT 5
#define DT_THRUST 6
#define SCK_THRUST 7

// Oggetti per il motore, le bilance e INA219
Servo esc;
HX711 scale_left, scale_right, scale_thrust;
Adafruit_INA219 ina219;

// Variabili globali
int pwm_min_percent = 30; // Percentuale minima di PWM (modificabile)
int pwm_max_percent = 50; // Percentuale massima di PWM (modificabile)
int pwm_min = 1100; // PWM minimo assoluto
int pwm_max = 2000; // PWM massimo assoluto
int test_duration = 15; // Durata del test in secondi
bool is_armed = false; // Stato del sistema
bool is_test_running = false; // Stato del test

// Variabili per il doppio clic
unsigned long last_button_press = 0; // Tempo dell'ultimo clic
const int double_click_interval = 500; // Tempo massimo per rilevare un doppio clic
bool waiting_for_second_click = false; // Stato di attesa per il secondo clic
bool button_state = false; // Stato attuale del pulsante
bool last_button_state = false; // Stato precedente del pulsante

// Variabili per calibrazione delle bilance
float calibration_factor_left = 217000.0;   // Fattore di calibrazione cella sinistra
float calibration_factor_right = -211000.0; // Fattore di calibrazione cella destra (invertito)
float calibration_factor_thrust = -214000.0; // Fattore di calibrazione cella thrust
const float g_to_N = 9.80665; // Conversione da kg a Newton

// Variabili INA219
float bus_voltage = 0.0; // Tensione letta dal sensore
float current_mA = 0.0;  // Corrente in milliampere
float power_W = 0.0;     // Potenza elettrica in Watt

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

  // Configura bilance
  configureScale(scale_left, DT_LEFT, SCK_LEFT, calibration_factor_left, "Sinistra");
  configureScale(scale_right, DT_RIGHT, SCK_RIGHT, calibration_factor_right, "Destra");
  configureScale(scale_thrust, DT_THRUST, SCK_THRUST, calibration_factor_thrust, "Thrust");

  // Configura INA219
  if (!ina219.begin()) {
    Serial.println("Errore: INA219 non trovato!");
    while (1);
  }
  Serial.println("INA219 configurato correttamente.");
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
    if (tareBalances()) {
      runTest();
    } else {
      Serial.println("Errore: Bilance non pronte dopo la taratura.");
    }
    is_test_running = false;
    disarmSystem();
  }

  delay(50);
}

void checkButton() {
  button_state = digitalRead(BUTTON_PIN) == LOW;

  if (button_state && !last_button_state) {
    unsigned long current_time = millis();

    if (waiting_for_second_click && current_time - last_button_press <= double_click_interval) {
      Serial.println("Doppio clic rilevato: avvio taratura e test.");
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

  last_button_state = button_state;
}

void armSystem() {
  is_armed = true;
  digitalWrite(LED_ARMED, HIGH);
  digitalWrite(LED_SAFE, LOW);
  Serial.println("Sistema armato.");
}

void disarmSystem() {
  is_armed = false;
  is_test_running = false;
  digitalWrite(LED_ARMED, LOW);
  digitalWrite(LED_SAFE, HIGH);
  Serial.println("Sistema disarmato.");
}

bool tareBalances() {
  Serial.println("Inizio taratura delle bilance...");
  bool left_ready = false, right_ready = false, thrust_ready = false;

  for (int retries = 0; retries < 10; retries++) {
    if (scale_left.is_ready()) {
      scale_left.tare();
      left_ready = true;
    }
    if (scale_right.is_ready()) {
      scale_right.tare();
      right_ready = true;
    }
    if (scale_thrust.is_ready()) {
      scale_thrust.tare();
      thrust_ready = true;
    }
    if (left_ready && right_ready && thrust_ready) {
      Serial.println("Taratura completata. Tutte le bilance sono pronte.");
      return true;
    }
    delay(500);
  }
  return false;
}

void runTest() {
  Serial.println("Avvio del test...");
  digitalWrite(LED_SAFE, LOW);

  int pwm_start = map(pwm_min_percent, 0, 100, pwm_min, pwm_max);
  int pwm_end = map(pwm_max_percent, 0, 100, pwm_min, pwm_max);
  int step_percent = 5; // Salita del 5% alla volta
  int steps = map(step_percent, 0, 100, pwm_min, pwm_max);

  for (int current_pwm = pwm_start; current_pwm <= pwm_end; current_pwm += steps) {
    esc.writeMicroseconds(current_pwm);

    float left_kg = scale_left.get_units();
    float right_kg = scale_right.get_units();
    float thrust_kg = scale_thrust.get_units();

    float thrust_N = thrust_kg * g_to_N;
    float torque_kg = right_kg - left_kg;
    float torque_N = torque_kg * g_to_N;

    float left_N = left_kg * g_to_N;
    float right_N = right_kg * g_to_N;

    bus_voltage = ina219.getBusVoltage_V();
    current_mA = ina219.getCurrent_mA();
    power_W = (bus_voltage * current_mA) / 1000.0;

    float pwm_percent = ((float)(current_pwm - pwm_min) / (pwm_max - pwm_min)) * 100.0;

    Serial.print("PWM: ");
    Serial.print(pwm_percent, 1);
    Serial.print("% - Left: ");
    Serial.print(left_kg, 2);
    Serial.print(" kg, ");
    Serial.print(left_N, 2);
    Serial.print(" N - Right: ");
    Serial.print(right_kg, 2);
    Serial.print(" kg, ");
    Serial.print(right_N, 2);
    Serial.print(" N - Thrust: ");
    Serial.print(thrust_kg, 2);
    Serial.print(" kg, ");
    Serial.print(thrust_N, 2);
    Serial.print(" N - Torque: ");
    Serial.print(torque_kg, 2);
    Serial.print(" kg, ");
    Serial.print(torque_N, 2);
    Serial.print(" N - Current: ");
    Serial.print(current_mA / 1000.0, 2);
    Serial.print(" A - Voltage: ");
    Serial.print(bus_voltage, 2);
    Serial.print(" V - Elec Power: ");
    Serial.print(power_W, 2);
    Serial.println(" W");

    delay(500);
  }

  Serial.println("Test completato.");
  esc.writeMicroseconds(1000);
}