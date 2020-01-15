//
// Created by baptiste on 27/02/19.
//

#include "header/resolver.h"
#include "header/Builder.h"
#include <stdio.h>
#include <iostream>

#include <header/resolver.h>
#include <cstring>
#include <random>
#include <functional>
#include <sstream>



using namespace std;


// Constructeur && init
resolver::resolver(int l, int h) {
    largeur = l;
    hauteur = h;
    afficheur = new Afficheur(hauteur, largeur);
}


void resolver::init(string filename) {
    Builder builder(filename);
    initialState = builder.load();
    stateSize = builder.size;
    afficheur->sizeS = stateSize;

    //afficheur->affiche(initialState);


}

void resolver::displayState(int **state) {
    afficheur->affiche(state);

}

// Méthodes de déplacement d'un véhicule

bool resolver::move(int **currentState, int carID, int *vector) {
    if (!checkMoveValide(currentState, carID, vector)) {
        return false;
    }

    currentState[carID][0] += vector[0];
    currentState[carID][1] += vector[1];
    return true;
}

bool resolver::moveUp(int **currentState, int carID) {
    int deplacement[2] = {-1, 0};
    return move(currentState, carID, deplacement);
}

bool resolver::moveRight(int **currentState, int carID) {
    int deplacement[2] = {0, 1};
    return move(currentState, carID, deplacement);
}

bool resolver::moveDown(int **currentState, int carID) {
    int deplacement[2] = {1, 0};
    return move(currentState, carID, deplacement);
}

bool resolver::moveLeft(int **currentState, int carID) {
    int deplacement[2] = {0, -1};
    return move(currentState, carID, deplacement);
}

bool resolver::checkMoveValide(int **state, int idCar, int *move) {
    // Les premiers test servent à verifier que le mouvement ne fais pas sortir la voiture du tableau
    // Il y a des tests différent selon la position (vertical=0&horizontal=1) de la voiture
    // vectical
    if (state[idCar][3] == 1) {
        if (state[idCar][0] + move[0] >= 6 || state[idCar][1] + move[1] + state[idCar][2] - 1 >= 6 ||
            state[idCar][0] + move[0] < 0 || state[idCar][1] + move[1] < 0)
            return false;
    } else { // vertical
        if (state[idCar][0] + move[0] + state[idCar][2] - 1 >= 6 || state[idCar][1] + move[1] >= 6 ||
            state[idCar][0] + move[0] < 0 || state[idCar][1] + move[1] < 0)
            return false;
    }

    // Ensuite, pour chaque voiture du tableau, (sauf elle même), on vérifie que le déplacement
    // ne fait pas entrer en collision deux voiture
    // Il y a des tests selon la position de la voiture idCar qu'on veut déplacer et selon la position de la voiture actuel qu'on test
    for (int i = 1; i < sizeOfArray(state); i++) {
        if (idCar != i) {
            if (state[idCar][3] == 0) {
                // idCar is vertical
                if (state[i][3] == 0) {
                    // current car vertical
                    // Test pour idCar vertical et i vertical
                    if (state[idCar][1] + move[1] == state[i][1] &&
                        (state[idCar][0] + move[0] >= state[i][0] &&
                         state[i][2] > state[idCar][0] + move[0] - state[i][0]))
                        return false;

                    if (state[idCar][1] + move[1] == state[i][1] &&
                        (state[idCar][0] + move[0] < state[i][0] &&
                         state[idCar][2] > state[i][0] - (state[idCar][0] + move[0])))
                        return false;


                } else {
                    // current car horizontal
                    // Test pour idCar vertical et i horizontal
                    if(state[idCar][2] == 1){
                        if ((state[i][1] <= state[idCar][1] + move[1] &&
                             state[i][1] + state[i][2] - 1 >= state[idCar][1] + move[1])) {
                            if (state[idCar][0] + move[0] <= state[i][0] &&
                                state[idCar][0] + move[0]   >= state[i][0] ) {

                                return false;
                            }
                        }
                    }else{
                        if ((state[i][1] <= state[idCar][1] + move[1] &&
                             state[i][1] + state[i][2] - 1 >= state[idCar][1] + move[1])) {
                            if (state[idCar][0] + move[0] <= state[i][0] &&
                                state[idCar][0] + move[0] + state[i][2]  >= state[i][0]) {

                                return false;
                            }
                        }
                    }



                }
            } else {
                // idCar is horizontal

                if (state[i][3] == 0) {
                    // current car vertical
                    // Test pour idCar horizontal et i vertical
                    if ((state[i][1] >= state[idCar][1] + move[1] &&
                         state[i][1] <= state[idCar][1] + move[1] + state[idCar][2] - 1)) {
                        if (state[idCar][0] + move[0] >= state[i][0] &&
                            state[idCar][0] + move[0] <= state[i][0] + state[i][2] - 1)
                            return false;
                    }
                } else {
                    // current car horizontal
                    // Test pour idCar horizontal et i horizontal
                    if (state[idCar][1] + move[1] <= state[i][1] &&
                        (state[idCar][2]) > state[i][1] - (state[idCar][1] + move[1]) &&
                        state[idCar][0] + move[0] == state[i][0])
                        return false;
                    if (state[idCar][1] + move[1] > state[i][1] &&
                        (state[i][2]) > (state[idCar][1] + move[1]) - state[i][1] &&
                        state[idCar][0] + move[0] == state[i][0])
                        return false;
                }


            }

        }
    }
    // All test passed
    // La voiture n'est pas en dehors du tableau et sont déplacement ne la fait pas rentrer en collision avec une autre
    return true;
}

