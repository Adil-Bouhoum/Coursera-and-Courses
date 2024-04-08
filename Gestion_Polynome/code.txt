#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Monome{
    float Coeff;
    int Exp;
    struct Monome *nxt;
}Monome;

Monome *CreerMonome(){
    Monome *monome = (Monome *)malloc(sizeof(Monome));
    printf("Entrez le Coefficient du monôme : ");
    scanf("%f", &monome->Coeff);
    printf("Entrez l'Exposant du monôme : ");
     scanf("%d", &monome->Exp);
    monome->nxt = NULL;
    return monome;
}

Monome* AjoutMonomeD(Monome *Liste) {
    Monome *mon = (Monome *)malloc(sizeof(Monome));
    mon = CreerMonome();
    mon->nxt = Liste;
    return mon;
}

Monome* AjoutMonomeF(Monome *Liste) {
    Monome *mon, *p;
    mon = (Monome *)malloc(sizeof(Monome));
    mon = CreerMonome();
    if (Liste == NULL) {
        return AjoutMonomeD(Liste);
    } else {
        p = Liste;
        while (p->nxt != NULL) {
            p = p->nxt;
        }
        mon->nxt = NULL;
        p->nxt = mon;
        return Liste;
    }
}

Monome* AjoutMonomePos(Monome *Liste,int pos){
    Monome *mon;
    mon = (Monome *)malloc(sizeof(Monome));
    mon = CreerMonome();
    if(pos == 1){
        return AjoutMonomeD(Liste);
    }else{
        Monome *p=Liste;
        for(int i=0; i<pos && p->nxt != NULL; i++){
            p=p->nxt;
        }
        if(p->nxt == NULL){
            return AjoutMonomeF(Liste);
        }else{
            mon->nxt=p->nxt;
            p->nxt=mon;
            return Liste;
        }
    }
}

Monome* AjoutMonomeTri(Monome *Liste){

    Monome *mon;
    mon = (Monome *)malloc(sizeof(Monome));
    mon = CreerMonome();
int puissance= mon->Exp;

    if (Liste == NULL || puissance > Liste->Exp) {
       return AjoutMonomeD(Liste);
    }

    Monome *p = Liste;
    while (p->nxt != NULL && p->nxt->Exp > puissance) {
        p = p->nxt;
    }
    mon->nxt = p->nxt;
    p->nxt = mon;
    return Liste;
}

void AfficherListe(Monome *Liste) {
    if (Liste == NULL) {
        printf("Polynôme => 0\n");
        return;
    }
    while (Liste != NULL) {
        if (Liste->Coeff != 0) {
            printf("%.1fX^%d + ", Liste->Coeff, Liste->Exp);
        }
        Liste = Liste->nxt;
    }
    printf("\n");
}

Monome* SupprimerD(Monome *Liste) {
    if (Liste == NULL) {
        printf("La liste est vide.\n");
        return NULL;
    }

    Monome *p = Liste;
    Liste = Liste->nxt;
    free(p);
    return Liste;
}

Monome* SupprimerF(Monome *Liste){
        if (Liste == NULL) {
        printf("La liste est vide.\n");
        return NULL;
    }
    Monome*p = Liste;
    while(p->nxt != NULL){
        p = p->nxt;
    }
    Monome *q = p;
    p=NULL;
    free(q);
    return Liste;
}

Monome* SupprimePos(Monome *Liste, int pos){
    if(pos == 1){
        return SupprimerD(Liste);
    }else{
        Monome *p=Liste;
        Monome *q;
        for(int i=0; i<pos && p->nxt != NULL; i++){
            q=p;
            p=p->nxt;
        }
        if(p->nxt == NULL){
            return SupprimerF(Liste);
        }else{
            q->nxt=p->nxt;
            free(p);
            return Liste;

        }
    }
}

Monome* SupprimerPuiss(Monome* Liste, int exp) {
    if (Liste == NULL) {
        printf("La liste est vide.\n");
        return NULL;
    }

    Monome *p = Liste;
    Monome *q = NULL; 

    while (p != NULL) {
        if (p->Exp == exp) {
            Monome *temp = p;

            if (q == NULL) {
                Liste = p->nxt;
            } else {
                q->nxt = p->nxt;
            }
            p = p->nxt; 
            free(temp); 
        } else {
            q = p; 
            p = p->nxt; 
        }
    }
    return Liste; 
}

