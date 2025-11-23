int ledVol1 = 7;
int ledVol2 = 6;
int ledVol3 = 5;

int ledBri1 = 10;
int ledBri2 = 9;
int ledBri3 = 8;

int potVolumen = A0;
int potBrillo = A1;

int volumenAnterior = -1;
int brilloAnterior = -1;

void setup() {
  pinMode(ledVol1, OUTPUT);
  pinMode(ledVol2, OUTPUT);
  pinMode(ledVol3, OUTPUT);
  
  pinMode(ledBri1, OUTPUT);
  pinMode(ledBri2, OUTPUT);
  pinMode(ledBri3, OUTPUT);
  
  Serial.begin(9600);
  
  encenderTodosLEDs();
  delay(500);
  apagarTodosLEDs();
  
  Serial.println("ARDUINO_INICIADO");
}

void loop() {
  int valorVolumen = analogRead(potVolumen);
  int valorBrillo = analogRead(potBrillo);
  
  int volumenActual = map(valorVolumen, 0, 1023, 0, 100);
  int brilloActual = map(valorBrillo, 0, 1023, 0, 100);
  
  controlarLEDsVolumen(volumenActual);
  
  controlarLEDsBrillo(brilloActual);
  
  if (volumenActual != volumenAnterior) {
    enviarDatosComputadora('V', volumenActual);
    volumenAnterior = volumenActual;
  }
  
  if (brilloActual != brilloAnterior) {
    enviarDatosComputadora('B', brilloActual);
    brilloAnterior = brilloActual;
  }
  
  if (Serial.available() > 0) {
    String mensaje = Serial.readString();
    mensaje.trim();
    
    if (mensaje == "COMPUTADORA_LISTA") {
      indicadorConexionExitosa();
    }
  }
  
  delay(100); 
}

void controlarLEDsVolumen(int porcentaje) {
  digitalWrite(ledVol1, porcentaje > 33 ? HIGH : LOW);
  digitalWrite(ledVol2, porcentaje > 66 ? HIGH : LOW);
  digitalWrite(ledVol3, porcentaje > 90 ? HIGH : LOW);
}

void controlarLEDsBrillo(int porcentaje) {
  digitalWrite(ledBri1, porcentaje > 33 ? HIGH : LOW);
  digitalWrite(ledBri2, porcentaje > 66 ? HIGH : LOW);
  digitalWrite(ledBri3, porcentaje > 90 ? HIGH : LOW);
}

void enviarDatosComputadora(char tipo, int valor) {
  Serial.print(tipo);
  Serial.print(":");
  Serial.println(valor);
}

void indicadorConexionExitosa() {
  for(int i = 0; i < 3; i++) {
    digitalWrite(ledVol1, HIGH);
    digitalWrite(ledBri1, HIGH);
    delay(200);
    digitalWrite(ledVol1, LOW);
    digitalWrite(ledBri1, LOW);
    delay(200);
  }
}

void encenderTodosLEDs() {
  digitalWrite(ledVol1, HIGH);
  digitalWrite(ledVol2, HIGH);
  digitalWrite(ledVol3, HIGH);
  digitalWrite(ledBri1, HIGH);
  digitalWrite(ledBri2, HIGH);
  digitalWrite(ledBri3, HIGH);
}

void apagarTodosLEDs() {
  digitalWrite(ledVol1, LOW);
  digitalWrite(ledVol2, LOW);
  digitalWrite(ledVol3, LOW);
  digitalWrite(ledBri1, LOW);
  digitalWrite(ledBri2, LOW);
  digitalWrite(ledBri3, LOW);
}