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
void MoverTarea(Lista *Pendientes,Lista *Realizadas,int id);
void MostrarTareas(Lista Tareas);
void LiberarLista(Lista Tareas);
void BuscarTareaPorId(Lista Tareas,int id);
void BuscarTareaPorPalabra(Lista Tareas,char *clave);
void LiberarMemoria(Lista Tareas);
void EliminarTareas(Lista Tareas, int eliminar);
void MostrarDatos(Lista Tareas);


int main(){
	int num=0,menu=0,destino,cont;
    int id,eliminar;
    char clave[50];
 	Lista Realizadas;
 	Lista Pendientes;
    Lista Proceso;
 	Realizadas=crearLista();
 	Pendientes=crearLista();
    Proceso=crearLista();
    while(menu!=8){
    printf("/////////MENU////////\n");
    printf("[0]Crear Tarea\n");
    printf("[1]Mostrar Tarea\n");
    printf("[2]Marcar tarea realizada\n");
    printf("[3]Buscar tarea por ID\n");
    printf("[4]Buscar traea por clave:\n");
    printf("[5]Eliminar tarea por ID:\n");
    printf("[6]Mostrar Datos:\n");
    printf("[7]Mover tareas pend realiz proc\n");
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
        printf("Ingrese el ID de la tarea realizada:\n");
        scanf("%d",&id);
        MoverTarea(&Pendientes,&Realizadas,id);
        break;
    
    case 3:
        printf("Buscar tareas por ID:\n");
        printf("Id :\n");
        scanf("%d",&id);
        BuscarTareaPorId(Realizadas,id);
        BuscarTareaPorId(Pendientes,id);
    case 4:

        printf("Buscar tareas por Clave:\n");
        printf("Clave :\n");
        scanf("%s",&clave);
        BuscarTareaPorPalabra(Realizadas,clave);
        BuscarTareaPorPalabra(Pendientes,clave);
        

    case 5:
        printf("Eliminar tarea buscada por id:\n");
        printf("Ingresar Id:\n");
        scanf("%d",&eliminar);
        EliminarTareas(Pendientes,eliminar);
        EliminarTareas(Realizadas,eliminar);

    case 6:
       MostrarDatos(Pendientes);
       MostrarDatos(Realizadas);
       MostrarDatos(Proceso);

    case 7:
    while(cont!=0&&destino!=9){
    printf("Realizadas:\n");
    MostrarTareas(Realizadas);
    printf("Pendientes:\n");
    MostrarTareas(Pendientes);
    printf("en Proceso:\n");
    MostrarTareas(Proceso);
    printf("Ingrese Id de la tarea con la que opera:\n");
    scanf("%d",&id);
    printf("Ingrese destino de la tarea :[1]Pendientes [2]Realizadas [3]Proceso\n");
    printf("Si desea eliminar marque [0]\n");
    printf("Si desea no hacer nada[9]\n");
    scanf("%d",&destino);
    if(destino==1){
        MoverTarea(&Realizadas,&Pendientes,id);
        MoverTarea(&Proceso,&Pendientes,id);
    }
    if(destino==2){
        MoverTarea(&Pendientes,&Realizadas,id);
        MoverTarea(&Proceso,&Realizadas,id);
    }

    if(destino==3){
        MoverTarea(&Pendientes,&Proceso,id);
        MoverTarea(&Realizadas,&Proceso,id);
    }

    if(destino==0){
        EliminarTareas(Pendientes,id);
        EliminarTareas(Realizadas,id);
        EliminarTareas(Proceso,id);
    }
    printf("Desea continuar si[1] no[0]\n");
    scanf("%d",&cont);

    if(cont==0){
        MostrarDatos(Realizadas);
        MostrarDatos(Pendientes);
        MostrarDatos(Proceso);
    }
    }

    case 8:
    printf("Salir:\n");
 
    
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

void MoverTarea(Lista *Pendientes,Lista *Realizadas,int id){
    struct Nodo *actual, *anterior;
    actual = *Pendientes;
    anterior = NULL;

    // Buscamos la tarea por su ID
    while(actual != NULL && actual->T.TareaID != id){
        anterior = actual;
        actual = actual->siguiente;
    }

    if(actual != NULL){
        // Si encontramos la tarea, la eliminamos de TareasPendientes
        if(anterior == NULL){
            *Pendientes = actual->siguiente;
        }else{
            anterior->siguiente = actual->siguiente;
        }

        // Agregamos la tarea a TareasRealizadas
        actual->siguiente = *Realizadas;
        *Realizadas = actual;

        printf("Tarea %d marcada como realizada.\n", id);
    }else{
        printf("No se encontró la tarea con ID %d.\n", id);
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

void BuscarTareaPorPalabra(Lista Tareas, char *clave){
    while(Tareas!=NULL){
        if(strstr(Tareas->T.Descripcion,clave)){
            printf("[ID:%d - Descripcion:%s - Duracion:%d]\n",Tareas->T.TareaID,Tareas->T.Descripcion,Tareas->T.Duracion);
           
        }
    }
}

void EliminarTareas(Lista Tareas, int id){
    Nodo* actual = Tareas;
    Nodo* anterior = NULL;

    while(actual!=NULL){
        if(actual->T.TareaID==id){ // encontramos la tarea
            if(anterior!=NULL){ // no es el primer elemento de la lista
                anterior->siguiente = actual->siguiente;
                printf("Tarea %d no encontrada en la lista.\n",id);
            }else{ // es el primer elemento de la lista
                Tareas= actual->siguiente;
            }
            printf("Tarea %d eliminada.\n",id);
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    
}

void MostrarDatos(Lista Tareas){
    int contDuracion=0, cant=0;
   while(Tareas!=NULL){
        contDuracion=contDuracion + Tareas->T.Duracion;
        cant++;
        Tareas=Tareas->siguiente;
   }

   printf("Cantidad de tareas : %d", cant);
   printf("Tiempo total de la lista: %d",contDuracion);

}








