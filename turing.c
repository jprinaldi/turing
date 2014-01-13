// Juan Pablo Rinaldi

#include <stdio.h>
#include "cinta.h"
#include "maquina.h"

/* evalua la maquina m con la entrada c */
// void evaluar(MT m, cinta *c);
void evaluar (MT m, cinta *c)
{
	int state = 0, i = 0, j = 0, k = 0;
	
	while ( state + 1 )
	{
		i = state;

		for ( k = 0; k < m.cant_simbolos; k++ )
		{
			if ( m.simbolos[k] == c -> actual -> x )
			{
				j = k;
			}
		}
		
		escribir_sim(c, m.func_trans[i][j].x);
		
		if ( m.func_trans[i][j].m == 'i' )
		{
			mov_izq(c);
		}
		
		if ( m.func_trans[i][j].m == 'd' )
		{
			mov_der(c);
		}
		
		state = m.func_trans[i][j].s;
	}
}

int main()
{
  MT m;
  cinta c;
  int i = 0,casos ,j;
  char entrada[1000];
  c.pri = c.ult = NULL;
  leer_maquina(&m);
  imprimir_maquina(m); /* imprime los datos de la máquina de Turing leída */
  scanf("%d\n", &casos); /* cuántas cadenas se leerán de la entrada */
  
  while(casos--) { 
    scanf("%s", entrada);
    guardar_cadena(&c, entrada, strlen(entrada)); /* guardamos en la cinta la entrada actual */
    printf("Cinta de entrada para el caso %d:\n",++i); 
    imprime_cinta(c); 
    evaluar(m, &c); /* evaluamos la máquina con esta entrada */
    printf("La cinta queda:\n");
    imprime_cinta(c);
    printf("La cadena%s es aceptada.\n\n\n", ((c.actual)->x != Blanco)?"": " no" ); /* la cadena es aceptada si la cabeza de lectura apunta a un símbolo que no es blanco */
    borrar_cinta(&c); /* Eliminamos todos los nodos de la cinta y pasamos al siguiente caso */
  }
  borrar_maquina(&m); /* liberamos la memoria asignada para la máquina */
  return 0;
}
