//
// Created by jbdargier on 08/04/19.
//

#ifndef RUSH_GENERATEUR_H
#define RUSH_GENERATEUR_H


#include <vector>
using namespace std;

class Generateur{
private:
    /**
    * Objet Afficheur qui s'occupe d'afficher à l'écran les états
    */
    Afficheur *afficheur;

public:

    /**
     * Constructeur du generateur
     */
    Generateur();

    /**
     * Destructeur par défaut
     */
    ~Generateur();

    /**
     * Fonction qui permet de générer un terrain de façon aléatoire avec NbVoiture dessus
     * @param NbVoiture
     * @return
     */
    int** GenereTerrain(int NbVoiture);

    /**
     * Fonction qui permet de créer un fichier contenant le terrain
     * @param terrain
     * @param nbVoiture
     */
    void creerFichier(int** terrain, int nbVoiture);
};

#endif //RUSH_GENERATEUR_H
