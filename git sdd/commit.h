#ifndef _COMMIT_H_
#define _COMMIT_H_


typedef struct key_value_pair {
    char* key;
    char* value;
} kvp;


typedef struct hash_table {
    kvp** T;
    int n;
    int size;
} HashTable;


typedef HashTable Commit;


kvp* createKeyVal(char* key, char* val);
// initialise un element

void freeKeyVal(kvp* kv);
// libere la memoire associé à l'element

char* kvts(kvp* k);
// convertit un element en une chaine de caractere de la forme "cle : valeur"

kvp* stkv(char* str);
// convertit une chaine de caractere en un element

Commit* initCommit(void);
// initialise un commit de taille fixee

unsigned long hashF(char* str);
// fonction de hachage

void commitSet(Commit* c, char* key, char* value);
// insere une paire (key, value) dans la table

Commit* createCommit(char* hash);
// initialise un commit et ajoute l'element obligatoire correspondant a la cle "tree"

void freeCommit(Commit* c);
// libere un commit

char* commitGet(Commit* c, char* key);
// retourne la valeur dont la cle est key s'il existe, NULL sinon

char* cts(Commit* c);
// convertit un commit en chaine de caractere

Commit* stc(char* ch);
// convertit une chaine de caractere en un commit

void ctf(Commit* c, char* file);
// ecrit la chaine de caractere reprensetant le commit dans file

Commit* ftc(char* file);
// charge un commit depuis un fichier qui le represente

char* blobCommit(Commit* c);
// effectue un enregistrement instantane d'un commit

void initRefs(void);
// cree le repertoire caché .refs s'il n'existe pas, puis les fichiers master et HEAD

void createUpdateRef(char* ref_name, char* hash);
// met a jour une reference si elle existe, sinon on commence par creer le fichier

void deleteRef(char* ref_name);
// supprime une reference

char* getRef(char* ref_name);
// renvoie vers quoi pointe une reference (hash) si le fichier existe, sinon NULL. si c'est vide, renvoie ""

void myGitAdd(char* file_or_folder);
// ajoute le fichier ou répertoire dans la zone de préparation

void myGitCommit(char* branch_name, char* message);
// crée un point de sauvegarde, avec un message donné en paramètre


#endif
