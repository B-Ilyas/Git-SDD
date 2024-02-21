#ifndef _FUSION_H_
#define _FUSION_H_

#include "list.h"
#include "work.h"
#include "commit.h"
#include "branch.h"


WorkTree* mergeWorkTrees(WorkTree* wt1, WorkTree* wt2, List** conflicts);
// renvoie le WorkTree de fusion de wt1 et wt2 sans conflits et modifie la liste conflicts donnée en paramètres en y insérant les conflits

List* merge(char* remote_branch, char* message);
// renvoie la liste de conflits si la branche courante et la branche remote_branch a (au moins) un conflit. Sinon, la fonction effectue la fusion de ces deux branches dont le message est donné en paramètre et renvoie NULL

void createDeletionCommit(char* branch, List* conflicts, char* message);
// crée le commit de suppression sur la branche branch



#endif
