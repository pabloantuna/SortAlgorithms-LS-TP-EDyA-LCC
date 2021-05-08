#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./GList/glist.h"
#include "./Persona/persona.h"
#define MAX_LINEA 100
#define SELECTION1 "salidaSelection1.txt"
#define SELECTION2 "salidaSelection2.txt"
#define INSERTION1 "salidaInsertion1.txt"
#define INSERTION2 "salidaInsertion2.txt"
#define MERGE1 "salidaMerge1.txt"
#define MERGE2 "salidaMerge2.txt"

GList leer_personas(FILE * entrada, GList lista) {
  char edadAux[5], nombreAux[MAX_LINEA], paisAux[MAX_LINEA];
  while (!feof(entrada)) {
    fscanf(entrada, "%[^,],", nombreAux);
    fscanf(entrada, "%[^,], ", edadAux);
    fscanf(entrada, "%[^\n]\n", paisAux);
    Persona *persona = persona_crear(nombreAux, paisAux, atoi(edadAux));
    lista = glist_agregar_final(lista, (void *) persona);
  }
  return lista;
}

// Argumento: ArchivoSalidaGenerador
int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("ERROR!\n");
    return -1;
  }
  FILE *entrada = fopen(argv[1], "r");
  GList lista = glist_inicializar();
  lista = leer_personas(entrada, lista);
  fclose(entrada);
  test_algoritmo_sort(SELECTION1, &glist_selectionSort,
                      &compara_edad, lista, &persona_escribir);
  test_algoritmo_sort(SELECTION2, &glist_selectionSort,
                      &compara_largo_lugar_nacimiento, lista,
                      &persona_escribir);
  test_algoritmo_sort(INSERTION1, &glist_insertionSort,
                      &compara_edad, lista, &persona_escribir);
  test_algoritmo_sort(INSERTION2, &glist_insertionSort,
                      &compara_largo_lugar_nacimiento, lista,
                      &persona_escribir);
  test_algoritmo_sort(MERGE1, &glist_mergeSort, &compara_edad,
                      lista, &persona_escribir);
  test_algoritmo_sort(MERGE2, &glist_mergeSort,
                      &compara_largo_lugar_nacimiento, lista,
                      &persona_escribir);
  glist_destruir(lista, &persona_destruir);

  return 0;
}
