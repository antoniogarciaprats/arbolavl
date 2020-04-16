// ----------------------------- arrdina.h -----------------------------
//  ---------------------------------------------------------------------
//        MODULO DE CABECERAS PARA USO DE OBJETOS EN UNA ESTRUCTURA DE
//                   ARRAY'S DINµMICOS DE UNA DIMENSI‡N
//  ---------------------------------------------------------------------
//                INSTRUCCIONES PARA LA COMPILACION;
//		1.- Defina una estructura ardi_[tip]_typo.
//		2.- Sustituya [tip] por una palabra significativa.
//  ---------------------------------------------------------------------

#ifndef ARDI_INT_TYPO

#define ARDI_INT_TYPO

struct ardi_int_typo  {
	int x;
   };

typedef struct ardi_int_rep *ardi_int;

//  ---------------------------------------------------------------------

ardi_int ardi_int_nuev (void);
ardi_int ardi_int_const (int tamano, struct ardi_int_typo valorinicial);
ardi_int ardi_int_copy (ardi_int a, int prim, int count);
int ardi_int_tamfis (ardi_int a);
int ardi_int_tamlog (ardi_int a);
int ardi_int_infe (ardi_int a);
int ardi_int_supe (ardi_int a);
void ardi_int_obti (ardi_int a, int i, struct ardi_int_typo *e);
void ardi_int_asig (ardi_int a, int i, struct ardi_int_typo e);
void ardi_int_aumd (ardi_int a, struct ardi_int_typo e);
void ardi_int_disd (ardi_int a, struct ardi_int_typo *e);
void ardi_int_dest (ardi_int *a);
void ardi_int_swap (ardi_int a, int l, int r);
int ardi_int_bbin (ardi_int a, struct ardi_int_typo e,
	int (*cmp_int) (const void *, const void *));
int ardi_int_bsecd (ardi_int a, struct ardi_int_typo e,
	int (*cmp_int) (const void *, const void *));
int ardi_int_bseci (ardi_int a, struct ardi_int_typo e,
	int (*cmp_int) (const void *, const void *));
void ardi_int_qsort (ardi_int a, int (*cmp_int) (const void *, const void *));

#endif

//  -------------------------------------------------------------------------



