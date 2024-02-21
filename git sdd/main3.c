#include "list.h"
#include "work.h"
#include "commit.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// test des fonctions du fichier commit.c


int main(void) {
 	
 	/*
    kvp* kv1 = createKeyVal("boite1", "chocolat");
    
    // affichage de kv1
   	printf("key : %s, value : %s\n", kv1->key, kv1->value);
    
    char* s1 = kvts(kv1);
    printf("%s\n", s1);
    
    free(s1);
    freeKeyVal(kv1);
    */
    
    /*
    kvp* kv2 = stkv("boite2 : caramel");
    
    // affichage de kv2
    printf("key : %s, value : %s\n", kv2->key, kv2->value);
    
    freeKeyVal(kv2);
   	*/
   	
	/*
    Commit* c1 = initCommit();
    commitSet(c1, "0", "lion");
    commitSet(c1, "1", "chat");
    commitSet(c1, "2", "dragon");
    
    // affichage de c1
    for (int i = 0; i < c1->size; i++) {
    	if (c1->T[i] != NULL) {
        	printf("key : %s, value : %s\n", c1->T[i]->key, c1->T[i]->value);

        }
    }
    
    char* s2 = cts(c1);
    printf("%s", s2);
    
    free(s2);
    */
    
    /*
    Commit* c2 = stc("boite1 : chocolat\nboite2 : caramel\nboite3 : vanille\nboite4 : poisson\n");
    
    // affichage de c2
    for (int i = 0; i < c2->size; i++) {
    	if (c2->T[i] != NULL) {
        	printf("indice : %d key : %s, value : %s\n", i, c2->T[i]->key, c2->T[i]->value);
        }
    }
    */
    
    /*
    printf("cle 2 trouve ? valeur : %s\n", commitGet(c1, "2"));
    printf("cle 5 trouve ? valeur : %s\n", commitGet(c1, "5"));
    printf("cle boite3 trouve ? valeur : %s\n", commitGet(c2, "boite3"));
    printf("cle boite5 trouve ? valeur : %s\n", commitGet(c2, "boite5"));
    
    ctf(c1, "com1");
    
    freeCommit(c1);
    */
    
    /*
    Commit* c3 = ftc("com1");
    
    printf("%lu\n", hashF("boite"));
    
    // affichage de c3
    for (int i = 0; i < c3->size; i++) {
    	if (c3->T[i] != NULL) {
        	printf("key : %s, value : %s\n", c3->T[i]->key, c3->T[i]->value);
        }
    }
    
    freeCommit(c3);
    */
    
    /*
    char* hash3 = blobCommit(c2);
    
    free(hash3);
    freeCommit(c2);
	*/
	
	/*
    initRefs();
    */
    
    /*
    createUpdateRef("HEAD", "Seofj1foevsopadpovsejfijeoiap12EJOVJsovjzofjezf");
    char* hash3 = getRef("HEAD");
    printf("hash : %s\n", hash3);
    
    free(hash3);
    */
    
    /*
    deleteRef("HEAD");
    char* hash4 = getRef("HEAD");
    printf("hash : %s\n", hash4);
    
    free(hash4);
    */
    
    /*
    myGitAdd("couleur");
    */
    
    /*
    Commit* c4 = initCommit();
    commitSet(c4, "author", "Joe Doe");
    
    
    // affichage de c4
    for (int i = 0; i < c4->size; i++) {
        if (c4->T[i] != NULL) {
            printf("key : %s, value : %s\n", c4->T[i]->key, c4->T[i]->value);
        }
    }

    ctf(c4, "essai/sous/c4");
    
    freeCommit(c4);
    
    myGitAdd("essai");
	*/
    
    /*
    myGitCommit("master", "fichier contenant des informations pas tres nettes");
    */
    
  	/*
    Commit* c5 = initCommit();
    commitSet(c5, "author", "Mi So");
    
    ctf(c5, "essai/sous/c5");
    
    myGitAdd("test");
    
    freeCommit(c5);
    */
    
    myGitCommit("Feature1", "fichier contenant des informations absolument droles");
	
	
}
