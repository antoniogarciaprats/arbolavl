// ------------------------------- avl.h -----------------------------
// ------------------------------------------------------------------------
// 	       MODULO DE CABECERAS PARA USO DE OBJETOS
//		   ARBOL BINARIO BALANCEADO (AVL)
// ------------------------------------------------------------------------
//	  	  INSTRUCCIONES PARA LA COMPILACION
//          1.- Define una estructura avl_[tip]_typo
//          2.- Sustituye [tip] por la palabra significativa
// ------------------------------------------------------------------------

#ifndef AVL_CHAR_TYPO

#define AVL_CHAR_TYPO

struct avl_char_typo   {
	char cadena [20];
	struct ardi_int_rep *punt_arr;
    };

typedef struct avl_char_ele *avl_char;

// ------------------------------------------------------------------------

avl_char avl_char_nuev (void);
int avl_char_vacio (avl_char a);
void avl_char_raiz (avl_char a, struct avl_char_typo *e);
void avl_char_mete (avl_char *a, struct avl_char_typo e,
		int (*cmp_char) (const void *, const void *));
void avl_char_saca (avl_char *a, struct avl_char_typo *e,
		int (*cmp_char) (const void *, const void *));
void avl_char_dest (avl_char *a);
void avl_char_copy (avl_char a, avl_char *d);
avl_char avl_char_find (avl_char a, struct avl_char_typo *e,
		int (*cmp_char) (const void *, const void *));
void avl_char_printf (avl_char a, int posicion);
void avl_char_glosario (FILE *fp, avl_char a);

#endif