#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Pines para el control del puente H
#define ENA 15  // PWM Motor A
#define IN1 16  // Dirección Motor A
#define IN2 17

#define ENB 5   // PWM Motor B
#define IN3 2   // Dirección Motor B
#define IN4 4

const int Frecuencia = 115200;  // Velocidad de comunicación por Bluetooth
char dato;

// Funciones de movimiento
void moverAtras(int velocidad) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidad); // Motor A
  analogWrite(ENB, velocidad); // Motor B
}

void moverAdelante(int velocidad) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
}

void girarIzquierda(int velocidad) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
}

void girarDerecha(int velocidad) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
}

void detener() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void setup() {
  SerialBT.begin("Speckles"); //Elige los nombres diponibles: Advincula City, Makunga, Ludog, Speckles
  Serial.begin(115200);

  // Configuración de pines
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
    if (SerialBT.available()) {
      dato = SerialBT.read();
      
      switch (dato) {
        case 'F': // Avanzar
          moverAdelante(255);
          Serial.println("Avanzando");
          break;
        case 'B': // Retroceder
          moverAtras(255);
          Serial.println("Retrocediendo");
          break;
        case 'L': // Giro izquierda
          girarIzquierda(255);
          Serial.println("Girando Izquierda");
          break;
        case 'R': // Giro derecha
          girarDerecha(255);
          Serial.println("Girando Derecha");
          break;
        case 'P': // Parar
          detener();
          Serial.println("Detenido");
          break;
        default:
          Serial.println("Comando no reconocido");
          break;
      }
    }
}
