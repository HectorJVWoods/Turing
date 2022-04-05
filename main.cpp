#include "Types.cpp"


string intGenerator(int x){
    string outputStr = "";
    while(x > 0){
        outputStr = outputStr + "1";
        x = x - 1;
    }
    return outputStr;
}

bool numberFiveTypeAcceptor(int x){
    return x == 5;
}

int fiveOperator(int x, int y){
    if(x == y) {
        return 5;
    }
    return -5;
}


int main() {
    //GeneratorType int8{8};
    GeneratorType numberFive8{8};
    //int8.setGenerator(intGenerator);
    //std::cout << int8.generate(450);
    //numberFive8.setAcceptor(numberFiveTypeAcceptor);
    numberFive8.defineOperator("++", fiveOperator);
    //std::cout << numberFive8.isMember(56);
    //std::cout << numberFive8.isMember(5);

    std::cout << numberFive8.operate("++", 5, 5);
    std::cout << numberFive8.operate("++", 5, 6);
    //std::cout << abc.name;

    return 0;
}