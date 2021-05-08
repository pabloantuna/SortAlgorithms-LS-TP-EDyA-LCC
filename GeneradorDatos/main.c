// Pablo Antuña - Ignacio Espindola
// TP1 Estructuras de Datos y Algoritmia
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#define MAX_LINEA 100  //Tamaño maximo para las lineas de los archivos

// contar_lineas: FILE* -> int
// La funcion toma un puntero a un archivo y cuenta la cantidad de lineas
int contar_lineas(FILE * archivo) {
  int lineas = 0;
  char fila[MAX_LINEA];
  while (!feof(archivo)) {
    fgets(fila, MAX_LINEA, archivo);
    lineas++;
  }
  // Restamos 1 a la cantidad de linea pues se toma que el archivo de entrada
  // terminara siempre con un enter
  lineas--;
  rewind(archivo);  // Retrocede hasta el inicio del archivo para releerlo
  return lineas;
}

// comparacion: void* -> void* -> int
// Esta es simplemente una funcion que sera utilizada en el qsort y nos sirve
// para ordenar el array de posiciones aleatorias generadas
int comparacion(const void *a, const void *b) {
  int *c = (int *) a, *d = (int *) b;
  return *c - *d;
}

// generar_posiciones_random: int -> int -> int*
// Esta funcion genera una cantidad dada de numeros aleatorios entre 0 y limite
// Estos numeros generados seran las lineas de donde obtendremos los nombres
int *generar_posiciones_random(int cantidad, int limite) {
  int *listaPosiciones = malloc(sizeof(int) * cantidad);
  for (int indice = 0; indice < cantidad; indice++) {
    listaPosiciones[indice] = rand() % limite;
  }
  qsort(listaPosiciones, cantidad, sizeof(int), &comparacion);
  return listaPosiciones;
}

// escribir: int -> int* -> char** -> int -> FILE* -> FILE* ->
// Esta funcion se encarga de escribir en el archivo de salida a las personas
// con edades y paises aleatorios
// Los argumentos son: cantidad de personas a obtener, lista de posiciones
// aleatorias, lista de paises, los archivos de entrada de nombres y de salida
void escribir(int cantidad, int *posNombres, char **paises, int cantPaises,
              FILE * archivoNombres, FILE * archivoSalida) {
  int posLecturaNombre = -1;
  char nombre[MAX_LINEA];
  for (int i = 0; i < cantidad; i++) {
    for (; posLecturaNombre < posNombres[i]; posLecturaNombre++) {
#ifdef _WIN32
      fscanf(archivoNombres, "%[^\n]\n", nombre);
#else
      fscanf(archivoNombres, "%[^\r]\r\n", nombre);
#endif
    }
    fprintf(archivoSalida, "%s, %d, %s\n", nombre, rand() % 100 + 1,
            paises[rand() % cantPaises]);
  }
}

// leer_paises: FILE* -> char** -> char**
// Esta funcion obtiene el archivo de paises, lee y guarda todo en un arreglo
char **leer_paises(FILE * archivo, char **lista, int cantPaises) {
  int indice = 0;
  while (indice < cantPaises) {
    fscanf(archivo, "%[^\n]\n", lista[indice]);
    indice++;
  }

  return lista;
}

// Argumentos: ArchivoNombres, ArchivoPaises, ArchivoSalida, CantidadDeGente
int main(int argc, char *argv[]) {
  if (argc != 5) {
    printf("ERROR!\n");

    return -1;
  }
  srand(time(NULL));
  FILE *nombres = fopen(argv[1], "r"), *paises = fopen(argv[2], "r");
  FILE *salida = fopen(argv[3], "w");  //Abrimos los 3 archivos
  int cantDatos = atoi(argv[4]), cantNombres, cantPaises;
  cantNombres = contar_lineas(nombres);
  cantPaises = contar_lineas(paises); //Contamos las lineas de los archivos
  int *listaPosNombres = generar_posiciones_random(cantDatos, cantNombres);
  char **listaPaises = malloc(sizeof(char *) * cantPaises);
  for (int i = 0; i < cantPaises; i++) {  //Damos espacio al arreglo de paises
    listaPaises[i] = malloc(sizeof(char) * MAX_LINEA);
  }
  listaPaises = leer_paises(paises, listaPaises, cantPaises);  //Leemos los paises
  escribir(cantDatos, listaPosNombres, listaPaises, cantPaises, nombres,
           salida);
  for (int i = 0; i < cantPaises; i++) {
    free(listaPaises[i]);  //Liberamos el espacio de cada pais
  }
  free(listaPaises);  //Liberamos la lista de paises
  free(listaPosNombres);
  fclose(nombres);
  fclose(paises);
  fclose(salida);
  return 0;
}
