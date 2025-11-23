import serial
import time
import screen_brightness_control as sbc
import os
import threading

PORT = "COM6"     
BAUD = 9600

def set_volume(percent):
    try:
        os.system(f"nircmd.exe setsysvolume {int(percent * 655.35)}")
    except Exception as e:
        print("Error al cambiar volumen:", e)

brillo_actual = 0
brillo_objetivo = 0

def brillo_worker():
    global brillo_actual, brillo_objetivo
    while True:
        if brillo_actual != brillo_objetivo:
            try:
                sbc.set_brightness(brillo_objetivo)
                brillo_actual = brillo_objetivo
            except:
                pass
        time.sleep(0.005) 

threading.Thread(target=brillo_worker, daemon=True).start()

def main():
    global brillo_objetivo

    try:
        ser = serial.Serial(PORT, BAUD, timeout=1)
    except:
        print("ERROR: No se pudo abrir COM6")
        return

    time.sleep(2)
    print("Driver iniciado. Esperando datos...")

    volumen = 0

    last_brightness_time = time.time()

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode().strip()
            if not line:
                continue

            print("Recibido:", line)

            if line.startswith("V:"):
                volumen = int(line.split(":")[1])
                set_volume(volumen)

            # BRILLO
            elif line.startswith("B:"):
                nuevo_brillo = int(line.split(":")[1])
                brillo_objetivo = nuevo_brillo

            print(f"Volumen={volumen}%   Brillo={brillo_objetivo}%\n")

        time.sleep(0.0001)

if __name__ == "__main__":
    main()
