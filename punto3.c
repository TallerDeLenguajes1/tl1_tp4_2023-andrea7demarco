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
Lista MoverTarea(Lista Pendientes,Lista Realizadas);
void MostrarTareas(Lista Tareas);
void LiberarLista(Lista Tareas);
void BuscarTareaPorId(Lista Tareas,int id);


int main(){
	int num=0,menu=0;
    int id;
 	Lista Realizadas;
 	Lista Pendientes;
 	Realizadas=crearLista();
 	Pendientes=crearLista();
    while(menu!=4){
    printf("////:::://///MENU////::::////\n");
    printf("[0]Crear Tarea\n");
    printf("[1]Mostrar Tarea\n");
    printf("[2]Marcar tarea realizada\n");
    printf("[3]Buscar tarea por ID\n");
    printf("[4]Salir:\n");
    fflush(stdin);
    scanf("%d",&menu);

    switch (menu)
    {
    case 0:
        Pendientes=crearTarea(Pendientes,num);
        num++;
        break;
    case 1:
        printf("Tareas PENDIENTES:\n");
        MostrarTareas(Pendientes);
        printf("Tareas Realizadas:\n");
        MostrarTareas(Realizadas);
        break;
    case 2:
        printf("marcar tareas realizadas");
        Realizadas=MoverTarea(Pendientes,Realizadas);
        break;
    
    case 3:
        printf("Buscar tareas por ID:\n");
        printf("Id :\n");
        scanf("%d",&id);
        BuscarTareaPorId(Realizadas,id);
        BuscarTareaPorId(Pendientes,id);
    
    default:
        break;
    }

    }

    //final // liberar memora //
    LiberarLista(Pendientes);
    LiberarLista(Realizadas);
    printf("FIN");
	return 0;


}

Lista crearLista(){
    Lista L;
    L=NULL;
    return L;
}

Lista crearTarea(Lista Pendientes, int num){ //creación dinámica de un nodo
	struct Nodo* nuevo; 
	nuevo=(struct Nodo*)malloc(sizeof(struct Nodo)); //reservo memoria dinámicamente para el nuevo nodo
    Tarea T;
	char buff[50];
	T.TareaID=num;
	srand(time(NULL));
	T.Duracion=rand()%100+10;
	printf("Ingrese la descripcion (TAREA[%d]):\n",T.TareaID);
	fflush(stdin);
	scanf("%s",&buff);
	T.Descripcion=malloc(sizeof(char*)*strlen(buff)+1);
	strcpy(T.Descripcion,buff);

	nuevo->T = T;
	nuevo->siguiente=Pendientes;
	Pendientes=nuevo;

    return Pendientes;
}

void MostrarTareas(Lista Tareas){
	while(Tareas!=NULL){
		printf("[ID:%d - Descripcion:%s - Duracion:%d]\n",Tareas->T.TareaID,Tareas->T.Descripcion,Tareas->T.Duracion);
		Tareas=Tareas->siguiente;
	}
}

void LiberarLista(Lista Tareas){
    Nodo* actual;
    while(Tareas!=NULL){
        actual = Tareas;
        Tareas=Tareas->siguiente;
        free(actual->T.Descripcion); 
        free(actual); 
    }
}

Lista MoverTarea(Lista Pendientes,Lista Realizadas){
    int id;
    	while(Pendientes!=NULL){
        printf("Ingrese el ID de la tarea realizada:\n");
        scanf("%d",&id);
		printf("[ID:%d]\n",Pendientes->T.TareaID);
		Pendientes=Pendientes->siguiente;

           Nodo* actual = Pendientes;
    Nodo* anterior = NULL;
    while(actual!=NULL){
        if(actual->T.TareaID==id){ // encontramos la tarea
            if(anterior!=NULL){ // no es el primer elemento de la lista
                anterior->siguiente = actual->siguiente;
            }else{ // es el primer elemento de la lista
                Pendientes = actual->siguiente;
            }
            // agregar tarea a lista de realizadas
            Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
            nuevo->T = actual->T;
            nuevo->siguiente = Realizadas;
            Realizadas = nuevo;
            printf("Tarea %d realizada y movida a la lista de realizadas.\n",id);

            
           return Realizadas;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    printf("Tarea %d no encontrada en la lista de pendientes.\n",id);

	}
 
}

void BuscarTareaPorId(Lista Tareas, int id){

    while(Tareas!=NULL){
        if(Tareas->T.TareaID==id){
            printf("[ID:%d - Descripcion:%s - Duracion:%d]\n",Tareas->T.TareaID,Tareas->T.Descripcion,Tareas->T.Duracion);

        }

	Tareas=Tareas->siguiente;
	}
}





