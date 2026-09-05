#include <Arduino.h>

// Ejemplo de uso de display 7 segmentos (seccion 5.3.3): banner con el
// alfabeto Siekoo (Figura 57) mostrando los apellidos del grupo en 4 digitos.
// Integrantes: Cantillo, Polania, Pedroza, Martinez
// Wiring: proyecto ESP32 7 segment 4 v2 (comun catodo), profe Nazhir Amaya Tejera

const int SEG_A = 5, SEG_B = 4, SEG_C = 19, SEG_D = 25, SEG_E = 26, SEG_F = 33, SEG_G = 32;
const int DIG[4] = {22, 21, 15, 2}; // DIG1..DIG4, comun catodo: LOW activa el digito

const char MENSAJE[] = "CANTILLO POLANIA PEDROZA MARTINEZ ";
int posicion = 0;

void apagarSegmentos() {
  digitalWrite(SEG_A, LOW);
  digitalWrite(SEG_B, LOW);
  digitalWrite(SEG_C, LOW);
  digitalWrite(SEG_D, LOW);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_F, LOW);
  digitalWrite(SEG_G, LOW);
}

// Alfabeto Siekoo (Figura 57): que segmentos enciende cada letra
void mostrarCaracter(char letra) {
  apagarSegmentos();
  switch (letra) {
    case 'A':
      digitalWrite(SEG_A, HIGH); digitalWrite(SEG_B, HIGH); digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_E, HIGH); digitalWrite(SEG_F, HIGH); digitalWrite(SEG_G, HIGH);
      break;
    case 'C':
      digitalWrite(SEG_A, HIGH); digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_E, HIGH); digitalWrite(SEG_F, HIGH);
      break;
    case 'D':
      digitalWrite(SEG_B, HIGH); digitalWrite(SEG_C, HIGH); digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_E, HIGH); digitalWrite(SEG_G, HIGH);
      break;
    case 'E':
      digitalWrite(SEG_A, HIGH); digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_E, HIGH); digitalWrite(SEG_F, HIGH); digitalWrite(SEG_G, HIGH);
      break;
    case 'I':
      digitalWrite(SEG_B, HIGH); digitalWrite(SEG_C, HIGH);
      break;
    case 'L':
      digitalWrite(SEG_D, HIGH); digitalWrite(SEG_E, HIGH); digitalWrite(SEG_F, HIGH);
      break;
    case 'M':
      digitalWrite(SEG_A, HIGH); digitalWrite(SEG_C, HIGH); digitalWrite(SEG_E, HIGH);
      break;
    case 'N':
      digitalWrite(SEG_C, HIGH); digitalWrite(SEG_E, HIGH); digitalWrite(SEG_G, HIGH);
      break;
    case 'O':
      digitalWrite(SEG_C, HIGH); digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_E, HIGH); digitalWrite(SEG_G, HIGH);
      break;
    case 'P':
      digitalWrite(SEG_A, HIGH); digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_E, HIGH); digitalWrite(SEG_F, HIGH); digitalWrite(SEG_G, HIGH);
      break;
    case 'R':
      digitalWrite(SEG_E, HIGH); digitalWrite(SEG_G, HIGH);
      break;
    case 'T':
      digitalWrite(SEG_D, HIGH); digitalWrite(SEG_E, HIGH);
      digitalWrite(SEG_F, HIGH); digitalWrite(SEG_G, HIGH);
      break;
    case 'Z':
      digitalWrite(SEG_A, HIGH); digitalWrite(SEG_B, HIGH); digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_E, HIGH); digitalWrite(SEG_G, HIGH);
      break;
    default:
      break; // espacio: los 7 segmentos quedan apagados
  }
}

void setup() {
  int pines[] = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, DIG[0], DIG[1], DIG[2], DIG[3]};
  for (int i = 0; i < 11; i++) {
    pinMode(pines[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    digitalWrite(DIG[i], HIGH); // los 4 digitos apagados al inicio
  }
}

void loop() {
  int largo = sizeof(MENSAJE) - 1;
  for (int barrido = 0; barrido < 60; barrido++) {
    for (int d = 0; d < 4; d++) {
      char letra = MENSAJE[(posicion + d) % largo];
      mostrarCaracter(letra);
      digitalWrite(DIG[d], LOW);
      delay(3);
      digitalWrite(DIG[d], HIGH);
    }
  }
  posicion = (posicion + 1) % largo;
}