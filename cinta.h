// Juan Pablo Rinaldi

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char simbolo; /* símbolo, sinónimo de char */
simbolo Blanco;      /* el primer símbolo que será el "Blanco" de la MT. */
typedef char movimiento; /* Un movimiento es un char */

/* Celda de la cinta. 
 * Tiene un símbolo, un puntero a la izquierda y otro a la derecha */
typedef struct celda_s { 
  simbolo x;
  struct celda_s *sig;
  struct celda_s *ant;
} celda;

/* La cinta tiene: un puntero al primer símbolo,
 * un puntero al símbolo actual (donde está la cabeza de lectura) 
 * y un puntero al último símbolo */
typedef struct cinta_s {
  celda *pri;
  celda *ult;
  celda *actual;
} cinta;

/* agrega una nueva celda con el símbolo sim a la derecha de la cinta */
void agregar_der(cinta *c, simbolo sim)
{
	celda *celdanueva = malloc(sizeof(celda));
	celdanueva -> x = sim;
	celdanueva -> sig = NULL;
	c -> ult -> sig = celdanueva;
	celdanueva -> ant = c -> ult;
	c -> ult = celdanueva;
}

/* agrega una nueva celda con el simbolo sim a la izquierda de la cinta */
void agregar_izq(cinta *c, simbolo sim)
{
	celda *celdanueva = malloc(sizeof(celda));
	celdanueva -> x = sim;
	celdanueva -> ant = NULL;
	c -> pri -> ant = celdanueva;
	celdanueva -> sig = c -> pri;	
	c -> pri =  celdanueva;
}


/* guarda los n primeros valores del arreglo s en la cinta, poniendo la
 *  cabeza de lectura en el primero.  */
void guardar_cadena(cinta* c, simbolo *s, int n)
{
	int i = 0;
	celda *ce = malloc(sizeof(celda));
	ce -> x = s[0];
	c -> actual = ce;
	c -> pri = c -> actual;
	c -> ult = c -> actual;
	c -> actual -> sig = NULL;
	c -> actual -> ant = NULL;
	for (i = 1; i < n ; i++)
	{
		agregar_der(c, s[i]);	
	}
}
// 

/* mueve la cabeza de lectura a la izquierda. 
 * Si la cabeza está en el primer nodo, crea uno con un blanco y pone
 * la cabeza de lectura en este nodo */
void mov_izq(cinta *c)
{	
	if ( c -> actual -> ant != NULL )
	{
		c -> actual = c -> actual -> ant;
	}
	
	else
	{
		agregar_izq(c, Blanco);
		c -> actual = c -> pri;
	}
}


/* mueve la cabeza de lectura a la derecha, si actual es igual al último, 
 * agrega uno en blanco y pone la cabeza de lectura en este nuevo nodo */
void mov_der(cinta *c)
{
	if ( ((c -> actual) -> sig) != NULL )
	{
		c -> actual = (c -> actual) -> sig;
	}
	
	else
	{
		agregar_der(c, Blanco);
		c -> actual = c -> ult;
	}
}


/* escribe un símbolo en donde se encuentre la cabeza de lectura */
void escribir_sim(cinta *c, simbolo x)
{
	c -> actual -> x = x;
}


/* imprime la cinta */
void imprime_cinta(cinta c)
{
	celda *aux = c.pri;
	celda *aux2 = c.pri;
	
	while ( aux != NULL )
	{
		printf("| %c ", aux -> x);
		aux = aux -> sig;
	}
	
	printf("|\n");
	
	while ( aux2 != NULL )
	{
		if ( aux2 == c.actual )
		{
			printf("  ^ ");
		}
		else
		{
			printf("    ");
		}
		aux2 = aux2 -> sig;
	}
	
	printf("\n\n");
}


/* libera la memoria de todas las celdas de la cinta */
void borrar_cinta(cinta *c)
{
	while ( c -> pri -> sig != NULL )
	{
		c -> pri = c -> pri -> sig;
		free ( c -> pri -> ant );
	}
	
	free( c -> pri );
}
