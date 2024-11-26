# **README - Calibrazione delle Celle di Carico**

Questo file descrive il processo di calibrazione delle celle di carico utilizzate nel Thrust Test Stand. La calibrazione è essenziale per ottenere letture accurate delle forze applicate.

## **Obiettivo**
- Determinare il fattore di calibrazione specifico per ogni cella di carico.
- Garantire che le misurazioni siano espresse correttamente in chilogrammi (kg) o Newton (N).

---

## **Hardware Necessario**
- Arduino Uno (o compatibile).
- Modulo HX711 (Amplificatore per celle di carico).
- Celle di carico: 
  - Sinistra.
  - Destra.
  - Thrust.
- Peso noto (preferibilmente tra 2 e 5 kg per precisione).
- Cavi di collegamento.
- Breadboard (opzionale).

---

## **Pinout**

### **Cella Sinistra**
- **DT**: Pin 3.
- **SCK**: Pin 2.

### **Cella Destra**
- **DT**: Pin 4.
- **SCK**: Pin 5.

### **Cella Thrust**
- **DT**: Pin 6.
- **SCK**: Pin 7.

---

## **Procedura di Calibrazione**

1. **Collegamento Hardware:**
   - Collega ogni cella di carico al modulo HX711.
   - Assicurati che i cavi siano ben saldati e collegati ai pin indicati.

2. **Caricamento del Codice:**
   - Usa il codice di calibrazione fornito per ciascuna cella (ad esempio, Sinistra, Destra, Thrust).
   - Modifica il valore del `calibration_factor` con il valore iniziale suggerito.

3. **Test con un Peso Noto:**
   - Posiziona il peso noto sopra la cella di carico.
   - Avvia il monitor seriale e osserva i valori letti.

4. **Calcolo del Fattore di Calibrazione:**
   - Se il peso letto non corrisponde al peso noto:
     ```
     Nuovo fattore di calibrazione = Fattore attuale * (Peso noto / Peso letto)
     ```
   - Aggiorna il fattore di calibrazione nel codice e ricaricalo sull’Arduino.

5. **Ripetizione della Procedura:**
   - Ripeti i passi precedenti per ogni cella di carico.

---

## **Output del Monitor Serial**
Durante la calibrazione, il monitor seriale mostrerà i seguenti valori:
- **Peso Letto**: Valore in chilogrammi calcolato dalla cella di carico.
- Messaggi diagnostici: Informazioni sull’azzeramento o eventuali errori.

Esempio: