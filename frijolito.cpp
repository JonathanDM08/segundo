#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESOS 10

typedef struct {
    char nombre[20];
    int tiempoLlegada;
    int rafagaCPU;
    int tiempoEspera;
    int tiempoRetorno;
} Proceso;

// Función para ordenar los procesos por tiempo de llegada (FCFS)
void ordenarPorLlegada(Proceso procesos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (procesos[i].tiempoLlegada > procesos[j].tiempoLlegada) {
                Proceso temp = procesos[i];
                procesos[i] = procesos[j];
                procesos[j] = temp;
            }
        }
    }
}

// Función para ordenar los procesos por ráfaga de CPU (SJF)
void ordenarPorRafaga(Proceso procesos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (procesos[i].rafagaCPU > procesos[j].rafagaCPU) {
                Proceso temp = procesos[i];
                procesos[i] = procesos[j];
                procesos[j] = temp;
            }
        }
    }
}

// Función para calcular el tiempo de espera y tiempo de retorno
void calcularTiempos(Proceso procesos[], int n) {
    int tiempoActual = 0;
    for (int i = 0; i < n; i++) {
        procesos[i].tiempoEspera = tiempoActual - procesos[i].tiempoLlegada;
        tiempoActual += procesos[i].rafagaCPU;
        procesos[i].tiempoRetorno = tiempoActual - procesos[i].tiempoLlegada;
    }
}

// Función para mostrar los resultados
void mostrarResultados(Proceso procesos[], int n) {
    printf("Proceso\tLlegada\tRafaga\tEspera\tRetorno\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\n", procesos[i].nombre, procesos[i].tiempoLlegada,
               procesos[i].rafagaCPU, procesos[i].tiempoEspera, procesos[i].tiempoRetorno);
    }
}

int main() {
    Proceso procesos[MAX_PROCESOS];
    int n, opcion;

    // Captura de datos
    printf("Ingrese el número de procesos: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Proceso %d:\n", i + 1);
        printf("Nombre: ");
        scanf("%s", procesos[i].nombre);
        printf("Tiempo de llegada: ");
        scanf("%d", &procesos[i].tiempoLlegada);
        printf("Ráfaga de CPU: ");
        scanf("%d", &procesos[i].rafagaCPU);
    }

    // Selección del algoritmo
    printf("Seleccione el algoritmo (1: FCFS, 2: SJF): ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        ordenarPorLlegada(procesos, n);
        printf("\nAlgoritmo seleccionado: FCFS\n");
    } else if (opcion == 2) {
        ordenarPorRafaga(procesos, n);
        printf("\nAlgoritmo seleccionado: SJF\n");
    } else {
        printf("Opción no válida.\n");
        return 1;
    }

    // Calcular los tiempos de espera y retorno
    calcularTiempos(procesos, n);

    // Mostrar los resultados
    mostrarResultados(procesos, n);

    return 0;
}

