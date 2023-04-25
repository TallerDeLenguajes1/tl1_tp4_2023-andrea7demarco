#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct Tarea
{
   int TareaID; //Numerado en ciclo iterativo
   char *Descripcion;
   int Duracion; // entre 10 -100
};
typedef struct Tarea Tareas;

void BuscarTarea(Tareas** realizadas,Tareas**pendientes, int contadorHecha,int contadorPendiente,int id);

int main(){
    char buff[500];
    int cant,i,sino,id;
	int contadorHecha=0,contadorPendiente=0; //declaro e inicializo contadores 
     //semilla
    printf("Cuantas tareas debe cargar:\n");
    scanf("%d",&cant); //(1)Desarrollar una interfaz por consola donde se solicite al usuario
    Tareas **tarea=(struct Tarea**)malloc(sizeof(struct Tarea*)*cant); //arreglo de doblo punt tipo Tarea 
	for(i=0; i<cant; i++){ 
    tarea[i]=NULL; //arreglo incializado en NULL (2)
    }
    for(i=0;i<cant;i++){ //(3)Carga las tareas
        tarea[i]=malloc(sizeof(struct Tarea*)); 
        tarea[i]->TareaID=i+1;
        printf("Ingresar la descripcion de la tarea:\n");
        fflush(stdin);
        gets(buff);
        tarea[i]->Descripcion=malloc(sizeof(char)*strlen(buff+1)); // reserva de memoria dinam para descr
        strcpy(tarea[i]->Descripcion,buff);
        tarea[i]->Duracion=rand()%100+10;
	    }
	    
	//tareas realizadas y  pendientes (4)
	//AMBOS tienen el mismo tamaño del arreglo anterior (cant)
	Tareas ** realizadas=(struct Tarea**)malloc(sizeof(struct Tarea*)*cant); 
	Tareas ** pendientes=(struct Tarea**)malloc(sizeof(struct Tarea*)*cant);
	//mostrar listado de tareas
	printf("///////////////////TAREAS A MOSTRAR///////////////\n");
	for(i=0;i<cant;i++){
		printf("------------------\n");
		printf("ID Tarea:%d\n",tarea[i]->TareaID);
		printf("Descripcion:%s\n",tarea[i]->Descripcion);
		printf("Duracion:%d\n",tarea[i]->Duracion);
		printf("Esta tarea FUE REALIZADA: SI[1] - NO[0]\n");
		scanf("%d",&sino);
		printf("------------------\n");
		
		if(sino==1){
			 //tareas realizadas (contador)
			 //se mueve dicha tarea a este arreglo(tareas realizadas)
			
			realizadas[contadorHecha]=tarea[i];  
			 tarea[i]=NULL; //una vez movida la tarea ese casillero del vector apunta a NULL
			contadorHecha++;
			
		} else {
			pendientes[contadorPendiente]=tarea[i];
			 tarea[i]=NULL;
			contadorPendiente++;
		}
	}
	
	//MOSTRAR LAS TAREAS REALIZADAS Y LISTAR LAS PENDIENTES
	printf("TAREAS REALIZADAS:\n ");
	for(i=0;i<contadorHecha;i++){
		
		printf("[ID:%d - Descripcion:%s - Duracion:%d ]\n",realizadas[i]->TareaID,realizadas[i]->Descripcion,realizadas[i]->Duracion);
		
	}
	printf("TAREAS PENDIENTES:\n");
	
	for(i=0;i<contadorPendiente;i++){
		
	printf("[ID:%d - Descripcion:%s - Duracion:%d ]\n",pendientes[i]->TareaID,pendientes[i]->Descripcion,pendientes[i]->Duracion);
		
	}

    // Buscar tarea
    printf("Ingrese id a buscar: ");
	scanf("%d",&id);
	
    BuscarTarea(realizadas,pendientes,contadorHecha,contadorPendiente, id);


    //poner al final - liberación memoria
    for(i=0;i<cant;i++){ //TAREAS
    	if(tarea[i]!=NULL){
    		free(tarea[i]->Descripcion);
    		free(tarea[i]);
		}
	}
    free(tarea);
    
    for(i=0;i<contadorHecha;i++){
    	if(realizadas[i]!=NULL){
    		free(realizadas[i]->Descripcion);
    		free(realizadas[i]);
		}
	}
	
	free(realizadas);
	
	for(i=0;i<contadorPendiente;i++){
		if(pendientes[i]!=NULL){
			free(pendientes[i]->Descripcion);
			free(pendientes[i]);
		}
		
	}
	
	free(pendientes);
    return 0;
}

void BuscarTarea(Tareas** realizadas,Tareas**pendientes, int contadorHecha,int contadorPendiente,int id){
	int i;
    for(i=0;i<contadorHecha;i++){
        if(realizadas[i]->TareaID == id){
            printf("[ID:%d - Descripcion:%s - Duracion:%d ]\n",realizadas[i]->TareaID, realizadas[i]->Descripcion, realizadas[i]->Duracion);
        }
	}
	for(i=0;i<contadorPendiente;i++){
		if(pendientes[i]->TareaID ==id){
			printf("[ID:%d - Descripcion:%s - Duracion:%d ]\n",pendientes[i]->TareaID, pendientes[i]->Descripcion, pendientes[i]->Duracion);
		}
	}
}


