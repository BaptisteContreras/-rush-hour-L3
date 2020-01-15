//
// Created by baptiste on 27/02/19.
//

#include <header/Afficheur.h>
#include "iostream"
#include "header/resolver.h"
#include "structs/Node.h"
using namespace std;


// Constructeur & destructeur
Afficheur::Afficheur(int hauteur, int largeur) : hauteur(hauteur), largeur(largeur) {
    carac = new char[16]{'A','B','C','D','E','F','G','H','I','J','L','M','N','O','P'};
}

Afficheur::~Afficheur() {
    delete [] carac;
}

// Méthdes public

void Afficheur::affiche(int **state) {
    string** stateConverted = stateToAffichage(state);
    display(stateConverted);
    for (int i = 0; i < largeur + 2; ++i) {
        delete [] stateConverted[i];
    }
    delete [] stateConverted;


}

// Méthde(s) privé

string **Afficheur::stateToAffichage(int **state) {
    int stateSize = sizeS;
    string** tab = new string*[hauteur+2]; // Rows
    for (int i = 0; i < hauteur+2; i++)
    {
        tab[i] = new string[largeur+2]; // Columns
    }

    initDisplayTab(tab); // initialisation de la grille avec les murs
    readState(state,stateSize,tab); // remplissage de la grille avec les éléments

    return tab;
}

void Afficheur::display(string **tab) {
    for (int i = 0; i < hauteur + 2; ++i) {
        for (int j = 0; j < largeur + 2; ++j) {
            if (i == 0 || i ==hauteur+1){
                if (j == largeur+1){

                    cout << tab[i][j] ;
                }else{

                    cout << tab[i][j] << "-";
                }
            }else{
                cout << tab[i][j] << " ";

            }
        }
        cout << endl;
    }
}

void Afficheur::initDisplayTab(string **tab) {

    for (int i = 0; i < hauteur+2; ++i) {
        for (int j = 0; j < largeur + 2; ++j) {
            if (i==0 || i == hauteur+1){

                tab[i][j] = "-";
            }else if (j == 0 || j == largeur+1){

                tab[i][j] = "|";
            }else{
                tab[i][j] = " ";

            }
        }
    }
}

void Afficheur::readState(int **state,int size, string **tab) {
    bool firstLine = true;

    for (int i = 0; i < size; ++i) {
        if (firstLine){
            firstLine = false;
            int tmpy = state[0][0]+1;
            int tmpx= state[0][1]+1;
            if (tmpx== 6)
                tmpx++;
            else if (tmpx == 1)
                tmpx--;
            if (tmpy == 6)
                tmpy++;
            else if(tmpy == 1)
                tmpy--;
            tab[tmpy][tmpx] = "<>";
        }else{
            if(state[i][3] == 0){
                placeVoitureVertical(i,state[i],tab);
            } else{
                placeVoitureHorizontal(i,state[i],tab);

            }
        }
    }
}

void Afficheur::placeVoitureVertical(int id,int *car, string **tab) {
    for (int i = 0; i < car[2] ; ++i) {
        tab[car[0]+i+1][car[1]+1] = carac[id];
    }
}

void Afficheur::placeVoitureHorizontal(int id,int *car, string **tab) {
    for (int i = 0; i < car[2] ; ++i) {
        tab[car[0]+1][car[1]+1+i] = carac[id];
    }
}

char Afficheur::getSymbole(int index) {
    return carac[index];
}




