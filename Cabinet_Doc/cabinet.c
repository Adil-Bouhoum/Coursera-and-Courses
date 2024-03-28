#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Patient {
    char nom[50];
    char prenom[50];
    int rdv;
    struct Patient *suivant;
} Patient;

Patient* creerPatient(char nom[], char prenom[], int rdv) {
    Patient* nouveauPatient = (Patient*)malloc(sizeof(Patient));
    if (nouveauPatient != NULL) {
        strcpy(nouveauPatient->nom, nom);
        strcpy(nouveauPatient->prenom, prenom);
        nouveauPatient->rdv = rdv;
        nouveauPatient->suivant = NULL;
    }
    return nouveauPatient;
}

Patient* AjoutPatientT(Patient* tete, Patient* P) {
    P->suivant = tete;
    return P;
}

Patient* AjoutPatientQ(Patient* tete, Patient* P) {
    if (tete == NULL)
        return P;
    Patient* temp = tete;
    while (temp->suivant != NULL) {
        temp = temp->suivant;
    }
    temp->suivant = P;
    return tete;
}

Patient* AjoutPatientPos(Patient* tete, Patient* P, int position) {
    if (position == 0 || tete == NULL) {
        P->suivant = tete;
        return P;
    }
    Patient* temp = tete;
    int i = 0;
    while (i < position - 1 && temp->suivant != NULL) {
        temp = temp->suivant;
        i++;
    }
    P->suivant = temp->suivant;
    temp->suivant = P;
    return tete;
}

Patient* SuppressionPatientT(Patient* tete) {
    if (tete == NULL)
        return NULL;
    Patient* temp = tete->suivant;
    free(tete);
    return temp;
}

Patient* SuppressionPatientQ(Patient* tete) {
    if (tete == NULL)
        return NULL;
    if (tete->suivant == NULL) {
        free(tete);
        return NULL;
    }
    Patient* prev = NULL;
    Patient* current = tete;
    while (current->suivant != NULL) {
        prev = current;
        current = current->suivant;
    }
    free(current);
    prev->suivant = NULL;
    return tete;
}

Patient* SuppressionPatientPos(Patient* tete, int position) {
    if (tete == NULL)
        return NULL;
    if (position == 0) {
        Patient* temp = tete->suivant;
        free(tete);
        return temp;
    }
    Patient* temp = tete;
    int i = 0;
    while (i < position - 1 && temp->suivant != NULL) {
        temp = temp->suivant;
        i++;
    }
    if (temp->suivant == NULL)
        return tete;
    Patient* delNode = temp->suivant;
    temp->suivant = delNode->suivant;
    free(delNode);
    return tete;
}

void AfficherSimple(Patient* tete) {
    Patient* temp = tete;
    while (temp != NULL) {
        printf("%s %s - RDV: %d\n", temp->nom, temp->prenom, temp->rdv);
        temp = temp->suivant;
    }
}

void RendezVous(Patient* tete) {
    int avecRDV = 0, sansRDV = 0;
    Patient* temp = tete;
    while (temp != NULL) {
        if (temp->rdv == 1)
            avecRDV++;
        else
            sansRDV++;
        temp = temp->suivant;
    }
    printf("Patients avec RDV : %d\n", avecRDV);
    printf("Patients sans RDV : %d\n", sansRDV);
}

Patient* PatientConsultation(Patient* tete) {
    if (tete == NULL)
        return NULL;
    if (tete->rdv == 1)
        return SuppressionPatientT(tete);
    else
        return SuppressionPatientPos(tete, 0);
}

void ConsulterSalleAttente(Patient* tete) {
    printf("Patients avec RDV :\n");
    Patient* temp = tete;
    while (temp != NULL) {
        if (temp->rdv == 1)
            printf("%s %s\n", temp->nom, temp->prenom);
        temp = temp->suivant;
    }
    printf("\nPatients sans RDV :\n");
    temp = tete;
    while (temp != NULL) {
        if (temp->rdv == 0)
            printf("%s %s\n", temp->nom, temp->prenom);
        temp = temp->suivant;
    }
}

int main() {
    Patient* tete = NULL;

    int choix;
    char nom[50], prenom[50];
    int rdv, position;

    do {
        printf("\nMenu :\n");
        printf("1. Ajouter un patient au début\n");
        printf("2. Ajouter un patient à la fin\n");
        printf("3. Ajouter un patient à une position donnée\n");
        printf("4. Supprimer un patient du début\n");
        printf("5. Supprimer un patient de la fin\n");
        printf("6. Supprimer un patient d'une position donnée\n");
        printf("7. Afficher la liste des patients\n");
        printf("8. Afficher le nombre de patients avec et sans rendez-vous\n");
        printf("9. Faire entrer un patient en consultation\n");
        printf("10. Consulter la salle d'attente\n");
        printf("0. Quitter\n");

        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez le nom du patient : ");
                scanf("%s", nom);
                printf("Entrez le prénom du patient : ");
                scanf("%s", prenom);
                printf("Rendez-vous (0 pour sans rendez-vous, 1 pour avec rendez-vous) : ");
                scanf("%d", &rdv);
                tete = AjoutPatientT(tete, creerPatient(nom, prenom, rdv));
                break;
            case 2:
                printf("Entrez le nom du patient : ");
                scanf("%s", nom);
                printf("Entrez le prénom du patient : ");
                scanf("%s", prenom);
                printf("Rendez-vous (0 pour sans rendez-vous, 1 pour avec rendez-vous) : ");
                scanf("%d", &rdv);
                tete = AjoutPatientQ(tete, creerPatient(nom, prenom, rdv));
                break;
            case 3:
                printf("Entrez le nom du patient : ");
                scanf("%s", nom);
                printf("Entrez le prénom du patient : ");
                scanf("%s", prenom);
                printf("Rendez-vous (0 pour sans rendez-vous, 1 pour avec rendez-vous) : ");
                scanf("%d", &rdv);
                printf("Entrez la position : ");
                scanf("%d", &position);
                tete = AjoutPatientPos(tete, creerPatient(nom, prenom, rdv), position);
                break;
            case 4:
                tete = SuppressionPatientT(tete);
                break;
            case 5:
                tete = SuppressionPatientQ(tete);
                break;
            case 6:
                printf("Entrez la position : ");
                scanf("%d", &position);
                tete = SuppressionPatientPos(tete, position);
                break;
            case 7:
                AfficherSimple(tete);
                break;
            case 8:
                RendezVous(tete);
                break;
            case 9:
                tete = PatientConsultation(tete);
                break;
            case 10:
                ConsulterSalleAttente(tete);
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 0);

    // Libération de la mémoire
    while (tete != NULL) {
        tete = SuppressionPatientT(tete);
    }

    return 0;
}
