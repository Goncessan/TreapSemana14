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
        Nodo* nNew = new Nodo(pid, prioridad, tiempo);
        nNew->pid = pid;
        nNew->prioridad = prioridad;
        nNew->tiempo = tiempo;
        nNew->prioridadHeap = rand();
        nNew->size = 1;
        nNew->sumTime = tiempo;
        
        return nNew;
    }
    
    if(prioridad < n->prioridad){
        n->izq = insertar(n->izq, pid, prioridad, tiempo);
        if(n->izq->prioridadHeap > n->prioridadHeap){
            rotarDerecha(n);
        }
    }else{
        n->der = insertar(n->der, pid, prioridad, tiempo);
        if(n->der->prioridadHeap > n->prioridadHeap){
            rotarIzquierda(n);
        }
    }
    
    actualizar(n);
    return n;
}


int main()

{
    cout<<"Hello World" << endl;

    return 0;
}
