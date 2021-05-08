#ifndef __GLIST_H__
#define __GLIST_H__

#include <stddef.h>
#include <stdio.h>
typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
  struct _GNodo *ant;
} GNodo;

typedef struct {
  GNodo *primero;
  GNodo *ultimo;
  int cantidad;
} Extremos;

typedef Extremos *GList;
typedef int (*Compara) (void *dato1, void *dato2);
typedef void (*Destruir) (void *dato);

typedef void (*FuncionVisitante) (void *dato, FILE * salida);
typedef GList(*AlgoritmoSort) (GList lista, Compara c);

/**
 * glist_inicializar: -> GList
 * Esta funcion se encarga de darle espacio a una glist
 * e inicializar sus valores Primero, Ultimo y Cantidad
 */
GList glist_inicializar();

/**
 * glist_copiar: GList -> GList
 * Toma una lista y genera una copia. 
 * La utilizamos para crearnos copias de la lista original y 
 * ordenarlas con diferentes algoritmos y criterios
 */
GList glist_copiar(GList lista);

/**
 * glist_recorrer: GList -> FILE* -> FuncionVisitante 
 * Esta funcion recorre todos los nodos de una lista, haciendo que todos 
 * ellos sean visitados por una funcion. 
 * La utilizamos para imprimir todas las personas de la glist
 */
void glist_recorrer(GList lista, FILE * salida, FuncionVisitante visit);

/**
 * glist_agregar_final: GList -> void* -> GList
 * Esta funcion agrega un elemento (del tipo de la lista) al final de ella
 */
GList glist_agregar_final(GList lista, void *dato);

/**
 * glist_destruir: GList -> Destruir 
 * Se encarga de liberar tanto el espacio del puntero de la lista como el de
 * cada nodo, siendo d la funcion encargada de liberar ese tipo de dato.
 */
void glist_destruir(GList lista, Destruir d);

/**
 * glist_destruir_copia: GList 
 * Hace lo mismo que glist_destruir, con la diferencia de que solo libera 
 * la lista sin destruir los nodos.
 */
void glist_destruir_copia(GList lista);

/**
 * test_algoritmo_sort: char* -> AlgoritmoSort -> Compara -> GList -> FuncionVisitante
 * Ordena la lista y la escribe en un archivo (no modifica la lista pasada como argumento)
 * Ademas, se encarga de tomar los tiempos que tarda cada algoritmo e imprimirlos en el archivo de salida
 */
void test_algoritmo_sort(char *nombreArchivo, AlgoritmoSort sort, Compara c,
                         GList lista, FuncionVisitante visit);

/**
 * node_swap: GNodo* -> GNodo* 
 * Consume dos nodos e intercambia los valores de sus datos.
 */
void node_swap(GNodo * nodo1, GNodo * nodo2);

/**
 * glist_selectionSort: GList -> Compara -> Glist
 * Ordena la lista utilizando el algoritmo de Selection Sort.
 */
GList glist_selectionSort(GList lista, Compara c);

/**
 * glist_insertar_nodo: GNodo* -> GNodo* -> int -> GList -> GList
 * Inserta el nodoAInsertar antes del nodo Destino.
 */
GList glist_insertar_nodo(GNodo * nodoAInsertar, GNodo * nodoDest, int noInicio,
                          GList lista);

/**
 * glist_insertionSort: GList -> Compara -> Glist
 * Ordena la lista utilizando el algoritmo de Insertion Sort.
 */
GList glist_insertionSort(GList lista, Compara c);

/**
 * glist_append: GNodo* -> GList -> GList
 * Esta funcion toma un puntero a un nodo y una lista, y agrega
 * el nodo al principio de la lista.
 */
GList glist_append(GNodo * nodo, GList lista);

/**
 * glist_merge: GList -> GList -> Compara -> Glist
 * Esta funcion toma dos listas y un metodo de comparacion, y devuelve una 
 * lista con los elementos de ambas, ordenados segun el criterio.
 */
GList glist_merge(GList lista1, GList lista2, Compara c);

/**
 * gList_split: GList -> GList
 * Funcion que devuelve aproximadamente la mitad derecha de la lista
 * y deja la otra lista como aproximadamente la mitad izquierda.
 */
GList glist_split(GList lista);

/**
 * glist_mergeSort: GList -> Compara -> GList
 * Ordena la lista utilizando el algoritmo de Merge Sort.
 */
GList glist_mergeSort(GList lista, Compara c);

#endif
