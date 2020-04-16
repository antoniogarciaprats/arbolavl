// ------------------------------- avl.c ----------------------------------
// ------------------------------------------------------------------------
// 	       MODULO DE CABECERAS PARA USO DE OBJETOS
//		   ARBOL BINARIO BALANCEADO (AVL)
// ------------------------------------------------------------------------
//	  	  INSTRUCCIONES PARA LA COMPILACION
//          1.- Sustituye [tip] por la palabra significativa
// ------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "avl.h"
#include "arrdina.h"

struct avl_char_ele    {
	struct avl_char_typo val;
	struct avl_char_ele *izq, *der;
	char altura;
    };

// ------------------------------------------------------------------------
//			FUNCIONES PRIVADAS
// ------------------------------------------------------------------------

void avl_char_error (char primit [20], int error)    {
	switch (error)    {
		case 1:	fprintf (stderr, "\n\t %s: No hay suficiente memoria.\n", primit);
			break;
		case 2: fprintf (stderr, "\n\t %s: El arbol binario esta vacio.\n", primit);
			break;
	  }
   }

// ------------------------------------------------------------------------

void avl_char_swap (struct avl_char_typo *a, struct avl_char_typo *b)    {
	struct avl_char_typo tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
   }

// ------------------------------------------------------------------------

int avl_char_max (int a, int b)    {

	return (a > b ? a : b);
   }

// ------------------------------------------------------------------------

int avl_char_altura (avl_char a)   {

	return (a == NULL ? -1 : a -> altura);
   }

// ------------------------------------------------------------------------

void avl_char_zig (avl_char *a)    {   // Rotacion simple a derechas
	avl_char b = (*a) -> izq;

	(*a) -> izq = b -> der;
	b -> der = *a;
	(*a) -> altura = avl_char_max (avl_char_altura ((*a) -> izq), avl_char_altura ((*a) -> der)) + 1;
	b -> altura = avl_char_max (avl_char_altura (b -> izq), (*a) -> altura) + 1;
	*a = b;
   }

// ------------------------------------------------------------------------

void avl_char_zag (avl_char *a)    {   // Rotacion simple a izquierdas
	avl_char b = (*a) -> der;

	(*a) -> der = b -> izq;
	b -> izq = *a;
	(*a) -> altura = avl_char_max (avl_char_altura ((*a) -> der), avl_char_altura ((*a) -> izq)) + 1;
	b -> altura = avl_char_max (avl_char_altura (b -> der), (*a) -> altura) + 1;
	*a = b;
    }

// ------------------------------------------------------------------------

void avl_char_zagzig (avl_char *a)   {   // Rotacion doble a derechas

	avl_char_zag (&(*a) -> izq);
	avl_char_zig (a);
    }

// ------------------------------------------------------------------------

void avl_char_zigzag (avl_char *a)   {  //Rotacion doble a izquierdas
	avl_char_zig (&(*a) -> der);
	avl_char_zag (a);
    }

// ------------------------------------------------------------------------
//			FUNCIONES PUBLICAS
// ------------------------------------------------------------------------

avl_char avl_char_nuev ()   {

	return (NULL);
   }

// ------------------------------------------------------------------------

int avl_char_vacio (avl_char a)   {

	return (a == NULL);
    }

// ------------------------------------------------------------------------

void avl_char_raiz (avl_char a, struct avl_char_typo *e)   {

	if (!a)    {
		avl_char_error ("avl_char_raiz", 2);
		exit (1);
	   }

	*e = a -> val;
    }

// ------------------------------------------------------------------------

void avl_char_mete (avl_char *a, struct avl_char_typo e,
		int (*cmp_char) (const void *, const void *))   {

	if (!*a)   {
		*a = (struct avl_char_ele *) malloc (sizeof (struct avl_char_ele));
		if (!*a)    {
			avl_char_error ("avl_char_mete", 1);
			exit (1);
		    }
		(*a) -> izq = (*a) -> der = NULL;
		(*a) -> val = e;
		(*a) -> altura = 0;
	  }
	else   {
	    if (cmp_char (&e, &(*a) -> val) < 0)    {
		 avl_char_mete (&(*a) -> izq, e, cmp_char);
		 if ((avl_char_altura ((*a) -> izq) - avl_char_altura ((*a) -> der)) == 2)
		    if (cmp_char (&e, &(*a) -> izq -> val) < 0)
			avl_char_zig (a);
		    else   avl_char_zagzig (a);
		 else (*a) -> altura = avl_char_max (avl_char_altura ((*a) -> izq), avl_char_altura ((*a) -> der)) + 1;
	      }

	    else if (cmp_char (&e, &(*a) -> val) > 0)   {
		 avl_char_mete (&(*a) -> der, e, cmp_char);
		 if ((avl_char_altura ((*a) -> izq) - avl_char_altura ((*a) -> der)) == -2)
		    if (cmp_char (&e, &(*a) -> der -> val) > 0)
			avl_char_zag (a);
		    else   avl_char_zigzag (a);
		 else (*a) -> altura = avl_char_max (avl_char_altura ((*a) -> izq), avl_char_altura ((*a) -> der)) + 1;
	      }

	    else;   // Entrada Duplicada
	 }
    }

// ------------------------------------------------------------------------

