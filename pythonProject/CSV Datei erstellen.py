# Autor: Daniel Katzberg
import serial
import csv
import time

# Serielle Verbindung zum Arduino herstellen
# Passe 'COM3' an den richtigen Port deines Arduino an
auslesenCSVInformationenArduino = serial.Serial('COM3', 9600)
time.sleep(2)  # Warte 2 Sekunden, bis die serielle Verbindung zum Arduino aufgebaut ist

# CSV-Datei 'CO2Daten.cvs' im gleichen Ordner zum Beschreiben öffnen
with open('CO2Daten.csv', 'w', newline='') as csvfile:
    csvwriter = csv.writer(csvfile)

    try:
        while True:
            # CSV-Zeile von der seriellen Schnittstelle des Arduino lesen
            line = auslesenCSVInformationenArduino.readline().decode('utf-8').strip()

            # Daten in eine Liste konvertieren
            data = line.split(';')

            # Mit den Daten eine weitere Zeile in die CSV-Datei schreiben
            csvwriter.writerow(data)
            auslesenCSVInformationenArduino.flush()

            # Ausgabe zur Kontrolle auf der Konsole
            print(data)

    except KeyboardInterrupt:
        # Skript mit Strg+C beenden
        print("Beenden")
        auslesenCSVInformationenArduino.close()