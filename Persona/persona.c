#include "persona.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void persona_escribir(void *dato, FILE * salida) {
  Persona *persona = (Persona *) dato;
  fprintf(salida, "%s, %d, %s\n", persona->nombre, persona->edad,
          persona->lugarDeNacimiento);
}

Persona *persona_crear(char *nombre, char *lugarNacimiento, int edad) {
  Persona *persona = malloc(sizeof(Persona));
  persona->lugarDeNacimiento =
      malloc(sizeof(char) * (strlen(lugarNacimiento) + 1));
  persona->nombre = malloc(sizeof(char) * (strlen(nombre) + 1));
  strcpy(persona->nombre, nombre);
  strcpy(persona->lugarDeNacimiento, lugarNacimiento);
  persona->edad = edad;
  return persona;
}

void persona_destruir(void *_dato) {
  Persona *dato = (Persona *) _dato;
  free(dato->lugarDeNacimiento);
  free(dato->nombre);
  free(dato);
}

//Funciones de comparacion
int compara_edad(void *_dato1, void *_dato2) {
  Persona *dato1, *dato2;
  dato1 = (Persona *) _dato1;
  dato2 = (Persona *) _dato2;
  return dato1->edad - dato2->edad;
}

int compara_largo_lugar_nacimiento(void *_dato1, void *_dato2) {
  Persona *dato1, *dato2;
  dato1 = (Persona *) _dato1;
  dato2 = (Persona *) _dato2;
  return strlen(dato1->lugarDeNacimiento) - strlen(dato2->lugarDeNacimiento);
}

