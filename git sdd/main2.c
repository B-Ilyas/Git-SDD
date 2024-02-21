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


// test des fonctions du fichier work.c


int main(void) {
    
    /*
    // test de stwf
    char* s1 = "noname\tsd/3sofk1ckmqspekf\t777";
    WorkFile* wf1 = stwf(s1);

    // affichage du WorkFile
    printf("nom : %s hash : %s mode : %d\n", wf1->name, wf1->hash, wf1->mode);
    
    liberer_wf(wf1);
    
    // test de wfts
    char* res = wfts(wf1);
    printf("%s\n", res);
    
    free(res);
    */
    
    /*
    // creation d'un WorkTree wt
    WorkTree* wt1 = initWorkTree();
    
    // Pour TAILLEMAX = 10
    
    // test de appendWorkTree
    appendWorkTree(wt1, "piano", NULL, 0);
    appendWorkTree(wt1, "chaise", NULL, 0);
    appendWorkTree(wt1, "lama", NULL, 0);
    appendWorkTree(wt1, "clavier", NULL, 0);
    appendWorkTree(wt1, "musique", "vn1ldpzQLDez7DKFE2hlfod", 777);
    appendWorkTree(wt1, "chaise", "dlgot5fkef23KDPZQq43", 777); // ne doit pas marcher
    appendWorkTree(wt1, "boom", "4fkorvs5QVOE1GDgkrovpel", 101);
    
    // affichage de wt1
    for (int i = 0; i < wt1->n; i++) {
        printf("%s %s %d\n", wt1->tab[i].name, wt1->tab[i].hash, wt1->tab[i].mode);
    }

    printf("nombre d'elements dans le tableau : %d\ntaille max : %d\n", wt1->n, wt1->size);
	
    // test de inWorkTree
    printf("%d\n", inWorkTree(wt1, "lama"));
    printf("%d\n", inWorkTree(wt1, "baba"));
    
    // test de wtts
    char *s1 = wtts(wt1);
    printf("%s\n", s1);
    
    free(s1);
    liberer_wt(wt1);
    */
    
    /*
    // test de stwt
    char* s2 = "trousse\tivsjiejoizppakkclspoe\t777\nescalier\taifoizjspcjspcpzepof\t101\n";
   	WorkTree* wt2 = stwt(s2);
  
    // affichage de wt2
    for (int i = 0; i < wt2->n; i++) {
        printf("name %s hash %s mode %d\n", wt2->tab[i].name, wt2->tab[i].hash, wt2->tab[i].mode);
    }
	
    printf("nombre d'elements dans le tableau : %d\ntaille max : %d\n", wt2->n, wt2->size);
   
    // test de wttf
    wttf(wt2, "essai.txt");

    liberer_wt(wt2);
    */
    
    /*
    // test de ftwt
    WorkTree* wt3 = ftwt("essai.txt");
    
    // affichage de wt3
    printf("affichage de wt3 :\n");
    for (int i = 0; i < wt3->n; i++) {
        printf("%s %s %d\n", wt3->tab[i].name, wt3->tab[i].hash, wt3->tab[i].mode);
    }
    
    printf("nombre d'elements dans le tableau : %d\ntaille max : %d\n", wt3->n, wt3->size);
	
	
	liberer_wt(wt3);
	*/
	
    /*
    // test de blobWorkTree
    char* hash1 = blobWorkTree(wt3);
    printf("%s\n", hash1);
    
    free(hash1);
    liberer_wt(wt3);
    */
    
    /*                  
	printf("%d\n", isFile(".", "avril"));
    printf("%d\n", isFile(".", "00"));
    */
    
    
    WorkTree* couleur = initWorkTree();
    
    appendWorkTree(couleur, "rouge", NULL, 0);
    appendWorkTree(couleur, "vert", NULL, 0);
    appendWorkTree(couleur, "autres", NULL, 0);
    appendWorkTree(couleur, "date", NULL, 0);
    appendWorkTree(couleur, "bleu", NULL, 0);
    
    // affichage de couleur
    printf("affichage de couleur :\n");
    for (int i = 0; i < couleur->n; i++) {
        printf("%s %s %d\n", couleur->tab[i].name, couleur->tab[i].hash, couleur->tab[i].mode);
    }
    
    
    printf("nombre d'elements dans le tableau : %d\ntaille max : %d\n", couleur->n, couleur->size);
                         
    char* hash2 = saveWorkTree(couleur, "couleur");
    
    // affichage de couleur apres saveWT
    printf("affichage de couleur apres saveWT\n");
    for (int i = 0; i < couleur->n; i++) {
        printf("%s %s %d\n", couleur->tab[i].name, couleur->tab[i].hash, couleur->tab[i].mode);
    }
    
    free(hash2);

    FILE* f = fopen("couleur/bleu", "w");
    
    if (f == NULL) {
        printf("Erreur ouverture !\n");
    } else {
        
        fprintf(f, "Bleu foncé\n");
        
        fclose(f);
    }

    restoreWorkTree(couleur, "couleur");
    
    liberer_wt(couleur);
   	
    
    return 1;
}


