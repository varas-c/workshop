/*
 * workshop.c
 *
 *  Created on: Mar 22, 2017
 *      Author: varas
 */

#include <commons/collections/list.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int dni;
	char sexo;
	char nombre[20];
	char apellido[20];
	int edad;
}Persona;


void imprimir_opciones_de_menu_principal()
{
	printf("1-Cargar Personas\n");
	printf("2-Listar todo \n");
	printf("3-Buscar por DNI \n");
	printf("4-Eliminar todos los datos \n");
}

int leer_opcion_de_teclado()
{
	int opt;
	printf("Ingrese su opcion: ");
	scanf("%i",&opt);
	return opt;
}


Persona* new_persona()
{
	Persona* persona;
	persona = (Persona*) malloc(sizeof(Persona));
	return persona;
}



Persona* leer_persona_de_teclado()
{
	Persona *persona;
	persona = new_persona();

	printf("DNI: "); scanf("%i", &(persona->dni));

	printf("Sexo: "); getchar(); persona->sexo = getchar();

	printf("Nombre: ");fscanf(stdin,"%s",persona->nombre);

	printf("Apellido: ");fscanf(stdin,"%s",persona->apellido);

	printf("Edad: "); scanf("%d", &(persona->edad));

	printf("\n");

	return persona;

}

void cargar_nueva_persona(t_list* lista)
{
	Persona* persona = leer_persona_de_teclado();
	list_add(lista,persona);
}






void mostrar_persona_por_pantalla(Persona* persona)
{

	printf("DNI: %i \n", persona->dni);
	printf("Sexo: %c \n", persona->sexo);
	printf("Nombre: %s \n", persona->nombre);
	printf("Apellido: %s \n", persona->apellido);
	printf("Edad: %i \n", persona->edad);

	printf("\n****************************\n");

}



Persona* buscar_persona_por_dni(t_list* lista, int dni)
{

	int _buscarDNI_(Persona* p)
	{
		return p->dni == dni;
	}

	return list_find(lista, (void*) _buscarDNI_);
}






/*
 * Libera una persona
 */
void _free_persona_(Persona* p)
{
	free(p);
}

/*
 * Hace free a todos los elementos y destruye la lista
 */
void opc_free_todo_de_lista(t_list* lista)
{
	list_clean_and_destroy_elements(lista,_free_persona_);
}




//************************************************
//************************************************
//************************************************
//*********** SUBMENUES **************************
//************************************************
//************************************************
//************************************************


/*
 * Estos son los "submenues" que se llaman desde el menu principal
 */


//Opcion buscar por DNI, llama a las funciones necesasrias para buscar una persona por DNI
void opc_buscar_por_dni(t_list* lista)
{
	system("clear");
	int dni;
	printf("DNI buscado: "); scanf("%i",&dni);


	Persona* persona = NULL;
	persona = buscar_persona_por_dni(lista,dni);

	if(persona != NULL)
	{
		mostrar_persona_por_pantalla(persona);
	}

	else
	{
		printf("DNI %i - No encontrado \n", dni);
	}

}


//Opcion Listar personas, muestra a todas las personas por pantalla
void opc_listar_personas(t_list* lista)
{
	system("clear");
	list_iterate(lista,(void*)mostrar_persona_por_pantalla);
}


//Opcion Cargar persona, llama a las funciones necesarias para cargar uan nueva persona en la lista
void opc_cargar_personas(t_list* lista)
{
	system("clear");
	bool salir = false;
	char opc;
	while(!salir)
	{
		printf("Cargar persona? - y/n  : ");
		getchar();
		opc = getchar();

		switch(opc)
		{
		case 'y':
			cargar_nueva_persona(lista);
			break;
		case 'n':
			salir = true;
			break;
		default:
			printf("Opcion incorrecta\n");
		break;
		}
	}
}


//************************************************
//************************************************
//************************************************
//*********** MENU PRINCIPAL **************************
//************************************************
//************************************************
//************************************************


int main()
{

	t_list* listaDePersonas = list_create();

	bool salir_del_programa = false;
	int opc;

	while(!salir_del_programa)
	{
		imprimir_opciones_de_menu_principal();

		opc = leer_opcion_de_teclado();

		switch(opc)
		{
			case 0:
				salir_del_programa = true;
			break;
			case 1:
				opc_cargar_personas(listaDePersonas);
				printf("\n****************************\n");
			break;
			case 2:
				opc_listar_personas(listaDePersonas);
				printf("\n****************************\n");
			break;
			case 3:
				opc_buscar_por_dni(listaDePersonas);
				printf("\n****************************\n");
			break;
			default:
				printf("Opcion incorrecta");
				printf("\n****************************\n");
			break;
			case 4:
				opc_free_todo_de_lista(listaDePersonas);
				printf("\n****************************\n");
			break;
		}
	}


	return 0;
}
