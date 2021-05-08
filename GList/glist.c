#include "glist.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

GList glist_inicializar() {
  GList lista = malloc(sizeof(Extremos));
  lista->primero = NULL;
  lista->ultimo = NULL;
  lista->cantidad = 0;
  return lista;
}

GList glist_copiar(GList lista) {
  GList nuevaLista = glist_inicializar();
  GNodo *nodoAux = lista->primero;
  for (; nodoAux != NULL; nodoAux = nodoAux->sig)
    nuevaLista = glist_agregar_final(nuevaLista, nodoAux->dato);

  return nuevaLista;
}

void glist_recorrer(GList lista, FILE * salida, FuncionVisitante visit) {
  GNodo *nodoAux = lista->primero;
  for (; nodoAux != NULL; nodoAux = nodoAux->sig)
    visit(nodoAux->dato, salida);
}

GList glist_agregar_final(GList lista, void *dato) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;
  nuevoNodo->ant = lista->ultimo;
  if (lista->ultimo != NULL)
    lista->ultimo->sig = nuevoNodo;
  if (lista->primero == NULL)
    lista->primero = nuevoNodo;
  lista->ultimo = nuevoNodo;
  lista->cantidad++;
  return lista;
}

void glist_destruir(GList lista, Destruir d) {
  GNodo *nodoAux = lista->primero;
  while (nodoAux != NULL) {
    d(nodoAux->dato);
    lista->primero = nodoAux->sig;
    free(nodoAux);
    nodoAux = lista->primero;
  }
  free(lista);
}

void glist_destruir_copia(GList lista) {
  GNodo *nodoAux = lista->primero;
  while (nodoAux != NULL) {
    lista->primero = nodoAux->sig;
    free(nodoAux);
    nodoAux = lista->primero;
  }
  free(lista);
}

void test_algoritmo_sort(char *nombreArchivo, AlgoritmoSort sort, Compara c,
                         GList lista, FuncionVisitante visit) {
  FILE *salida = fopen(nombreArchivo, "w");
  GList listaCopia = glist_copiar(lista);
  clock_t start_t;
  start_t = clock();
  listaCopia = sort(listaCopia, c);
  start_t = clock() - start_t;
  double tiempo = ((double) start_t) / CLOCKS_PER_SEC;
  fprintf(salida, "Tiempo: %f\n", tiempo);
  glist_recorrer(listaCopia, salida, visit);
  fclose(salida);
  glist_destruir_copia(listaCopia);
}

void node_swap(GNodo * nodo1, GNodo * nodo2) {
  void *aux = nodo1->dato;
  nodo1->dato = nodo2->dato;
  nodo2->dato = aux;
}

GList glist_selectionSort(GList lista, Compara c) {
  GNodo *nodoAux = lista->primero, *nodoAux2, *nodoMin = nodoAux;
  for (; nodoAux != lista->ultimo->ant; nodoAux = nodoAux->sig) {
    nodoAux2 = nodoAux->sig;
    nodoMin = nodoAux;
    for (; nodoAux2 != NULL; nodoAux2 = nodoAux2->sig) {
      if (c(nodoMin->dato, nodoAux2->dato) > 0)
        nodoMin = nodoAux2;
    }
    if (nodoMin != nodoAux)
      node_swap(nodoAux, nodoMin);
  }
  return lista;
}

