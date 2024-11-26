#include "HX711.h"

// Pin per la cella di carico sinistra
#define DT_PIN 4 // Pin Data
#define SCK_PIN 5 // Pin Clock

// Oggetto per la cella di carico
HX711 scale_right;

// Variabili per calibrazione
float calibration_factor_right = 211000.0; // Nuovo fattore di calibrazione calcolato

void setup() {
  Serial.begin(9600);
  Serial.println("Avvio lettura cella di carico destra...");

  // Configura la cella di carico
  scale_right.begin(DT_PIN, SCK_PIN);

  // Controlla che la cella sia pronta
  while (!scale_right.is_ready()) {
    Serial.println("Cella di carico destra non pronta. Attendi...");
    delay(500);
  }
  Serial.println("Cella di carico destra pronta!");

  // Azzeramento e calibrazione iniziale
  scale_right.set_scale(calibration_factor_right);
  scale_right.tare(); // Azzeramento della bilancia
  Serial.println("Bilancia azzerata.");
}

void loop() {
  if (scale_right.is_ready()) {
    // Lettura in kg
    float weight_right = scale_right.get_units(10); // Media su 10 letture per maggiore precisione

    // Stampa del valore
    Serial.print("Peso letto dalla cella destra: ");
    Serial.print(weight_right, 2);
    Serial.println(" kg");
  } else {
    Serial.println("Errore: La cella di carico destra non è pronta.");
  }

  delay(500); // Attesa di 500 ms tra le letture
}