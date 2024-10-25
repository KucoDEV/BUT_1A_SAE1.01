/**
 * \file SAE.c
 * \brief Gestion des stages et des étudiants.
 *
 * Ce fichier contient les fonctions nécessaires à la gestion des offres de stages,
 * des candidatures et des affectations des étudiants dans un système de suivi des stages.
 *
 * \authors MIOTTO Quentin, PICHOT-MOÏSE Mathéo
 * \date 23 Octobre 2024
 */
#include "SAE.h"


/**
 * \brief Remplit les tableaux avec les informations des offres de stages à partir d'un fichier.
 * 
 * Cette fonction lit les informations des offres de stages à partir du fichier "offrestage.txt" et les stocke 
 * dans les tableaux fournis. Chaque offre contient une référence, un département, une indication
 * si l'offre est pourvue, le nombre de candidatures et les étudiants candidats.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si le stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[], tEtu2[], tEtu3[] Tableaux contenant les IDs des étudiants affectés aux stages.
 * \param tlog Pointeur sur le nombre total d'offres chargées.
 * \param tmax Nombre maximal d'offres dans le tableau.
 * \return 0 si tout s'est bien passé, -1 en cas d'erreur de lecture.
 */
int remplirOffreStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tmax) {
    FILE *flot;
    int ref, dept, pourvu, candid, etu1, etu2, etu3;
    int i=0;

    flot = fopen("DATA/offrestage.txt", "r"); // Ouvrir le fichier
    
    if (flot  == NULL) return -1; // Erreur lors du chargement
    
    while(i < tmax && fscanf(flot, "%d", &ref) == 1) { // Si i<tmax et que le fichier trouve encore une ligne
        if (ref >= 1000) {
            tRef[i] = ref;
            if (fscanf(flot, "%d%d%d", &dept, &pourvu, &candid) != 3) { // Si les 3 ne sont pas présent c'est pas une ligne correcte
                break;
            }

            if (candid==3) {
                if (fscanf(flot, "%d%d%d", &etu1, &etu2, &etu3) != 3) {
                    break;
                }
            }
            else if (candid==2) {
                if (fscanf(flot, "%d%d", &etu1, &etu2) != 2) {
                    break;
                }
                etu3=0;
            }
            else if  (candid==1) {
                if (fscanf(flot, "%d", &etu1) != 1) {
                    break;
                }
                etu2=0; 
                etu3=0;
            }
            else {
                etu1=0;
                etu2=0;
                etu3=0;
            }
            
            tDpt[i] = dept;
            tPourvu[i] = pourvu;
            tCandid[i] = candid;
            tEtu1[i] = etu1;
            tEtu2[i] = etu2;
            tEtu3[i] = etu3;

            i++;
            (*tlog)++;
        }
    }
    fclose(flot);
    return 1; // Fonction réussi
}

/**
 * \brief Remplit les tableaux avec les informations des étudiants à partir d'un fichier.
 * 
 * Cette fonction lit les informations des étudiants à partir du fichier "etudiants.txt" et les stocke dans 
 * les tableaux fournis. Chaque étudiant est associé à un numéro et à la référence du stage auquel
 * il est affecté, ainsi que sa note finale.
 * 
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références des stages associés aux étudiants.
 * \param tNoteFinal[] Tableau des moyennes finales des étudiants.
 * \param tlog Pointeur sur le nombre total d'étudiants chargés.
 * \param tmax Nombre maximal d'étudiants dans le tableau.
 * \return 0 si tout s'est bien passé, -1 ou -2 en cas d'erreur de lecture.
 */
int remplirListeEtudiants(int tNumEtu[], int tRefStage[], float tNoteFinal[], int *tlog, int tmax) {
    int i=0, num, ref;
    float note;
    FILE *flot;
    flot = fopen("DATA/etudiants.txt", "r");

    if (flot == NULL) return -1; // Erreur lors du chargement

    fscanf(flot,"%d%d%f", &num, &ref, &note);
    while(!feof(flot)) {
        if (i < tmax) {
            tNumEtu[i] = num;
            tRefStage[i] = ref;
            tNoteFinal[i] = note;
            (*tlog)++;
            i++;
            fscanf(flot,"%d%d%f", &num, &ref, &note);
        }
        else {
            fclose(flot);
            return -2; 
        }
    }
    fclose(flot);
    return 1; // Fonction réussi
}