// destructeur
resolver::~resolver() {
    //delete (afficheur);
    for (int i = 0; i < sizeOfArray(initialState); ++i) {
        delete[] initialState[i];
    }
    delete[] initialState;
}

// Méthodes sur l'historique
void resolver::readHistory() {
    while (!history.empty()) {
        int **up = history.front();
        afficheur->affiche(up);
        history.pop();
        for (int i = 0; i < sizeOfArray(up); ++i) {
            delete[] up[i];
        }
        delete[] up;
    }
}


void resolver::clearHistory() {
    queue<int **> empty;
    swap(history, empty);
}




int resolver::sizeOfArray(int **array) {


    return stateSize;

}

void resolver::addToHistory(int **state, bool clone) {
    int **toadd = state;
    if (clone) {
        toadd = cloneState(state);
    }
    history.push(toadd);
}


int **resolver::cloneState(int **toclone) {
    int size = sizeOfArray(toclone);
    int **dest = new int *[size];
    for (int i = 0; i < size; ++i) {
        dest[i] = new int[4];
        dest[i][0] = toclone[i][0];
        dest[i][1] = toclone[i][1];
        dest[i][2] = toclone[i][2];
        dest[i][3] = toclone[i][3];
    }
    return dest;
}

bool resolver::isSameState(int **stateInitial, int **stateFinal) {
    for (int i = 0; i < sizeOfArray(stateInitial); ++i) {
        if (stateInitial[i][0] != stateFinal[i][0] || stateInitial[i][1] != stateFinal[i][1])
            return false;
    }
    return true;
}

// Méthodes pour la résolution du jeu
int resolver::resolve() {

   Node res = parcourLargeur(initialState);
   afficheSolution(res);


    return 0;
}

Node resolver::parcourLargeur(int **initialState) {
    // Declaration
    // Si le déplacement a réussi
    string currentHash = hashState(initialState);
    int index = 0;
    childrenSet.insert(currentHash); // init state
    Node root(0,initialState);

    addChildrenInQueue(initialState,&index); // init children

    int** tmpState;
    int cmt = 0;
    while (!children.empty()){

        tmpState = children.front(); // premier élément de la queue

       currentHash = hashState(tmpState); // calcul du hash
        if (!hashAlreadyIn(currentHash)){ // test si le hash est déjà dans le set
            addChildrenInQueue(tmpState,&index);
            childrenSet.insert(currentHash);
        }
        if (isWinningState(tmpState)){
            cout << cmt << " parcours" << endl;
            return old[index];

        }
        children.pop(); // suppression de la tête de file
        cmt++;
        index++;
        destructState(tmpState); // plus de fuite mémoire

    }
    cout << cmt << " parcours finished" << endl;


    return root;
}

