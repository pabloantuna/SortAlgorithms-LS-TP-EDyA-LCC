#ifndef __PERSONA_H__
#define __PERSONA_H__

#include <stddef.h>
#include <stdio.h>

typedef struct {
  char *nombre;
  int edad;
  char *lugarDeNacimiento;
} Persona;

/**
 * persona_escribir: void* -> FILE*
 * Escribe una persona dada en un archivo de salida dado
 */
void persona_escribir(void *persona, FILE * salida);

/**
 * persona_crear: char* -> char* -> int -> Persona*
 * Crea una persona
 */
Persona *persona_crear(char *nombre, char *lugarNacimiento, int edad);

/**
 * persona_destruir: void*
 * Destruye una persona
 */
void persona_destruir(void *_dato);

/**
 * compara_edad: void* -> void* -> int
 * Funcion de comparacion en base a la edad
 */
int compara_edad(void *_dato1, void *_dato2);

/**
 * compara_largo_lugar_nacimiento: void* -> void* -> int
 * Funcion de comparacion en base al largo del lugar de nacimiento
 */
int compara_largo_lugar_nacimiento(void *_dato1, void *_dato2);

#endif
