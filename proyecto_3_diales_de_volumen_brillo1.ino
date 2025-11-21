int ledvol1 = 7;
int ledvol2 = 6;
int ledvol3 = 5;

int ledbri1 = 10;
int ledbri2 = 9;
int ledbri3 = 8;

int potvol = A0;
int potbri = A1;

void setup() {
  // LEDs volumen
  pinMode(ledvol1, OUTPUT);
  pinMode(ledvol2, OUTPUT);
  pinMode(ledvol3, OUTPUT);

  // LEDs brillo
  pinMode(ledbri1, OUTPUT);
  pinMode(ledbri2, OUTPUT);
  pinMode(ledbri3, OUTPUT);

  // Potenciómetros
  pinMode(potvol, INPUT);
  pinMode(potbri, INPUT);
}

void loop() {
  // Lecturas de potenciómetros
  int valorVol = analogRead(potvol);  // 0 a 1023
  int valorBri = analogRead(potbri);  // 0 a 1023

  // UMBRALES 25%, 50%, 75%
  int umbral1 = 256;
  int umbral2 = 512;
  int umbral3 = 768;

  // --------------------------
  // LEDs de VOLUMEN (A0)
  // --------------------------
  digitalWrite(ledvol1, valorVol >= umbral1 ? HIGH : LOW);
  digitalWrite(ledvol2, valorVol >= umbral2 ? HIGH : LOW);
  digitalWrite(ledvol3, valorVol >= umbral3 ? HIGH : LOW);

  // --------------------------
  // LEDs de BRILLO (A1)
  // --------------------------
  digitalWrite(ledbri1, valorBri >= umbral1 ? HIGH : LOW);
  digitalWrite(ledbri2, valorBri >= umbral2 ? HIGH : LOW);
  digitalWrite(ledbri3, valorBri >= umbral3 ? HIGH : LOW);
}
