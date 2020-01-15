//
// Created by baptiste on 27/02/19.
//

#ifndef RUSH_AFFICHEUR_H
#define RUSH_AFFICHEUR_H


#include <string>
#include <vector>
#include "structs/Node.h"

using namespace std;
class Afficheur {

public:
    char getSymbole(int index);
    /**
     * Méthode qui affiche un état du jeu
     * @param state
     */
    void affiche(int** state);
    /**
     * Constructeur de l'afficheur, prend en paramètre la hauteur et la largeur du plateau pour l'affichge
     * @param hauteur
     * @param largeur
     */
    Afficheur(int hauteur, int largeur);

    /**
     * Destructeur par défaut
     */
    virtual ~Afficheur();


    int sizeS;



    void initSize(int s);

private:
    /**
     * Transforme un état en tableau de string pouvant être affiché
     * @param state
     * @return
     */
    string ** stateToAffichage(int** state);

    /**
     * Parcour et affiche un tableau de string représentant un état transformé
     * tab est un tableau 2D de hateur * largeur
     * @param tab
     */
    void display(string ** tab);

    /**
     * Hauteur du plateau
     * Largeur du plateau
     * Sert à définir les dimension du plateau à afficher
     * Par défaut 6*6
     */
    int hauteur,largeur;

    /**
     * Tableau de charactère pour représenter les voitures
     */
    char *carac;




    /**
     * Initialise le tableau de string avec les bordures
     * les cases du plateau sont affiché comme vide
     * @param tab
     */
    void initDisplayTab(string**tab);

    /**
     * Lis l'état et affiche les voitures en fonction de leur coordonnées/taille/pos
     * Affiche un caractère par voiture
     * La voiture à faire sortir est représenté par un B
     * La sortie est représentée par <>
     * @param state
     * @param size
     * @param tab
     */
    void readState(int** state,int size, string** tab);

    /**
     * Place correctement une voiture vertical ne fonction de sa taille
     * @param id
     * @param car
     * @param tab
     */
    void placeVoitureVertical(int id,int* car, string** tab);

    /**
     * place correctement une voiture horizontal en fonction de sa taille
     * @param id
     * @param car
     * @param tab
     */
    void placeVoitureHorizontal(int id,int* car, string** tab);






};


#endif //RUSH_AFFICHEUR_H
