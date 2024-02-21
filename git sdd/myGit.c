#include "list.h"
#include "work.h"
#include "commit.h"
#include "branch.h"
#include "fusion.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Main principal


int main(int argc, char* argv[]) {
    // ./myGit init
    if (strcmp(argv[1], "init") == 0) {
        initRefs();
        initBranch();
    }
    
    // ./myGit list-refs
    if (strcmp(argv[1], "list-refs") == 0) {
        List* L = listdir(".refs");
        
        Cell* tmp = *L;
        while (tmp) {
            printf("%s\n", ctos(tmp));
            tmp = tmp->next;
        }
        
        liberer_list(L);
    }
    
    // ./myGit create-ref <name> <hash>
    if (strcmp(argv[1], "create-ref") == 0) {
        createUpdateRef(argv[2], argv[3]);
    }
    
    // ./myGit delete-ref <name>
    if (strcmp(argv[1], "delete-ref") == 0) {
        deleteRef(argv[2]);
    }
    
    // ./myGit add <elem> [<elem2> <elem3> ...]
    if (strcmp(argv[1], "add") == 0) {
        for (int i = 2; i < argc; i++) {
            myGitAdd(argv[i]);
        }
    }
    
    // ./myGit list-add
    if (strcmp(argv[1], "list-add") == 0) {
        if (file_exists(".add")) {
            system("cat .add");
        } else {
            printf("Le fichier .add n'existe pas\n");
        }
    }
    
    // ./myGit clear-add
    if (strcmp(argv[1], "clear-add") == 0) {
        system("rm .add");
        system("touch .add");
    }
    
    // ./myGit commit <branch_name> [-m <message>]
    if (strcmp(argv[1], "commit") == 0) {
        
        if (argc > 3 && strcmp(argv[3], "-m") == 0) {
            char message[2000] = "";
            strcpy(message, argv[4]);
            
            for (int i = 5; i < argc; i++) {
                strcat(message, " ");
                strcat(message, argv[i]);
            }

            myGitCommit(argv[2], message);
            
        } else {
            myGitCommit(argv[2], NULL);
        }
    }
        
    // ./myGit get-current-branch
    if (strcmp(argv[1], "get-current-branch") == 0) {
    	char* s = getCurrentBranch();
        printf("%s\n", s);
        free(s);
    }
    
    // ./myGit branch <branch_name>
    if (strcmp(argv[1], "branch") == 0) {
        if (branchExists(argv[2])) {
            printf("La branche %s existe deja !\n", argv[2]);
        } else {
            createBranch(argv[2]);
        }
    }
    
    // ./myGit branch-print <branch_name>
    if (strcmp(argv[1], "branch-print") == 0) {
        if (branchExists(argv[2])) {
            printBranch(argv[2]);
        } else {
            printf("La branche %s n'existe pas !\n", argv[2]);
        }
    }
    
    // ./myGit checkout-branch <branch_name>
    if (strcmp(argv[1], "checkout-branch") == 0) {
        if (branchExists(argv[2])) {
            myGitCheckoutBranch(argv[2]);
        } else {
            printf("La branche %s n'existe pas !\n", argv[2]);
        }
    }
    
    // ./myGit checkout-commit <pattern>
    if (strcmp(argv[1], "checkout-commit") == 0) {
        myGitCheckoutCommit(argv[2]);
    }
    
    // ./myGiy merge <branch> <message>
    if (strcmp(argv[1], "merge") == 0) {
    
        char message[2000] = "";
        strcpy(message, argv[3]);
        
        for (int i = 4; i < argc; i++) {
            strcat(message, " ");
            strcat(message, argv[i]);
        }
        
        List* conflicts = merge(argv[2], message);
        
        if (conflicts == NULL) { // pas de collision
			return 1;
			
        } else {
            char option[3];
            
            printf("Collision(s) entre les branches détectée(s).\nVoici la liste de conflits :\n\n");
            
            Cell* tmp1 = *conflicts;

    		while (tmp1) {
        		printf("\t%s\n", ctos(tmp1));
        		tmp1 = tmp1->next;
    		}
            
            char* current_branch = getCurrentBranch();
            
    		printf("\nChoisissez l'une des options suivantes :\n\t'1' - si vous souhaitez garder les versions de la branche courante (%s)\n\t'2' - si vous souhaitez garder les versions de la branche %s\n\t'3' - si vous souhaitez configurer manuellement\n", current_branch, argv[2]);
            
            fgets(option, 3, stdin);
            
            if (strstr(option, "1") != NULL) {
                printf("Vous avez choisi de garder la version de la branche courante.\n");
                
                createDeletionCommit(argv[2], conflicts, "Commit de suppression");
                List* confs1 = merge(argv[2], message);
                liberer_list(confs1);
                
            } else {
                if (strstr(option, "2") != NULL) {
                    printf("Vous avez choisi de garder la version de la branche %s.\n", argv[2]);
                    
                    createDeletionCommit(current_branch, conflicts, "Commit de suppression sur la branche courante");
                    List* confs2 = merge(argv[2], message);
                    liberer_list(confs2);
                    
                } else {
                    if (strstr(option, "3") != NULL) {
                        printf("Vous avez choisi de selectionner manuellement pour chaque conflit.\n");
                        char ouiounon[10];
                        
                        List* garde_rem = initList();
                        List* garde_cur = initList();
                        
                        Cell* tmp = *conflicts;
                        
                        while (tmp != NULL) {
                            printf("Voulez-vous garder la version du fichier %s de la branche courante ?\t'Oui'\t'Non'\n", tmp->data);
                            fgets(ouiounon, 10, stdin);
                            
                            Cell* cell = buildCell(tmp->data);
                            
                            if (strstr(ouiounon, "Oui") != NULL) {
                                insertFirst(garde_cur, cell);
                            } else {
                                if (strstr(ouiounon, "Non") != NULL) {
                                    insertFirst(garde_rem, cell);
                                } else {
                                    printf("Réponse non identifiée. Arret.\nVeillez à ecrire 'Oui' ou 'Non' la prochaine fois.\n");
                                    return 0;
                                }
                            }
                            
                            tmp = tmp->next;
                        }
                        
                        
                        createDeletionCommit(current_branch, garde_rem, "Commit de suppression sur la branche courante");
                        createDeletionCommit(argv[2], garde_cur, "Commit de suppression");
                        
                        merge(argv[2], message);
                        
                        liberer_list(garde_rem);
                        liberer_list(garde_cur);
                        
                    } else {
                        printf("Votre demande n'a pas été identifiée. Arret.\nVeillez à choisir entre '1', '2' ou '3' la prochaine fois.\n");
                    }
                
                }

            }
            
            free(current_branch);
        }
        
        liberer_list(conflicts);
        
    }
    
    
    return 1;
}