void resolver::addChildrenInQueue(int** state,int*index) {

    bool movedUp = false;
    bool movedDown = false;
    bool movedRight = false;
    bool movedLeft = false;

    // Etat actuel clonné
    int **mUp;
    int **mDown;
    int **mRight;
    int **mLeft;

    // Ajout des enfants de l'état actuel dans le SET
    // les enfants sont ajouté si le mouvement à abouti
    for (int i = 1; i < stateSize; ++i) {
        // clone l'état courrant
        mUp = cloneState(state);
        mDown = cloneState(state);
        mRight = cloneState(state);
        mLeft = cloneState(state);
        movedUp = moveUp(mUp,i);
        movedDown = moveDown(mDown,i);
        movedRight = moveRight(mRight, i);
        movedLeft = moveLeft(mLeft, i);
        if (movedUp){
            children.push(mUp);
           // int** tmpCopy = cloneState(mUp);
            Node st1bis(*index,mUp);
            struct move move1bis;
            move1bis.idCar = i;
            move1bis.d = UP;
            st1bis.m = move1bis;
            old.push_back(st1bis);

        }
        if (movedDown){

            children.push(mDown);
          //  int** tmpCopy = cloneState(mUp);
            Node st2bis(*index,mDown);
            struct move move2bis;
            move2bis.idCar = i;
            move2bis.d = DOWN;
            st2bis.m = move2bis;
            old.push_back(st2bis);

        }
        if (movedRight){

            children.push(mRight);
           // int** tmpCopy = cloneState(mUp);
            Node st3bis(*index,mRight);
            struct move move3bis;
            move3bis.idCar = i;
            move3bis.d = RIGHT;
            st3bis.m = move3bis;
            old.push_back(st3bis);
        }
        if (movedLeft){
            children.push(mLeft);
           // int** tmpCopy = cloneState(mUp);
            Node st4bis(*index,mLeft);
            struct move move4bis;
            move4bis.idCar = i;
            move4bis.d = LEFT;
            st4bis.m = move4bis;
            old.push_back(st4bis);
        }
    }

}

string resolver::hashState(int **state) {
    // le hash d'un état est la concaténation de ses lignes
    string toReturn = "";
    bool first = true;
    for (int i = 0; i < stateSize; ++i) {
        if (first){
            first = false;

            toReturn += to_string(state[0][0]);
            toReturn += to_string(state[0][1]);

        }else{
            toReturn += to_string(state[i][0]);
            toReturn += to_string(state[i][1]);
            toReturn += to_string(state[i][2]);
            toReturn += to_string(state[i][3]);

        }
    }
    return toReturn;
}

bool resolver::hashAlreadyIn(string hash) {
    return childrenSet.find(hash) != childrenSet.end();
}



bool resolver::isWinningState(int **state) {
    // on regarde si la voiture se trouve devant la sortie
    if(state[1][3] == 0){
        return (state[0][0] == (state[1][0]+state[1][2]-1) && state[0][1] == state[1][1]) || (state[0][0] == state[1][0] && state[0][1] == state[1][1]);
    } else{
        return (state[0][0] == state[1][0] && state[0][1] == (state[1][1] + state[1][2] -1)) || (state[0][0] == state[1][0] && state[0][1] == state[1][1] );

    }
}



void resolver::destructState(int **state) {
    for (int i = 0; i < stateSize; ++i) {
        delete [] state[i];
    }
    delete [] state;

}