GList glist_insertar_nodo(GNodo * nodoAInsertar, GNodo * nodoDest, int noInicio,
                          GList lista) {
  if (nodoDest != nodoAInsertar->ant) {
    // Si inserto en el inicio de la lista
    if (!noInicio) {
      // Si inserto el ultimo
      if (nodoAInsertar == lista->ultimo) {
        nodoAInsertar->sig = lista->primero;
        nodoAInsertar->ant->sig = NULL;
        lista->ultimo = nodoAInsertar->ant;
      } else {
        nodoAInsertar->ant->sig = nodoAInsertar->sig;
        nodoAInsertar->sig->ant = nodoAInsertar->ant;
        nodoAInsertar->sig = lista->primero;
      }
      nodoAInsertar->ant = NULL;
      lista->primero->ant = nodoAInsertar;
      lista->primero = nodoAInsertar;
    } else {
      // Si inserto el ultimo
      if (nodoAInsertar == lista->ultimo) {
        nodoAInsertar->ant->sig = NULL;
        lista->ultimo = nodoAInsertar->ant;
      } else {
        nodoAInsertar->ant->sig = nodoAInsertar->sig;
        nodoAInsertar->sig->ant = nodoAInsertar->ant;
      }
      nodoAInsertar->ant = nodoDest;
      nodoAInsertar->sig = nodoDest->sig;
      nodoDest->sig->ant = nodoAInsertar;
      nodoDest->sig = nodoAInsertar;
    }
  }
  return lista;
}

GList glist_insertionSort(GList lista, Compara c) {
  int bandera;
  GNodo *nodoAux = lista->primero, *nodoAux2;
  GNodo *nodoGuia = lista->primero;
  while (nodoGuia != NULL) {
    nodoAux = nodoGuia;
    nodoAux2 = nodoAux->ant;
    bandera = 0;
    nodoGuia = nodoGuia->sig;
    for (; nodoAux2 != NULL && !bandera; nodoAux2 = nodoAux2->ant) {
      if (c(nodoAux2->dato, nodoAux->dato) < 0) {
        bandera = 1;
        nodoAux2 = nodoAux2->sig;
      }
    }
    lista = glist_insertar_nodo(nodoAux, nodoAux2, bandera, lista);
  }
  return lista;
}

GList glist_append(GNodo * nodo, GList lista) {
  nodo->ant = NULL;
  nodo->sig = lista->primero;
  lista->primero->ant = nodo;
  lista->primero = nodo;
  lista->cantidad++;

  return lista;
}

GList glist_merge(GList lista1, GList lista2, Compara c) {
  if (lista1->cantidad == 0)
    return lista2;
  if (lista2->cantidad == 0)
    return lista1;
  if (c(lista1->primero->dato, lista2->primero->dato) <= 0) {
    if (lista1->cantidad == 1) {
      lista1 = glist_append(lista1->primero, lista2);
    } else {
      GNodo *nodoAux = lista1->primero;
      lista1->primero = lista1->primero->sig;
      lista1->cantidad--;
      lista1 = glist_merge(lista1, lista2, c);
      lista1 = glist_append(nodoAux, lista1);

    }

    return lista1;
  } else {
    if (lista2->cantidad == 1) {
      lista2 = glist_append(lista2->primero, lista1);
    } else {
      GNodo *nodoAux = lista2->primero;
      lista2->primero = lista2->primero->sig;
      lista2->cantidad--;
      lista2 = glist_merge(lista1, lista2, c);
      lista2 = glist_append(nodoAux, lista2);
    }

    return lista2;
  }
}

GList glist_split(GList lista) {
  int medio = lista->cantidad / 2, indice = 0;
  GNodo *nodoAux = lista->primero;
  GList lista2 = malloc(sizeof(Extremos));
  for (; indice < medio; indice++, nodoAux = nodoAux->sig);
  lista2->primero = nodoAux;
  lista2->ultimo = lista->ultimo;
  lista->ultimo = nodoAux->ant;
  lista2->cantidad = lista->cantidad - medio;
  lista->cantidad = medio;

  lista2->primero->ant = NULL;
  lista->ultimo->sig = NULL;

  return lista2;
}

GList glist_mergeSort(GList lista, Compara c) {
  if (lista->cantidad <= 1)
    return lista;
  GList aux = lista;
  GList derecha = glist_split(lista);
  derecha = glist_mergeSort(derecha, c);
  lista = glist_mergeSort(lista, c);

  lista = glist_merge(lista, derecha, c);
  aux->primero = lista->primero;
  aux->ultimo = lista->ultimo;
  aux->cantidad = lista->cantidad;
  lista = aux;
  free(derecha);

  return lista;
}
