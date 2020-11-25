#include <iostream>
#include <string>
using namespace std;

struct Puesto
{
    string nombre;
    float salario;
};

// Funciones que dependen del tipo de dato de los nodos
Puesto solicitarDato()
{
    Puesto unPuesto;
    cout << "Nombre del chile: ";
    getline(cin, unPuesto.nombre);
    cout << "SHU (Scoville Heat Units): ";
    cin >> unPuesto.salario;
    cin.ignore();
    return unPuesto;
}
void mostrarDato(Puesto unPuesto)
{
    cout << endl<< "Nombre del chile: " << unPuesto.nombre;
    cout << endl<< "SHU (Scoville Heat Units):" << unPuesto.salario;
}

void mostrarDatoPPST(Puesto unPuesto)
{
    if (unPuesto.salario >= 50000)
    {
        cout << endl << "-------------------------------------";
        cout << endl<< "   Contiene mas de 50000 SHUs";
        cout << endl<< "-------------------------------------";
        cout << endl<< "Nombre del chile: " << unPuesto.nombre;
        cout << endl<< "SHU (Scoville Heat Units):" << unPuesto.salario;
    }
}

enum comparacion
{
    menorque,
    mayorque,
    igualque
};

bool comparar(Puesto a, comparacion operador, Puesto b)
{
    bool resultado = false;
    switch (operador)
    {
    case menorque:
        resultado = a.salario < b.salario;
        break;
    case mayorque:
        resultado = a.salario > b.salario;
        break;
    case igualque:
        resultado = a.salario == b.salario;
        break;
    }
    return resultado;
}

//------ Creacion de nodo y de arbol ------
typedef Puesto T;

struct Nodo
{
    T info;
    struct Nodo *izq;
    struct Nodo *der;
};
typedef struct Nodo *Arbol;

Arbol crearArbol(T x);

//------ Agregar nodos a un arbol ------
void asignarIzq(Arbol a, T unDato);
void asignarDer(Arbol a, T unDato);
void agregarNodo(Arbol a);
void menurecorrer(Arbol arbol);
//------ Recorrer un arbol (in, pre y post orden) ------
void preorden(Arbol a);
void inorden(Arbol a);
void postorden(Arbol a);
void recorrerArbol(Arbol a);
void recorrerArbolinorden(Arbol a);

void crearPersonalizado(Arbol p);

int main()
{
    cout << "Tercer Parcial. Bienvenido:\n";


        cout << "Ingresa el primer Chile Porfavor:\n";
    Arbol arbol = crearArbol(solicitarDato());

    bool continuar = true;
    do
    {
        int opcion = 0;
        cout << "\nMenu: \n";
        cout << "\t1) Agregar\n";
        cout << "\t2) Recorrer\n";
        cout << "\t3) Salir\n";
        cout << "\tOpcion elegida: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1:
            agregarNodo(arbol);
            break;
        case 2:
            menurecorrer(arbol);
            break;
        case 3:
            continuar = false;
            break;
        default:
            cout << "Opcion erronea!" << endl;
            break;
        }
    } while (continuar);

    return 0;
}


void menurecorrer(Arbol arbol){
    bool continuar = true;
    do
    {
        int opcion = 0;
       
        cout << "\t1) In Orden\n";
        cout << "\t2) Post Orden\n";
        cout << "\t3) Salir\n";
        cout << "\tOpcion elegida: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1:
           recorrerArbolinorden(arbol);
             continuar = false;
            break;
        case 2:
            recorrerArbol(arbol);
              continuar = false;
            break;
        case 3:
            continuar = false;
            break;
        default:
            cout << "Opcion erronea!" << endl;
            break;
        }
    } while (continuar);
}



// Implementacion de funciones de arboles
Arbol crearArbol(T x)
{
    Arbol p = new Nodo;
    p->info = x;
    p->izq = NULL;
    p->der = NULL;
    return p;
}

//------ Agregar nodos a un arbol ------
void asignarIzq(Arbol a, T unDato)
{
    if (a == NULL)
        cout << "Error: arbol vacio" << endl;
    else if (a->izq != NULL)
        cout << "Error: subarbol IZQ ya existe" << endl;
    else
        a->izq = crearArbol(unDato);
}

void asignarDer(Arbol a, T unDato)
{
    if (a == NULL)
        cout << "Error: arbol vacio" << endl;
    else if (a->der != NULL)
        cout << "Error: subarbol DER ya existe" << endl;
    else
        a->der = crearArbol(unDato);
}

void agregarNodo(Arbol a)
{
    //solicitar informacion (dato a agregar)
    cout << "Dato a agregar:\n";
    T unDato = solicitarDato();

    Arbol p = a;

    //desplazarse hasta el lugar adecuado
    while (true)
    {
        if (comparar(unDato, igualque, p->info))
        {
            cout << "Error: dato ya existe!" << endl;
            return;
        }
        else if (comparar(unDato, menorque, p->info))
        { //ir a la izquierda
            if (p->izq == NULL)
                break;
            else
                p = p->izq;
        }
        else
        { //ir a la derecha
            if (p->der == NULL)
                break;
            else
                p = p->der;
        }
    }

    //agregar el nuevo nodo
    if (comparar(unDato, menorque, p->info))
        asignarIzq(p, unDato);
    else
        asignarDer(p, unDato);
}

//------ Recorrer un arbol (in, pre y post orden) ------
void preorden(Arbol a)
{
    if (a != NULL)
    {
        cout << "\n";
        mostrarDato(a->info);
        preorden(a->izq);
        preorden(a->der);
    }
}
void inorden(Arbol a)
{
    if (a != NULL)
    {
        inorden(a->izq);
        cout << "\n";
        mostrarDato(a->info);
        inorden(a->der);
    }
}
void postorden(Arbol a)
{
    if (a != NULL)
    {
        postorden(a->izq);
        postorden(a->der);
        cout << "\n";
        mostrarDatoPPST(a->info);
    }
}

void recorrerArbol(Arbol a)
{
  
    cout << "\nRecorrido POST orden:-----";
    postorden(a);
    cout << endl;
}
void recorrerArbolinorden(Arbol a)
{
 
    cout << "\nRecorrido IN orden:-----";
    inorden(a);
    cout << endl;
   
}