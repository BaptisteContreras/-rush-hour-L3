//
// Created by jbdargier on 08/04/19.
//

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <header/Afficheur.h>
#include <header/resolver.h>
#include "header/Generateur.h"


Generateur::Generateur() {
}

Generateur::~Generateur() {}

void Generateur::creerFichier (int** terrain, int nbVoiture){
    //on crée un stream d'écriture avec le nom du fichier voulu
    std::ofstream outFile("../data/terrain.txt");
    outFile << terrain[0][0] << " " << terrain[0][1] << endl;
    for(int i=1; i<=nbVoiture; ++i){
        for(int j=0; j< 4; ++j){
            outFile << terrain[i][j] << " ";
        }
        outFile << endl;
    }
    outFile.close();
}

int** Generateur::GenereTerrain(int nbVoiture)
{
    afficheur = new Afficheur(6, 6);
    resolver rushResolver(6, 6);

    srand(time(nullptr));
    int** tabVoiture = new int*[nbVoiture];

    int tailleTerrain = 5;
    bool voiturePeutEtrePlace;

    int* sortie = new int[2];

    //Pour avoir une sortie aléatoire (a débeuguer)

    /*int largeur = rand() % tailleTerrain + 1;
    if(largeur == 1 or largeur == tailleTerrain){
        sortie[0] = largeur;
        sortie[1] = rand() % tailleTerrain;
    }else {
        sortie[0] = rand() % tailleTerrain;
        if (rand() % 2 == 0) {
            sortie[1] = 1;
        } else {
            sortie[1] = 5;
        }
    }*/

    sortie[0] = 2;
    sortie[1] = 5;

    tabVoiture[0] = sortie;


    int* voitureASortir = new int[4];
    voitureASortir[0] = sortie[0];
    //voitureASortir[2] = rand() % 2 + 2;
    voitureASortir[2] = 2;
    if(voitureASortir[2] == 2){
        voitureASortir[1] = sortie[1]-1;
    }else{
        voitureASortir[1] = sortie[1]-2;
    }
    if(sortie[1] == 0 or sortie[1] == 5){
        voitureASortir[3] = 1;
    }else{
        voitureASortir[3] = 0;
    }
    tabVoiture[1] = voitureASortir;

    //boucle permettant de positionner les voitures sur le terrain en fonction de celles déjà positionnées
    //afin d'avoir un état final
    for(int i=2; i<nbVoiture+1; ++i) {
        int posX, posY, tailleVoiture, orientation;
        voiturePeutEtrePlace = false;
        int* voiture = new int[4];

        while(!voiturePeutEtrePlace){
            bool rentre = true;
            tailleVoiture = rand() % 2 + 2;
            orientation = rand() % 2;

            if(orientation == 0) {
                do{
                    posX = rand() % tailleTerrain;
                }while(posX+tailleVoiture > 6);
                posY = rand() % tailleTerrain;
            }else{
                do{
                    posY = rand() % tailleTerrain;
                }while(posY+tailleVoiture > 6);
                posX = rand() % tailleTerrain;
                //permet d'éviter qu'il y ai de voiture dans le meme axe que celle à sortir
                /*if(posX == 2){
                    rentre = false;
                }*/
            }

            //en fonction de l'orientation on vérifie si aucune voiture déjà placée se trouve sur celle qu'on vient de créer
            if(orientation==0){
                for(int j=posX; j<posX+tailleVoiture; ++j){
                    //pour éviter qu'il y ai des voitures sur la ligne de la sortie
                    /*if(j==2){
                        rentre = false;
                    }*/
                    for(int k=1; k<i; ++k){
                        if(tabVoiture[k][3]==0){
                            if(posY==tabVoiture[k][1]){
                                for(int l=tabVoiture[k][0]; l<tabVoiture[k][0]+tabVoiture[k][2]; ++l){
                                    if(j==l){
                                        rentre = false;
                                    }
                                }
                            }
                        }else{
                            for(int l=tabVoiture[k][1]; l<tabVoiture[k][1]+tabVoiture[k][2]; ++l){
                                if(j==tabVoiture[k][0] && l==posY){
                                    rentre = false;
                                }
                            }
                        }
                    }
                }
            }else{
                for(int j=posY; j<posY+tailleVoiture; ++j){
                    for(int k=1; k<i; ++k){
                        if(tabVoiture[k][3]==0){
                            for(int l=tabVoiture[k][0]; l<tabVoiture[k][0]+tabVoiture[k][2]; ++l){
                                if(j==tabVoiture[k][1] && l==posX){
                                    rentre = false;
                                }
                            }
                        }else{
                            if(posX==tabVoiture[k][0]){
                                for(int l=tabVoiture[k][1]; l<tabVoiture[k][1]+tabVoiture[k][2]; ++l){
                                    if(j==l){
                                        rentre = false;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if(rentre){
                voiturePeutEtrePlace = true;
            }
        }

        if(voiturePeutEtrePlace){
            voiture[0] = posX;
            voiture[1] = posY;
            voiture[2] = tailleVoiture;
            voiture[3] = orientation;
            tabVoiture[i] = voiture;
        }
    }

    rushResolver.changeSize(nbVoiture);
    afficheur->sizeS = nbVoiture;

    //boucle permettant de trouver un état initial de l'état final générer auparavant
    int i=0;
    while(i<500){
        int idVoiture = (rand()%nbVoiture) + 1;
        rushResolver.moveLeft(tabVoiture, 1);
        rushResolver.moveLeft(tabVoiture, 1);
        rushResolver.moveLeft(tabVoiture, 1);
        rushResolver.moveLeft(tabVoiture, 1);
        int mouvement = (rand()%4)+1;
        switch(mouvement) {
            case 1:
                rushResolver.moveLeft(tabVoiture, idVoiture);
                break;
            case 2:
                rushResolver.moveRight(tabVoiture, idVoiture);
                break;
            case 3:
                rushResolver.moveUp(tabVoiture, idVoiture);
                break;
            case 4:
                rushResolver.moveDown(tabVoiture, idVoiture);
                break;
        }
        ++i;

    }

    //une fois l'état initial créé on le stock dans un fichier
    creerFichier(tabVoiture, nbVoiture);
    //on affiche le résultat
    cout << "Terrain final généré" << endl;
    afficheur->affiche(tabVoiture);
    return tabVoiture;
}
