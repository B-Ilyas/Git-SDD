#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>


// test des fonctions du fichier list.c


int main(void) {
    
    // quelques tests
	// system("ls");
	// FILE* f = fopen("test.txt", "w");
	// fprintf(f, "Test");
    // fclose(f);
	
    
    // test de la fonction hashFile
	// hashFile("test.txt", "brouillon.tmp");
	
    
    // test
	// static char template[] = "/tmp/myfileXXXXXX";
	// char fname[1000];
	// strcpy(fname, template);
	// mkstemp(fname);
	
	// printf("%s\n", sha256file("avril"));
    
    /*
    // creation d'une liste
    Cell* nc1 = buildCell("kangourou");
    Cell* nc2 = buildCell("dragon");
    Cell* nc3 = buildCell("wikipedia");
    List* l1 = initList();
    insertFirst(l1, nc1);
    insertFirst(l1, nc2);
    insertFirst(l1, nc3);
    

    // affichage de la liste
    Cell* tmp1 = *l1;

	printf("---Affichage de l1---\n");
    while (tmp1) {
        printf("%s\n", ctos(tmp1));
        tmp1 = tmp1->next;
    }
    */
    
    /*
    // quelques tests
    int i = 2;
    char* s1 = "kangourou";
    char* s2 = "plafond";
	
	char* ch1 = ctos(searchList(l1, s1));
	char* ch2 = ctos(searchList(l1, s2));
	char* s3 = ltos(l1);
	
    printf("ltos : %s\n", s3);
    printf("element d'indice %d de la liste : %s\n", i, ctos(listGet(l1, i)));
    printf("Presence de %s dans la liste ? : %s\n", s1, ch1);
    printf("Presence de %s dans la liste ? : %s\n", s2, ch2);
	
	free(s3);
	*/
	
	/*
    List *l2 = stol("je|suis|en|vacances");
    
    
    // affichage de la liste
    Cell* tmp2 = *l2;
    
    printf("---Affichage de l2---\n");
    while (tmp2) {
        printf("%s\n", ctos(tmp2));
        tmp2 = tmp2->next;
    }
	*/
	
	/*
    ltof(l1, "try.txt");
    List *lres = ftol("try.txt");
    
    liberer_list(l1);
    liberer_list(l2);
    
    // affichage de la liste
    Cell* tmp3 = *lres;

    while (tmp3) {
        printf("%s\n", ctos(tmp3));
        tmp3 = tmp3->next;
    }
    
    liberer_list(lres);
    */
    
    /*
    List* l4 = listdir(".");
    
    // affichage de la liste
    Cell* tmp4 = *l4;
    
    while (tmp4) {
        printf("%s\n", ctos(tmp4));
        tmp4 = tmp4->next;
    }
    
    liberer_list(l4);
    */
    
    /*
    // test de file_exists
    printf("presence du fichier %s : %d\n", "try.txt", file_exists("try.txt"));
    printf("presence du fichier %s : %d\n", "unknown", file_exists("unknown"));
    */
    
    /*
    // test de cp
    cp("recu.txt", "try.txt");
    
    // test de hashToPath
    char* hash_path1 = hashToPath("a2fjsoal434ldkz");
    printf("%s \n", hash_path1);
    
    free(hash_path1);
    */
    
    
    // test de blobFile
    blobFile("try.txt");
        
}
