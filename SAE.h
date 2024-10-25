/**
 * \file SAE.h
 * \brief Fichier contenant les déclarations des fonctions du programme de gestion des stages.
 *
 * Ce fichier contient les déclarations des fonctions utilisées pour gérer les offres de stages, 
 * les étudiants, et les responsables dans le programme de gestion des stages.
 *
 * \authors MIOTTO Quentin, PICHOT-MOÏSE Mathéo
 * \date 23 Octobre 2024
 *
 * Ce fichier permet de centraliser les déclarations des fonctions pour les utiliser dans les différents fichiers source du programme.
 */
#include <stdio.h>
#include <stdlib.h>

// Remplir Tableaux
int remplirOffreStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tmax);
int remplirListeEtudiants(int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlog, int tmax);

// Sauvegarde
int modificationFichier(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tNumEtu[], int tRefStage[], float tNoteFinal[], int *tlogEtu);

// Responsable
int afficherTableau(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tmax);
int afficherStagesPourvus(int tRef[], int tDpt[], int tPourvu[], int *tlogOffre, int tNumEtu[], int tRefStage[], int *tlogEtu);
int afficherStagesNonPourvus(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int *tlog);
int afficherEtudiantsSansStage(int tNumEtu[], int tRefStage[], int *tlogEtu);
int afficherInfoStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog);
int supprimerStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog);
int affecterEtudiant(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlogEtu);
int rechercherStage(int tRef[], int tDpt[], int *tlog);
int menuResponsable(void);
int globalResponsable(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlogOffre, int tmaxOffre, int *tlogEtu, int tmaxEtu);

// Etudiant
int verifieLogin(int id, int tNumEtu[], int tlogEtu);
int login(void);
int menuEtudiant(void);
int globalEtudiant(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlogOffre, int tmaxOffre, int *tlogEtu, int tmaxEtu);

// Jury
int menuJury(void);
int globalJury(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlogOffre, int tmaxOffre, int *tlogEtu, int tmaxEtu);

// Global
int menuSelection(void);
void global(void);