/**
 * \brief Sauvegarde les modifications apportées aux stages et aux étudiants dans un fichier.
 * 
 * Cette fonction enregistre les modifications effectuées sur les offres de stages 
 * et les notes des étudiants dans un fichier, afin de préserver les données après l'exécution 
 * du programme. Elle met à jour les fichiers en fonction des tableaux passés en paramètres.
 * 
 * \param tRef[] Tableau contenant les références des stages.
 * \param tDpt[] Tableau contenant les départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[] Tableau contenant les IDs des premiers étudiants affectés aux stages.
 * \param tEtu2[] Tableau contenant les IDs des seconds étudiants affectés aux stages.
 * \param tEtu3[] Tableau contenant les IDs des troisièmes étudiants affectés aux stages.
 * \param tlogOffre Pointeur sur le nombre total d'offres dans le tableau.
 * \param tNumEtu[] Tableau contenant les IDs des étudiants.
 * \param tRefStage[] Tableau contenant les références de stages associées aux étudiants.
 * \param tNoteFinal[] Tableau contenant les moyennes finales des étudiants.
 * \param tlogEtu Pointeur sur le nombre total d'étudiants dans le tableau.
 * \return 1 si la sauvegarde s'est bien effectuée, -1 en cas d'erreur.
 */
int modificationFichier(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tNumEtu[], int tRefStage[], float tNoteFinal[], int *tlogEtu) {
    FILE *flot;
    flot = fopen("DATA/offrestage.txt", "w");
    if (flot == NULL) return -1;

    for (int i = 0; i < *tlog; i++) {
        fprintf(flot, "\n%d %d\n%d\n%d", tRef[i], tDpt[i], tPourvu[i], tCandid[i]);
        if (tPourvu[i] == 0) {
            if (tCandid[i] == 3) fprintf(flot, "\n%d\n%d\n%d", tEtu1[i], tEtu2[i], tEtu3[i]);
            else if (tCandid[i] == 2) fprintf(flot, "\n%d\n%d", tEtu1[i], tEtu2[i]);
            else if (tCandid[i] == 1) fprintf(flot, "\n%d", tEtu1[i]);
        }
    }

    fclose(flot);
    
    flot = fopen("DATA/etudiants.txt", "w");
    if (flot == NULL) return -1; // Problème ouverture fichier

    if (*tlogEtu > 0) {
        for (int i = 0; i < *tlogEtu; i++) {
            fprintf(flot, "%d %d %.2f\n", tNumEtu[i], tRefStage[i], tNoteFinal[i]);
        }
    }

    fclose(flot);
    return 1; // Fonction réussi
}


/**
 * \brief Affiche les informations de tous les stages présents dans les tableaux.
 * 
 * Cette fonction affiche les informations des stages à partir des tableaux, incluant 
 * les références, les départements, l'état pourvu ou non, le nombre de candidatures 
 * et les étudiants candidats.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si le stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[], tEtu2[], tEtu3[] Tableaux des IDs des étudiants affectés.
 * \param tlog Pointeur sur le nombre total d'offres à afficher.
 * \param tmax Nombre maximal d'offres dans le tableau.
 * \return 1 si tout s'est bien passé.
 */
int afficherTableau(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tmax) {
    int code;

    printf("\nREF\tDPT\tPOURVU\tCANDID\tETU1\tETU2\tETU3\n");
    for (int i=0; i < *tlog; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", tRef[i], tDpt[i], tPourvu[i], tCandid[i], tEtu1[i], tEtu2[i], tEtu3[i]);
    }
    return 1; // Fonction réussi
}

/**
 * \brief Affiche uniquement les stages qui ont été pourvus.
 * 
 * Cette fonction parcourt le tableau des stages et affiche uniquement ceux 
 * qui ont été pourvus, en montrant les détails sur le stage et les étudiants affectés.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si le stage est pourvu.
 * \param tlogOffre Pointeur sur le nombre total de stages.
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références des stages associés aux étudiants.
 * \param tlogEtu Pointeur sur le nombre total d'étudiants.
 * \return 1 si tout s'est bien passé.
 */
