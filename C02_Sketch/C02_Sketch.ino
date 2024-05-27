//Bibliotheken, NICHT ÄNDERN.
#include "MHZ19.h"                                        
#include <SoftwareSerial.h>               

// Pin Nummern auf dem Arduino für die LEDs
const int roteLEDPinNummer = 5;    //Ansteuerung des roten Lichtes
const int gelbeLEDPinNummer = 6;   //Ansteuerung des gelben Lichtes
const int grueneLEDPinNummer = 7;  //Ansteuerung des grünen Lichtes

// Pin Nummern auf dem Arduino für den CO2-Sensor
#define RXPINNummer 11  // RX Anschluss des CO2-Sensors
#define TXPINNummer 10  // TX Anschluss des CO2-Sensors        
#define BAUDRATE 9600   // Baudrate des CO2-Sensors. NICHT ÄNDERN!!                                  

//Die Variable co2Sensor steht hier als Stellvertreter für den CO2-Sensor
MHZ19 co2Sensor; 

//Stellt im Programm die Verbindung zum RX / TX Anschluss des Sensors her.
SoftwareSerial co2Serial(TXPINNummer, RXPINNummer); 

void setup()
{
    // Einrichtung und Start der Datenauswertung. NICHT ÄNDERN!
    Serial.begin(9600); 
    co2Serial.begin(BAUDRATE);             
    co2Sensor.begin(co2Serial);                        
    co2Sensor.autoCalibration();    
    
    // Stellt die PINs für die Ampel als Output ein. Das heißt, es werden Signale zur Ampel geschickt.
    pinMode(roteLEDPinNummer, OUTPUT);
    pinMode(gelbeLEDPinNummer, OUTPUT);
    pinMode(grueneLEDPinNummer, OUTPUT);  

    //Überschrift in der CSV Zeile
    Serial.println("Zeitstempel;CO2-Wert in ppm");                       
}

void loop()
{
    // In dieser Variable werden später die CO2 Werte gespeichert. Die Einheit dafür ist ppm ((Parts per Million) Teile pro Millionen Teile)
    int co2WertInPPM; 

    // An dieser Stelle wird nun der aktuelle CO2 Wert ausgelesen.
    co2WertInPPM = co2Sensor.getCO2();                             
    
    // Die CO2-Daten werden als mit einem Zeitstempel versehen
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

    // Bis zur nächsten Auslesung sollen 2000 Millisekunden = 2 Sekunden gewartet werden.
    delay(2000);
}