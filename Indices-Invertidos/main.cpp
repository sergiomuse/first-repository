/*
  GNU GCC COMPILER
*/
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
using namespace std;

void pausa();

class Disco
{
public:
    char codigo[40],nombre[40],cantante[40],genero[40],precio[40],casa[40];

} x;
class Indice
{
public:
    char codigo[40];
    long int posicion;
} y;

class nodo
{
public:
    char codigo[40],nombre[40],cantante[40],genero[40],precio[40],casa[40];
    nodo *siguiente;
    nodo *anterior;
};
typedef nodo *pnodo;
class Lista
{
public:
    pnodo inicio,fin;
    int tam;
    void Inicializar();
    void Agregar();
    void Mostrar();
    void Modificar();
    void Eliminar();
    void Buscar();
} li;

void Lista::Inicializar()
{
    inicio=NULL;
    fin=NULL;
    tam=0;
}
void Lista::Agregar()
{
    ofstream File("Disco.txt",ios::app);
    ofstream FileIndex("Indices.txt",ios::app);
    if(tam==0)
    {
        pnodo nuevo=new nodo;
        fflush(stdin);

        cout << "\nIngresa el codigo del disco: ";
        fflush(stdin);
        cin.getline(x.codigo,40);
        cout << "\nIngresa el nombre: ";
        cin.getline(x.nombre,40);
        cout << "\nIngresa el cantante: ";
        cin.getline(x.cantante,40);
        cout<<"\nIngresa el genero: ";
        cin.getline(x.genero,40);
        cout<<"\nIngresa el precio: ";
        cin.getline(x.precio,40);
        cout<<"\nIngresa la casa: ";
        cin.getline(x.casa,40);

        strcpy(nuevo->codigo,x.codigo);
        strcpy(nuevo->nombre,x.nombre);
        strcpy(nuevo->cantante,x.cantante);
        strcpy(nuevo->genero,x.genero);
        strcpy(nuevo->precio,x.precio);
        strcpy(nuevo->casa,x.casa);
        File.write((char *)&x,sizeof(x));
        inicio=nuevo;
        inicio->anterior=NULL;
        fin=nuevo;
        fin->siguiente=NULL;
        strcpy(y.codigo,x.codigo);
        File.seekp(0,File.end);
        y.posicion=File.tellp();
        y.posicion=y.posicion-sizeof(x);
        FileIndex.write((char *)&y,sizeof(y));
        tam++;
    }
    else
    {
        pnodo nuevo=new nodo;
        fflush(stdin);
        cout << "\nIngresa el codigo: ";
        fflush(stdin);
        cin.getline(x.codigo,40);
        cout << "\nIngresa el nombre: ";
        cin.getline(x.nombre,40);
        cout << "\nIngresa el cantante: ";
        cin.getline(x.cantante,40);
        cout<<"\nIngresa el genero: ";
        cin.getline(x.genero,40);
        cout<<"\nIngresa el precio: ";
        cin.getline(x.precio,40);
        cout<<"\nIngresa la casa: ";
        cin.getline(x.casa,40);

        strcpy(nuevo->codigo,x.codigo);
        strcpy(nuevo->nombre,x.nombre);
        strcpy(nuevo->cantante,x.cantante);
        strcpy(nuevo->genero,x.genero);
        strcpy(nuevo->precio,x.precio);
        strcpy(nuevo->casa,x.casa);

        File.write((char *)&x,sizeof(x));
        fin->siguiente=nuevo;
        nuevo->anterior=fin;
        fin=nuevo;
        fin->siguiente=NULL;
        strcpy(y.codigo,x.codigo);
        File.seekp(0,File.end);
        y.posicion=File.tellp();
        y.posicion=y.posicion-sizeof(x);
        FileIndex.write((char *)&y,sizeof(y));
        tam++;
    }
    File.close();
    FileIndex.close();
}