int afficherStagesPourvus(int tRef[], int tDpt[], int tPourvu[], int *tlogOffre, int tNumEtu[], int tRefStage[], int *tlogEtu) {
    int stagePourvu = 0;

    printf("REF\tDPT\tETU\n");

    for (int i = 0; i < *tlogOffre; i++) {
        if (tPourvu[i] == 1) {
            printf("%d\t%d", tRef[i], tDpt[i]);

            int etudiantAffecte = 0;
            for (int j = 0; j < *tlogEtu; j++) {
                if (tRefStage[j] == tRef[i]) {
                    etudiantAffecte = tNumEtu[j];
                    break;
                }
            }
            printf("\t%d\n", etudiantAffecte);
            stagePourvu = 1;
        }
    }

    if (stagePourvu == 0) {
        printf("\nAucun stage pourvu pour le moment.\n");
    }
    return 1; // Fonction réussi
}

/**
 * \brief Affiche uniquement les stages qui n'ont pas encore été pourvus.
 * 
 * Cette fonction parcourt le tableau des stages et affiche ceux qui n'ont pas 
 * encore d'étudiants affectés, en montrant les détails pour chaque stage.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si le stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tlog Pointeur sur le nombre total d'offres.
 * \return 1 si tout s'est bien passé.
 */
int afficherStagesNonPourvus(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int *tlog) {
    printf("\nStages non pourvus :\n");
    printf("REF\tDPT\tNB CANDID\n");
    for (int i = 0; i < *tlog; i++) {
        if (tPourvu[i] == 0) {
            printf("%d\t%d\t%d\n", tRef[i], tDpt[i], tCandid[i]);
        }
    }
    return 1; // Fonction réussi
}

/**
 * \brief Affiche les étudiants qui n'ont pas encore de stage.
 * 
 * Cette fonction parcourt le tableau des étudiants et affiche ceux qui n'ont pas 
 * encore été affectés à un stage, en montrant leur numéro et d'autres informations pertinentes.
 * 
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références de stages associés aux étudiants.
 * \param tlogEtu Pointeur sur le nombre total d'étudiants.
 * \return 1 si tout s'est bien passé.
 */
int afficherEtudiantsSansStage(int tNumEtu[], int tRefStage[], int *tlogEtu) {
    printf("\nÉtudiants sans stage :\n");
    for (int i = 0; i < *tlogEtu; i++) {
        if (tRefStage[i] == -1) {
            printf("ID Étudiant: %d\n", tNumEtu[i]);
        }
    }
    return 1; // Fonction réussi
}

/**
 * \brief Affiche les détails d'un stage particulier.
 * 
 * Cette fonction affiche les informations complètes d'un stage à partir de sa référence,
 * incluant les étudiants affectés, les départements, et le statut de pourvu ou non.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si le stage est pourvu.
 * \param tCandid[] Tableau des candidatures pour chaque stage.
 * \param tEtu1[], tEtu2[], tEtu3[] Tableaux des étudiants affectés.
 * \param tlog Pointeur sur le nombre total d'offres dans le tableau.
 * \return 1 si tout s'est bien passé, -1 si le stage n'a pas été trouvé.
 */
int afficherInfoStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog) {
    int ref;
    printf("\nNuméro de référence du stage à afficher: ");
    scanf("%d", &ref);

    for (int i = 0; i < *tlog; i++) {
        if (tRef[i] == ref) {
            printf("\nInformations du stage :\n");
            printf("REF: %d, DPT: %d, Pourvu: %d, Candidats: %d, ETU1: %d, ETU2: %d, ETU3: %d\n", tRef[i], tDpt[i], tPourvu[i], tCandid[i], tEtu1[i], tEtu2[i], tEtu3[i]);
            return 1; // Fonction réussi
        }
    }
    return -1; // Stage non trouver
}

/**
 * \brief Recherche et affiche un stage à partir de sa référence.
 * 
 * Cette fonction permet de rechercher un stage spécifique à partir de sa référence, 
 * et d'afficher les informations le concernant si le stage est trouvé.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tlog Pointeur sur le nombre total d'offres dans le tableau.
 * \return 1 si le stage a été trouvé et affiché, -1 si le stage n'existe pas.
 */
