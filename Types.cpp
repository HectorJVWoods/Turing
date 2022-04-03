#include "Types.h"
#include <iostream>
#include <string>

using namespace std;

class TuringType{
public:
    string name;
    int nextAvailableAssociation = 0;
    int size;
    string* associations; // Empty pointer that refers to a not yet defined array (cool syntax tbh)

    /**
     *
     * @param s The size of the type, in bits (so number of associations is 2^s)
     */
    TuringType(int s){
        size = s;
        associations = new string[2^size];
    }

    /**
     * TuringType Constructor
     * @param s The size of the type, in bits (so number of associations is 2^s)
     * @param n Name for the type; what it is called.
     */
    TuringType(int s, string n){
        size = s;
        name = n;
        associations = new string[2^size];
    }

    void setName(string n){
        name = n;
    }
    /**
     * Add a new string -> binary int association to the type.
     * @param n The association.
     */
    void addAssociation(string n){
        associations[nextAvailableAssociation] = n;
        nextAvailableAssociation = nextAvailableAssociation + 1;
    }

    /**
     * Add a new String -> binary int association to the type.
     * @param n The association.
     * @param location The index of the association. If already used this will replace
     * the association at that index.
     */
    void addAssociation(string n, int i){
        associations[i] = n;
        if(i == nextAvailableAssociation){ //this happens to be the next available, so increment.
            nextAvailableAssociation = nextAvailableAssociation + 1;
        }
    }

    /**
     * Get the integer value that corresponds to the associated string.
     * @param n the integer
     * @return the string
     */
    int toInt(string n){
        for(int i = 0; i < size; i++){
            if(associations[i] == n){
                return i;
            }
        }
        return -1;
    }

    /**
     * Get the string associated to the integer.
     * @param i the integer
     * @return the string
     */
    string getAssociation(int i){
        return associations[i];
    }
};

TuringType typeDefinitionParser(string textToParse){

    return TuringType(8);
}