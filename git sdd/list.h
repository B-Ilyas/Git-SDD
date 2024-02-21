#ifndef _LIST_H_
#define _LIST_H_


typedef struct cell {
	char *data;
	struct cell *next;
} Cell;


typedef Cell* List;


int hashFile(char* source, char* dest);
// calcule le hash du contenu du fichier source et l'ecrit dans le fichier dest

char *sha256file(char* file);
// renvoie une chaine de caracteres contenant le hash du fichier donné en parametre

List* initList(void);
// initialise une liste vide

Cell* buildCell(char *ch);
// alloue et retorune une cellule de la liste

void insertFirst(List *L, Cell *C);
// ajoute un element en tete de la liste

char* ctos(Cell *c);
// retourne une chaine de caracteres qu'elle represente

char* ltos(List* L);
// transforme une liste en chaine de caracteres avec le format chaine1|chaine2|...

Cell* listGet(List* L, int i);
// renvoie le ieme element d'une liste

Cell* searchList(List *L, char* str);
// recherche un element dans une liste a partir de son contenu et renvoie une reference vers lui ou NULL s'il n'est pas dans la liste

List* stol(char* s);
// transforme une chaine de caracteres representant une liste en une liste chainee

void ltof(List* L, char* path);
// ecrit une liste dans un fichier

List* ftol(char* path);
// lit une liste enregistree dans un fichier

void liberer_cell(Cell* c);
// libere l'espace memoire occupée par cellule

void liberer_list(List* l);
// libere l'espace memoire occupée par une liste

List* listdir(char* root_dir);
// renvoie une liste contenant le nom des fichiers et repertoires qui s'y trouvent

_Bool file_exists(char *file);
// retourne 1 si le fichier existe dans le repertoire courant et 0 sinon

void cp(char *to, char *from);
// copie le contenu d'un fichier vers un autre, en faisant une lecture ligne par ligne du fichier source (from)

char* hashToPath(char* hash);
// retourne le chemin d'un fichier a partir de son hash

void blobFile(char* file);
// enregistre un instantané du fichier


#endif