void Lista::Mostrar()
{
    pnodo actual=inicio;

    if(tam==0)
        cout<<"No hay elementos... "<<endl;
    else
    {
        while(actual!=NULL)
        {
            cout<<"Indice de la tesis: "<<actual->codigo<<endl;
            cout<<"Titulo: "<<actual->nombre<<endl;
            cout<<"cantante: "<<actual->cantante<<endl;
            cout<<"genero: "<<actual->genero<<endl;
            cout<<"precio: "<<actual->precio<<endl;
            cout<<"casa: "<<actual->casa<<endl;
            cout<<endl;
            actual=actual->siguiente;
        }
    }
}
void Lista::Modificar()
{
    if(tam==0)
        cout<<"No hay nada que modificar "<<endl;
    else
    {
        ofstream File("AuxDisco.txt",ios::app);
        ofstream FileIndex("AuxInd.txt",ios::app);
        ifstream fileRead("Disco.txt");
        ifstream fileReadIndex("Indices.txt");
        string comparacodigo;
        bool flag=false;
        pnodo actual=inicio;
        if(!fileReadIndex.good())
            cout<<"No Existe el Archivo "<<endl;
        else
        {
            cout<<"Dame el indice de la descarga a modificar: ";
            cin.ignore();
            getline(cin,comparacodigo);
            while(actual!=NULL)
            {
                fileReadIndex.read((char *)&y,sizeof(y));
                fileRead.seekg(y.posicion);
                fileRead.read((char *)&x,sizeof(x));
                if(fileReadIndex.eof())
                    break;
                if(comparacodigo==actual->codigo)
                {
                    flag=true;
                    fflush(stdin);
                    cout << "\nIngresa el codigo: ";
                    fflush(stdin);
                    cin.getline(x.codigo,40);
                    cout << "\nIngresa el nombre: ";
                    cin.getline(x.nombre,40);
                    cout << "\nIngresa el cantante: ";
                    cin.getline(x.cantante,40);
                    cout<<"\nIngresa el genero: ";
                    cin.getline(x.genero,40);
                    cout<<"\nIngresa el precio: ";
                    cin.getline(x.precio,40);
                    cout<<"\nIngresa la casa: ";
                    cin.getline(x.casa,40);

                    strcpy(actual->codigo,x.codigo);
                    strcpy(actual->nombre,x.nombre);
                    strcpy(actual->cantante,x.cantante);
                    strcpy(actual->genero,x.genero);
                    strcpy(actual->precio,x.precio);
                    strcpy(actual->casa,x.casa);
                    File.write((char *)&x,sizeof(x));
                    strcpy(y.codigo,x.codigo);
                    FileIndex.write((char *)&y,sizeof(y));
                }
                else
                {
                    File.write((char *)&x,sizeof(x));
                    FileIndex.write((char *)&y,sizeof(y));
                }
                actual=actual->siguiente;
            }
        }
        if(flag==false)
            cout<<"No se encontro ninguna disco con ese indice"<<endl;

        File.close();
        FileIndex.close();
        fileRead.close();
        fileReadIndex.close();
        remove("Indices.txt");
        rename("AuxInd.txt","Indices.txt");
        remove("Disco.txt");
        rename("AuxDisco.txt","Disco.txt");
    }
}