void resolver::afficheSolution(Node end) {
    int j = end.idParent;
    afficheur->affiche(end.state);
    cout << "Il faut bouger la voiture : " << afficheur->getSymbole(end.m.idCar);
    switch (end.m.d){
        case 0: cout << " vers le HAUT " << endl;
            break;
        case 1: cout << " vers le BAS " << endl;
            break;
        case 2: cout << " vers la DROITE " << endl;
            break;
        case 3: cout << " vers la GAUCHE " << endl;
            break;
    }
    int h =0;
    while (j > 0){
        Node tmp = old[j];
        afficheur->affiche(tmp.state);
        j = tmp.idParent;
        h++;
        cout << "Il faut bouger la voiture : " << afficheur->getSymbole(tmp.m.idCar);
        switch (tmp.m.d){
            case 0: cout << " vers le HAUT " << endl;
                break;
            case 1: cout << " vers le BAS " << endl;
                break;
            case 2: cout << " vers la DROITE " << endl;
                break;
            case 3: cout << " vers la GAUCHE " << endl;
                break;
        }
        cout << "--------------------------____-------------------" << endl;
    }

    afficheur->affiche(initialState);

    cout << "La solition à été trouvé en " << h+2 << " coup(s)" << endl; // plus 2 car on ne compte pas le dernier coup ni le premier (état initial) mais en comptant a la main c'est juste

}

//***********************************UNUSED***************************************************************



bool resolver::moveEqual(struct move move1, struct move move2) {
    return move1.idCar == move2.idCar && move1.d == move2.d;
}


bool resolver::checkIfBlocked(vector<struct move> moves) {
    if (moves.size() < 6) // Pas assez de moves pour determiner
    {
        return false;
    }
    struct move move1;
    struct move move2;
    struct move move3;

    struct move move4;
    struct move move5;
    struct move move6;


    move1 = moves[0];
    move2 = moves[1];
    move3 = moves[2];

    for (int i = 3; i <moves.size()-2 ;i++ ) {
        move4 = moves[i];
        move5 = moves[i+1];
        move6 = moves[i+2];

        if (moveEqual(move1,move4) && moveEqual(move2,move5) && moveEqual(move3,move6))
            return true;
        move1 = move4;
        move2 = move5;
        move3 = move6;
    }



    return false;
}

