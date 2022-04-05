#include "Types.h"
#include <iostream>
#include <string>
#include <functional>
#include <map>

using namespace std;






class TuringType{
public:
    string name;
    int nextAvailableAssociation = 0;
    int size;
    string* associations; // Empty pointer that refers to a not yet defined array (cool syntax tbh)


    /**
     * Wrapper for functions that take two ints and return an int, i.e any turing machines as far as the compiler
     * is concerned!
     */
    typedef std::function<int(int, int)> typeMachine;

    /**
     * Operators that act on this type. Each operator is defined by a string and refers to a machine that acts on
     * the type.
     */
    std::map<string, typeMachine> operators;


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

    /**
     * Set the name for the type
     * @param n the name.
     */
    void setName(string n){
        name = n;
    }

    /**
     * define an operator of the form "x (...) y" where (...) is the operator
     * @param operatorSymbols symbols of the form (...)
     * @param machine the machine that the symbols correspond to. Machine should take 2 parameters
     */
     //TODO: define how operators work for different types, right now they are type independent!
    void defineOperator(string operatorSymbols, typeMachine machine){
        operators.insert(std::make_pair(operatorSymbols, machine));
    }

    int operate(string oper, int x, int y){
        typeMachine machine = operators[oper];
        return machine(x, y);
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


/**
 * a function that always returns true. Default acceptor function before one is set.
 * @param _ a parameter we don't care about
 * @return always true
 */
inline bool alwaysTrue(int _){
   return true;
}

/**
 * A Type that has three machines that allow you to define what is and isn't a member of the type:
 * acceptor    - takes bits and returns true or false, if the bits are a member then true, otherwise false.
 * generator   - generates strings corresponding to some bits
 * degenerator - reverse of the generator
 */
class GeneratorType : public TuringType{
public:
    GeneratorType(int s) : TuringType(s) {
        setAcceptor(alwaysTrue); // set the acceptor to always true for now since we have not set any rules.
    }
    string (*generator)(int);
    int (*degenerator)(string);
    bool (*acceptor)(int);


    /**
     * Sets the generator for the type, i.e how bits are converted to some string.
     * @param f a function that returns a string and takes a single int (or really, some bits) as input
     */
    void setGenerator(string (*f)(int)){
        generator = f;
    }

    /**
     * Set the acceptor for the type; a function that gives a yes no answer for whether the bits belong to the type
     * @param f acceptor function.
     */
    void setAcceptor(bool(*f)(int)){
        acceptor = f;
    }


    /**
     * Sets the de-generator for the type, i.e how some string is converted back to bits.
     * @param f a function that returns an int (or in reality, some bits) and takes a string
     */
    void setDegenerator(int (*f)(string)){
        degenerator = f;
    }

    /**
     * Generate a string from an int (or in reality some bits)
     * @param bits an integer (or in reality some bits) that you want to generate symbols for
     * @return some symbols generated by the generator
     */
    string generate(int bits){
        return generator(bits);
    }

    /**
     * Get back the int (or really, bits) corresponding to a set of symbols, i.e reverse the generation process.
     * @param symbols Some symbols recognisable to the type
     * @return bits corresponding to the symbols
     */
    int degenerate(string symbols){
        return degenerator(symbols);
    }

    /**
     * Determine whether bits are valid members of the type.
     * @param bits the bits
     * @return yes or no
     */
    bool isMember(int bits){
        return acceptor(bits);
    }
};


