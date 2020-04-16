// ----------------------------- arrdina.c -----------------------------
//  ---------------------------------------------------------------------
//        MODULO EN C PARA USO DE OBJETOS EN UNA ESTRUCTURA DE
//                   ARRAY'S DINµMICOS DE UNA DIMENSI‡N
//  ---------------------------------------------------------------------
//                INSTRUCCIONES PARA LA COMPILACION;
//		1.- Sustituya [tip] por una palabra significativa.
//  ---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arrdina.h"

struct ardi_int_rep   {
	int tamfis;
	int tamlog;
	struct ardi_int_typo *arr;
   };

//  ---------------------------------------------------------------------
//               	FUNCIONES PRIVADAS
//  ---------------------------------------------------------------------

void ardi_int_error (int error, char prim [20])     {

	switch (error)    {
		case 1: fprintf (stderr, "\n\t%s: Error, no hay memoria suficiente.\n", prim);
			break;
		case 2: fprintf (stderr, "\n\t%s: Error, el array no existe.\n", prim);
			break;
		case 3:	fprintf (stderr, "\n\t%s: Error, el array esta vacio.\n", prim);
			break;
		case 4:	fprintf (stderr, "\n\t%s: Error, tama§o < 1.\n", prim);
			break;
		case 5:	fprintf (stderr, "\n\t%s: Error, prim < 0.\n", prim);
			break;
		case 6:	fprintf (stderr, "\n\t%s: Error, count > elementos del array.\n", prim);
			break;
		case 7:	fprintf (stderr, "\n\t%s: Error, fuera de rango del array.\n", prim);
			break;
	  }
    }

//  ---------------------------------------------------------------------

struct ardi_int_typo *ardi_int_aloarr (int tamano)   {
	struct ardi_int_typo *arr;

	if (tamano == 0) return (NULL);
	else   {
		arr = (struct ardi_int_typo *) malloc (sizeof (struct ardi_int_typo) * tamano);
		if (arr == NULL)   {
		     ardi_int_error (1, "ardi_int_aloarr");
		     exit (1);
		   }
		return (arr);
	  }
   }

//   -------------------------------------------------------------------

ardi_int ardi_int_alo (int tamano)    {
	ardi_int p;

	p = (ardi_int) malloc (sizeof (struct ardi_int_rep));
	if (p == NULL)   {
	     ardi_int_error (1, "ardi_int_alo");
	     exit (1);
	   }

	p -> arr = ardi_int_aloarr (tamano);
	p -> tamfis = tamano;
	p -> tamlog = 0;
	return (p);
   }

//   -------------------------------------------------------------------

void ardi_int_daloarr (struct ardi_int_typo *arr)   {

	if (arr)   free (arr);
   }

//   -------------------------------------------------------------------

void ardi_int_dalo (ardi_int *p)    {

	if (*p != NULL)   {
	      ardi_int_daloarr ((*p) -> arr);
	      free (*p);
	      *p = NULL;
	 }
   }

//  ---------------------------------------------------------------------
//  		               	FUNCIONES PUBLICAS
//  ---------------------------------------------------------------------

ardi_int ardi_int_nuev ()  {
	ardi_int x;

	x = ardi_int_alo (0);
	return (x);
  }

//  ---------------------------------------------------------------------

ardi_int ardi_int_const (int tamano, struct ardi_int_typo valorinicial)   {
	ardi_int x;
	int i = 0, tamfis;

	if (tamano < 1)   {
		ardi_int_error (4, "ardi_int_const");
		exit (1);
	    }

	tamfis = (int) pow (2, ceil (log (tamano) / log (2)));
	x = ardi_int_alo (tamfis);
	while (i < tamano)     *(x -> arr+i++) = valorinicial;
	x -> tamlog = tamano;

	return (x);
  }

//  ---------------------------------------------------------------------

ardi_int ardi_int_copy (ardi_int a, int prim, int count)  {
	ardi_int x;
	int tamfis;

	if (!a)   {
		ardi_int_error (2, "ardi_int_copy");
		exit (1);
	   }
	if ((prim < 0) || (prim > a -> tamlog - 1))   {
		ardi_int_error (5, "ardi_int_copy");
		exit (1);
	   }
	if (count + prim - 1 > a -> tamlog - 1)   {
		ardi_int_error (6, "ardi_int_copy");
		exit (1);
	   }

	tamfis = (int) pow (2, ceil (log (count) / log (2)));
	x = ardi_int_alo (tamfis);
	memcpy (x -> arr, a -> arr + prim, count * sizeof (struct ardi_int_typo));
	x -> tamlog = count;

	return (x);
  }

//  ---------------------------------------------------------------------

int ardi_int_tamfis (ardi_int a)  {

	if (!a)   {
		ardi_int_error (2, "ardi_int_tamfis");
		exit (1);
	   }
	return (a -> tamfis);
   }

//  ---------------------------------------------------------------------

int ardi_int_tamlog (ardi_int a)  {

	if (!a)   {
		ardi_int_error (2, "ardi_int_tamlog");
		exit (1);
	   }
	return (a -> tamlog);
   }

//  ---------------------------------------------------------------------

int ardi_int_infe (ardi_int a)   {

	if (!a)   {
		ardi_int_error (2, "ardi_int_infe");
		exit (1);
	   }
	return (0);
   }

//  ---------------------------------------------------------------------

int ardi_int_supe (ardi_int a)   {

	if (!a)   {
		ardi_int_error (2, "ardi_int_supe");
		exit (1);
	   }
	return (a -> tamlog - 1);
   }

//  ---------------------------------------------------------------------

