#include "list.h"
#include "work.h"
#include "commit.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define TAILLEMAX 7


kvp* createKeyVal(char* key, char* val) {
    /* initialise un élément dont les champs sont donnés en paramètres */
    
    kvp* e = (kvp*)malloc(sizeof(kvp));
    
    if (key != NULL) {
    	e->key = strdup(key);
    } else {
    	e->key = NULL;
    }
    
    if (key != NULL) {
    	e->value = strdup(val);
    } else {
    	e->value = NULL;
    }
    
    return e;
}


void freeKeyVal(kvp* kv) {
    /* libere l'espace mémoire alloué par un élément */
    
    free(kv->key);
    free(kv->value);
    free(kv);
}


char* kvts(kvp* k) {
    /* transforme un élément en une chaine de caractères au format 'key : value' */
    
    char* s = (char*)malloc(1000*sizeof(char));
    
    sprintf(s, "%s : %s", k->key,k->value);
    
    return s;
}


kvp* stkv(char* str) {
    /* transforme une chaine de caractères représentant un élément en un élément */
    
    char cle[100];
    char val[100];
    
    sscanf(str, "%s : %[^\n]", cle, val);
    
    return createKeyVal(cle, val);
}


Commit* initCommit(void) {
    /* initialise un commit */
    
    Commit* c = (Commit*)malloc(sizeof(Commit));
    c->T = (kvp**)malloc(TAILLEMAX*sizeof(kvp*));
    c->n = 0;
    c->size = TAILLEMAX;
    
    for (int i = 0; i < c->size; i++) {
        c->T[i] = NULL;
    }
    
    return c;
}


void freeCommit(Commit* c) {
    /* libère l'espace mémoire alloué par un Commit */
    
	for (int i = 0; i < c->size; i++) {
		if (c->T[i] != NULL) {
			freeKeyVal(c->T[i]);
		}
	}
	
	free(c->T);
	free(c);
}


unsigned long hashF(char* str) {
    /* fonction de hachage */
    
    unsigned long hash = 5831;
    
    for (int i = 0; str[i] != '\0'; i++) {
        hash = hash * 33 + str[i];
    }
    
    return hash;
}


void commitSet(Commit* c, char* key, char* value) {
    /* ajoute un élément au Commit, dont les champs sont donnés en paramètres */
    
    if (c->n < c->size) {
        int i = hashF(key)%(c->size);

        while (c->T[i] != NULL) {
            i = (i + 1)%(c->size);
        }

        c->T[i] = createKeyVal(key, value);
        (c->n)++;
        
    } else {
        printf("Plus d'espace !\n");
    }
}


Commit* createCommit(char* hash) {
    /* crée un Commit en insérant l'élément obligatoire dont la clé est "tree" et la valeur est donné en paramètre */
    
    Commit* c = initCommit();
    commitSet(c, "tree", hash);
    
    return c;
}


char* commitGet(Commit* c, char* key) {
    /* renvoie la valeur associé à la clé key du Commit s'il existe, NULL sinon */
    
    int i = hashF(key)%(c->size);
    int j = 0;
    
    while (c->T[i] != NULL && j < c->size) {
        if (strcmp(c->T[i]->key, key) == 0) {
            return c->T[i]->value;
        }
        
        i = (i + 1)%(c->size);
        j++;
    }
    
    return NULL;
}


char* cts(Commit* c) {
    /* transforme un Commit en une chaine de caractères. Chaque élément seront séparés par des retours à la ligne */
    
    char s[2000] = "";
    
    for (int i = 0; i < c->size; i++) {
        if (c->T[i] != NULL) {
        	char* ch = kvts(c->T[i]);
            strcat(s, ch);
            free(ch);
            strcat(s, "\n");
        }
    }
    
    return strdup(s);
}


Commit* stc(char* ch) {
    /* transforme une chaine de caractères représentant un Commit en un Commit */
    
    Commit* c = initCommit();
    int i = 0;
    int j = 0;
    
    while (ch[i] != '\0') {
    	char ligne[256] = "";
        while (ch[i] != '\n' && ch[i] != '\0') {
            ligne[j] = ch[i];
            j++;
            i++;
        }
        
        kvp* kv = stkv(ligne);

        commitSet(c, kv->key, kv->value);
        
        freeKeyVal(kv);
        i++;
        j = 0;
    }
    
    
    return c;
}


void ctf(Commit* c, char* file) {
    /* ecrit un Commit dans un fichier */
    
    FILE* f = fopen(file, "w");
    
    if (f == NULL) {
        printf("Erreur ouverture du fichier !\n");
        return ;
    }
    
    printf("Ecriture du fichier en cours...\n");
    char* s = cts(c);
    fprintf(f, "%s", s);
    
    free(s);
    
    fclose(f);
    printf("Succès de l'écriture du fichier !\n");
}


Commit* ftc(char* file) {
    /* transforme un fichier représentant un Commit en un Commit */
    
    FILE *f = fopen(file, "r");
    
    if (f == NULL){
        printf("Erreur ouverture fichier %s\n", file);
        return NULL;
    }
    
    printf("Lecture du fichier...\n");
    char buff[10000];
    char res[10000] = "";
    
    while (fgets(buff, 10000, f) != NULL) {
        strcat(res, buff);
    }
    
    fclose(f);
    printf("Succès de la lecture du fichier !\n");
    
    return stc(res);
}