int rechercherStage(int tRef[], int tDpt[], int *tlog) {
    int choix, valeurRecherchee;
    printf("\nRecherche de stage par :\n");
    printf("\t1. Numéro de référence\n");
    printf("\t2. Département\n");
    printf("Votre choix: ");
    scanf("%d", &choix);

    if (choix == 1) {
        printf("Numéro de référence: ");
        scanf("%d", &valeurRecherchee);
        for (int i = 0; i < *tlog; i++) {
            if (tRef[i] == valeurRecherchee) {
                printf("Stage trouvé : REF: %d, DPT: %d\n", tRef[i], tDpt[i]);
                return 1; // Fonction réussi
            }
        }
    } else if (choix == 2) {
        printf("Département: ");
        scanf("%d", &valeurRecherchee);
        for (int i = 0; i < *tlog; i++) {
            if (tDpt[i] == valeurRecherchee) {
                printf("Stage trouvé : REF: %d, DPT: %d\n", tRef[i], tDpt[i]);
            }
        }
        return 1; // Fonction réussi
    }
    return -1; // Aucun stage trouvé
}

/**
 * \brief Ajoute une nouvelle offre de stage dans les tableaux.
 * 
 * Cette fonction permet d'ajouter un nouveau stage en saisissant les informations pertinentes
 * telles que la référence du stage, le département associé, le nombre de candidatures, 
 * et les étudiants affectés. Si le stage existe déjà, il ne sera pas ajouté.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si le stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[], tEtu2[], tEtu3[] Tableaux des IDs des étudiants affectés.
 * \param tlog Pointeur sur le nombre total d'offres dans le tableau.
 * \param tmax Nombre maximal d'offres dans le tableau.
 * \return 1 si le stage a été ajouté avec succès, -1 ou -2 si il y a eu une erreur.
 */
int ajoutStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tmax) {
    int ref, dept;
    
    printf("\nNuméro de référence du stage: ");
    scanf("%d", &ref);
    printf("Département du stage: ");
    scanf("%d", &dept);

    for (int i = 0; i < *tlog; i++) {
        if (tRef[i] == ref) return -1; // Stage existe déjà
    }
    
    if (*tlog < tmax) {
        tRef[*tlog] = ref;
        tDpt[*tlog] = dept;
        tPourvu[*tlog] = 0;
        tCandid[*tlog] = 0;
        tEtu1[*tlog] = 0;
        tEtu2[*tlog] = 0;
        tEtu3[*tlog] = 0;
        (*tlog)++;
        return 1; // Fonction réussi
    }
    else {
        return -2; // Tableau trop petit
    }
}

/**
 * \brief Supprime une offre de stage du tableau.
 * 
 * Cette fonction permet de supprimer une offre de stage à partir de sa référence. 
 * Les informations sur ce stage et les étudiants affectés sont supprimées, 
 * et les éléments des tableaux sont réorganisés pour combler le vide laissé.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si le stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[], tEtu2[], tEtu3[] Tableaux des IDs des étudiants affectés.
 * \param tlog Pointeur sur le nombre total d'offres dans le tableau.
 * \return 1 si le stage a été supprimé avec succès, -1 si le stage n'a pas été trouvé.
 */
int supprimerStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog) {
    int ref, dept;
    printf("\nNuméro de référence du stage à supprimer: ");
    scanf("%d", &ref);

    for (int i = 0; i < *tlog; i++) {
        if (tRef[i] == ref) {
            // Décaler les différents tableaux
            for (int j = i; j < *tlog - 1; j++) {
                tRef[j] = tRef[j + 1];
                tDpt[j] = tDpt[j + 1];
                tPourvu[j] = tPourvu[j + 1];
                tCandid[j] = tCandid[j + 1];
                tEtu1[j] = tEtu1[j + 1];
                tEtu2[j] = tEtu2[j + 1];
                tEtu3[j] = tEtu3[j + 1];
            }
            (*tlog)--;
            printf("Stage supprimé avec succès!\n");
            return 1; // Fonction réussi
        }
    }
    return -1;
}

/**
 * \brief Affecte un étudiant à un stage spécifique.
 * 
 * Cette fonction permet d'affecter un étudiant à un stage en vérifiant d'abord s'il est déjà 
 * assigné à un autre stage. Si l'affectation est valide, l'étudiant est ajouté au stage, 
 * et les candidatures du stage sont mises à jour en conséquence.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si le stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[], tEtu2[], tEtu3[] Tableaux des étudiants affectés aux stages.
 * \param tlog Pointeur sur le nombre total d'offres dans le tableau.
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références de stages associés aux étudiants.
 * \param tNoteFinal[] Tableau des moyennes finales des étudiants.
 * \param tlogEtu Pointeur sur le nombre total d'étudiants.
 * \return 1 si l'affectation a réussi, -1 en cas d'erreur ou si le stage est déjà complet.
 */
