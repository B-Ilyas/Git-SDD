#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>


int hashFile(char* source, char* dest) {
    /* calcule le hash du contenu du fichier source et l'ecrit dans le fichier dest */
    
    char buff[256];
    sprintf(buff, "cat %s | sha256sum > %s", source, dest);
    system(buff);
    
    return 1;
}


char *sha256file(char* file) {
    /* renvoie une chaine de caracteres contenant le hash du fichier donné en parametre */
    
    static char template[] = "fileXXXXXX";
    char fname[1000];
    strcpy(fname, template);
    mkstemp(fname);
    
    hashFile(file, fname);
    
    char res[65];
    FILE *f = fopen(fname, "r");
    
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier");
        
        return NULL;
    }
    
    fgets(res, 65, f);
    res[64] = '\0';
    
    fclose(f);
    
    char buff[10000];
    sprintf(buff, "rm %s", fname);
    system(buff);
    
    return strdup(res);
}


List* initList(void) {
    /* initialise une liste vide */
    
	List* L = (List*)malloc(sizeof(List));
    *L = NULL;
    
	return L;
}


Cell* buildCell(char *ch) {
    /* alloue et retorune une cellule de la liste */
    
	Cell* c = (Cell *)malloc(sizeof(Cell));
	c->data = strdup(ch);
	c->next = NULL;
	
	return c;
}


void insertFirst(List *L, Cell *C) {
    /* ajoute un element en tete de la liste */
    
	C->next = *L;
	*L = C;
}


char* ctos(Cell *c) {
    /* retourne une chaine de caracteres qu'elle represente */
    
    if (c != NULL) {
        return c->data;
    } else
        return NULL;
}


char* ltos(List* L) {
    /* transforme une liste en chaine de caracteres avec le format chaine1|chaine2|... */
    
    if (*L == NULL) {
        return "";
    }
    
	char *s = (char *)malloc(256*sizeof(char));
	Cell* tmp = *L;
    strcpy(s, tmp->data);
    
	while (tmp->next != NULL) {
		strcat(s, "|");
		strcat(s, tmp->next->data);
		tmp = tmp->next;
	}
    
	return s;
}


Cell* listGet(List* L, int i) {
    /* renvoie le ieme element d'une liste */
    
	Cell* tmp = *L;
	int k = 0;
	while ((k < i) && (tmp != NULL)) {
		k++;
		tmp = tmp->next;
	}
    
	if (tmp != NULL) {
        if (k == i) {
            return tmp;
        }
    } else {
        printf("INDEX OUT OF RANGE !\n");
    }
    
    return NULL;
}


Cell* searchList(List *L, char* str) {
    /* recherche un element dans une liste a partir de son contenu et renvoie une reference vers lui ou NULL s'il n'est pas dans la liste */

	Cell* tmp = *L;
	
	while ((tmp != NULL) && (strcmp(tmp->data, str) != 0)) {
		tmp = tmp->next;
	}
	
	if (tmp) {
		return tmp;
	} else {
		return NULL;
	}
}


List* stol(char* s) {
    /* transforme une chaine de caracteres representant une liste en une liste chainee */
    
	List* L = initList();
	int i = 0;
	int j;
	while (s[i] != '\0') {
		char *r = (char *)malloc(2000*sizeof(char));
		j = 0;
		while ((s[i] != '|') && (s[i] != '\0')) {
			r[j] = s[i];
			j++;
			i++;
		}
        
        if (s[i] == '|') {
            i++;
        }
		
		Cell* nc = buildCell(r);
		insertFirst(L, nc);
		
		free(r);
	}
	
	return L;
}


void ltof(List* L, char* path) {
    /* ecrit une liste dans un fichier */
    
	FILE *f = fopen(path, "w");
	
	if (f == NULL){
		printf("Erreur ouverture fichier %s\n", path);
		return;
	}
	
	printf("Ecriture du fichier...\n");
	Cell* tmp = *L;
	
    while (tmp != NULL) {
        fprintf(f, "%s\n", tmp->data);
        tmp = tmp->next;
    }
	
	fclose(f);
	printf("Succès de l'écriture du fichier !\n");
}


List* ftol(char* path) {
    /* lit une liste enregistree dans un fichier */
    
    List* L = initList();
	FILE *f = fopen(path, "r");
	
	if (f == NULL){
		printf("Erreur ouverture fichier %s\n", path);
		return NULL;
	}
	
	printf("Lecture du fichier...\n");
	char buff[256];
	
	while (fgets(buff, 256, f) != NULL) {
        buff[strlen(buff) - 1] = '\0'; // obligé de laisser.
		Cell* nc = buildCell(buff);
		insertFirst(L, nc);
	}

	fclose(f);
	printf("Succès de la lecture du fichier !\n");
	
	return L;
}
 

void liberer_cell(Cell* c) {
    /* libere l'espace memoire occupée par une cellule */
    
    Cell* suiv = NULL;
    
    while (c != NULL) {
        suiv = c->next;
        free(c->data);
        free(c);
        c = suiv;
    }
}


void liberer_list(List* l) {
    /* libere l'espace memoire occupée par une liste */
    
    liberer_cell(*l);
    free(l);
}


List* listdir(char* root_dir) {
    /* renvoie une liste contenant le nom des fichiers et repertoires qui s'y trouvent */
    
    List *L = initList();
    DIR* dp = opendir(root_dir);
    
    if (dp == NULL) {
        printf("Error directory\n");
        return NULL;
    }
    
    struct dirent *ep;
    while ((ep = readdir(dp)) != NULL) {
        if (strncmp(ep->d_name, ".", 1) != 0 && strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0) {
            insertFirst(L, buildCell(ep->d_name));
        }
    }
    
    closedir(dp);
    
    return L;
}


_Bool file_exists(char *file) {
    /* retourne true (= 1) si le fichier existe dans le repertoire courant et false (= 0) sinon */
    
    struct stat buffer;
    
    return (stat(file, &buffer) == 0);
}


void cp(char* to, char* from) {
    /* copie le contenu d'un fichier vers un autre, en faisant une lecture ligne par ligne du fichier source (from) */
    
    printf("Copie du fichier %s dans le fichier %s en cours...\n", from, to);
    if (file_exists(from) == 1) {
        List *L = ftol(from);
        ltof(L, to);
        
        liberer_list(L);
        
        printf("Succès de la copie du fichier %s dans le fichier %s\n", from, to);
        
    } else {
        
        printf("Fichier %s inexistante dans le repertoire courant\n", from);
    }
}


char* hashToPath(char* hash) {
    /* retourne le chemin d'un fichier a partir de son hash */
    
    char path[70] = "";
    path[0] = hash[0];
    path[1] = hash[1];
  	path[2] = '/';

    int i = 2;
    
    while (hash[i] != '\0') {
        path[i + 1] = hash[i];
        i++;
    }
    path[69] = '\0';
    
    return strdup(path);
}


void blobFile(char* file) {
    /* enregistre un instantané du fichier */
    
    char* hash = sha256file(file);
    char* hash_path = hashToPath(hash);
    
    char hashdir[3];
    sprintf(hashdir, "%c%c", hash_path[0], hash_path[1]);
    
    if (file_exists(hashdir) == 0) { // le repertoire n'existe pas
        char buff[9];
        sprintf(buff, "mkdir %s", hashdir);
        system(buff);
    }
    
    cp(hash_path, file);
    
    free(hash);
    free(hash_path);
}