void Lista::Eliminar()
{
    if(tam==0)
        cout<<"No hay nada que eliminar "<<endl;
    else
    {
        string comparacodigo;
        bool flag=false;
        pnodo actual=inicio,sup;
        ofstream File("AuxDisco.txt",ios::app);
        ofstream FileIndex("AuxInd.txt",ios::app);
        ifstream fileRead("Disco.txt");
        ifstream fileReadIndex("Indices.txt");
        if(!fileReadIndex.good())
            cout<<"No Existe el Archivo "<<endl;
        else
        {
            cout<<"Dame el codigo del disco a eliminar: ";
            cin.ignore();
            getline(cin,comparacodigo);
            while(actual!=NULL)
            {
                fileReadIndex.read((char *)&y,sizeof(y));
                fileRead.seekg(y.posicion);
                fileRead.read((char *)&x,sizeof(x));
                if(fileReadIndex.eof())
                    break;
                if(comparacodigo==actual->codigo)
                {
                    flag=true;
                    sup=actual;
                    if(actual==inicio)
                    {
                        if(tam==1)
                        {
                            cout<<"Indice del disco: "<<actual->codigo<<endl;
                            cout<<"Nombre: "<<actual->nombre<<endl;
                            cout<<"Cantante: "<<actual->cantante<<endl;
                            cout<<"Genero: "<<actual->genero<<endl;
                            cout<<"Precio: "<<actual->precio<<endl;
                            cout<<"Casa: "<<actual->casa<<endl;
                        }
                        else
                        {
                            inicio=actual->siguiente;
                            inicio->anterior=NULL;
                            cout<<"Indice del disco: "<<actual->codigo<<endl;
                            cout<<"Nombre: "<<actual->nombre<<endl;
                            cout<<"Cantante: "<<actual->cantante<<endl;
                            cout<<"Genero: "<<actual->genero<<endl;
                            cout<<"Precio: "<<actual->precio<<endl;
                            cout<<"Casa: "<<actual->casa<<endl;
                        }

                    }
                    else
                    {
                        if(actual==fin)
                        {
                            fin=fin->anterior;
                            fin->siguiente=NULL;
                            cout<<"Indice del disco: "<<actual->codigo<<endl;
                            cout<<"Nombre: "<<actual->nombre<<endl;
                            cout<<"Cantante: "<<actual->cantante<<endl;
                            cout<<"Genero: "<<actual->genero<<endl;
                            cout<<"Precio: "<<actual->precio<<endl;
                            cout<<"Casa: "<<actual->casa<<endl;
                        }
                        else
                        {
                            actual->siguiente->anterior=actual->anterior;
                            actual->anterior->siguiente=actual->siguiente;
                        }
                    }
                    delete(sup);
                    tam--;
                    cout<<"Eliminando Registro...\nListo"<<endl;

                }
                else
                {
                    File.write((char *)&x,sizeof(x));
                    strcpy(y.codigo,actual->codigo);
                    File.seekp(0,File.end);
                    y.posicion=File.tellp();
                    y.posicion=y.posicion-sizeof(x);
                    FileIndex.write((char *)&y,sizeof(y));
                }
                actual=actual->siguiente;
            }
        }
        if(flag==false)
            cout<<"No se encontro ninguna disco en el indice"<<endl;

        File.close();
        FileIndex.close();
        fileRead.close();
        fileReadIndex.close();
        remove("Indices.txt");
        rename("AuxInd.txt","Indices.txt");
        remove("Disco.txt");
        rename("AuxDisco.txt","Disco.txt");
    }
}

void Lista::Buscar()
{
    if(tam==0)
        cout<<"No hay nada que Buscar"<<endl;
    else
    {
        string comparacodigo;
        bool flag=false;
        pnodo actual=inicio;
        cout<<"Dame el codigo del disco a buscar: ";
        cin.ignore();
        getline(cin,comparacodigo);
        while(actual!=NULL)
        {
            if(comparacodigo==actual->codigo)
            {
                flag=true;
                cout<<"Indice del disco: "<<actual->codigo<<endl;
                cout<<"Nombre: "<<actual->nombre<<endl;
                cout<<"Cantante: "<<actual->cantante<<endl;
                cout<<"Genero: "<<actual->genero<<endl;
                cout<<"Precio: "<<actual->precio<<endl;
                cout<<"Casa: "<<actual->casa<<endl;
            }
            actual=actual->siguiente;
        }
        if(flag==false)
            cout<<"No se encontro ningun disco con ese indice"<<endl;
    }
}
int main()
{
    int opc;
    do
    {
        system("CLS");
        cout<<"============DISCOTECA=============="<<endl;
        cout<<"Ingresa una opcion: \n "
            <<"1)Agregar disco \n "
                <<"2)Mostrar discos\n "
                <<"3)Modificar\n "
                <<"4)Eliminar\n "
                <<"5)Buscar\n "
                <<"6)Salir "<<endl;
        cin>>opc;
        switch(opc)
    {
    case 1:
        li.Agregar();
        pausa();
            break;
        case 2:
            li.Mostrar();
            pausa();
            break;
        case 3:
            li.Modificar();
            pausa();
            break;
        case 4:
            li.Eliminar();
            pausa();
            break;
        case 5:
            li.Buscar();
            pausa();
            break;
        case 6:
            break;
        default:
            cout<<"Opcion no valida..."<<endl;
            pausa();
            break;
        }
    }
    while(opc!=6);
}


void pausa(){
system("PAUSE");
}
