#include <stdio.h>

// Remplir Tableaux
int remplirOffreStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tmax);
int remplirListeEtudiants(int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlog, int tmax);

// Responsable
int afficherTableau(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tmax);
int afficherStagesPourvus(int tRef[], int tDpt[], int tPourvu[], int *tlogOffre, int tNumEtu[], int tRefStage[], int *tlogEtu);
int afficherStagesNonPourvus(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int *tlog);
int menuResponsable(void);
int globalResponsable(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlogOffre, int tmaxOffre, int *tlogEtu, int tmaxEtu);

// Etudiant
int globalEtudiant(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlogOffre, int tmaxOffre, int *tlogEtu, int tmaxEtu);

// Jury
int globalJury(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlogOffre, int tmaxOffre, int *tlogEtu, int tmaxEtu);

// Global
int menuSelection(void);
void global(void);