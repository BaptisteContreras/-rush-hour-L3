//
// Created by baptiste on 29/03/19.
//

#ifndef RUSH_NODE_H
#define RUSH_NODE_H

#include <iosfwd>
#include <ostream>
#include "move.h"

using namespace std;

class Node {

public:
    /**
     * Constructeur d'un noeud
     * @param parent Noeud parent
     * @param state Etat actuel du jeu
     */
    Node(int parent, int **state);

    /**
     * Constructeur par défaut
     */
    Node();



    /**
     * Etat du jeu
     */
    int** state;

    /**
     * Renvois la profondeur de la solution
     * @return int
     */

    int idParent;

    /**
     * Permet de savoir quel mouvement a été appliqué sur quelle voiture
     */
    struct move m;




};


#endif //RUSH_NODE_H
