// Juan Pablo Rinaldi

#include <stdio.h>
#define ESTADOFINAL -1
#define ESTADOINICIAL 0

typedef int estado; /* estado es un sinónimo de int */

/* Estructura usada para representar el codominio de la función de transición */
typedef struct accion_s {
  simbolo x; /* Símbolo que se escribirá en la cinta */
  movimiento m; /* Movimiento a efectuar */
  estado s; /* estado al que pasamos */
} accion;

/* máquina de turing 
0 es el estado inicial. estados cuenta cuántos estados hay que no son el final 
 Por ej: Si estados = 3 hay cuatro estados: -1(final), 0 (inicial), 1, 2*/
typedef struct maquina_s {
  int cant_estados; /* cantidad de estados */
  int cant_simbolos; /* cantidad de simbolos */
  simbolo *simbolos; /* lista de simbolos */
  accion **func_trans; /* función de transición */
} MT;

/* devuelve la posicion de un simbolo en un arreglo de simbolos */
int pos(simbolo *s, simbolo c)
{
  int i = 0;
  while(s[i] != c)
    i++;
  return i;
}

/* hace lugar para la tabla de transiciones 
  almacena espacio para estados*simbolos nodos de tipo accion */
void crear_func_trans(MT *m)
{
	int i;

	m -> func_trans = malloc (m -> cant_estados * sizeof(accion*));

	for (i=0; i < m -> cant_estados; i++)
	{
		m ->func_trans[i] = malloc( m -> cant_simbolos * sizeof(accion));
	}

}

/* hace lugar para guardar los simbolos */
void crear_simbolos(MT *m)
{
	m -> simbolos = malloc((m -> cant_simbolos) * sizeof(simbolo));
}


/* lee los simbolos de la máquina y los guarda en m.simbolos */
void leer_simbolos(MT *m)
{
	int i;

	for (i = 0; i < (m -> cant_simbolos); i++)
	{
		m -> simbolos[i] = getchar();
		getchar();
	}
}


/* lee la función de transicion */

void leer_func_trans(MT *m)
{
	int i = 0;
	int j = 0;
	int n = 0;
	char w;
	int veces = (m -> cant_simbolos) * (m -> cant_estados);
	
	while(veces--)
	{
		scanf("%d",&i);
		getchar();
		w = getchar();
		getchar();

		for( n = 0; n < (m -> cant_simbolos); n++ )
		{
			if (m -> simbolos[n] == w)	
			{
				j = n;
			}
		}
		
		(m -> func_trans[i][j]).x = getchar();
		getchar();
		(m -> func_trans[i][j]).m = getchar();
		getchar();
		scanf("%d",&(m -> func_trans[i][j]).s);	
	}
}
    
/* leer MT */
void leer_maquina(MT *m)
{
	scanf("%d %d\n", &(m->cant_estados), &(m->cant_simbolos));
	crear_simbolos(m); /* hace espacio para la cantidad de símbolos especificada */
	leer_simbolos(m); /* leemos los símbolos de la entrada */
	Blanco = (*m).simbolos[0]; /* el primer símbolo es el "blanco" */
	crear_func_trans(m);  /* hace espacio para la función de transición */
	leer_func_trans(m); /* lee los datos de la función de transición */
}


/* Imprime los datos de la máquina leída */
void imprimir_maquina(MT m)
{
	int n = 0, i = 0, j = 0;
	int count = m.cant_simbolos;
		
	printf("\nEstados = %d\n\n",m.cant_estados);
	printf("Simbolos (%d):",m.cant_simbolos);
	
	for ( i = 0; i < m.cant_simbolos; i++)
	{
		printf(" %c",m.simbolos[i]);
	}
	
	printf("\n\nFuncion de transicion:\n");
	
	for( n = 0; n < (m.cant_simbolos); n++ )
	{
		printf("       %c ",m.simbolos[n]);
	}
	
	printf("\n");
	
	while (count--)
	{
		printf("----------");
	}
	
	printf("\n");
	
	for ( i = 0; i < m.cant_estados; i++ )
	{
		printf(" %d | ",i);
		for ( j = 0; j < m.cant_simbolos; j++ )
		{
			if (m.func_trans[i][j].s != -1)
			{
				printf("%c %c  %d   ",m.func_trans[i][j].x,m.func_trans[i][j].m,m.func_trans[i][j].s);
			}
			
			if (m.func_trans[i][j].s == -1)
			{
				printf("%c %c %d   ",m.func_trans[i][j].x,m.func_trans[i][j].m,m.func_trans[i][j].s);
			}
		}
		printf("\n");
	}
	printf("\n\n");
}

 
void borrar_maquina(MT *m)
{
	int i = 0;
 
	for ( i = 0; i < (m -> cant_estados); i++ )
		free ( m -> func_trans[i] );

	free ( m -> simbolos );
}
