#include "work.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>

#define TAILLEMAX 10


int getChmod(const char* path) {
    /* recupere les autorisations du fichier dont le chemin est donné en parametre */
    
	struct stat ret;
	
	if (stat(path, &ret) == -1) {
		return -1;
	}
	
	return (ret.st_mode & S_IRUSR) | (ret.st_mode & S_IWUSR) | (ret.st_mode & S_IXUSR) | /* owner */
	(ret.st_mode & S_IRGRP) | (ret.st_mode & S_IWGRP) | (ret.st_mode & S_IXGRP) | /* group */ (ret.st_mode & S_IROTH) | (ret.st_mode & S_IWOTH) | (ret.st_mode & S_IXOTH); /* other */
}


void setMode(int mode, char* path) {
    /* modifie les autorisations du fichier */
    
	char buff[100];
	sprintf(buff, "chmod %o %s", mode, path);
	system(buff);
}


WorkFile* createWorkFile(char* name) {
    /* cree un WorkFile dont le nom est donné en paramètre */
    
	WorkFile* wf = (WorkFile*)malloc(sizeof(WorkFile));
	wf->name = strdup(name);
	wf->hash = NULL;
	wf->mode = 0;
	
	return wf;
}


void liberer_wf(WorkFile* wf) {
    /* libère la mémoire allouée par un WorkFile */
    
	if (wf->name != NULL) {
		free(wf->name);
	}
	
	if (wf->hash != NULL) {
		free(wf->hash);
	}
	
	free(wf);
}


char* wfts(WorkFile* wf) {
    /* transforme un WorkFile en une chaine de caractères dont les champs seront séparés par un tabulation */
    
    char buff[1000];
    sprintf(buff, "%s\t%s\t%d", wf->name, wf->hash, wf->mode);
    
	return strdup(buff);
}


WorkFile* stwf(char* ch) {
    /* transforme une chaine de caractères représentant un WorkFile en un WorkFile */
    
    char name[1000] = "";
    char hash[65] = "";
    int mode;
	
    sscanf(ch, "%s\t%s\t%d", name, hash, &mode);
    
    WorkFile* wf = createWorkFile(name);
    wf->hash = strdup(hash);
    wf->mode = mode;
    
	return wf;
}


WorkTree* initWorkTree(void) {
    /* initialise un WorkTree */
    
	WorkTree* wt = (WorkTree*)malloc(sizeof(WorkTree));
	wt->tab = (WorkFile*)malloc(TAILLEMAX*sizeof(WorkFile));
	wt->size = TAILLEMAX;
	wt->n = 0;
	
	return wt;
}


void liberer_wt(WorkTree* wt) {
    /* libère l'espace mémoire alloué par un WorkTree */
    
	if (wt == NULL) {
		return ;
	}
	
	for (int i = 0; i < wt->n; i++) {
		if (wt->tab[i].name != NULL) {
			free(wt->tab[i].name);
		}
	
		if (wt->tab[i].hash != NULL) {
			free(wt->tab[i].hash);
		}
	}
	
	free(wt->tab);
	free(wt);
}


int inWorkTree(WorkTree* wt, char* name) {
    /* retourne l'indice dans lequel se situe le WorkFile dans le WorkTree, dont le nom est donné en paramètre. -1 si le tel WorkFile n'existe pas */
    
	for (int i = 0; i < wt->n; i++) {
		if (strcmp((wt->tab[i]).name, name) == 0) {
			return i;
		}
	}
	
	return -1;
}


int appendWorkTree(WorkTree* wt, char* name, char* hash, int mode) {
    /* ajoute un WorkFile dont les champs sont précisés en paramètre dans le WorkTree s'il y a de la place et qu'il n'existe pas déjà. Sinon, la fonction ne fait rien */
    
    if (inWorkTree(wt, name) == -1) {
        if (wt->n < wt->size) {
            wt->tab[wt->n].name = strdup(name);
            wt->tab[wt->n].mode = mode;
            
            if (hash != NULL) {
                wt->tab[wt->n].hash = strdup(hash);
            } else {
                wt->tab[wt->n].hash = NULL;
            }

            (wt->n)++;
            
            printf("Succes de l'ajout du fichier dans le WorkTree !\n");

            return 1;
        } else {
            printf("Plus de place dans le WorkTree !\n");
        }
    } else {
        printf("Fichier deja present dans le WorkTree !\n");
    }

    return 0;
}


char* wtts(WorkTree* wt) {
    /* convertit un WorkTree en une chaine de caractères dont les WorkFile seront séparés par un retour à la ligne */
    
    if (wt->n > 0) {
    	char* s = (char*)malloc(2000*sizeof(char));
    	char* ch = wfts(&(wt->tab[0]));
    	strcpy(s, ch);
    	free(ch);
    	
    	for (int i = 1; i < wt->n; i++) {
    		char* ch = wfts(&(wt->tab[i]));
    		strcat(s, "\n");
        	strcat(s, ch);
        	free(ch);
    	}
    	
    	return strcat(s, "\n");
    }
    
    return NULL;
}


