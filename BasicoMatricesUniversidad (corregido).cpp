#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;

// Declaraci�n de constantes
#define NUMERO_ALUMNOS 5
#define NUMERO_MATERIAS 5
#define NUMERO_NOTAS 4
#define MAX_CALIFICACION 100
#define MIN_CALIFICACION 0
#define MAXIMA_LONGITUD_CADENA 100

// Declaraci�n de prototipos de funci�n
void llamaCiclo();
int busquedaAleatorios(int minimo, int maximo);
void llenarMatriz(float matriz[NUMERO_ALUMNOS][NUMERO_NOTAS + 1]);
void imprimirMatrizLinea();
float imprimirMatriz(float matriz[NUMERO_ALUMNOS][NUMERO_NOTAS + 1], char alumnos[NUMERO_ALUMNOS][MAXIMA_LONGITUD_CADENA], string nombreFacultad);
void mostrarResultadosFinales(int numerocalculos, int ganadosFacultad_1, int ganadosFacultad_2, int ganadosFacultad_3, float promedio_facultad_1, float promedio_facultad_2, float promedio_facultad_3);

// Funci�n principal
int main() {
    srand(getpid());
    llamaCiclo();
    return 0;
}

void llamaCiclo() {
    float matriz_facultad_1[NUMERO_ALUMNOS][NUMERO_NOTAS + 1];
    float matriz_facultad_2[NUMERO_ALUMNOS][NUMERO_NOTAS + 1];
    float matriz_facultad_3[NUMERO_ALUMNOS][NUMERO_NOTAS + 1];
    char opcion;
    bool repetir = true;
    int ganadosFacultad_1 = 0, ganadosFacultad_2 = 0, ganadosFacultad_3 = 0;
    int numerocalculos = 0;

    char alumnos[NUMERO_ALUMNOS][MAXIMA_LONGITUD_CADENA] = {"Carlos", "Luis", "Maria", "Pedro", "Juan"};

    do {
        llenarMatriz(matriz_facultad_1);
        float promedio_facultad_1 = imprimirMatriz(matriz_facultad_1, alumnos, "Facultad de Ingenieria");

        llenarMatriz(matriz_facultad_2);
        float promedio_facultad_2 = imprimirMatriz(matriz_facultad_2, alumnos, "Facultad de Arquitectura");

        llenarMatriz(matriz_facultad_3);
        float promedio_facultad_3 = imprimirMatriz(matriz_facultad_3, alumnos, "Facultad de Administracion");

        // Calculo del mejor promedio de las facultades
        if (promedio_facultad_1 > promedio_facultad_2 && promedio_facultad_1 > promedio_facultad_3) {
            ganadosFacultad_1++;
        } else if (promedio_facultad_2 > promedio_facultad_1 && promedio_facultad_2 > promedio_facultad_3) {
            ganadosFacultad_2++;
        } else if (promedio_facultad_3 > promedio_facultad_1 && promedio_facultad_3 > promedio_facultad_2) {
            ganadosFacultad_3++;
        }

        numerocalculos++;

        cout << "Desea otro calculo (s/n)? ";
        cin >> opcion;
        if (opcion == 'n') {
            repetir = false;
        }
    } while (repetir);

    mostrarResultadosFinales(numerocalculos, ganadosFacultad_1, ganadosFacultad_2, ganadosFacultad_3, 0, 0, 0);// utilice el ejemplo que nos mostro en clase
}

int busquedaAleatorios(int minimo, int maximo) {
    return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}

void llenarMatriz(float matriz[NUMERO_ALUMNOS][NUMERO_NOTAS + 1]) {
    for (int y = 0; y < NUMERO_ALUMNOS; y++) {
        float suma = 0;
        for (int x = 0; x < NUMERO_NOTAS; x++) {
            int calificacion = 0;
            if (x == 0 || x == 3) {
                calificacion = busquedaAleatorios(MIN_CALIFICACION, 20);
            } else if (x == 1) {
                calificacion = busquedaAleatorios(MIN_CALIFICACION, 25);
            } else if (x == 2) {
                calificacion = busquedaAleatorios(MIN_CALIFICACION, 35);
            }
            suma += (float)calificacion;
            matriz[y][x] = calificacion;
        }
        matriz[y][NUMERO_NOTAS] = suma; // Agregamos promedio al final de la matriz
    }
}

