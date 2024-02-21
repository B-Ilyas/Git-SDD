#include "list.h"
#include "work.h"
#include "commit.h"
#include "branch.h"
#include "fusion.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// test des fonctions du fichier fusion.c


int main(void) {
    
    /*
    WorkTree* wt1 = initWorkTree();
    appendWorkTree(wt1, "clavier", "sksdo1k45fsdqq34522211pfiv", 101);
    appendWorkTree(wt1, "chaise", "dlgot5fkef23KDPZQq43", 777);
    appendWorkTree(wt1, "lama", "vlfpoel123LFEEKF3fldp", 777);
    
    // affichage de wt1
    printf("affichage de wt1 :\n");
    for (int i = 0; i < wt1->n; i++) {
        printf("%s %s\n", wt1->tab[i].name, wt1->tab[i].hash);
   	}
    
    WorkTree* wt2 = initWorkTree();
    appendWorkTree(wt2, "clavier", "lckQVOZMFKGspa3sdf1rpp", 101);
    appendWorkTree(wt2, "musique", "vn1ldpzQLDez7DKFE2hlfod", 777);
    appendWorkTree(wt2, "chaise", "dlgotf23KDPZQq43", 777);
    appendWorkTree(wt2, "boom", "4fkorvs5QVOE1GDgkrovpel", 101);
    
    // affichage de wt2
    printf("affichage de wt2 :\n");
    for (int i = 0; i < wt2->n; i++) {
        printf("%s %s\n", wt2->tab[i].name, wt2->tab[i].hash);
    }
    
    List* L = initList();
    List** conflicts = &L;
    
    WorkTree* nwt = mergeWorkTrees(wt1, wt2, conflicts);
    
    // affichage de la liste
    printf("affichage de conflicts :\n");
    Cell* tmp = **conflicts;
    while (tmp) {
        printf("%s\n", ctos(tmp));
        tmp = tmp->next;
    }
    
    // affichage de nwt, resultat de mergeWorkTrees
    printf("affichage de nwt :\n");
    for (int i = 0; i < nwt->n; i++) {
        printf("%s %s\n", nwt->tab[i].name, nwt->tab[i].hash);
    }
    
    liberer_wt(wt1);
    liberer_wt(wt2);
    liberer_wt(nwt);
    liberer_list(L);
	*/
    
	/*
    List* Lmerge = merge("master", "message");
    
    // affichage de la liste
    printf("affichage de conflicts :\n");
    Cell* tmp = *Lmerge;
    
    while (tmp) {
        printf("%s\n", ctos(tmp));
        tmp = tmp->next;
    }
    
    */
    
    return 1;
}

