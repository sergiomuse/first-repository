#include "Grafo.h"

Grafo G[MAX_TAM][MAX_TAM];
Vertice destinos[MAX_TAM];

void imprimir(int destino, int previo[], Grafo G[MAX_TAM][MAX_TAM]);

Grafo::Grafo()  {
    for(int i = 0; i < MAX_TAM; i++)    {
        for(int j = 0; j < MAX_TAM; j++)    {
            G[i][j].costo = 0;
        }
    }
}


void Grafo::cargarArchivo() {
    string campo;
    int i = 0;
    int campo2;
    numVertices = 0;
    numAristas = 0;
    string origen, destino;
    ifstream archivoDestino(DESTINOS_ARCHIVO);
    ifstream archivoEscala(ESCALAS_ARCHIVO);
    if(archivoDestino.is_open() && archivoEscala.is_open())   {
        while(!archivoDestino.eof())   {
            getline(archivoDestino, campo, SEP_CAMPO);
            if(archivoDestino.eof())   {
                break;
            }
            destinos[i].nombre = campo;
            i++;
        }
        numVertices = i;
        archivoDestino.close();
        i = 0;
        while(!archivoEscala.eof()) {
            getline(archivoEscala, campo, SEP_CAMPO);
            if(archivoEscala.eof()) {
                break;
            }
            origen = campo;
            getline(archivoEscala, campo, SEP_CAMPO);
            destino = campo;
            getline(archivoEscala, campo, SEP_REGISTRO);
            campo2 = atoi(campo.c_str());
            agregarArista(origen, destino, campo2);
            i++;
        }
        numAristas = i;
        archivoEscala.close();
    }
    else    {
        cout << "Error en el archivo" << endl;
    }
}

void Grafo::guardarArchivo() {
    string campo;
    ofstream archivoDestino(DESTINOS_ARCHIVO);
    ofstream archivoEscalas(ESCALAS_ARCHIVO);
    if(archivoDestino.good() && archivoEscalas.good())  {
        for(int i = 0; i < numVertices; i++)    {
            archivoDestino << destinos[i].nombre << SEP_CAMPO;
        }
        archivoDestino.close();
        for(int i = 0; i < numVertices; i++)    {
            for(int j = i; j < numVertices; j++)    {
                if(G[i][j].costo != 0)    {
                    archivoEscalas << destinos[i].nombre << SEP_CAMPO
                        << destinos[j].nombre << SEP_CAMPO
                        << G[i][j].costo << SEP_REGISTRO;
                }
            }
        }
        archivoEscalas.close();
    }
    else    {
        cout << "Error en el archivo" << endl;
    }
}

int Grafo::buscarVertice(string buscar) {
    int pos = -1;
    for(int i = 0; i < numVertices; i++) {
        if(buscar == destinos[i].nombre)    {
            return pos = i;
        }
    }
    return pos;
}

void Grafo::agregarVertice()    {
    Vertice vertice;
    vertice.nombre = vertice.agregarVer();
    destinos[numVertices++].nombre = vertice.nombre;
}

void Grafo::agregarEscala() {
    string origen, destino;
    Arista arista;
    cout << "De:  ";
        cin.ignore();
        getline(cin, origen);
    cout << "A:  ";
        getline(cin, destino);
    arista.peso = arista.agregarAri();
    agregarArista(origen, destino, arista.peso);
}

void Grafo::agregarArista(string origen, string destino, int cos) {
    int ori = buscarVertice(origen);
    int des = buscarVertice(destino);
    if(ori != -1 && des != -1)  {
        G[ori][des].costo = cos;
        G[des][ori].costo = cos;
        numAristas+=2;
    }
    else    {
        cout << "Error" << endl;
    }
}

void Grafo::mostrar()   {
    cout << "\t";
    for(int i = 0; i < numVertices; i++)    {
        cout << destinos[i].nombre << " \t";
    }
    cout << endl;
    for(int i = 0; i < numVertices; i++)    {
        cout << "\t";
        for(int j = 0; j < numVertices; j++)    {
            cout << G[i][j].costo << "    \t\t";
        }
        cout << destinos[i].nombre << "\t";
        cout << endl;
    }
}

