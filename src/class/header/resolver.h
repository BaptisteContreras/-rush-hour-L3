//
// Created by baptiste on 27/02/19.
//

#ifndef RUSH_PLATEAU_H
#define RUSH_PLATEAU_H

#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <random>
#include <bits/stdc++.h>
#include "structs/move.h"
#include "Afficheur.h"
#include "enum/direction.h"
#include "structs/Node.h"


using namespace std;

class resolver {

public:
    /**
     * Constructeur qui prend en paramètre la largeur et la hauteur du plateau
     * Par defaut 6x6
     * @param l
     * @param h
     */
    resolver(int l, int h);


    /**
     * Taille de l'état initial
     */
    int stateSize;

    /**
     * setter pour l'attribut stateSize
     * @param s
     */
    void changeSize(int s);

    /**
     * Méthode qui va initialiser le premier état du jeu grâce au fichier passé en paramètre
     * @param filename
     */
    void init(string filename);

    /**
     * Lis et affiche les mouvement dans l'historique
     */
    void readHistory();

    /**
     * Supprime tout les mouvements de l'historique
     */
    void clearHistory();

    /**
     * Change l'état de base par un nouveau passé en paramètre
     * @param newState
     */
    void changeCurrentState(int **newState);

    /**
     * Destructeur de la classe
     */
    virtual ~resolver();

    /**
     * Affiche dans la console l'état passé en paramètre
     * @param state
     */
    void displayState(int **state);

    /**
     * Retourne le nombre d'élément pour un tableau 2D d'entier donné en paramètre
     * Comme il est impossible d'avoir la taillé d'un int**, la méthode retourne stateSize qui est la taille de l'état inital stocké
     * @param array
     * @return
     */
     int sizeOfArray(int **array);


    /**
     * Clone un état
     * la sortie et chaque voiture sont copié
     * @param toclone
     * @return
     */
    int** cloneState(int** toclone);




    /**
     * Vérifie que chaque ligne d'un état initial est la même que celle dans l'état final
     * @param stateInitial
     * @param stateFinal
     * @return
     */
    bool isSameState(int** stateInitial, int** stateFinal);

    /**
     * Applique un mouvement vers le haut sur une voiture donnée (Y+1)
     * Renvois true si le déplacement a été  appliqué  sur le véhicule
     * @param currentState
     * @param carID
     * @return
     */
    bool moveUp(int **currentState, int carID);

    /**
     * Applique un mouvement vers le bas sur une voiture donnée (Y-1)
     * Renvois true si le déplacement a été  appliqué  sur le véhicule
     * @param currentState
     * @param carID
     * @return
     */
    bool moveDown(int **currentState, int carID);

    /**
     * Applique un mouvement vers la droite sur une voiture donnée (X+1)
     * Renvois true si le déplacement a été  appliqué  sur le véhicule
     * @param currentState
     * @param carID
     * @return
    */
    bool moveRight(int **currentState, int carID);

    /**
     * Applique un mouvement vers la gauche sur une voiture donnée (X-1)
     * Renvois true si le déplacement a été  appliqué  sur le véhicule
     * @param currentState
     * @param carID
     * @return
    */
    bool moveLeft(int **currentState, int carID);

    /**
     * Fonction principale pour résoudre le jeu
     * utilise le parcour en largeur
     * @return
     */
    int resolve();







private:
    /**
     * Largeur du plateau de jeu
     * La largeur représente l'axe des X
     */
    int largeur;
    /**
     * Hauteur du plateau de jeu
     * la hauteur représente l'axe des Y
     */
    int hauteur;
    /**
     * Etat de base du jeu
     * Tableau 2D d'entier
     * La première ligne contient les coordonnées de la sortie
     * La deuxième ligne représente le véhicule à sortir [y, x, taille (de 1 à 3), position (0=vertical, 1=horizontal)]
     * Les lignes qui suivent contiennent : y, x, taille (de 1 à 3), position (0=vertical, 1=horizontal)
     * y,x car : lignes=y et colonnes=x
     */
    int **initialState;

    /**
     * Applique un vecteur de déplacement sur les coordonnées X et Y d'une voiture passé en paramètre
     * Renvois true si le déplacement a été  appliqué  sur le véhicule
     * Ne doit pas être appel", il faut utiliser les surcouches (moveUp, moveDown, moveLeft, moveRight)
     * Attention, les fonctions de mouvement change directement l'état passé en paramètre,
     * Il ne faut pas oublier de cloner l'état si on veut garder un historique et ne pas modifier directement l'état initial
     * cf cloneState
     * @param currentState
     * @param carID
     * @param vector
     * @return
     */
    bool move(int **currentState, int carID, int *vector);



