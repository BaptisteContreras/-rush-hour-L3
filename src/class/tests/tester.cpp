//
// Created by baptiste on 24/03/19.
//

#include <header/tester.h>

#include "stdio.h"
#include "iostream"
//#include <bits/unordered_set.h>



using  namespace std;



bool tester::test_moveDown(bool affichage) {
    return
            test_moveDownVertical(affichage) &&
            test_moveDownVerticalColisionVertical(affichage) &&
            test_moveDownVerticalColisionHorizontal(affichage) &&
            test_moveDownVerticalColisionMur(affichage) &&
            test_moveDownHorizontal(affichage) &&
            test_moveDownHorizontalColisionVertical(affichage) &&
            test_moveDownHorizontalColisionHorizontal(affichage) &&
            test_moveDownHorizontalColisionMur(affichage);

}

bool tester::test_moveUp(bool affichage) {
    return
            test_moveUpVertical(affichage)&&
            test_moveUpVerticalColisionVertical(affichage)&&
            test_moveUpVerticalColisionHorizontal(affichage)&&
            test_moveUpVerticalColisionMur(affichage)&&
            test_moveUpHorizontal(affichage)&&
            test_moveUpHorizontalColisionVertical(affichage)&&
            test_moveUpHorizontalColisionHorizontal(affichage)&&
            test_moveUpHorizontalColisionMur(affichage);

}

bool tester::test_moveRight(bool affichage) {
    return
            test_moveRightVertical(affichage)&&
            test_moveRightVerticalColisionVertical(affichage)&&
            test_moveRightVerticalColisionHorizontal(affichage)&&
            test_moveRightVerticalColisionMur(affichage)&&
            test_moveRightHorizontal(affichage)&&
            test_moveRightHorizontalColisionVertical(affichage)&&
            test_moveRightHorizontalColisionHorizontal(affichage)&&
            test_moveRightHorizontalColisionMur(affichage);

}

bool tester::test_moveLeft(bool affichage) {
    return
            test_moveLeftVertical(affichage)&&
            test_moveLeftVerticalColisionVertical(affichage)&&
            test_moveLeftVerticalColisionHorizontal(affichage)&&
            test_moveLeftVerticalColisionMur(affichage)&&
            test_moveLeftHorizontal(affichage)&&
            test_moveLeftHorizontalColisionVertical(affichage)&&
            test_moveLeftHorizontalColisionHorizontal(affichage)&&
            test_moveLeftHorizontalColisionMur(affichage);

}

bool tester::test_allMove(bool affichage) {
    return test_moveLeft(affichage)&&test_moveRight(affichage)&&test_moveUp(affichage)&&test_moveDown(affichage);
}


bool tester::test_moveDownVertical(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{1,3,2,0}; // main car
    state[2] = new int[4]{5,3,1,0};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveDown(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (isSameState(state,stateFinal)){
        cout << "move Down Vertical failed ";
        return false;
    }

    return true;
}

bool tester::test_moveDownVerticalColisionVertical(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{1,3,2,0}; // main car
    state[2] = new int[4]{3,3,2,0};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveDown(stateFinal,1);

    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveDownVerticalColisionVertical failed " << endl;
        return false;
    }
    return true;
}

