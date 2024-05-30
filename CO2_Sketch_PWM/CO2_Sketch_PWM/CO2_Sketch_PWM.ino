//Autor: Daniel Katzberg

//Bibliotheken, NICHT ÄNDERN.
#include <Arduino.h>                         

// Pin Nummern auf dem Arduino für die LEDs
const int roteLEDPinNummer = 5;    //Ansteuerung des roten Lichtes
const int gelbeLEDPinNummer = 6;   //Ansteuerung des gelben Lichtes
const int grueneLEDPinNummer = 7;  //Ansteuerung des grünen Lichtes

// Pin Nummern auf dem Arduino für den CO2-Sensor    
#define BAUDRATE 9600   // Baudrate des CO2-Sensors. NICHT ÄNDERN!!                                  

unsigned long stoppuhr = 0; //Damit in gleichen Zeitabständen ein CO2 - Wert erhoben wird.
int PWNPinNummer = 10; //Digitaler Pin
int maxPPMWert = 5000; //Der maximale PPM
unsigned long pwmZeit;

void setup()
{   
    // Stellt die PINs für die Ampel als Output ein. Das heißt, es werden Signale zur Ampel geschickt.
    pinMode(roteLEDPinNummer, OUTPUT);
    pinMode(gelbeLEDPinNummer, OUTPUT);
    pinMode(grueneLEDPinNummer, OUTPUT);  

    pinMode(PWNPinNummer, INPUT);

    // Einrichtung und Start der Datenauswertung. NICHT ÄNDERN!
    Serial.begin(BAUDRATE); 

    //Überschrift in der CSV Zeile
    Serial.println("Zeitstempel;CO2-Wert in ppm");                       
}

void loop()
{
    if (millis() - stoppuhr >= 2000) {

      // In dieser Variable werden später die CO2 Werte gespeichert. Die Einheit dafür ist ppm ((Parts per Million) Teile pro Millionen Teile)
      int co2WertInPPM; 

      // An dieser Stelle wird nun der aktuelle CO2 Wert berechnet.
      pwmZeit = pulseIn(PWNPinNummer, HIGH, 2000000) / 1000;
      float pulseAnteil = pwmZeit / 1004.0; //Die 1004 kommt von der kompletten Signallänge. Siehe hier: https://wolles-elektronikkiste.de/en/mh-z14-and-mh-z19-co2-sensors
      co2WertInPPM = maxPPMWert * pulseAnteil;                     
      
      // Die CO2-Daten werden als mit einem ZeitstempemaxPPMWertl versehen
      // Eine Zeile (= ein Datum) könnte dann so aussehen:
      // 152334;723
      // Dies entspricht dem CSV - Dateistandard.
      Serial.print(millis());   
      Serial.print(";");
      Serial.println(co2WertInPPM);             
      
      // Der Co2 - Wert ist über 1400 ppm, so leuchtet die rote LED.
      // LOW bedeutet: LED ist aus
      // HIGH bedeutet: LED ist an
      if (co2WertInPPM >= 1400) {
        digitalWrite(roteLEDPinNummer, HIGH);
        digitalWrite(gelbeLEDPinNummer, LOW);
        digitalWrite(grueneLEDPinNummer, LOW);
      }

      //Ist der CO2 Wert zwischen 1000 und 1400, so leuchtet die gelbe LED.
      if (co2WertInPPM < 1400 && co2WertInPPM >= 1000) {
        digitalWrite(roteLEDPinNummer, LOW);
        digitalWrite(gelbeLEDPinNummer, HIGH);
        digitalWrite(grueneLEDPinNummer, LOW);
      }

      //Ist der CO2 Wert kleiner als 1000 die grüne LED.
      if (co2WertInPPM < 1000) {
        digitalWrite(roteLEDPinNummer, LOW);
        digitalWrite(gelbeLEDPinNummer, LOW);
        digitalWrite(grueneLEDPinNummer, HIGH);
      }

      stoppuhr = millis();
    }
}