
#include <iostream>
#include "Grafo.h"
using namespace std;

int main()  {
    int opc;
    Grafo gra;
    do  {
        system("cls");
        cout << "==========TURI-MAX===============" << endl;
        cout << "1)Cargar archivo" << endl;
        cout << "2)Guardar archvo" << endl;
        cout << "3)Agregar Destino" << endl;
        cout << "4)Agregar Escala" << endl;
        cout << "5)Mostrar Escalas" << endl;
        cout << "6)Eliminar Destino" << endl;
        cout << "7)Eliminar Escala" << endl;
        cout << "8)Mostrar Rutas" << endl;
        cout << "9)Salir" << endl;
        cout << "\nEliga una opcion: ";
            cin >> opc;
        switch(opc) {
        case 1:
            system("cls");
            gra.cargarArchivo();
            system("pause");
            break;
        case 2:
            system("cls");
            gra.guardarArchivo();
            system("pause");
            break;
        case 3:
            system("cls");
            gra.agregarVertice();
            system("pause");
            break;
        case 4:
            system("cls");
            gra.agregarEscala();
            system("pause");
            break;
        case 5:
            system("cls");
            gra.mostrar();
            system("pause");
            break;
        case 6:
            system("cls");
            gra.eliminarVertice();
            system("pause");
            break;
        case 7:
            system("cls");
            gra.eliminarArista();
            system("pause");
            break;
        case 8:
            system("cls");
            gra.mostrarRutas();
            system("pause");
            break;
        case 9:
            system("pause");
            break;
        default:
            cout << "Opcion invalida" << endl;
            system("pause");
            break;
        }
    }
    while(opc != 9);
    return 0;
}