bool  tester::test_moveDownVerticalColisionHorizontal(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5}; // main car
    state[1] = new int[4]{1,4,3,0}; // main car
    state[2] = new int[4]{4,2,3,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveDown(stateFinal,1);

    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveDownVerticalColisionHorizontal failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveDownVerticalColisionMur(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5}; // main car
    state[1] = new int[4]{4,5,2,0}; // main car
    state[2] = new int[4]{0,0,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveDown(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveDownVerticalColisionMur failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveDownHorizontal(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{0,3,2,1}; // main car
    state[2] = new int[4]{0,0,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveDown(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (isSameState(state,stateFinal)){
        cout << "test_moveDownHorizontal failed ";
        return false;
    }
    return true;
}

bool tester::test_moveDownHorizontalColisionVertical(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{3,2,3,1}; // main car
    state[2] = new int[4]{4,4,2,0};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveDown(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveDownHorizontalColisionVertical failed ";
        return false;
    }
    return true;
}

bool tester::test_moveDownHorizontalColisionHorizontal(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{3,3,2,1}; // main car
    state[2] = new int[4]{4,2,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveDown(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveDownHorizontalColisionHorizontal failed ";
        return false;
    }
    return true;
}

bool tester::test_moveDownHorizontalColisionMur(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{5,4,2,1}; // main car
    state[2] = new int[4]{0,0,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveDown(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveDownHorizontalColisionMur failed ";
        return false;
    }
    return true;
}

bool tester::test_moveUpVertical(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{4,3,2,0}; // main car
    state[2] = new int[4]{1,3,2,0};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveUp(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (isSameState(state,stateFinal)){
        cout << "test_moveUpVertical failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveUpVerticalColisionVertical(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{3,3,2,0}; // main car
    state[2] = new int[4]{1,3,2,0};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveUp(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveUpVerticalColisionVertical failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveUpVerticalColisionHorizontal(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{3,3,2,0}; // main car
    state[2] = new int[4]{2,3,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveUp(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveUpVerticalColisionHorizontal failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveUpVerticalColisionMur(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{0,0,2,0}; // main car
    state[2] = new int[4]{5,5,2,0};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveUp(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveUpVerticalColisionMur failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveUpHorizontal(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{3,3,2,1}; // main car
    state[2] = new int[4]{5,5,2,0};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveUp(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (isSameState(state,stateFinal)){
        cout << "test_moveUpHorizontal failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveUpHorizontalColisionVertical(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{3,1,3,1}; // main car
    state[2] = new int[4]{1,3,2,0};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveUp(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveUpHorizontalColisionVertical failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveUpHorizontalColisionHorizontal(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{3,3,2,1}; // main car
    state[2] = new int[4]{2,3,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveUp(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveUpHorizontalColisionHorizontal failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveUpHorizontalColisionMur(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{0,0,2,1}; // main car
    state[2] = new int[4]{5,5,2,0};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveUp(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveUpHorizontalColisionMur failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveRightVertical(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{2,0,3,0}; // main car
    state[2] = new int[4]{1,1,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveRight(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (isSameState(state,stateFinal)){
        cout << "test_moveRightVertical failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveRightVerticalColisionVertical(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{3,0,2,0}; // main car
    state[2] = new int[4]{4,1,2,0};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveRight(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveRightVerticalColisionVertical failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveRightVerticalColisionHorizontal(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{2,0,2,0}; // main car
    state[2] = new int[4]{3,1,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveRight(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveRightVerticalColisionHorizontal failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveRightVerticalColisionMur(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{3,5,2,0}; // main car
    state[2] = new int[4]{5,1,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveRight(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveRightVerticalColisionMur failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveRightHorizontal(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{3,0,2,1}; // main car
    state[2] = new int[4]{5,1,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveRight(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (isSameState(state,stateFinal)){
        cout << "test_moveRightHorizontal failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveRightHorizontalColisionVertical(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{3,0,2,1}; // main car
    state[2] = new int[4]{1,2,3,0};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveRight(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveRightHorizontalColisionVertical failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveRightHorizontalColisionHorizontal(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{3,0,2,1}; // main car
    state[2] = new int[4]{3,2,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveRight(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveRightHorizontalColisionHorizontal failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveRightHorizontalColisionMur(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{5,4,2,1}; // main car
    state[2] = new int[4]{0,5,2,0};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveRight(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveRightHorizontalColisionMur failed " << endl;
        return false;
    }
    return true;
}



bool tester::test_moveLeftVertical(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{4,5,2,0}; // main car
    state[2] = new int[4]{1,4,3,0};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveLeft(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (isSameState(state,stateFinal)){
        cout << "test_moveLeftVertical failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveLeftVerticalColisionVertical(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{1,5,2,0}; // main car
    state[2] = new int[4]{0,4,2,0};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveLeft(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveLeftVerticalColisionVertical failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveLeftVerticalColisionHorizontal(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{0,5,3,0}; // main car
    state[2] = new int[4]{2,3,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveLeft(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveLeftVerticalColisionHorizontal failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveLeftVerticalColisionMur(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{0,0,2,0}; // main car
    state[2] = new int[4]{5,3,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveLeft(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveLeftVerticalColisionMur failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveLeftHorizontal(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{0,4,2,1}; // main car
    state[2] = new int[4]{5,3,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveLeft(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (isSameState(state,stateFinal)){
        cout << "test_moveLeftHorizontal failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveLeftHorizontalColisionVertical(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{1,4,2,1}; // main car
    state[2] = new int[4]{0,3,2,0};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveLeft(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveLeftHorizontalColisionVertical failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveLeftHorizontalColisionHorizontal(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{0,4,2,1}; // main car
    state[2] = new int[4]{0,2,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveLeft(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveLeftHorizontalColisionHorizontal failed " << endl;
        return false;
    }
    return true;
}

bool tester::test_moveLeftHorizontalColisionMur(bool affichage) {
    int** state = new int*[3];
    state[0] = new int[4]{2,5};
    state[1] = new int[4]{0,0,2,1}; // main car
    state[2] = new int[4]{5,2,2,1};
    int** stateFinal;
    stateFinal = cloneState(state);
    moveLeft(stateFinal,1);
    if (affichage){
        afficheur->affiche(state);
        afficheur->affiche(stateFinal);
    }
    if (!isSameState(state,stateFinal)){
        cout << "test_moveLeftHorizontalColisionMur failed " << endl;
        return false;
    }
    return true;
}


bool tester::moveLeft(int **currentState, int carID) {
    return res->moveLeft(currentState,carID);
}

bool tester::moveRight(int **currentState, int carID) {
    return res->moveRight(currentState,carID);
}

bool tester::moveDown(int **currentState, int carID) {
    return res->moveDown(currentState,carID);
}

bool tester::moveUp(int **currentState, int carID) {
    return res->moveUp(currentState,carID);;
}

bool tester::isSameState(int **stateInitial, int **stateFinal) {
    return res->isSameState(stateInitial,stateFinal);
}

int **tester::cloneState(int **toclone) {
    return res->cloneState(toclone);
}

tester::~tester() {
    delete(afficheur);

}



tester::tester(resolver *r)  {
    afficheur = new Afficheur(6,6);
    afficheur->sizeS = 3;
    res = r;
    r->changeSize(3);

}