int affecterEtudiant(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tNumEtu[], int tRefStage[], float tNoteFinal[], int *tlogEtu) {
    int ref, place, x;

    printf("\nStages disponibles :\n");
    for (int i = 0; i < *tlog; i++) {
        if (tPourvu[i] == 0 && tCandid[i] >= 1) {
            printf("Référence: %d, Département: %d, Nombre de candidature: %d\n", tRef[i], tDpt[i], tCandid[i]);
        }
    }

    printf("\nNuméro de référence du stage: ");
    scanf("%d", &ref);

    int stageTrouve = -1;
    for (int i = 0; i < *tlog; i++) {
        if (tRef[i] == ref) {
            stageTrouve = i;
            break;
        }
    }

    if (stageTrouve == -1) return -2; // Stage non trouver

    printf("\nÉtudiants candidats pour ce stage :\n");
    for (int i = 0; i < *tlog; i++) {
        if (tRef[i] == ref) {
            for (x = 0; x < *tlogEtu; x++) {
                if (tEtu1[i] == tNumEtu[x] || tEtu2[i] == tNumEtu[x] || tEtu3[i] == tNumEtu[x]) {
                    printf("ID Étudiant: %d, Note: %d\n", tNumEtu[x], tNoteFinal[x]);
                    place = x;
                }
            }
        }
    }

    int etu;
    printf("ID de l'étudiant à affecter (ou 0 pour revenir en arrière): ");
    scanf("%d", &etu);

    if (etu == 0) return -3;

    // Rechercher si l'étudiant a postulé ailleurs et le retirer
    for (int i = 0; i < *tlog; i++) {
        if (tRefStage[i] != ref) {
            if (tEtu1[i] == etu) {
                tEtu1[i] = tEtu2[i];
                tEtu2[i] = tEtu3[i];
                tEtu3[i] = 0;
                tCandid[i]--;
            }
            else if (tEtu2[i] == etu) {
                tEtu2[i] = tEtu3[i];
                tEtu3[i] = 0;
                tCandid[i]--;
            }
            else if (tEtu3[i] == etu) {
                tEtu3[i] = 0;
                tCandid[i]--;
            }
        }
    }

    // Affecter l'étudiant au stage
    for (int i = 0; i < *tlog; i++) {
        if (tRef[i] == ref) {
            if (tEtu1[i] == etu || tEtu2[i] == etu || tEtu3[i] == etu) {
                tPourvu[i] = 1;
                tCandid[i] = 0;
                tEtu1[i] = 0;
                tEtu2[i] = 0;
                tEtu3[i] = 0;
                tRefStage[place] = ref;
                return 1; // Fonction réussi
            }
        }
    }
    return -1; // L'étudiant n'est pas candidat pour ce stage
}

/**
 * \brief Affiche le menu du responsable.
 *
 * Cette fonction présente les différentes options disponibles pour un responsable,
 * comme la gestion des stages et les affectations des étudiants.
 * 
 * \return Le choix de l'utilisateur correspondant à une option du menu.
 */
int menuResponsable(void) {
    int choix;
    printf("\nAction :\n");
    printf("\t1. Ajouter une offre de stage\n");
    printf("\t2. Supprimer une offre de stage\n");
    printf("\t3. Affecter un stage à un étudiant\n");
    printf("Affichage :\n");
    printf("\t4. Afficher tous les stages\n");
    printf("\t5. Afficher les stages pourvus avec étudiants\n");
    printf("\t6. Afficher les stages non pourvus\n");
    printf("\t7. Afficher les étudiants sans stage\n");
    printf("\t8. Rechercher un stage (par numéro ou département)\n");
    printf("\t9. Afficher les informations d'un stage donné\n");
    printf("\t10. Quitter\n");
    printf("Votre choix: ");
    scanf("%d", &choix);
    return choix;
}

