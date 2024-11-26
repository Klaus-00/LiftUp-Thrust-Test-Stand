#include "HX711.h"

// Pin per la cella di carico sinistra
#define DT_PIN 3 // Pin Data
#define SCK_PIN 2 // Pin Clock

// Oggetto per la cella di carico
HX711 scale_left;

// Variabili per calibrazione
float calibration_factor_left = 217000.0; // Nuovo fattore di calibrazione calcolato

void setup() {
  Serial.begin(9600);
  Serial.println("Avvio lettura cella di carico sinistra...");

  // Configura la cella di carico
  scale_left.begin(DT_PIN, SCK_PIN);

  // Controlla che la cella sia pronta
  while (!scale_left.is_ready()) {
    Serial.println("Cella di carico sinistra non pronta. Attendi...");
    delay(500);
  }
  Serial.println("Cella di carico sinistra pronta!");

  // Azzeramento e calibrazione iniziale
  scale_left.set_scale(calibration_factor_left);
  scale_left.tare(); // Azzeramento della bilancia
  Serial.println("Bilancia azzerata.");
}

void loop() {
  if (scale_left.is_ready()) {
    // Lettura in kg
    float weight_left = scale_left.get_units(10); // Media su 10 letture per maggiore precisione

    // Stampa del valore
    Serial.print("Peso letto dalla cella sinistra: ");
    Serial.print(weight_left, 2);
    Serial.println(" kg");
  } else {
    Serial.println("Errore: La cella di carico sinistra non è pronta.");
  }

  delay(500); // Attesa di 500 ms tra le letture
}