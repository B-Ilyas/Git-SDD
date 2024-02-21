#ifndef _WORK_H_
#define _WORK_H_


typedef struct {
	char* name;
	char* hash;
	int mode;
} WorkFile;


typedef struct {
	WorkFile* tab;
	int size; // taille max
	int n; // couramment stocké
} WorkTree;


int getChmod(const char* path);
// recupere  les autorisations

void setMode(int mode, char* path);
// modifie les autorisations

WorkFile* createWorkFile(char* name);
// crée un WorkFile et l'initialise

void liberer_wf(WorkFile* wf);
// libere l'espace alloué par le wf

char* wfts(WorkFile* wf);
// convertit un WorkFile en chaine de caracteres contenant les différents champs séparés par des tabulations

WorkFile* stwf(char* ch);
// convertit une chaine de caracteres représentant un WorkFile en un WorkFile

WorkTree* initWorkTree(void);
// alloue un WorkTree de taille fixée et l'initialise

void liberer_wt(WorkTree* wt);
// libere l'espace alloué par le wt

int inWorkTree(WorkTree* wt, char* name);
// vérifie la présence d'un fichier ou répertoire dans un WorkTree. Elle retourne la position du fichier dans le tableau s'il est present et -1 sinon

int appendWorkTree(WorkTree* wt, char* name, char* hash, int mode);
// ajoute un fichier ou repertoire au WorkTree (s'il n'existe pas deja)

char* wtts(WorkTree* wt);
// convertit un WorkTree en chaine de caracteres contenant les différents WorkFile séparés par des retours-chariot

WorkTree* stwt(char* s);
// convertit une chaine de caracteres représentant un WorkTree en un WorkTree

int wttf(WorkTree* wt, char* file);
// ecrit dans le fichier file la chaine de caracteres représentant un WorkTree

WorkTree* ftwt(char* file);
// construit un WorkTree a partir d'un fichier qui contient sa représentation en chaine de caractères

char* blobWorkTree(WorkTree* wt);
// crée un fichier temporaire représentant le WorkTree pour pouvoir ensuite créer l'enregistrement instantané du WorkTree (avec l'extension ".t"). Elle retourne le hash du fichier temporaire

_Bool isFile(char* path, char* name);
// renvoie 1 si le fichier name dans path est un fichier, 0 sinon

char* saveWorkTree(WorkTree* wt, char* path);
// crée un enregistrement instantané de son contenu, puis de lui-meme

void restoreWorkTree(WorkTree* wt, char* path);
// restaure un WorkTree


#endif
