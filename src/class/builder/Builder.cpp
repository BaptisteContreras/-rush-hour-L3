//
// Created by baptiste on 27/02/19.
//

#include <sstream>
#include <iterator>
#include "header/Builder.h"

#include <vector>
#include <header/Builder.h>
#include <iostream>


using namespace std;


// Constructeurs

Builder::Builder(string filename) {
    file = filename;
}

Builder::Builder() {
    Builder("../data/default.txt");
}

// Destructeur

Builder::~Builder() {
}

// Méthodes
int** Builder::load() {
    string line;
    ifstream input(file);
    int nb_lines = countLineIn(file);
    bool firstLine = true;
    int ** initState = new int*[nb_lines]; // Rows
    for (int i = 0; i < nb_lines; i++)
    {
        initState[i] = new int[4]; // Columns
    }



    int cmt = 0;

    for (line; getline(input, line);) {

        istringstream sStream(line);
        vector<std::string> split(istream_iterator<std::string>{sStream}, istream_iterator<std::string>());
        if (firstLine){
            firstLine = false;
            initState[cmt][0] = stoi(split[0]);
            initState[cmt][1] = stoi(split[1]);

        }else{
            initState[cmt][0] = stoi(split[0]);
            initState[cmt][1] = stoi(split[1]);
            initState[cmt][2] = stoi(split[2]);
            initState[cmt][3] = stoi(split[3]);

        }
        cmt++;
    }
    size = nb_lines;
    cout << file << " loaded ! " << endl;
    return initState;
}



bool Builder::checkInput(int x, int y, int size, int pos) {
    return false;
}

int Builder::countLineIn(string file) {
    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile(file);
    while (std::getline(myfile, line))
        ++number_of_lines;
    return number_of_lines;
}







