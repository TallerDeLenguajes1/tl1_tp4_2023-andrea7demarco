


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
void BuscarTareaPorPalabra(Tareas** realizadas, Tareas** pendientes,int cant, char *clave );
int main(){
    char buff[500];
	char clave[50];
    int cant,i=0,j=0,rta,id;
 //declaro e inicializo contadores 
     //semilla
	 srand(time(NULL));

    printf("Cuantas tareas debe cargar:\n");
    scanf("%d",&cant); //(1)Desarrollar una interfaz por consola donde se solicite al usuario
	Tareas ** realizadas=(struct Tarea**)malloc(sizeof(struct Tarea*)*cant); 
	Tareas ** pendientes=(struct Tarea**)malloc(sizeof(struct Tarea*)*cant);

	for(i=0;i<cant;i++){
		realizadas[i]=NULL;
		pendientes[i]=NULL;
	}
    for(i=0;i<cant;i++){ //(3)Carga las tareas
	    pendientes[i]=malloc(sizeof(*(pendientes[i])));// asigna la cantidad de memoria necesaria para el puntero a Tareas en la posición i del arreglo pendientes.
        pendientes[i]->TareaID=i+1;
        printf("Ingresar la descripcion de la tarea:\n");
        fflush(stdin);
        gets(buff);
        pendientes[i]->Descripcion=malloc(sizeof(char)*strlen(buff)+1); // reserva de memoria dinam para descr
        strcpy(pendientes[i]->Descripcion,buff);
        pendientes[i]->Duracion=rand()%100+10;
	    }
	    
	//tareas realizadas y  pendientes (4)
	//AMBOS tienen el mismo tamaño del arreglo anterior (cant)

	//mostrar listado de tareas
	printf("///////////////////TAREAS A MOSTRAR///////////////\n");
	for(i=0;i<cant;i++){
		printf("------------------\n");
		printf("ID Tarea:%d\n",pendientes[i]->TareaID);
		printf("Descripcion:%s\n",pendientes[i]->Descripcion);
		printf("Duracion:%d\n",pendientes[i]->Duracion);
		printf("Esta tarea FUE REALIZADA: SI[1] - NO[0]\n");
		scanf("%d",&rta);
		printf("------------------\n");
		
		if(rta==1){
			realizadas[j]=pendientes[i];
			pendientes[i]=NULL;
			j++;

		} 
	}
	
	//MOSTRAR LAS TAREAS REALIZADAS Y LISTAR LAS PENDIENTES
	printf("TAREAS REALIZADAS:\n ");
	for(j=0;j<cant;j++){
		if(realizadas[j]!=NULL){
					printf("[ID:%d - Descripcion:%s - Duracion:%d ]\n",realizadas[j]->TareaID,realizadas[j]->Descripcion,realizadas[j]->Duracion);

		}
		
	}
	printf("TAREAS PENDIENTES:\n");
	
	for(i=0;i<cant;i++){
		if(pendientes[i]!=NULL){
printf("[ID:%d - Descripcion:%s - Duracion:%d ]\n",pendientes[i]->TareaID,pendientes[i]->Descripcion,pendientes[i]->Duracion);
		}
	
		
	}

	printf("Ingrese la palabra clave a buscar:\n");
	scanf("%s",&clave);
	fflush(stdin);
	BuscarTareaPorPalabra(realizadas,pendientes,cant,clave);

    //poner al final - liberación memoria
  
for(i=0;i<cant;i++){
    if(realizadas[i]!=NULL&&pendientes[i]!=NULL){
        free(pendientes[i]->Descripcion);
		free(pendientes[i]);
        free(realizadas[i]->Descripcion);
        free(realizadas[i]);
    }
}
free(pendientes);
free(realizadas);

    return 0;
}



void BuscarTareaPorPalabra(Tareas** realizadas, Tareas** pendientes,int cant, char *clave ){
	int i,encontrada=0;
	printf("Tareas buscadas por palabra clave:\n");
	    for(i=0;i<cant;i++){
			if(realizadas[i]!=NULL && encontrada==0){
                if(strstr(realizadas[i]->Descripcion,clave)){
					encontrada=1;
                    printf("[ID:%d - Descripcion:%s - Duracion:%d ]\n",realizadas[i]->TareaID, realizadas[i]->Descripcion, realizadas[i]->Duracion);
                }
			}

	}
	for(i=0;i<cant;i++){
		if(pendientes[i]!=NULL&&encontrada==0){
	           if(strstr(pendientes[i]->Descripcion,clave)){
				encontrada=1;
		         	printf("[ID:%d - Descripcion:%s - Duracion:%d ]\n",pendientes[i]->TareaID, pendientes[i]->Descripcion, pendientes[i]->Duracion);
		        }
		}

	}
	}