int PolynomesEgaux(Monome* Poly1, Monome* Poly2) {
    while (Poly1 != NULL && Poly2 != NULL) {
        if (Poly1->Coeff != Poly2->Coeff || Poly1->Exp != Poly2->Exp) {
            return 0; // Les coefficients ou les exposants ne correspondent pas
        }
        Poly1 = Poly1->nxt;
        Poly2 = Poly2->nxt;
    }
    // Les deux polynômes doivent être terminés pour être égaux
    return (Poly1 == NULL && Poly2 == NULL);
}


int Appartient(Monome* Liste, float coeff, int exp) {
    while (Liste != NULL) {
        if (Liste->Coeff == coeff && Liste->Exp == exp) {
            return 1; // Le monôme appartient au polynôme
        }
        Liste = Liste->nxt;
    }
    return 0; // Le monôme n'appartient pas au polynôme
}


int ModifierCoefficient(Monome* Liste, int exp, float new_coeff) {
    while (Liste != NULL) {
        if (Liste->Exp == exp) {
            Liste->Coeff = new_coeff;
            return 1; // Mise à jour effectuée
        }
        Liste = Liste->nxt;
    }
    return 0; // L'exposant n'a pas été trouvé
}


void ProduitScalaire(Monome* Liste, float scalaire) {
    while (Liste != NULL) {
        Liste->Coeff *= scalaire;
        Liste = Liste->nxt;
    }
}

Monome* SommePolynomes(Monome* Poly1, Monome* Poly2) {
    Monome* resultat = NULL;
    while (Poly1 != NULL || Poly2 != NULL) {
        Monome* nouveau_monome = (Monome*)malloc(sizeof(Monome));
        if (Poly1 != NULL && Poly2 != NULL) {
            if (Poly1->Exp > Poly2->Exp) {
                *nouveau_monome = *Poly1;
                Poly1 = Poly1->nxt;
            } else if (Poly1->Exp < Poly2->Exp) {
                *nouveau_monome = *Poly2;
                Poly2 = Poly2->nxt;
            } else {
                nouveau_monome->Coeff = Poly1->Coeff + Poly2->Coeff;
                nouveau_monome->Exp = Poly1->Exp;
                Poly1 = Poly1->nxt;
                Poly2 = Poly2->nxt;
            }
        } else if (Poly1 != NULL) {
            *nouveau_monome = *Poly1;
            Poly1 = Poly1->nxt;
        } else {
            *nouveau_monome = *Poly2;
            Poly2 = Poly2->nxt;
        }
        nouveau_monome->nxt = resultat;
        resultat = nouveau_monome;
    }
    // Inverser le résultat pour obtenir le polynôme correctement ordonné
    Monome* reversed = NULL;
    while (resultat != NULL) {
        Monome* temp = resultat->nxt;
        resultat->nxt = reversed;
        reversed = resultat;
        resultat = temp;
    }
    return reversed;
}