char* blobCommit(Commit* c) {
    /* effectue un enregistrement instantané d'un Commit */
    
    static char template[] = "fileXXXXXX";
    char fname[1000];
    strcpy(fname, template);
    mkstemp(fname);
    
    ctf(c, fname);
    char* hash = sha256file(fname);
    char c_path[100];
    char* hash_path = hashToPath(hash);
    strcpy(c_path, hash_path);
    free(hash_path);
    
    char hashdir[3];
    sprintf(hashdir, "%c%c", hash[0], hash[1]);
    
    if (file_exists(hashdir) == 0) {
        char buff[9];
        sprintf(buff, "mkdir %s", hashdir);
        system(buff);
    }
    
    strcat(c_path, ".c");
    cp(c_path, fname);
    
    // suppression du fichier temporaire
    char buff[2000];
    sprintf(buff, "rm %s", fname);
    system(buff);
    
    return hash;
}


void initRefs(void) {
    /* crée le répertoire caché .refs s'il n'existe pas, avec les références master et HEAD */
    
    if (file_exists(".refs") == 0) { // n'existe pas
        system("mkdir .refs");
        system("touch .refs/master");
        system("touch .refs/HEAD");
    }
}


void createUpdateRef(char* ref_name, char* hash) {
    /* crée la référence ref_name si elle n'existe pas, puis met à jour son contenu par hash */
    
    char path_ref_name[strlen(ref_name) + 7];
    sprintf(path_ref_name, ".refs/%s", ref_name);
    
    if (file_exists(path_ref_name) == 0) {
        char create_ref[strlen(ref_name) + 13];
        sprintf(create_ref, "touch .refs/%s", ref_name);
        system(create_ref);
    }
    
    FILE *f = fopen(path_ref_name, "w");
    
    if (f == NULL) {
        printf("Erreur ouverture du fichier !\n");
        return ;
    }
    
    fprintf(f, "%s\n", hash);
    
    fclose(f);
}


void deleteRef(char* ref_name) {
    /* supprime la référence ref_name si elle existe */
    
    char path_ref_name[strlen(ref_name) + 7];
    sprintf(path_ref_name, ".refs/%s", ref_name);
    
    if (file_exists(path_ref_name) == 1) {
        char del_ref_name[strlen(ref_name) + 10];
        sprintf(del_ref_name, "rm .refs/%s", ref_name);
        
        system(del_ref_name);
    } else {
        printf("La reference %s n'existe pas\n", ref_name);
    }
}


char* getRef(char* ref_name) {
    /* retourne le contenu de la référence donnée en paramètre */
    
    char path_ref_name[100];
    sprintf(path_ref_name, ".refs/%s", ref_name);
    
    if (file_exists(path_ref_name) == 1) {
        FILE* f = fopen(path_ref_name, "r");
        
        if (f == NULL) {
            printf("Erreur ouverture du fichier !\n");
            return NULL;
        }
        
        char buff[100];
        
        if (fgets(buff, 100, f) == NULL) {
        	fclose(f);
            return "";
            
        } else {
            buff[strlen(buff) - 1] = '\0';
            fclose(f);
            return strdup(buff);
        }
        
    }
    
    printf("La reference %s n'existe pas\n", ref_name);
    
    return NULL;
}


void myGitAdd(char* file_or_folder) {
    /* ajoute le fichier ou répertoire dans la zone de préparation */
    
    WorkTree* wt;
    
    if (file_exists(".add") == 0) { // n'existe pas
        system("touch .add");
        wt = initWorkTree();
    } else {
        wt = ftwt(".add");
    }
    
    if (file_exists(file_or_folder) == 1) {
        appendWorkTree(wt, file_or_folder, NULL, 0);
        wttf(wt, ".add");
    } else {
        printf("Le fichier ou repertoire %s n'existe pas\n", file_or_folder);
    }
    
    liberer_wt(wt);
}


void myGitCommit(char* branch_name, char* message) {
    /* crée un point de sauvegarde, avec un message donné en paramètre */
    
    if (file_exists(".refs") == 0) {
        printf("Initialiser d'abord les references du projet\n");
        return ;
    }
     
    char path_branch_name[256];
    sprintf(path_branch_name, ".refs/%s", branch_name);
    
    if (file_exists(path_branch_name) == 0) {
        printf("La branche n'existe pas\n");
        return ;
    }
    
    char* hash_last = getRef(branch_name);
    char* hash_HEAD = getRef("HEAD");
    
    if (strcmp(hash_last, hash_HEAD) != 0) {
        printf("HEAD doit pointer sur le dernier commit de la branche\n");
        free(hash_last);
    	free(hash_HEAD);
    	
        return ;
    }
    
    WorkTree* wt = ftwt(".add");
    
    if (wt == NULL) {
        printf("Le fichier .add est vide ou n'existe pas\n");
        free(hash_last);
        free(hash_HEAD);
        
        return ;
    }
    
    system("rm .add");
    
    char* hash_wt = saveWorkTree(wt, ".");
    
    Commit* c = createCommit(hash_wt);
    
    FILE* f = fopen(path_branch_name, "r");
    char buff[100];
    
    if (fgets(buff, 100, f) != NULL) { // fichier non vide
        commitSet(c, "predecessor", hash_last);
    }
    
    fclose(f);
    
    if (message != NULL) {
        commitSet(c, "message", message);
    }
    
    char* hash_c = blobCommit(c);
    
    createUpdateRef(branch_name, hash_c);
    createUpdateRef("HEAD", hash_c);
    
    // libération
    free(hash_last);
    free(hash_HEAD);
	liberer_wt(wt);
	freeCommit(c);
    free(hash_wt);
    free(hash_c);
    
}
