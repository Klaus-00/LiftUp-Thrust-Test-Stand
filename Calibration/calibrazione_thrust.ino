#include "HX711.h"

// Pin per la cella di carico sinistra
#define DT_PIN 6 // Pin Data
#define SCK_PIN 7 // Pin Clock

// Oggetto per la cella di carico
HX711 scale_thrust;

// Variabili per calibrazione
float calibration_factor_thrust = -214000.0; // Nuovo fattore di calibrazione calcolato

void setup() {
  Serial.begin(9600);
  Serial.println("Avvio lettura cella di carico destra...");

  // Configura la cella di carico
  scale_thrust.begin(DT_PIN, SCK_PIN);

  // Controlla che la cella sia pronta
  while (!scale_thrust.is_ready()) {
    Serial.println("Cella di carico thrust non pronta. Attendi...");
    delay(500);
  }
  Serial.println("Cella di carico thrust pronta!");

  // Azzeramento e calibrazione iniziale
  scale_thrust.set_scale(calibration_factor_thrust);
  scale_thrust.tare(); // Azzeramento della bilancia
  Serial.println("Bilancia azzerata.");
}

void loop() {
  if (scale_thrust.is_ready()) {
    // Lettura in kg
    float weight_thrust = scale_thrust.get_units(10); // Media su 10 letture per maggiore precisione

    // Stampa del valore
    Serial.print("Peso letto dalla cella thrust: ");
    Serial.print(weight_thrust, 2);
    Serial.println(" kg");
  } else {
    Serial.println("Errore: La cella di carico thrust non è pronta.");
  }

  delay(500); // Attesa di 500 ms tra le letture
}