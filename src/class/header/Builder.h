//
// Created by baptiste on 27/02/19.
//

#ifndef RUSH_BUILDER_H
#define RUSH_BUILDER_H

#include <string>
#include <fstream>



using namespace std;


class Builder {

public:
    /**
     * Constructeur par défaut (appèle le deuxieme avec en paramètre le fichier "default.txt"
     */
    Builder();

    /**
     * Constructeur prennant en paramètre un nom de fichier à charger
     * @param filename
     */
    Builder(string filename);

    /**
     * Destructeur par défaut
     */
    ~Builder();

    /**
     * Charge le contenu du fichier "file" dans un tableau 2D
     * @return
     */
    int **load();

    /**
     * taille du fichier chargé
     */
    int size;

private:
    /**
     * Fichier à charger
     */
    string file;

    /**
     * Méthode pour vérifier que les lignes chargé ne contiennent pas d'erreur (dépassement d'index ou mauvais type)
     * @param x
     * @param y
     * @param size
     * @param pos
     * @return
     */
    bool checkInput(int x, int y, int size, int pos);

    /**
     * Compte le nombre de ligne à charger pour initialiser l'état initial
     * @param file
     * @return
     */
    int countLineIn(string file);

};


#endif //RUSH_BUILDER_H