int main() {
    Monome* poly1 = NULL;
    Monome* poly2 = NULL;
    int choix;
    do {
        printf("Menu :\n");
        printf("1. Ajouter un monôme au polynôme 1\n");
        printf("2. Ajouter un monôme au polynôme 2\n");
        printf("3. Supprimer un monôme du polynôme 1\n");
        printf("4. Supprimer un monôme du polynôme 2\n");
        printf("5. Vérifier l'égalité des polynômes\n");
        printf("6. Vérifier l'appartenance d'un monôme à un polynôme\n");
        printf("7. Modifier le coefficient d'un exposant dans un polynôme\n");
        printf("8. Calculer le produit d'un polynôme par un scalaire\n");
        printf("9. Calculer la somme de deux polynômes\n");
        printf("10. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                printf("Choisissez le type d'ajout pour le polynôme 1 :\n");
                printf("1. Ajout au début\n");
                printf("2. Ajout à la fin\n");
                printf("3. Ajout par position\n");
                printf("4. Ajout trié\n");
                printf("Entrez votre choix : ");
                int choixAjout1;
                scanf("%d", &choixAjout1);
                switch (choixAjout1) {
                    case 1:
                        poly1 = AjoutMonomeD(poly1);
                        break;
                    case 2:
                        poly1 = AjoutMonomeF(poly1);
                        break;
                    case 3:
                        printf("Entrez la position : ");
                        int pos;
                        scanf("%d", &pos);
                        poly1 = AjoutMonomePos(poly1, pos);
                        break;
                    case 4:
                        poly1 = AjoutMonomeTri(poly1);
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
                break;
            case 2:
                printf("Choisissez le type d'ajout pour le polynôme 2 :\n");
                printf("1. Ajout au début\n");
                printf("2. Ajout à la fin\n");
                printf("3. Ajout par position\n");
                printf("4. Ajout trié\n");
                printf("Entrez votre choix : ");
                int choixAjout2;
                scanf("%d", &choixAjout2);
                switch (choixAjout2) {
                    case 1:
                        poly2 = AjoutMonomeD(poly2);
                        break;
                    case 2:
                        poly2 = AjoutMonomeF(poly2);
                        break;
                    case 3:
                        printf("Entrez la position : ");
                        int pos;
                        scanf("%d", &pos);
                        poly2 = AjoutMonomePos(poly2, pos);
                        break;
                    case 4:
                        poly2 = AjoutMonomeTri(poly2);
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
                break;
             case 3:
                printf("Entrez la position du monôme à supprimer dans le polynôme 1 : ");
                int pos1;
                scanf("%d", &pos1);
                poly1 = SupprimePos(poly1, pos1);
                break;
            case 4:
                printf("Entrez la position du monôme à supprimer dans le polynôme 2 : ");
                int pos2;
                scanf("%d", &pos2);
                poly2 = SupprimePos(poly2, pos2);
                break;
            case 5:
                if (PolynomesEgaux(poly1, poly2)) {
                    printf("Les polynômes sont égaux.\n");
                } else {
                    printf("Les polynômes ne sont pas égaux.\n");
                }
                break;
            case 6:
                printf("Vérification de l'appartenance d'un monôme à un polynôme :\n");
                printf("Entrez le coefficient du monôme : ");
                float coeff;
                scanf("%f", &coeff);
                printf("Entrez l'exposant du monôme : ");
                int exp;
                scanf("%d", &exp);
                if (Appartient(poly1, coeff, exp)) {
                    printf("Le monôme appartient au polynôme 1.\n");
                } else if (Appartient(poly2, coeff, exp)) {
                    printf("Le monôme appartient au polynôme 2.\n");
                } else {
                    printf("Le monôme n'appartient à aucun des polynômes.\n");
                }
                break;
            case 7:
                printf("Modification du coefficient d'un exposant dans un polynôme :\n");
                printf("Entrez l'exposant : ");
                int exp_modif;
                scanf("%d", &exp_modif);
                printf("Entrez le nouveau coefficient : ");
                float new_coeff;
                scanf("%f", &new_coeff);
                int modif1 = ModifierCoefficient(poly1, exp_modif, new_coeff);
                int modif2 = ModifierCoefficient(poly2, exp_modif, new_coeff);
                if (modif1 || modif2) {
                    printf("Coefficient modifié avec succès.\n");
                    printf("Polynôme 1 après modification : ");
                    AfficherListe(poly1);
                    printf("Polynôme 2 après modification : ");
                    AfficherListe(poly2);
                } else {
                    printf("L'exposant n'a pas été trouvé dans les polynômes.\n");
                }
                break;
            case 8:
                printf("Calcul du produit d'un polynôme par un scalaire :\n");
                printf("Entrez le scalaire : ");
                float scalaire;
                scanf("%f", &scalaire);
                ProduitScalaire(poly1, scalaire);
                ProduitScalaire(poly2, scalaire);
                printf("Polynôme 1 multiplié par le scalaire : ");
                AfficherListe(poly1);
                printf("Polynôme 2 multiplié par le scalaire : ");
                AfficherListe(poly2);
                break;
            case 9:
                printf("Calcul de la somme de deux polynômes :\n");
                Monome* somme = SommePolynomes(poly1, poly2);
                printf("La somme des polynômes est : ");
                AfficherListe(somme);
                // Libérer la mémoire allouée pour la liste de la somme
                Monome* temp;
                while (somme != NULL) {
                    temp = somme;
                    somme = somme->nxt;
                    free(temp);
                }
    break;
            case 10:
                printf("Fin du programme.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 10);
    return 0;
}