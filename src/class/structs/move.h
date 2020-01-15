//
// Created by baptiste on 20/03/19.
//

#ifndef RUSH_MOVE_H
#define RUSH_MOVE_H

#include "enum/direction.h"
/**
 * Structure Move
 * Permet de stocker le déplacement appliqué à une voiture
 * Moins lourd qu'une classe
 * Est utilisé dans une FIFO (cf classe resolver)
 */
struct move {
    int idCar;
    direction d;

};


#endif //RUSH_MOVE_H
