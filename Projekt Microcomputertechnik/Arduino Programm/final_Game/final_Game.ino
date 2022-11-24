#include <LedControl.h>

//Funktionsdeklarationen
bool checke_spielfeldgrenzen(int y, int x);
bool mache_einen_richtungsschritt(int *y, int *x);


int AnzahlMatrix = 4;                              //Anzahl der LED-Matrix des "Display" Moduls

LedControl LEDMatrix = LedControl(13, 14, 15, 4);  //Anschlüsse der LED Matrix definieren
/*
VCC → 5V
GND
Pin 12 → DATA IN Pin
Pin 10 → CLK Pin
Pin 11 → CS Pin
*/

//Definition der Taster
#define taster_L 46
#define taster_R 44
#define taster_O 34
#define taster_U 32
#define taster_Quit 26

//Jede Einzelne LED Matrix besteht aus 8x8 LEDs.
//Die inreiheliegenden LEDs wurden im folgenden Programm, für jede Matrix, jeweils mit den Indizes von 0 bis 7 angesprochen.

// Startwert des zu steuernden Pin definieren
int y = 4;
int x = 4;
int Matrix = 0;

int n = 0;

// Variable für den Status des Programms (aktiv->true/beendet->false)                                    
bool status;

//Variablen der Zeit                                  
float VerstricheneZeit;
float StartZeit;

void setup() {
  StartZeit = millis();             
  Serial.begin(9600);              //Serieller Monitor Start
  randomSeed(analogRead(5));       //Zufallsgenerator Start
  
  for (int i = 0; i <= AnzahlMatrix; i++) {
    LEDMatrix.shutdown(i, false);  // Matrix "aufwecken"
    LEDMatrix.clearDisplay(i);     // Matrix clear
  }
  
  pinMode(taster_L, INPUT);  // Pins als Input "Lesepins" definieren
  pinMode(taster_R, INPUT);
  pinMode(taster_O, INPUT);
  pinMode(taster_U, INPUT);
  pinMode(taster_Quit, INPUT);
  status = true;             // Variable für den Status des Programms (aktiv->true/beendet->false)
  ParcoursBauen();           //Funktion ParcoursBauen aufrufen
}

void ParcoursBauen() {
  int AnzahlLED = 4;
  int Minimum = 0;
  int Maximum = 7;

  for (int i = 0; i < AnzahlLED; i++) {
    int Spalter = random(Minimum, Maximum);
    int Zeiler = random(Minimum, Maximum);
    int Matrixr = random(0, 0);
    LEDMatrix.setLed(Matrixr, Spalter, Zeiler, true);         //Zufällig ausgewählte LED anschalten
  }
}

void loop() {                         
  LEDMatrix.setLed(0, x, y, true);                           //Startposition anschalten
  while (status == true) {
    status = mache_einen_richtungsschritt(&y, &x);
  }
  while (status == false) {
    if (n == 0) {
      // Zeit berechnen
      float Sekunden;
      VerstricheneZeit = millis() - StartZeit;
      Sekunden = VerstricheneZeit / 1000;
      String GesamtSekunden = String(Sekunden);

      // . durch , ersetzen
      GesamtSekunden.replace(".", ",");

      // Ausgabe im Seriellen Monitor
      Serial.println("Sekunden insgesamt: " + GesamtSekunden + " Sekunden");
      n += 1;
    }
    return 0;
  }
}
