#include <iostream>
#include "header/resolver.h"
#include "header/tester.h"
#include <random>
#include "header/Generateur.h"


int main(int argc, const char **argv) {

    cout << "nombre d'argument : " << argc << endl;


    bool tests = false;
    bool verbTest = true;
    bool generation = false;

    resolver rushResolver(6, 6);

    if (argc > 1){
        if (argv[1] == "help"){
            cout << "utilisation : \n executable |path_file] [test] [verb] [generation] \n " << endl;
            return 0;
        }
        if (argc != 5){
            cout << "utilisation : \n executable |path_file] [test] [verb] [generation] \n Il faut spécifier aucun ou tout les arguments" << endl;
            return 0;
        }
        rushResolver.init(argv[1]);
        if (!strcmp(argv[2],"true"))
            tests = true;
        else
            tests = false;
        if (!strcmp(argv[3],"true"))
            verbTest = true;
        else
            verbTest = false;
        if (!strcmp(argv[4],"true"))
            generation = true;
        else
            generation = false;



    }






    if (tests){
        tester test(&rushResolver);

        if (test.test_allMove(verbTest)){
            cout << "all test passed with success ! " << endl;
        }else{
            cout << "all test passed but error detected ! " << endl;

        }
    }else{
        rushResolver.resolve();
        if (generation){
            Generateur g;
            g.GenereTerrain(11);

        }

    }


    return 0;

}