/**
 * \brief Gère les actions principales du responsable de stage.
 * 
 * Cette fonction permet au responsable de gérer les stages disponibles. 
 * Le responsable peut ajouter, supprimer, modifier des stages et voir les candidatures 
 * des étudiants. Elle gère l'interaction avec les tableaux des stages et étudiants.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si le stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[], tEtu2[], tEtu3[] Tableaux des étudiants affectés aux stages.
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références des stages associés aux étudiants.
 * \param tNoteFinal[] Tableau des moyennes finales des étudiants.
 * \param tlogOffre Pointeur sur le nombre total d'offres dans le tableau.
 * \param tmaxOffre Nombre maximal d'offres dans le tableau.
 * \param tlogEtu Pointeur sur le nombre total d'étudiants dans le tableau.
 * \param tmaxEtu Nombre maximal d'étudiants dans le tableau.
 * \return 1 si toutes les actions ont été effectuées avec succès.
 */
int globalResponsable(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int tNumEtu[], int tRefStage[], float tNoteFinal[], int *tlogOffre, int tmaxOffre, int *tlogEtu, int tmaxEtu) {
    int choix, code;
    choix = menuResponsable();
    while (choix != 10) {
        switch (choix) {
        // Action :
            case 1: // Ajouter une offre de stage
                code = ajoutStage(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre, tmaxOffre);
                if (code == 1) printf("\nLe stage a été ajouté avec succès !\n");
                if (code == -1) printf("\nLe stage avec ce numéro de référence et ce département existe déjà !\n");
                if (code == -2) printf("\nLe tableau est trop petit !\n");
                break;

            case 2: // Supprimer une offre de stage
                code = supprimerStage(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre);
                if (code == 1) printf("\nLe stage a été supprimé avec succès !\n");
                if (code == -1) printf("\nAucun stage trouvé avec ce numéro de référence !\n");
                break;

            case 3: // Affecter un stage à un étudiant
                code = affecterEtudiant(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre, tNumEtu, tRefStage, tNoteFinal, tlogEtu);
                if (code == 1) printf("\nL'étudiant a été affecté avec succès !\n");
                if (code == -1) printf("\nL'étudiant n'est pas candidat pour ce stage.\n");
                if (code == -2) printf("\nStage non trouvé.\n");
                break;

        // Affichage :
            case 4: // Afficher tous les stages
                code = afficherTableau(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre, tmaxOffre);
                break;

            case 5: // Afficher les stages pourvus avec étudiants affectés
                code = afficherStagesPourvus(tRef, tDpt, tPourvu, tlogOffre, tNumEtu, tRefStage, tlogEtu);
                break;

            case 6: // Afficher les stages non pourvus
                code = afficherStagesNonPourvus(tRef, tDpt, tPourvu, tCandid, tlogOffre);
                break;

            case 7: // Afficher les étudiants sans stage
                code = afficherEtudiantsSansStage(tNumEtu, tRefStage, tlogEtu);
                break;

            case 8: // Rechercher un stage par numéro ou département
                code = rechercherStage(tRef, tDpt, tlogOffre);
                if (code == -1) printf("\nStage non trouvé !\n");
                break;

            case 9: // Afficher les informations d'un stage donné
                code = afficherInfoStage(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre);
                if (code == -1) printf("\nStage non trouvé !\n");
                break;

            default: // Choix invalide
                printf("\nChoix non valide !\n");
                break;
        }
        choix = menuResponsable();
    }
    code = modificationFichier(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre, tNumEtu, tRefStage, tNoteFinal, tlogEtu);
    if (code == 1) return 1; // Fonction réussi
    else return -1; // Problème ouverture fichier
}


/**
 * \brief Vérifie l'identité d'un étudiant à partir de son identifiant.
 * 
 * Cette fonction permet de vérifier si un étudiant est bien enregistré dans le système
 * en comparant l'identifiant saisi avec ceux présents dans le tableau des étudiants.
 * 
 * \param id Identifiant de l'étudiant.
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tlogEtu Nombre total d'étudiants dans le tableau.
 * \return 1 si l'étudiant est trouvé, 0 sinon.
 */
int verifieLogin(int id, int tNumEtu[], int tlogEtu) {
    for (int i = 0; i < tlogEtu; i++) {
        if (tNumEtu[i] == id) {
            return 1; // Fonction réussi
        }
    }
    return -1;
}