void imprimirMatrizLinea() {
    cout << "+--------";
    for (int x = 0; x < NUMERO_NOTAS + 1; x++) {
        cout << "+---------";
    }
    cout << "+\n";
}

float imprimirMatriz(float matriz[NUMERO_ALUMNOS][NUMERO_NOTAS + 1], char alumnos[NUMERO_ALUMNOS][MAXIMA_LONGITUD_CADENA], string nombreFacultad) {
    float promedioMayor = matriz[0][NUMERO_NOTAS];
    float promedioMenor = matriz[0][NUMERO_NOTAS];
    float totalGeneral = 0;
    float promedioGeneral = 0;
    char alumnoPromedioMayor[MAXIMA_LONGITUD_CADENA];
    char alumnoPromedioMenor[MAXIMA_LONGITUD_CADENA];
    memcpy(alumnoPromedioMayor, alumnos[0], MAXIMA_LONGITUD_CADENA);
    memcpy(alumnoPromedioMenor, alumnos[0], MAXIMA_LONGITUD_CADENA);

    cout << nombreFacultad << endl;
    cout << "(Nota1)=>Primer Parcial  (Nota2)=>Segundo Parcial (Nota3)=>Final (Nota4)=>Actividades" << endl;
    imprimirMatrizLinea();
    cout << setw(9) << "Alumno";
    for (int x = 0; x < NUMERO_NOTAS; x++) {
        cout << setw(9) << "Nota" << x + 1;
    }
    cout << setw(8) << "Tot" << endl;
    imprimirMatrizLinea();

    for (int y = 0; y < NUMERO_ALUMNOS; y++) {
        cout << "!" << setw(8) << alumnos[y] << "!";
        float suma = 0;
        for (int x = 0; x < NUMERO_NOTAS; x++) {
            int calificacion = matriz[y][x];
            cout << setw(9) << calificacion << "!";
        }
        float promedio = matriz[y][NUMERO_NOTAS];
        totalGeneral += matriz[y][NUMERO_NOTAS];
        if (promedio > promedioMayor) {
            promedioMayor = promedio;
            memcpy(alumnoPromedioMayor, alumnos[y], MAXIMA_LONGITUD_CADENA);
        }
        if (promedio < promedioMenor) {
            promedioMenor = promedio;
            memcpy(alumnoPromedioMenor, alumnos[y], MAXIMA_LONGITUD_CADENA);
        }
        cout << setw(9) << fixed << setprecision(2) << promedio << "!" << endl;
        imprimirMatrizLinea();
    }

    promedioGeneral = totalGeneral / NUMERO_ALUMNOS;
    cout << "Nota mayor: " << setw(10) << alumnoPromedioMayor << setw(10) << promedioMayor << endl;
    cout << "Nota menor: " << setw(10) << alumnoPromedioMenor << setw(10) << promedioMenor << endl;
    cout << "Nota prom : " << setw(10) << promedioGeneral << endl << endl;
    return promedioGeneral;
}
//modifique un poco el codigo de lo que nos ense�o.espero que este bien.
void mostrarResultadosFinales(int numerocalculos, int ganadosFacultad_1, int ganadosFacultad_2, int ganadosFacultad_3, float promedio_facultad_1, float promedio_facultad_2, float promedio_facultad_3) {
    cout << "Resultados finales:" << endl;
    cout << "Total de calculos realizados: " << numerocalculos << endl;
    cout << "Facultad de Ingenieria gano: " << ganadosFacultad_1 << " veces." << endl;
    cout << "Facultad de Arquitectura gano: " << ganadosFacultad_2 << " veces." << endl;
    cout << "Facultad de Administracion gano: " << ganadosFacultad_3 << " veces." << endl;

    // cual es la mejor faculdad de las que tenemos
    if (ganadosFacultad_1 > ganadosFacultad_2 && ganadosFacultad_1 > ganadosFacultad_3) {
        cout << "La mejor facultad es: Facultad de Ingenieria." << endl;
    } else if (ganadosFacultad_2 > ganadosFacultad_1 && ganadosFacultad_2 > ganadosFacultad_3) {
        cout << "La mejor facultad es: Facultad de Arquitectura." << endl;
    } else if (ganadosFacultad_3 > ganadosFacultad_1 && ganadosFacultad_3 > ganadosFacultad_2) {
        cout << "La mejor facultad es: Facultad de Administracion." << endl;
    } else {
        cout << "Hay un empate entre las facultades." << endl;// se agrego este mensaje cuando las facultades por alguna ocasion empataran.
    }
}
