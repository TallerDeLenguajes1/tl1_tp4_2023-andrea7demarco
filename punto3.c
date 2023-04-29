#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct Tarea{
	int TareaID; //Numerado en ciclo iterativo
	char *Descripcion; //
	int Duracion; // entre 10 – 100
}typedef Tarea;

struct Nodo{
	Tarea T;
	struct Nodo *siguiente;
}typedef Nodo;

typedef struct Nodo* Lista;

Lista crearLista();
Lista crearTarea(Lista Pendientes, int num);
void MostarTareas(Lista Pendientes);


int main(){
	int num=0;
 	Lista Realizadas;
 	Lista Pendientes;
 	Realizadas=crearLista();
 	Pendientes=crearLista();
	Pendientes=crearTarea(Pendientes,num);
    MostarTareas(Pendientes);
	return 0;
}

Lista crearLista(){
    Lista L;
    L=NULL;
    return L;
}

Lista crearTarea(Lista Pendientes, int num){
	struct Nodo* nuevo; 
	nuevo=malloc(sizeof(struct Nodo)); //reservo memoria dinámicamente para el nuevo nodo
    Tarea T;
	char buff[50];
	T.TareaID=num;
	srand(time(NULL));
	T.Duracion=rand()%100+10;
	printf("Ingrese la descripcion:\n");
	fflush(stdin);
	scanf("%s",&buff);
	T.Descripcion=malloc(sizeof(char*)*strlen(buff)+1);
	strcpy(T.Descripcion,buff);

	nuevo->T = T;
	nuevo->siguiente=Pendientes;
	Pendientes=nuevo;

    return Pendientes;
}

void MostarTareas(Lista Tareas){
	while(Tareas!=NULL){
		printf("[ID:%d - Descripcion:%s - Duracion:%d]\n",Tareas->T.TareaID,Tareas->T.Descripcion,Tareas->T.Duracion);
		Tareas=Tareas->siguiente;
	}
}

