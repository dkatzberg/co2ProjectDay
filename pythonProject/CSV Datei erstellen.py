import serial
import csv
import time

# Serielle Verbindung zum Arduino herstellen
ser = serial.Serial('COM3', 9600)  # Passe 'COM3' an den richtigen Port deines Arduino an
time.sleep(2)  # Warte, bis die serielle Verbindung aufgebaut ist

# CSV-Datei öffnen
with open('CO2Daten.csv', 'w', newline='') as csvfile:
    csvwriter = csv.writer(csvfile)

    # Schreibe die Header-Zeile (optional)
     # csvwriter.writerow(['Sensor1', 'Sensor2'])

    try:
        while True:
            # Zeile von der seriellen Schnittstelle lesen
            line = ser.readline().decode('utf-8').strip()

            # Daten in eine Liste konvertieren
            data = line.split(';')

            # Daten in die CSV-Datei schreiben
            csvwriter.writerow(data)
            ser.flush()

            # Ausgabe zur Kontrolle
            print(data)

    except KeyboardInterrupt:
        # Skript mit Strg+C beenden
        print("Beenden")
        ser.close()