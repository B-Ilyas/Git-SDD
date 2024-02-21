#include "list.h"
#include "work.h"
#include "commit.h"
#include "branch.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// test des fonctions du fichier branch.c


int main(void) {
    
    /*
    initBranch();
    */
   
    /*
    printf("branchExists master ? %d\n", branchExists("master"));
    printf("branchExists pig ? %d\n", branchExists("pig"));
     
   	createBranch("pig");
   	*/
   	
   	/*
    char* current_branch = getCurrentBranch();
    printf("getCurrentBranch : %s\n", current_branch);
    free(current_branch);
    */
    
    // printBranch("master");
    
    /*
    List* l1 = branchList("master");

    // affichage de la liste
    if (l1 != NULL) {
        Cell* tmp = *l1;
        
        while (tmp) {
            printf("%s\n", ctos(tmp));
            tmp = tmp->next;
        }
    }

	liberer_list(l1);
    */
    
    /*
    Commit* c1 = initCommit();
    commitSet(c1, "author", "Unknown");
    commitSet(c1, "title", "The sound of silence");
    
    Commit* c2 = initCommit();
    commitSet(c2, "author", "Professor");
    commitSet(c2, "title", "Manual for lazy people");

    ctf(c1, "essai/c1");
    ctf(c2, "essai/c2");

    myGitAdd("essai");
    myGitCommit("pig", "dossier 1");
    */
    
    /*
    List* l2 = getAllCommits();

    // affichage de la liste
    if (l2 != NULL) {
        Cell* tmp2 = *l2;
        
        while (tmp2) {
            printf("%s\n", ctos(tmp2));
            tmp2 = tmp2->next;
        }
    }
    
    liberer_list(l2);
    */

    
    // myGitCheckoutBranch("pig");
    
    
    // test de filterList
    
    List* L = initList();
    insertFirst(L, buildCell("file13414"));
    insertFirst(L, buildCell("file573924"));
    insertFirst(L, buildCell("fidl340134"));
    insertFirst(L, buildCell("01JFfjd"));
    
    // affichage de la liste avant
    printf("affichage de la liste avant de la filtrer\n");
    Cell* tmp = *L;
    while (tmp) {
        printf("%s\n", ctos(tmp));
        tmp = tmp->next;
    }
    
    List* nL = filterList(L, "file");
    
    // affichage de la liste apres
    printf("affichage de la liste apres\n");
    Cell* tmp2 = *nL;
    while (tmp2) {
    	printf("%s\n", ctos(tmp2));
        tmp2 = tmp2->next;
    }
    
    liberer_list(L);
    liberer_list(nL);
    
    
    return 1;
}
