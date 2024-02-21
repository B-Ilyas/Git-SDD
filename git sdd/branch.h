#ifndef _BRANCH_H_
#define _BRANCH_H_


#include "list.h"


void initBranch(void);
// initialise une branche nommée master

int branchExists(char* branch);
// renvoie 1 si la branche existe, 0 sinon

void createBranch(char* branch);
// crée une branche dont le nom est donné en paramètre

char* getCurrentBranch(void);
// renvoie le nom de la branche courante

void printBranch(char* branch);
// affiche tous les commits de la branche. Pour chaque commit, la fonction affiche son hash et son message s'il en a

List* branchList(char* branch);
// retourne la liste chainee des hash de tous les Commit de la branche

List* getAllCommits(void);
// retourne la liste chainee des hash de tous les commits de toutes les branches

void restoreCommit(char* hash_commit);
// restaure le WorkTree associe au Commit dont le hash est donné en paramètre

void myGitCheckoutBranch(char* branch);
// permet de se déplacer de la branche courante a la branche branch

List* filterList(List* L, char* pattern);
// renvoie la liste chainée des chaines de caractères qui commencent par la chaine pattern

void myGitCheckoutCommit(char* pattern);
// restaure le WorkTree associe au commit dont le hash commence par la chaine pattern donné en paramètre. Si plusieurs ou aucun Commit ne possède un hash commencant par la chaine pattern, alors la fonction ne fait rien et affiche l'erreur associée


#endif
