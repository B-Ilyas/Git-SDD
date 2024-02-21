#include "list.h"
#include "work.h"
#include "commit.h"
#include "branch.h"
#include "fusion.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


WorkTree* mergeWorkTrees(WorkTree* wt1, WorkTree* wt2, List** conflicts) {
    /* renvoie le WorkTree de fusion de wt1 et wt2 sans conflits et modifie la liste conflicts donnée en paramètres en y insérant les conflits */
    
    WorkTree* nwt = initWorkTree();
    _Bool conflict = false;
    
    for (int i = 0; i < wt1->n; i++) {
        for (int j = 0; j < wt2->n; j++) {
            if (strcmp(wt1->tab[i].name, wt2->tab[j].name) == 0 && strcmp(wt1->tab[i].hash, wt2->tab[j].hash) != 0) { // conflit
                insertFirst(*conflicts, buildCell(wt1->tab[i].name));
                conflict = true;
            }
        }

        if (conflict == false) {
            appendWorkTree(nwt, wt1->tab[i].name, wt1->tab[i].hash, wt1->tab[i].mode);
        } else {
            conflict = false;
        }
    }
    
    for (int j = 0; j < wt2->n; j++) {
        if (searchList(*conflicts, wt2->tab[j].name) == NULL) { // n'est pas un conflit
            appendWorkTree(nwt, wt2->tab[j].name, wt2->tab[j].hash, wt2->tab[j].mode);
        }
    }
    
    return nwt;
}


List* merge(char* remote_branch, char* message) {
    /* renvoie la liste de conflits si la branche courante et la branche remote_branch a (au moins) un conflit. Sinon, la fonction effectue la fusion de ces deux branches dont le message est donné en paramètre et renvoie NULL  */
    
	printf("Commencement de merge de la branche %s avec la branche courante...\n", remote_branch);
	
    List* L = initList();
    List** conflicts = &L;
    char* current_branch = getCurrentBranch();
    
    // reconsitution du wt de remote_branch
    char hash_path_rem_c[100] = "";
    char* hash_rem_c = getRef(remote_branch);
    strcpy(hash_path_rem_c, hash_rem_c);
    strcat(hash_path_rem_c, ".c");
    char* chemin_rem_c = hashToPath(hash_path_rem_c);
    Commit* rem_c = ftc(chemin_rem_c);
    
    char hash_path_wt1[100] = "";
    strcpy(hash_path_wt1, commitGet(rem_c, "tree"));
    strcat(hash_path_wt1, ".t");
    char* chemin_wt1 = hashToPath(hash_path_wt1);
    WorkTree* wt1 = ftwt(chemin_wt1);
    
    // reconsitution du wt de current_branch
    char hash_path_cur_c[100] = "";
    char* hash_cur_c = getRef(current_branch);
    strcpy(hash_path_cur_c, hash_cur_c);
    strcat(hash_path_cur_c, ".c");
    char* chemin_cur_c = hashToPath(hash_path_cur_c);
    Commit* cur_c = ftc(chemin_cur_c);
    
    char hash_path_wt2[100] = "";
    strcpy(hash_path_wt2, commitGet(cur_c, "tree"));
    strcat(hash_path_wt2, ".t");
    char* chemin_wt2 = hashToPath(hash_path_wt2);
    WorkTree* wt2 = ftwt(chemin_wt2);
    
    // fusion des deux wt
    WorkTree* wt_fusion = mergeWorkTrees(wt1, wt2, conflicts);
    
    
    // liberation
    free(current_branch);
    
    free(chemin_rem_c);
    freeCommit(rem_c);
    
    free(chemin_wt1);
    liberer_wt(wt1);
    
    free(chemin_cur_c);
    freeCommit(cur_c);
    
    free(chemin_wt2);
    liberer_wt(wt2);
    
    
    if (**conflicts == NULL) {
    	char* hash_wt_fusion = blobWorkTree(wt_fusion);
        Commit* c = createCommit(hash_wt_fusion);
        commitSet(c, "predecessor", hash_cur_c);
        commitSet(c, "merged_predecessor", hash_rem_c);
        commitSet(c, "message", message);
        
        char* hash_c_fusion = blobCommit(c);
        
        // maj de la ref de la branche courante et HEAD
        createUpdateRef(current_branch, hash_c_fusion);
        createUpdateRef("HEAD", hash_c_fusion);
        
        deleteRef(remote_branch);
        
        restoreWorkTree(wt_fusion, ".");
        
        printf("Les branches ont été émergé avec succès !\n");
        
        
        // liberation
        free(hash_rem_c);
        free(hash_cur_c);
        free(hash_wt_fusion);
        free(hash_c_fusion);
        freeCommit(c);
        liberer_wt(wt_fusion);
        liberer_list(L);
        
        return NULL;
        
    } else {
    	printf("Rien à faire, au moins une collision détectée entre la branche %s et la branche courante\n", remote_branch);
        
        // liberation
        free(hash_rem_c);
        free(hash_cur_c);
        liberer_wt(wt_fusion);
        
        return *conflicts;
    }
}


void createDeletionCommit(char* branch, List* conflicts, char* message) {
    /* crée le commit de suppression sur la branche branch */
    
	printf("Commencement de createDeletionCommit sur la branche %s...\n", branch);
	
	char* current_branch = getCurrentBranch();
	
    myGitCheckoutBranch(branch);

    char hash_path_c[100] = "";
    char* hash_c = getRef(branch);
    strcpy(hash_path_c, hash_c);
    strcat(hash_path_c, ".c");
    char* chemin_c = hashToPath(hash_path_c);
    Commit* c = ftc(chemin_c);
    
    char hash_path_wt[100] = "";
    strcpy(hash_path_wt, commitGet(c, "tree"));
    strcat(hash_path_wt, ".t");
    char* chemin_wt = hashToPath(hash_path_wt);
    WorkTree* wt = ftwt(chemin_wt);   
    
    if (file_exists(".add") == 1) {
        system("./myGit clear-add");
    }
    
    for (int i = 0; i < wt->n; i++) {
        if (searchList(conflicts, wt->tab[i].name) == NULL) { // n'est pas un conflit
            myGitAdd(wt->tab[i].name);
        }
    }
    
    myGitCommit(branch, message); // commit obtenu apres suppression des conflits
    
    myGitCheckoutBranch(current_branch);
    
    printf("Fin de createDeletionCommit !\n");
    
    free(current_branch);
    free(hash_c);
    free(chemin_c);
    freeCommit(c);
    free(chemin_wt);
    liberer_wt(wt);
    
}