void avl_char_saca (avl_char *a, struct avl_char_typo *e,
		int (*cmp_char) (const void *, const void *))   {
	avl_char viejo;

	if (!*a)    {
		avl_char_error ("avl_char_saca", 2);
		exit (1);
	    }
	else  {
	    if (cmp_char (e, &(*a) -> val) < 0)    {
		 avl_char_saca (&(*a) -> izq, e, cmp_char);
		 if ((avl_char_altura ((*a) -> izq) - avl_char_altura ((*a) -> der)) == -2)
		    if ((avl_char_altura ((*a) -> der -> izq) - avl_char_altura ((*a) -> der -> der)) == 1)
			avl_char_zigzag (a);
		    else   avl_char_zag (a);
		 else (*a) -> altura = avl_char_max (avl_char_altura ((*a) -> izq), avl_char_altura ((*a) -> der)) + 1;
	      }

	    else if (cmp_char (e, &(*a) -> val) > 0)   {
		 avl_char_saca (&(*a) -> der, e, cmp_char);
		 if ((avl_char_altura ((*a) -> izq) - avl_char_altura ((*a) -> der)) == 2)
		    if ((avl_char_altura ((*a) -> izq -> izq) - avl_char_altura ((*a) -> izq -> der)) == -1)
			avl_char_zagzig (a);
		    else   avl_char_zig (a);
		 else (*a) -> altura = avl_char_max (avl_char_altura ((*a) -> izq), avl_char_altura ((*a) -> der)) + 1;
	      }

	    else   {
		if (!(*a) -> izq)    {
			viejo = *a;
			(*a) = (*a) -> der;
                        ardi_int_dest (&viejo -> val.punt_arr);
			free (viejo);
		   }
		else if (!(*a) -> der)    {
			viejo = *a;
			(*a) = (*a) -> izq;
                        ardi_int_dest (&viejo -> val.punt_arr);
			free (viejo);
		   }
		else   {
			viejo = (*a) -> izq;
			while (viejo -> der)	viejo = viejo -> der;
			avl_char_swap (&viejo -> val, &(*a) -> val);
			avl_char_saca (&(*a) -> izq, e, cmp_char);
			if ((avl_char_altura ((*a) -> izq) - avl_char_altura ((*a) -> der)) == -2)
			    if ((avl_char_altura ((*a) -> der -> izq) - avl_char_altura ((*a) -> der -> der)) == 1)
				avl_char_zigzag (a);
			    else   avl_char_zag (a);
			else (*a) -> altura = avl_char_max (avl_char_altura ((*a) -> izq), avl_char_altura ((*a) -> der)) + 1;
		   }
	      }
	 }
    }

// ------------------------------------------------------------------------

void avl_char_dest (avl_char *a)   {

	if (*a)   {
	      avl_char_dest (&(*a) -> izq);
	      avl_char_dest (&(*a) -> der);
	      ardi_int_dest (&(*a) -> val.punt_arr);
	      free (*a);
	      *a = NULL;
	 }
    }

// ------------------------------------------------------------------------

void avl_char_copy (avl_char a, avl_char *d)    {
	int prim = 0, count;

	if (a)   {
		*d = (struct avl_char_ele *) malloc (sizeof (struct avl_char_ele));
		if (!*d)    {
			avl_char_error ("avl_char_copy", 1);
			exit (1);
		    }
		strcpy ((*d) -> val.cadena, a -> val.cadena);
		(*d) -> altura = a -> altura;
		count = ardi_int_tamlog (a -> val.punt_arr);
		(*d) -> val.punt_arr = ardi_int_copy (a -> val.punt_arr, prim, count);

		avl_char_copy (a -> der, &(*d) -> der);
		avl_char_copy (a -> izq, &(*d) -> izq);
	    }
	 else *d = NULL;
    }

// ------------------------------------------------------------------------

avl_char avl_char_find (avl_char a, struct avl_char_typo *e,
		int (*cmp_char) (const void *, const void *))    {

	if (!a) return (NULL);
	if (cmp_char (&a -> val, e) > 0)
	      return (avl_char_find (a -> izq, e, cmp_char));
	else if (cmp_char (&a -> val, e) < 0)
	      return (avl_char_find (a -> der, e, cmp_char));
	else    {
		*e = a -> val;
		return (a);
	 }
   }

// ------------------------------------------------------------------------

void avl_char_printf (avl_char a, int posicion)     {

	if (a) {
		avl_char_printf (a -> der, posicion + 6);
		printf ("%*s %d \n", posicion, a -> val.cadena, a -> altura);
		avl_char_printf (a -> izq, posicion + 6);
	   }
    }

// -------------------------------------------------------------------------

void avl_char_glosario (FILE *fp, avl_char a)   {
	struct ardi_int_typo e, d;
	int tam, i;

	if (a)    {
	      avl_char_glosario (fp, a -> izq);
              tam = ardi_int_tamlog (a -> val.punt_arr);
              fprintf (fp, "%s", a -> val.cadena);
              fprintf (fp, "%c", ':');
              d.x = 0;
	      for (i = 0; i < tam; i++)   {
		     ardi_int_obti (a -> val.punt_arr, i, &e);
                     if (d.x != e.x)    {
                          fprintf (fp, "%c", ' ');
		          fprintf (fp, "%d", e.x);
                          fprintf (fp, "%c", ',');
                       }
                     d.x = e.x;
		 }
	      fprintf (fp, "%c", '\n');
	      avl_char_glosario (fp, a -> der);
	  }
   }

// -----------------------------------------------------------------------  