void Grafo::eliminarVertice()   {
    string eliminar;
    int pos;
    int opc = 0;
    bool flag = false;
    cout << "Destino a eliminar:  ";
        cin.ignore();
        getline(cin, eliminar);
    pos = buscarVertice(eliminar);
    if(pos != -1)    {
        do  {
            cout << "Desea eliminar " << eliminar << endl;
            cout << "1.- Si" << endl;
            cout << "2.- No" << endl;
                cin >> opc;
            switch(opc) {
            case 1:
                flag = true;
                for(int i = pos; i < numVertices; i++)  {
                    destinos[i].nombre = destinos[i+1].nombre;
                }
                for(int j = pos; j < numVertices; j++)  {
                    for(int i = 0; i < numVertices; i++)  {
                        if(i!=j)    {
                            G[j][i].costo = G[j+1][i].costo;
                            G[i][j].costo = G[j+1][i].costo;
                        }
                    }
                }
                numVertices--;
                cout << "Destino Eliminado" << endl;
                break;
            case 2:
                flag = true;
                cout << "Destino No eliminado" << endl;
                break;
            default:
                break;
            }
        }
        while(flag == false);
    }
    else    {
        cout << "No existe el destino " << eliminar << endl;
    }
}

void Grafo::eliminarArista()    {
    string origenEliminar, destinoEliminar;
    int posOrigen;
    int posDestino;
    int opc = 0;
    bool flag = false;
    cout << "Eliminar Escala de:  ";
        cin.ignore();
        getline(cin, origenEliminar);
    cout << "A:  ";
        getline(cin, destinoEliminar);
    posOrigen = buscarVertice(origenEliminar);
    posDestino = buscarVertice(destinoEliminar);
    if(posOrigen != -1 && posDestino != -1)    {
        do  {
            cout << "Desea eliminar " << origenEliminar << " a " << destinoEliminar << endl;
            cout << "1.- Si" << endl;
            cout << "2.- No" << endl;
                cin >> opc;
            switch(opc) {
            case 1:
                flag = true;
                G[posOrigen][posDestino].costo = 0;
                G[posDestino][posOrigen].costo = 0;
                numAristas--;
                cout << "Escala Eliminada" << endl;
                break;
            case 2:
                flag = true;
                cout << "Escala No eliminada" << endl;
                break;
            default:
                break;
            }
        }
        while(flag == false);
    }
    else    {
        cout << "No existe la escala de " << origenEliminar << " a " << destinoEliminar << endl;
    }
}


void Grafo::mostrarRutas()  {
    string origen, destino, peso;
    cout << "Origen:  ";
        cin.ignore();
        getline(cin, origen);
    cout << "Destino:  ";
        getline(cin, destino);
    dijkstra(buscarVertice(origen), buscarVertice(destino));
}

void Grafo::dijkstra(int origen, int destino)  {
    int i, j, minimo;
    int g[MAX_TAM];
    bool visitado[MAX_TAM];
    int previo[numAristas];

    for(i = 0; i < numVertices; i++)    {
        g[i] = INF;
        visitado[i] = false;
        previo[i] = -1;
    }
    g[origen] = 0;

    for(j = 0; j < numVertices; j++)    {
        minimo = -1;
        for(i = 0; i < numVertices; i++)    {
            if(!visitado[i] && ((minimo == -1) || (g[i] < g[minimo])))  {
                minimo = i;
            }
        }

        visitado[minimo] = true;
        for(i = 0; i < numVertices; i++)    {
            if(G[minimo][i].costo)    {
                if(g[minimo]+ G[minimo][i].costo < g[i])  {
                    g[i] = g[minimo] + G[minimo][i].costo;
                    previo[i] = minimo;
                }
            }
        }
    }
    cout << endl << "Distancia minima" << endl;
    imprimir(destino, previo, G);
    cout << "Total:  " << g[destino] << endl;
}

void imprimir(int destino, int previo[], Grafo G[MAX_TAM][MAX_TAM])  {
    if(previo[destino] != -1)   {
        imprimir(previo[destino], previo, G);
    }
    if(previo[destino] != -1)   {
        cout << destinos[previo[destino]].nombre << " - " << destinos[destino].nombre
            << ":  " << G[previo[destino]][destino].costo << endl;
    }
}