WorkTree* stwt(char* s) {
    /* transforme une chaine dde caractères representant un WorkTree en un WorkTree */
    
    WorkTree* wt = initWorkTree();
    char name[100];
    char hash[100];
    int mode;
	int i = 0;
	int j = 0;
	
	while (s[i] != '\0') {
		char copy[1000] = "";
        while (s[i] != '\n' && s[i] != '\0') {
        	copy[j] = s[i];
        	i++;
        	j++;
        }
        
        if (s[i] == '\n') {
            //WorkFile* wf = stwf(copy);
            sscanf(copy, "%s\t%s\t%d", name, hash, &mode);
            appendWorkTree(wt, name, hash, mode);
            //liberer_wf(wf);
        }
        
        i++;
        j = 0;
	}
	
	return wt;
}


int wttf(WorkTree* wt, char* file) {
    /* ecrit un WorkTree dans un fichier */
    
    FILE *f = fopen(file, "w");
    
    if (f == NULL){
        printf("Erreur ouverture fichier %s\n", file);
        return 0;
    }
    
    printf("Ecriture du fichier...\n");
    
    char *s = wtts(wt);
    fprintf(f, "%s", s);

    fclose(f);
    
    free(s);
    printf("Succès de l'écriture du fichier !\n");
    
    return 1;
}


WorkTree* ftwt(char* file) {
    /* transforme un fichier représentant un WorkTree en un WorkTree */
    
    FILE *f = fopen(file, "r");
    
    if (f == NULL){
        printf("Erreur ouverture fichier %s\n", file);
        return NULL;
    }
    
    printf("Lecture du fichier...\n");
    char buff[256];
    char res[1000] = "";
    
    while (fgets(buff, 256, f) != NULL) {
        strcat(res, buff);
    }

    fclose(f);
    printf("Succès de la lecture du fichier !\n");
    
    return stwt(res);
}


char* blobWorkTree(WorkTree* wt) {
    /* effectue un enregistrement instantané d'un WorkTree */
    
    static char template[] = "fileXXXXXX";
    char fname[1000];
    strcpy(fname, template);
    mkstemp(fname);
    
    wttf(wt, fname);
    char* hash = sha256file(fname);
    char wt_path[100];
    char* hash_path = hashToPath(hash);
    strcpy(wt_path, hash_path);
    free(hash_path);
    
    char hashdir[3];
    sprintf(hashdir, "%c%c", hash[0], hash[1]);
    
    if (file_exists(hashdir) == 0) {
        char buff[9];
        sprintf(buff, "mkdir %s", hashdir);
        system(buff);
    }
    
    strcat(wt_path, ".t");
    cp(wt_path, fname);
    
    // suppression du fichier temporaire
    char buff[strlen(fname) + 4];
    sprintf(buff, "rm %s", fname);
    system(buff);
    
    return hash;
}


_Bool isFile(char* path, char* name) {
    /* retourne true si name situé dans le repertoire path est un fichier, false sinon */
    
    DIR* dir = opendir(path);
    
    if (dir == NULL) {
        printf("Error directory !\n");
        
        return false;
    }
    
    struct dirent *ep = NULL;
    
    while ((ep = readdir(dir)) != NULL) {
        if (strcmp(ep->d_name, name) == 0 && (ep->d_type != 4)) { // c'est un fichier
        	closedir(dir);
        	
            return true;
        }
    }
    
    closedir(dir);
    
    return false;
}


char* saveWorkTree(WorkTree* wt, char* path) {
    /* effectue un enregistrement instantané de tout le contenu du WorkTree situé dans path */
    
    for (int i = 0; i < wt->n; i++) {
        char chemin[strlen(path) + strlen(wt->tab[i].name) + 2];
        sprintf(chemin, "%s/%s", path, wt->tab[i].name);
        
        if (isFile(path, wt->tab[i].name) == 1) {
            printf("Commencement de blobFile du fichier %s...\n", wt->tab[i].name);
            blobFile(chemin);
            printf("Fin du blobFile du fichier %s !\n", wt->tab[i].name);
            
            wt->tab[i].hash = sha256file(chemin);
            wt->tab[i].mode = getChmod(chemin);
        } else {
            WorkTree* newWT = initWorkTree();
            List* L = listdir(chemin);
            Cell* tmp = *L;
            
            while (tmp) {
                appendWorkTree(newWT, tmp->data, NULL, 0);
                tmp = tmp->next;
            }
            
            liberer_list(L);
            
            wt->tab[i].hash = saveWorkTree(newWT, chemin);
            wt->tab[i].mode = getChmod(chemin);
            
            liberer_wt(newWT);
        }
        
    }
    
    return blobWorkTree(wt);
}


void restoreWorkTree(WorkTree* wt, char* path) {
    /* restaure le WorkTree donné en paramètre et situé dans path */
    
    for (int i = 0; i < wt->n; i++) {
    	char* hash_path = hashToPath(wt->tab[i].hash);
        char wt_hash[100];
        strcpy(wt_hash, hash_path);
        
        free(hash_path);
        
        char* chemin = (char*)malloc(1000*sizeof(char));
        sprintf(chemin, "%s/%s", path, wt->tab[i].name);
        
        if (file_exists(wt_hash) == 1) { // c'est un fichier
            cp(chemin, wt_hash);
            setMode(wt->tab[i].mode, chemin);
            
        } else {
            if (file_exists(strcat(wt_hash, ".t")) == 1) { // c'est un repertoire
                WorkTree* newWT = ftwt(wt_hash);
                restoreWorkTree(newWT, chemin);
                setMode(wt->tab[i].mode, chemin);
                
                liberer_wt(newWT);
  
            } else {
                printf("Fichier %s inexistante dans le repertoire courant\n", wt->tab[i].name);
            }
        }
        
        free(chemin);
    }
}




