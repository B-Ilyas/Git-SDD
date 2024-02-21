#include "list.h"
#include "work.h"
#include "commit.h"
#include "branch.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void initBranch(void) {
    /* initialise une branche nommée master */
    
    system("echo master > .current_branch");
}


int branchExists(char* branch) {
    /* renvoie 1 si la branche existe, 0 sinon */
    
    char path[strlen(branch) + 7];
    sprintf(path, ".refs/%s", branch);
    
    return file_exists(path);
}


void createBranch(char* branch) {
    /* crée une branche dont le nom est donné en paramètre */
    
	char* commit_head = getRef("HEAD");
    createUpdateRef(branch, commit_head);
    free(commit_head);
}


char* getCurrentBranch(void) {
    /* renvoie le nom de la branche courante */
    
    FILE* f = fopen(".current_branch", "r");
    
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        return NULL;
    }
    
    char buff[100];
    fscanf(f, "%s", buff);
    
    fclose(f);
    
    return strdup(buff);
}


void printBranch(char* branch) {
    /* affiche tous les commits de la branche. Pour chaque commit, la fonction affiche son hash et son message s'il en a */
    
    char* hash_c = getRef(branch);
    
    if (strcmp(hash_c, "") == 0) {
        printf("Aucun commit\n");
        return ;
    }
    
    char hash_path_c[100];
    char* hash_path = hashToPath(hash_c);
    sprintf(hash_path_c, "%s.c", hash_path);
    
    Commit* c = ftc(hash_path_c);
    
    while (c != NULL) {
    	
        if (commitGet(c, "message") != NULL) {
            printf("hash du commit : %s\nmessage : %s\n", hash_c, commitGet(c, "message"));
        } else {
            printf("hash du commit : %s\n", hash_c);
        }
        
        if (commitGet(c, "predecessor") != NULL) {
            strcpy(hash_c, commitGet(c, "predecessor"));
			free(hash_path);
            hash_path = hashToPath(hash_c);
           
            sprintf(hash_path_c, "%s.c", hash_path);
            
            freeCommit(c);
            
            c = ftc(hash_path_c);
        } else {
        	freeCommit(c);
            c = NULL;
        }
    }
    
    free(hash_c);
    free(hash_path);
}


List* branchList(char* branch) {
    /* retourne la liste chainee des hash de tous les Commit de la branche */
    
    List* L = initList();
    
    char* hash_c = getRef(branch);
    
    if (strcmp(hash_c, "") == 0) {
        return NULL;
    }
    
    char hash_path_c[100];
    char* hash_path = hashToPath(hash_c);
    sprintf(hash_path_c, "%s.c", hash_path);
    
    Commit* c = ftc(hash_path_c);
    
    while (c != NULL) {
        insertFirst(L, buildCell(hash_c));
        
        if (commitGet(c, "predecessor") != NULL) {
            strcpy(hash_c, commitGet(c, "predecessor"));
            free(hash_path);
            hash_path = hashToPath(hash_c);
            
            sprintf(hash_path_c, "%s.c", hash_path);
            
            freeCommit(c);
            
            c = ftc(hash_path_c);
        } else {
        	freeCommit(c);
            c = NULL;
        }
    }
    
    free(hash_c);
    free(hash_path);
    
    return L;
}


List* getAllCommits(void) {
    /* retourne la liste chainee des hash de tous les commits de toutes les branches */
    
    List* L = initList();
    List* all_refs = listdir(".refs");
    Cell* tmp = *all_refs;
    
    while (tmp != NULL) {
        List* branch_list = branchList(tmp->data);
        
        if (branch_list != NULL) {
            Cell* branch_cell = *branch_list;
            
            while (branch_cell != NULL) {
                if (searchList(L, branch_cell->data) == NULL) { // pour ne pas avoir de repetition
                    insertFirst(L, buildCell(branch_cell->data));
                }
                branch_cell = branch_cell->next;
            }
        }

        tmp = tmp->next;
        liberer_list(branch_list);
    }
    
    liberer_list(all_refs);
    
    return L;
}


void restoreCommit(char* hash_commit) {
    /* restaure le WorkTree associe au Commit dont le hash est donné en paramètre */
    
	char hash_c[100] = "";
	strcpy(hash_c, hash_commit);
	strcat(hash_c, ".c");
    char* hash_path_c = hashToPath(hash_c);
    
    Commit* c = ftc(hash_path_c);
    char hash_wt[100] = "";
    strcpy(hash_wt, commitGet(c, "tree"));
    strcat(hash_wt, ".t");
    char* hash_path_wt = hashToPath(hash_wt);
    
    WorkTree* wt = ftwt(hash_path_wt);
    restoreWorkTree(wt, ".");
    
	free(hash_path_c);
	free(hash_path_wt);
   	freeCommit(c);
    liberer_wt(wt);
}


void myGitCheckoutBranch(char* branch) {
    /* permet de se déplacer de la branche courante a la branche branch */
    
    FILE* f = fopen(".current_branch", "w");
    fprintf(f, "%s", branch);
    fclose(f);
    
    char* hash_c = getRef(branch);
    createUpdateRef("HEAD", hash_c);
    
    restoreCommit(hash_c);
    
    free(hash_c);
}


List* filterList(List* L, char* pattern) {
    /* renvoie la liste chainée des chaines de caractères qui commencent par la chaine pattern */
    
    List* nL = initList();
    Cell* tmp = *L;
    
    while (tmp != NULL) {
        if (strncmp(tmp->data, pattern, strlen(pattern)) == 0) {
            insertFirst(nL, buildCell(tmp->data));
        }
        
        tmp = tmp->next;
    }
    
    return nL;
}


void myGitCheckoutCommit(char* pattern) {
    /* restaure le WorkTree associe au commit dont le hash commence par la chaine pattern donné en paramètre. Si plusieurs ou aucun Commit ne possède un hash commencant par la chaine pattern, alors la fonction ne fait rien et affiche l'erreur associée */
    
	List* all_commits = getAllCommits();
    List* L_filt_c = filterList(all_commits, pattern);
    Cell* tmp = *L_filt_c;
    
    if (tmp == NULL) {
        printf("No pattern matching\n");
        
    } else {
        if (tmp->next == NULL) {
            createUpdateRef("HEAD", tmp->data);
            restoreCommit(tmp->data);

        } else {
            printf("Multiple machings found :\n");
            while (tmp) {
                printf("%s\n", ctos(tmp));
                tmp = tmp->next;
            }
            
            printf("Veuillez preciser la requete\n");
        }
    }
    
    liberer_list(L_filt_c);
    liberer_list(all_commits);
}
