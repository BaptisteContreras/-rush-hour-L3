//
// Created by baptiste on 24/03/19.
//

#ifndef RUSH_TESTER_H
#define RUSH_TESTER_H

#include "header/resolver.h"
#include "header/Afficheur.h"
//#include <bits/unordered_set.h>


class tester {
public:


    tester(resolver *res);

    virtual ~tester();

    // TEST FONCTIONS DE DEPLACEMENT
    bool test_moveDown(bool affichage);

    bool test_moveUp(bool affichage);

    bool test_moveRight(bool affichage);

    bool test_moveLeft(bool affichage);

    bool test_allMove(bool affichage);


    // TESTS

    // Move Down
    bool  test_moveDownVertical(bool affichage);

    bool  test_moveDownVerticalColisionVertical(bool affichage);

    bool  test_moveDownVerticalColisionHorizontal(bool affichage);

    bool  test_moveDownVerticalColisionMur(bool affichage);

    bool  test_moveDownHorizontal(bool affichage);

    bool  test_moveDownHorizontalColisionVertical(bool affichage);

    bool  test_moveDownHorizontalColisionHorizontal(bool affichage);

    bool  test_moveDownHorizontalColisionMur(bool affichage);

    // Move Up
    bool  test_moveUpVertical(bool affichage);

    bool  test_moveUpVerticalColisionVertical(bool affichage);

    bool  test_moveUpVerticalColisionHorizontal(bool affichage);

    bool  test_moveUpVerticalColisionMur(bool affichage);

    bool  test_moveUpHorizontal(bool affichage);

    bool  test_moveUpHorizontalColisionVertical(bool affichage);

    bool  test_moveUpHorizontalColisionHorizontal(bool affichage);

    bool  test_moveUpHorizontalColisionMur(bool affichage);
    // Move Right
    bool  test_moveRightVertical(bool affichage);

    bool  test_moveRightVerticalColisionVertical(bool affichage);

    bool  test_moveRightVerticalColisionHorizontal(bool affichage);

    bool  test_moveRightVerticalColisionMur(bool affichage);

    bool  test_moveRightHorizontal(bool affichage);

    bool  test_moveRightHorizontalColisionVertical(bool affichage);

    bool  test_moveRightHorizontalColisionHorizontal(bool affichage);

    bool  test_moveRightHorizontalColisionMur(bool affichage);


    // Move Left
    bool  test_moveLeftVertical(bool affichage);

    bool  test_moveLeftVerticalColisionVertical(bool affichage);

    bool  test_moveLeftVerticalColisionHorizontal(bool affichage);

    bool  test_moveLeftVerticalColisionMur(bool affichage);

    bool  test_moveLeftHorizontal(bool affichage);

    bool  test_moveLeftHorizontalColisionVertical(bool affichage);

    bool  test_moveLeftHorizontalColisionHorizontal(bool affichage);

    bool  test_moveLeftHorizontalColisionMur(bool affichage);




private:

    /**
     * Afficheur pour visualer les tests
     */
    Afficheur* afficheur;

    /**
     * cf cloneState de resolver.h
     * @param toclone
     * @return
     */
    int** cloneState(int** toclone);


    bool isSameState(int** stateInitial, int** stateFinal);

    /**
     * Applique un mouvement vers le haut sur une voiture donnée (Y+1)
     * Renvois un nouvel état après avoir appliqué le déplacement sur le véhicule
     * @param currentState
     * @param carID
     * @return
     */
    bool moveUp(int **currentState, int carID);

    /**
     * Applique un mouvement vers le bas sur une voiture donnée (Y-1)
     * Renvois un nouvel état après avoir appliqué le déplacement sur le véhicule
     * @param currentState
     * @param carID
     * @return
     */
    bool moveDown(int **currentState, int carID);

    /**
     * Applique un mouvement vers la droite sur une voiture donnée (X+1)
     * Renvois un nouvel état après avoir appliqué le déplacement sur le véhicule
     * @param currentState
     * @param carID
     * @return
    */
    bool moveRight(int **currentState, int carID);

    /**
     * Applique un mouvement vers la gauche sur une voiture donnée (X-1)
     * Renvois un nouvel état après avoir appliqué le déplacement sur le véhicule
     * @param currentState
     * @param carID
     * @return
    */
    bool moveLeft(int **currentState, int carID);


    /**
     * Resolver
     * Permet d'acceder aux méthodes de déplacement
     */
    resolver* res;




};


#endif //RUSH_TESTER_H