/**
 * \brief Gère la procédure de connexion pour les étudiants.
 * 
 * Cette fonction permet aux étudiants de se connecter en saisissant leur identifiant. 
 * La connexion est validée en vérifiant l'existence de l'identifiant dans le tableau des étudiants.
 * 
 * \return L'identifiant de l'étudiant.
 */
int login(void) {
    int id;
    printf("\nQuel est votre identifiant : ");
    scanf("%d", &id);
    return id;
}

/**
 * \brief Affiche le menu pour les étudiants.
 * 
 * Cette fonction présente les options disponibles pour les étudiants, incluant la consultation 
 * des stages disponibles, la gestion des candidatures, et la déconnexion.
 * 
 * \return Le choix de l'étudiant, correspondant à une des options du menu.
 */
int menuEtudiant(void) {
    int choix;
    printf("\nAction :\n");
    printf("\t1. Afficher la liste de stage\n");
    printf("\t2. Candidater à un stage\n");
    printf("\t3. Voir vos candidatures\n");
    printf("\t4. Quitter\n");
    printf("Votre choix: ");
    scanf("%d", &choix);
    return choix;
}

int globalEtudiant(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int tNumEtu[], int tRefStage[], float tNoteFinal[], int *tlogOffre, int tmaxOffre, int *tlogEtu, int tmaxEtu) {
    int choix, code, id;
    id = login();
    code = verifieLogin(id, tNumEtu, *tlogEtu);
}


/**
 * \brief Affiche les notes des étudiants.
 * 
 * Cette fonction affiche les informations des étudiants, incluant leur numéro et leur note finale.
 * 
 * \param tNumEtu[] Tableau contenant les IDs des étudiants.
 * \param tNoteFinal[] Tableau contenant les moyennes finales des étudiants.
 * \param tlogEtu Pointeur sur le nombre total d'étudiants dans le tableau.
 * \return 1 si l'affichage a été effectué correctement, -1 si aucun étudiant n'est à afficher.
 */
int afficherNotes(int tNumEtu[], int tRefStage[], float tNoteFinal[], int *tlogEtu) {
    if (*tlogEtu <= 0) return -1;

    printf("\nNUM\tNOTE\n");
    for (int i = 0; i < *tlogEtu; i++) {
        printf("%d\t%.2f\n", tNumEtu[i], tNoteFinal[i]);
    }
    return 1;
}

/**
 * \brief Affiche le menu pour le jury.
 * 
 * Cette fonction affiche un menu simple permettant au jury de choisir une action.
 * 
 * \return Le choix de l'utilisateur.
 */
int menuJury(void) {
    int choix;
    printf("\nAction :\n");
    printf("\t1. Ajouter des notes\n");
    printf("\t2. Afficher les notes\n");
    printf("\t3. Quitter\n");
    printf("Votre choix: ");
    scanf("%d", &choix);
    return choix;
}

/**
 * \brief Gère les actions du jury sur les offres de stages et les notes des étudiants.
 * 
 * Cette fonction permet d'ajouter des notes aux étudiants ou d'afficher les notes 
 * déjà présentes. Elle gère également la sauvegarde des modifications dans les fichiers 
 * une fois les actions terminées.
 * 
 * \param tRef[] Tableau contenant les références des stages.
 * \param tDpt[] Tableau contenant les départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[] Tableau contenant les IDs des premiers étudiants affectés aux stages.
 * \param tEtu2[] Tableau contenant les IDs des seconds étudiants affectés aux stages.
 * \param tEtu3[] Tableau contenant les IDs des troisièmes étudiants affectés aux stages.
 * \param tNumEtu[] Tableau contenant les IDs des étudiants.
 * \param tRefStage[] Tableau contenant les références de stages associées aux étudiants.
 * \param tNoteFinal[] Tableau contenant les moyennes finales des étudiants.
 * \param tlogOffre Pointeur sur le nombre total d'offres dans le tableau.
 * \param tmaxOffre Taille maximale du tableau des offres.
 * \param tlogEtu Pointeur sur le nombre total d'étudiants dans le tableau.
 * \param tmaxEtu Taille maximale du tableau des étudiants.
 * \return 1 si toutes les actions ont été effectuées avec succès, -1 en cas d'erreur.
 */