    /**
     * Vérifie si le déplacement est valide
     * vérifie si la voiture n'écrase pas une autre ou ne sors pas du plateau
     * @param state
     * @param idCar
     * @param move
     * @return
     */
    bool checkMoveValide(int **state, int idCar, int *move);

    /**
     * Ajoute un état dans l'historique
     * Si clone = true, l'état à ajouté sera cloné
     * @param state
     * @param clone
     */
    void addToHistory(int **state, bool clone);


    /**
     * FIFO pour le parcour en profondeur
     * plus utilisé
     */
    queue<int **> history;

    /**
    * FIFO pour stocker les mouvements
    * plus utilisé
    */
    queue<struct move> moveHistory;


    /**
     * Objet Afficheur qui s'occupe d'afficher à l'écran les états
     */
    Afficheur *afficheur;

    /**
     * Première version de la résolution
     * Parcour en profondeur avec construction du graphe et parcour en même temps
     * Problème : trop long
     * Problème de boucle : retour en arrière avec 2 / 3 et 4 voiture
     * Provoque un stack overflow des fois due a une boucle infini
     * Inutilisé
     * @param currentState
     * @param moves
     * @param lastMove
     * @param lastMove2
     * @param lastMove3
     * @param lastMove4
     * @param cmt
     * @return
     */
    vector<struct move> parcourProfondeur(int** currentState,vector<struct move> moves,struct move lastMove,struct move lastMove2,struct move lastMove3,struct move lastMove4,int cmt);

    /**
     * Parcour en largeur du graphe
     * permet de trouver une solution en 240 000 itérations
     * Retourne un Noeud qui contient l'état actuel et son noeud parent
     * En remontant les parents du noeud final on peut reconstruire le chemin à suivre pour la solution
     * @param currentState tableau 2D qui est l'état initial à partir duquel on va faire le graph et le parcour
     * Le parcour s'arrete quand on trouve un état final
     * @return Noeud final qui contient l'état final et son parent
     */
    Node parcourLargeur(int ** currentState);


    /**
     * Renvois Vrai si dans la voiture à atteind la sortie
     * @param state Etat à vérifier
     * @return Bool
     */
    bool isWinningState(int** state);


    /**
     * Libère la mémoire allouée pour un état
     * @param state Etat à détruire
     */
    void destructState(int** state);

    /**
     * Applique le mouvement correspondant au move passé en paramètre
     * plus utilisé
     * @param state Etat de départ
     * @param move1 voiture + mouvement
     * @return Etat après mouvement
     */
    int** applyMoveTo(int** state, struct move move1);

    /**
     * Hash un état
     * Les ligne du tableau sont concaténé
     * un hash unique par état
     * @param state Etat à haché
     * @return hach de l'état
     */
    string hashState(int** state);
    /**
     * Set de hash des états dèjà visité
     */
    unordered_set<string> childrenSet;
    /**
     * FIFO des état à visiter pour le parcour en largeur
     */
    queue<int**> children;

    /**
     * liste des noeuds parcouru.
     *
     */
    vector<Node> old;
    /**
     * Vérifie si un hash donné se trouve dans le childrenSet
     * @param hash hash d'un état
     * @return vrai si l'état le hash se trouve dans le set
     */
    bool hashAlreadyIn(string hash);
    /**
     * Pour un noeud, ajoute tout ses fils dans la FIFO pour le parcour en largreur
     * Les fils sont en fait les 4 mouvements (Up,Down,Right,Left) appliqués à toute les voitures
     * de l'état. Si un mouvement est impossible, aucun noeud n'est crée
     * @param st Noeud parent
     */
    void addChildrenInQueue(int** state,int* index);

    /**
     * Vérifie si un état est bloqué (si il y a une boucle inifinie avec plusieurs voitures)
     * plus utilisé
     * @param moves liste des mouvements appliqués
     * @return
     */
    bool checkIfBlocked(vector<struct move> moves);


    /**
     * Renvois Vrai si deux état sont similaire ligne à ligne et colonne à colonne
     * @param move1 Etat 1
     * @param move2 Etat 2
     * @return Vrai si similaire
     */
    bool moveEqual(struct move move1, struct move move2);


    /**
     * Affiche toute les étapes pour résoudre le jeu en partant du noeud final
     * @param end
     */
    void afficheSolution(Node end);



};


#endif //RUSH_PLATEAU_H
