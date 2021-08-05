#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#define DESTINOS_ARCHIVO "Destinos.txt"
#define ESCALAS_ARCHIVO "Escalas.txt"
#define SEP_CAMPO '|'
#define SEP_REGISTRO '\n'
#define MAX_TAM 10
#define INF 9999

using namespace std;

class Vertice   {
    public:
        string nombre;
    public:
        Vertice()   {}
        string agregarVer() {
            cout << "Nombre del Destino:  ";
                cin.ignore();
                getline(cin, nombre);
            return nombre;
        }
    friend class Grafo;
};

class Arista    {
    public:
        int peso;
    public:
        Arista()    {}
        int agregarAri()  {
            cout << "Costo:  ";
                cin >> peso;
            return peso;
        }
    friend class Grafo;
};

class Grafo {
    public:
        int costo;
        int numVertices;
        int numAristas;
    public:
        Grafo();
        void cargarArchivo();
        void guardarArchivo();
        void agregarVertice();
        void agregarEscala();
        void agregarArista(string origen, string destino, int costo);
        void mostrar();
        int buscarVertice(string buscar);
        void eliminarArista();
        void eliminarVertice();
        void mostrarRutas();
        void dijkstra(int origen, int destino);
};

#endif // GRAFO_H
