#include <iostream>
using namespace std;

struct Nodo{
    int pid;
    int prioridad;
    int tiempo;
    int prioridadHeap;
    int size;
    int sumTime;
    Nodo* izq;
    Nodo* der;
    
    Nodo(int _pid, int _prioridad, int _tiempo) 
    : pid(_pid), 
      prioridad(_prioridad),
      tiempo(_tiempo),
      prioridadHeap(rand()),
      size(1),
      sumTime (_tiempo),
      izq(nullptr), 
      der(nullptr) {}
};

int tamaño(Nodo* n){
    if(n == nullptr)
        return 0;
    return n->size;
}

long suma(Nodo* n){
    if(n == nullptr)
        return 0;
    return n->sumTime;
    
    
}

void actualizar(Nodo* n){
    if (n == nullptr)
        return;
    n->size = 1 + tamaño(n->izq) + tamaño(n->der);
    n->sumTime = n->tiempo + suma(n->izq) + suma(n->der);
}

Nodo* rotarIzquierda(Nodo* x){
    Nodo* y = x->der;
    Nodo* T2 = y->izq;
    
    y->izq = x;
    x->der = T2;
    
    actualizar(x);
    actualizar(y);
    
    return y;
}

Nodo* rotarDerecha(Nodo* y){
    Nodo* x = y->izq;
    Nodo* T2 = x->der;
    
    x->der = y;
    y->izq = T2;
    
    actualizar(y);
    actualizar(x);
    
    return x;
}

Nodo* insertar(Nodo* n, int pid, int prioridad, int tiempo){
    if(n == nullptr){
        return new Nodo(pid, prioridad, tiempo);
    }
    
    if(prioridad < n->prioridad){
        n->izq = insertar(n->izq, pid, prioridad, tiempo);
        if(n->izq->prioridadHeap > n->prioridadHeap){
            n = rotarDerecha(n);
        }
    }else{
        n->der = insertar(n->der, pid, prioridad, tiempo);
        if(n->der->prioridadHeap > n->prioridadHeap){
            n = rotarIzquierda(n);
        }
    }
    
    actualizar(n);
    return n;
}

int contarMenor(Nodo* n, int p){ //p = prioridad
    if(n == nullptr)
        return 0;
    if(n->prioridad >= p)
        return contarMenor(n->izq, p);
    else
        return 1 + tamaño(n->izq) + contarMenor(n->der, p);
}

int sumaEnRango(Nodo* n, int p1, int p2){
    if(n == nullptr)
        return 0;

    if(n->prioridad < p1)
        return sumaEnRango(n->der, p1, p2);
    if(n->prioridad > p2)
        return sumaEnRango(n->izq, p1, p2);

    int retorno = n->tiempo;
    retorno += sumaEnRango(n->izq, p1, p2);
    retorno += sumaEnRango(n->der, p1, p2);

    return retorno;
}

long menorTiempoEnRango(Nodo* n, int p1, int p2){
    if (n == nullptr)
        return LONG_MAX;
    
    long menorTiempo = LONG_MAX;

    if(p1 <= n->prioridad && n->prioridad <= p2){
        menorTiempo = n->tiempo;
    }

    long menorIzq = menorTiempoEnRango(n->izq, p1, p2);
    long menorDer = menorTiempoEnRango(n->der, p1, p2);

    return min(menorTiempo, min(menorIzq, menorDer));
}

void imprimirInOrden(Nodo* n){
    if(n == nullptr)
        return;
    imprimirInOrden(n->izq);
    cout << "PID: " << n->pid << ", Prioridad: " << n->prioridad << ", Tiempo: " << n->tiempo << endl;
    cout << "Tamaño Subárbol: " << n->size << ", Suma Tiempos Subárbol: " << n->sumTime << endl;
    imprimirInOrden(n->der);
}

int main()
{
    Nodo* raiz = nullptr;
    raiz = insertar(raiz, 101, 15, 120);
    raiz = insertar(raiz, 102, 10, 80);
    raiz = insertar(raiz, 103, 20, 60);
    //agregar más xd
    imprimirInOrden(raiz);
    cout << "Procesos con prioridad menor a 18: " << contarMenor(raiz, 18) << endl;
    cout << "Suma de tiempos en rango de prioridades [10, 20]: " << sumaEnRango(raiz, 10, 20) << endl;
    cout << "Menor tiempo en rango de prioridades [10, 15]: " << menorTiempoEnRango(raiz, 10, 15) << endl;

    return 0;
}