void ardi_int_obti (ardi_int a, int i, struct ardi_int_typo *e)     {

	if (!a)   {
		ardi_int_error (2, "ardi_int_obti");
		exit (1);
	   }
	if ((i < 0) || (i > a -> tamlog - 1))   {
		ardi_int_error (7, "ardi_int_obti");
		exit (1);
	   }

	*e = a -> arr [i];
  }

//  ---------------------------------------------------------------------

void ardi_int_asig (ardi_int a, int i, struct ardi_int_typo e)    {

	if (!a)   {
		ardi_int_error (2, "ardi_int_asig");
		exit (1);
	   }
	if (i < 0 || i > a -> tamlog - 1)   {
		ardi_int_error (7, "ardi_int_asig");
		exit (1);
	   }

	a -> arr [i] = e;
   }

//  ---------------------------------------------------------------------

void ardi_int_aumd (ardi_int a, struct ardi_int_typo e)   {
	struct ardi_int_typo *b;

	if (!a)   {
		ardi_int_error (2, "ardi_int_aumd");
		exit (1);
	   }

	if (!a -> tamlog)    *(a -> arr) = e;
	else if ((a -> tamlog) < (a -> tamfis))    a -> arr [a -> tamlog] = e;
	else   {
		b = ardi_int_aloarr (a -> tamfis * 2);
		memcpy (b, a -> arr, a -> tamfis * sizeof (struct ardi_int_typo));
		b [a -> tamlog] = e;
		ardi_int_daloarr (a -> arr);
		a -> arr = b;
		a -> tamfis *= 2;
	  }
	a -> tamlog++;
   }

//  ---------------------------------------------------------------------

void ardi_int_disd (ardi_int a, struct ardi_int_typo *e)   {
	struct ardi_int_typo *b;

	if (!a)   {
		ardi_int_error (2, "ardi_int_disd");
		exit (1);
	   }
	if (!a -> tamlog)   {
		ardi_int_error (3, "ardi_int_disd");
		exit (1);
	   }

	*e = a -> arr [a -> tamlog - 1];
	a -> tamlog--;

	if (a -> tamlog < (a -> tamfis / 2))   {
		b = ardi_int_aloarr (a -> tamfis / 2);
		memcpy (b, a -> arr, (a -> tamfis / 2) * sizeof (struct ardi_int_typo));
		ardi_int_daloarr (a -> arr);
		a -> arr = b;
		a -> tamfis /= 2;
	   }
   }

//  ---------------------------------------------------------------------

void ardi_int_dest (ardi_int *a)   {

	if (!*a)   {
		ardi_int_error (2, "ardi_int_dest");
		exit (1);
	   }
	ardi_int_dalo (a);
   }

//  --------------------------------------------------------------------

void ardi_int_swap (ardi_int a, int l, int r)   {
	struct ardi_int_typo aux;

	if (!a)   {
		ardi_int_error (2, "ardi_int_swap");
		exit (1);
	   }
	if (!a -> tamlog)   {
		ardi_int_error (3, "ardi_int_swap");
		exit (1);
	   }
	if (l < 0 || l > a -> tamlog - 1 || r < 0 || r > a -> tamlog - 1)   {
		ardi_int_error (7, "ardi_int_swap");
		exit (1);
	   }
	aux = a -> arr [l];
	a -> arr [l] = a -> arr [r];
	a -> arr [r] = aux;
   }

//  ---------------------------------------------------------------------

int ardi_int_bbin (ardi_int a, struct ardi_int_typo e,
			int (*cmp_int) (const void *, const void *))   {
	struct ardi_int_typo *t;

	if (!a)   {
		ardi_int_error (2, "ardi_int_bbin");
		exit (1);
	   }
	if (!a -> tamlog)   {
		ardi_int_error (3, "ardi_int_bbin");
		exit (1);
	   }

	t = (struct ardi_int_typo *) bsearch (&e, a -> arr, a -> tamlog,
		sizeof (struct ardi_int_typo), cmp_int);

	if (!t)   return (-1);
	else   return (t - a -> arr);
   }

//  ---------------------------------------------------------------------

int ardi_int_bsecd (ardi_int a, struct ardi_int_typo e,
			int (*cmp_int) (const void *, const void *))   {
	int i;

	if (!a)   {
		ardi_int_error (2, "ardi_int_bsecd");
		exit (1);
	   }

	if (a -> tamlog)
		for (i = a -> tamlog - 1; i >= 0; i--)
		      if (!cmp_int (&(a -> arr [i]), &e))    return (i);
	return (-1);
   }

//  ---------------------------------------------------------------------

int ardi_int_bseci (ardi_int a, struct ardi_int_typo e,
			int (*cmp_int) (const void *, const void *))    {
	int i;

	if (!a)   {
		ardi_int_error (2, "ardi_int_bseci");
		exit (1);
	   }

	if (a -> tamlog)
		for (i = 0; i <= a -> tamlog - 1; i++)
		      if (!cmp_int (&(a -> arr [i]), &e))    return (i);
	return (-1);
   }

//  ---------------------------------------------------------------------

void ardi_int_qsort (ardi_int a, int (*cmp_int) (const void *, const void *))   {

	if (!a)   {
		ardi_int_error (2, "ardi_int_qsort");
		exit (1);
	   }
	if (!a -> tamlog)   {
		ardi_int_error (3, "ardi_int_qsort");
		exit (1);
	   }

	qsort (a -> arr, a -> tamlog, sizeof (struct ardi_int_typo), cmp_int);
  }

//  ------------------------------------------------------------------

