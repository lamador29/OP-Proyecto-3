import serial
import time
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume
from ctypes import cast, POINTER
from comtypes import CLSCTX_ALL
import screen_brightness_control as sbc

# CONFIG
PORT = "COM4"   # ← Cambia según tu PC
BAUD = 9600

def set_volume(percent):
    devices = AudioUtilities.GetSpeakers()
    interface = devices.Activate(IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
    volume = cast(interface, POINTER(IAudioEndpointVolume))

    # pycaw usa valores -65.25 a 0.0 en decibeles
    vol_range = volume.GetVolumeRange()
    
    min_vol = vol_range[0]
    max_vol = vol_range[1]

    new_vol = min_vol + (percent / 100) * (max_vol - min_vol)
    volume.SetMasterVolumeLevel(new_vol, None)

def set_brightness(percent):
    try:
        sbc.set_brightness(percent)
    except:
        pass  
    
def map_value(raw):
    return int((raw / 1023) * 100)

def main():
    try:
        ser = serial.Serial(PORT, BAUD, timeout=1)
    except:
        print("ERROR: No se pudo abrir el puerto COM")
        return

    time.sleep(2)
    print("Driver iniciado. Esperando datos de Arduino...")

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode().strip()
            
            try:
                parts = line.split()
                potV = int(parts[0].split(":")[1])
                potB = int(parts[1].split(":")[1])
            except:
                continue

            volume = map_value(potV)
            brightness = map_value(potB)

            set_volume(volume)
            set_brightness(brightness)

            ser.write(f"{volume},{brightness}\n".encode())

            print(f"Volumen={volume}%   Brillo={brightness}%")

        time.sleep(0.01)

if __name__ == "__main__":
    main()