vector<struct move> resolver::parcourProfondeur(int **currentState, vector<struct move> moves,struct move lastMove,struct move lastMove2,struct move lastMove3,struct move lastMove4,int cmt) {
    int less = 999999999; // plus petite taille
    vector<struct move> goodPath; // plus court chemin
    if (isWinningState(currentState)) // Si l'état actuel est gagant, on le return
        return moves;
    if (cmt >= 16){
        //cout << "stopped by cmt " << cmt << endl;
        return {};

    }else{
        //  if (cmt < 10)
        //cout << "NOT stopped " << cmt << endl;
    }

    // Declaration
    // Si le déplacement a réussi
    bool movedUp = false;
    bool movedDown = false;
    bool movedRight = false;
    bool movedLeft = false;

    // Historique des déplacement
    vector<struct move> movesUp;
    vector<struct move> movesDown;
    vector<struct move> movesRight;
    vector<struct move> movesLeft;

    // Etat actuel clonné
    int **mUp;
    int **mDown;
    int **mRight;
    int **mLeft;

    // Denier mouvement fait (pour eviter retour en arrière)
    struct move lastUp;
    struct move lastDown;
    struct move lastRight;
    struct move lastLeft;

    lastUp.idCar = -1;
    lastUp.d = NONE;
    lastDown.idCar = -1;
    lastDown.d = NONE;
    lastRight.idCar = -1;
    lastRight.d = NONE;
    lastLeft.idCar = -1;
    lastLeft.d = NONE;


    for (int i = 1; i < stateSize; ++i) {
        // On clone l'état actuel pour chaque mouvement
        mUp = cloneState(currentState);
        mDown = cloneState(currentState);
        mRight = cloneState(currentState);
        mLeft = cloneState(currentState);
        // On applique tout les déplacements pour chaque voiture et on stocke si on à réussi a se déplacer ou non
        if ((lastMove.idCar == i && lastMove.d == DOWN) || (lastMove4.idCar == i && lastMove4.d == UP)){
            movedUp = false;
        }else{
            movedUp = moveUp(mUp, i);
        }
        if ((lastMove.idCar == i && lastMove.d == UP) || (lastMove4.idCar == i && lastMove4.d == DOWN)){

            movedDown = false;
        }
        else{
            movedDown = moveDown(mDown, i);
        }
        if ((lastMove.idCar == i && lastMove.d == LEFT) || (lastMove4.idCar == i && lastMove4.d == LEFT)){

            movedRight = false;
        }else{
            movedRight = moveRight(mRight, i);
        }
        if ((lastMove.idCar == i && lastMove.d == RIGHT) || (lastMove4.idCar == i && lastMove4.d == RIGHT)){

            movedLeft = false;
        }else{
            movedLeft = moveLeft(mLeft, i);
        }

        // Si le mouvement à reussi
        if (movedUp) {
            // On appele parcourProfondeur avec le nouvel état
            lastUp.idCar = i;
            lastUp.d = UP;
            movesUp = parcourProfondeur(mUp, moves,lastUp,lastMove,lastMove2,lastMove3,cmt+1);
            // Si le retour de l'appel recursif n'est pas vide (cas ou l'état du jeu est bloqué)
            // On test si la taille de l'historique de retour est plus petite que la taille mini acutel
            // Si c'est le cas, l'historique devient le plus court chemin actuel
            if ( !movesUp.empty() && movesUp.size() < less ) {
                less = movesUp.size();
                goodPath = movesUp;
            }else{
                destructState(mUp);
            }
        }else{
            destructState(mUp);
        }
        if (movedDown) {
            lastDown.idCar = i;
            lastDown.d = DOWN;
            movesDown = parcourProfondeur(mDown, moves,lastDown,lastMove,lastMove2,lastMove3,cmt+1);
            if ( !movesDown.empty() && movesDown.size() < less) {
                less = movesDown.size();
                goodPath = movesDown;
            }else{
                destructState(mDown);
            }
        }else{
            destructState(mDown);
        }
        if (movedRight) {
            lastRight.idCar = i;
            lastRight.d = RIGHT;
            movesRight = parcourProfondeur(mRight, moves,lastRight,lastMove,lastMove2,lastMove3,cmt+1);
            if ( !movesRight.empty() && movesRight.size() < less ) {
                less = movesRight.size();
                goodPath = movesRight;
            }else{
                destructState(mRight);
            }
        }else{
            destructState(mRight);
        }
        if (movedLeft) {
            lastLeft.idCar = i;
            lastLeft.d = LEFT;
            movesLeft = parcourProfondeur(mLeft, moves,lastLeft,lastMove,lastMove2,lastMove3,cmt+1);
            if ( !movesLeft.empty() && movesLeft.size() < less) {
                less = movesLeft.size();
                goodPath = movesLeft;
            }else{
                destructState(mLeft);
            }
        }else{
            destructState(mLeft);
        }




    }
    if (less == 999999999) // si aucune solution trouvée on return une liste vide
        return {};

    // On  ajoute l'état actuel a l'historique et on le renvoi (cf : le jeu n'est pas bloqué et on a trouvé une solution depuis cet état)
    goodPath.push_back(lastMove);
    return moves;
}


void resolver::changeCurrentState(int **newState) {
    initialState = newState;
}

int **resolver::applyMoveTo(int **state, struct move move1) {
    int** toReturn = cloneState(state);
    switch (move1.d){
        case UP:
            moveUp(toReturn,move1.idCar);
            break;
        case DOWN:
            moveDown(toReturn,move1.idCar);
            break;
        case RIGHT:
            moveRight(toReturn,move1.idCar);
            break;
        case LEFT:
            moveLeft(toReturn,move1.idCar);
            break;
        case NONE:
            break;
    }
    return toReturn;
}

void resolver::changeSize(int s) {
    stateSize = s;

}