int globalJury(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int tNumEtu[], int tRefStage[], float tNoteFinal[], int *tlogOffre, int tmaxOffre, int *tlogEtu, int tmaxEtu) {
    int choix, code;
    choix = menuJury();
    while (choix!=3) {
        switch (choix) {
        case 1: // Ajouter une offre de stage
            break;
        
        case 2: // Afficher notes
            code = afficherNotes(tNumEtu, tRefStage, tNoteFinal, tlogEtu);
            if (code == -1) printf("Aucun étudiant à afficher.\n");
            break;

        default: // Choix invalide
            printf("\nChoix non valide !\n");
            break;
        }
        choix = menuJury();
    }
    code = modificationFichier(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre, tNumEtu, tRefStage, tNoteFinal, tlogEtu);
    if (code == 1) return 1; // Fonction réussi
    else return -1; 
}


/**
 * \brief Affiche le menu principal du programme pour la sélection de l'utilisateur.
 * 
 * Cette fonction présente les différentes options aux utilisateurs pour qu'ils puissent
 * sélectionner leur rôle : étudiant, responsable ou jury.
 * 
 * \return Le choix de l'utilisateur sous forme d'un entier correspondant à une option du menu.
 */
int menuGlobal(void) {
    int choix;
    printf("\nAction :\n");
    printf("\t1. Responsable\n");
    printf("\t2. Elève\n");
    printf("\t3. Jury\n");
    printf("\t4. Quitter\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    return choix;
}

/**
 * \brief Gère les actions principales du système de gestion de stages.
 * 
 * Cette fonction permet de choisir qui on est.
 * 
 * \param choix Le choix de l'utilisateur.
 * \param code Le code de retour des différentes fonctions
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si le stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[], tEtu2[], tEtu3[] Tableaux des étudiants affectés aux stages.
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références des stages associés aux étudiants.
 * \param tNoteFinal[] Tableau des moyennes finales des étudiants.
 * \param tlogOffre Pointeur sur le nombre total d'offres dans le tableau.
 * \param tmaxOffre Nombre maximal d'offres dans le tableau.
 * \param tlogEtu Pointeur sur le nombre total d'étudiants dans le tableau.
 * \param tmaxEtu Nombre maximal d'étudiants dans le tableau.
 */
void global(void) {
    int choix, code;
    // Tableaux Offres De Stages
    int tRef[200]={0}, tDpt[200]={0}, tPourvu[200]={0}, tCandid[200]={0}, tEtu1[200]={0}, tEtu2[200]={0}, tEtu3[200]={0}, tmaxOffre=200, tlogOffre=0;
    // Tableaux Liste Etudiants
    int tNumEtu[200]={0}, tRefStage[200]={0}, tmaxEtu=200, tlogEtu=0;
    float tNoteFinal[200];

    code = remplirOffreStage(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, &tlogOffre, tmaxOffre); // Remplir le tableau des offres de stages
    if (code == -1) {
        printf("\nUne erreur est survenue lors du chargement du fichier (Offre Stage) !\n");
        exit(1); // Termine tout
    }

    code = remplirListeEtudiants(tNumEtu, tRefStage, tNoteFinal, &tlogEtu, tmaxEtu);
    if (code == -1) {
        printf("\nUne erreur est survenue lors du chargement du fichier (Liste) !\n");
        exit(1); // Termine tout
    }
    else if (code == -2) {
        printf("\nLe fichier étudiant est vide !\n");
        exit(1); // Termine tout
    }

    choix = menuGlobal();
    while(choix!=4) {
        switch (choix) {
            case 1: // Partie Responsable
                code = globalResponsable(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tNumEtu, tRefStage, tNoteFinal, &tlogOffre, tmaxOffre, &tlogEtu, tmaxEtu);
                break;
            
            case 2: // Partie Etudiants
                code = globalEtudiant(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tNumEtu, tRefStage, tNoteFinal, &tlogOffre, tmaxOffre, &tlogEtu, tmaxEtu);
                break;
            
            case 3: // Partie Jury
                code = globalJury(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tNumEtu, tRefStage, tNoteFinal, &tlogOffre, tmaxOffre, &tlogEtu, tmaxEtu);
                break;

            default: // Choix invalide
                printf("\nChoix non valide !\n");
                break;
        }
        choix = menuGlobal();
    }
}