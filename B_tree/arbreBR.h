
typedef int freq;
typedef struct table{
    char *str;
    freq f;
} tb;
typedef tb *mot;
typedef struct noeud{
	struct noeud *fg;
	char *str;
    freq f;
	struct noeud *fd;
} Noeud, *PNoeud;
typedef PNoeud Arbre_binaireR;
// fonctions
PNoeud creerNoeud(char *E){		/* Creer un nouveau noeud */
	PNoeud PN=(PNoeud)malloc(sizeof(Noeud));
	PN->str=E;
	PN->f = 1;
	PN->fg=PN->fd=NULL;
	return PN;
}
PNoeud CreerNoeud(char *E, freq f){		/* Creer un nouveau noeud */
	PNoeud PN=(PNoeud)malloc(sizeof(Noeud));
	PN->str=E;
	PN->f = f;
	PN->fg=PN->fd=NULL;
	return PN;
}
Arbre_binaireR construireArbre(Arbre_binaireR AG,Arbre_binaireR AD,PNoeud PN){		/* Construire un arbre a partir d'un noeud et deux sous arbres */
	PN->fg=AG;
	PN->fd=AD;
	return PN;
}



