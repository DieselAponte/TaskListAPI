#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cctype>
#include <algorithm>

using namespace std;


void imprimirMenu() {
    cout << "-------------------- MENU -------------------" << endl;
    cout << "1: Escribir una nueva Tarea" << endl;
    cout << "2: Observar tareas pendientes" << endl;
    cout << "3: Eliminar una tarea pendiente" << endl;
    cout << "4: Resaltar una tarea pendiente" << endl;
    cout << "-----Ingrese una opcion (numeros enteros)-----" << endl;
}

void restringirEntradaN(int& n) {
    while (!(cin >> n)) {
        cin.clear(); // Clear the error flag
        cin.ignore(100000, '\n'); // Ignore invalid input
        cout << "Dato invalido..." << endl;
        cout << "Ingrese un entero para poder ingresar a alguna de las opciones" << endl;
        imprimirMenu();
    }
}

void restringirEntradaS(string& p) {
    while (!(cin >> p)) {
        cin.clear(); // Clear the error flag
        cin.ignore(100000, '\n'); // Ignore invalid input
        cout << "Dato invalido..." << endl;
        cout << "Ingrese una palabra (Caracteres del teclado)" << endl;
    }
}

int agregarTarea() {
    string tareaNueva;
    int numeroLinea = 1;
    ofstream listaTareas("Tareas.txt", ios::app);
    if (!listaTareas) {
        cout << "Error al abrir el archivo ..." << endl;
        return 1;
    }
    cout << "Cual es la nueva tarea? " << endl;
    cin.ignore();
    getline(cin, tareaNueva);
    listaTareas << numeroLinea << ": " << tareaNueva << endl;
    numeroLinea++;
    cout << "Se ha agregado la tarea a la lista correctamente "<< endl;
    listaTareas.close();
}
void observarTarea() {
    string mostrarTareas;
    ifstream listaTareas2("Tareas.txt");
    if (!listaTareas2) {
        cout << "Error al abrir el archivo ..." << endl;
    }

    while (getline(listaTareas2, mostrarTareas)) {
        cout << mostrarTareas << endl;
    }
    listaTareas2.close();
}
int eliminarTarea() {
    int eliminarPos = 0;
    cout << "Ingrese la posicion de la tarea que quiere eliminar: " << endl;
    observarTarea();
    restringirEntradaN(eliminarPos);

    ifstream listaTareas("Tareas.txt");
    ofstream tempTareas("TempTareas.txt");
    string linea;
    int lineaActual = 1;
    bool tareaEliminada = false;

    if (!listaTareas || !tempTareas) {
        cout << "Error al abrir los archivos ..." << endl;
        return 1;
    }

    while (getline(listaTareas, linea)) {
        if (lineaActual != eliminarPos) {
            tempTareas << linea << endl;
        } else {
            tareaEliminada = true;
        }
        lineaActual++;
    }

    listaTareas.close();
    tempTareas.close();

    remove("Tareas.txt");
    rename("TempTareas.txt", "Tareas.txt");

    if (tareaEliminada) {
        cout << "Tarea eliminada con exito" << endl;
    } else {
        cout << "Tarea no encontrada ..." << endl;
    }

    return 0;
}

void resaltarTarea();
int main() {
    int opcion;
    string respuestaOperacion;
    string respuestaOperacionMin;

    cout << "Lista de Tareas - Diesel Aponte" << endl;
    do {
        imprimirMenu();
        restringirEntradaN(opcion);
        switch (opcion) {
            case 1: {
                agregarTarea();
                break;
            }
            case 2: {
                observarTarea();
                break;
            }
            case 3:
                eliminarTarea();
                break;
            case 4:
                cout << "Funcionalidad no implementada" << endl;
                break;
            default:
                cout << "Opcion invalida" << endl;
                break;
        }
        cout << "Quieres hacer alguna otra operacion? (Si/No)" << endl;
        restringirEntradaS(respuestaOperacion);
        respuestaOperacionMin = respuestaOperacion;
        transform(respuestaOperacionMin.begin(), respuestaOperacionMin.end(), respuestaOperacionMin.begin(), ::tolower);

    } while (respuestaOperacionMin != "no" && respuestaOperacionMin != "n");

    cout <<"Finalizando el programa ..." << endl;
    cout <<"Presione cualquier tecla: " << endl;
    getch();
    return 0;
}
