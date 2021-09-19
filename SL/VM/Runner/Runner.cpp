//
// Created by a404m on 9/19/21.
//

#include "Runner.h"
#include <sstream>

using namespace SL;

Runner::Runner(const CodeGenerator& code) : varHolder({}) {
    Command command;
    for(const auto& line : code.codeHolder){
        std::istringstream lineStream(line);
        std::string word,word2;
        lineStream >> word;
        command = (Command)stoi(word);
        switch (command) {
            case POSITIVE:
                lineStream >> word;
                varHolder[word].positive();
                break;
            case NEGATIVE:
                lineStream >> word;
                varHolder[word].negative();
                break;
            case MULTIPLICATION:
                lineStream >> word;
                lineStream >> word2;
                if (isName(word2)){
                    varHolder[word].multiplication(varHolder[word2]);
                }else if(isNumber(word2)){
                    varHolder[word].multiplication(Var(std::stold(word2)));
                }else if(isString(word2)){
                    varHolder[word].multiplication(Var(word2));
                }else if(isBool(word2)){
                    varHolder[word].multiplication(Var(word2 == "true"));
                }else{
                    throw std::runtime_error("MULTIPLICATION");
                }
                break;
            case DEVIATION:
                lineStream >> word;
                lineStream >> word2;
                if (isName(word2)){
                    varHolder[word].deviation(varHolder[word2]);
                }else if(isNumber(word2)){
                    varHolder[word].deviation(Var(std::stold(word2)));
                }else if(isString(word2)){
                    varHolder[word].deviation(Var(word2));
                }else if(isBool(word2)){
                    varHolder[word].deviation(Var(word2 == "true"));
                }else{
                    throw std::runtime_error("DEVIATION");
                }
                break;
            case REMAINING:
                lineStream >> word;
                lineStream >> word2;
                if (isName(word2)){
                    varHolder[word].remaining(varHolder[word2]);
                }else if(isNumber(word2)){
                    varHolder[word].remaining(Var(std::stold(word2)));
                }else if(isString(word2)){
                    varHolder[word].remaining(Var(word2));
                }else if(isBool(word2)){
                    varHolder[word].remaining(Var(word2 == "true"));
                }else{
                    throw std::runtime_error("REMAINING");
                }
                break;
            case PLUS:
                lineStream >> word;
                std::getline(lineStream,word2);
                word2.erase(0,1);
                if (isName(word2)){
                    varHolder[word].plus(varHolder[word2]);
                }else if(isNumber(word2)){
                    varHolder[word].plus(Var(std::stold(word2)));
                }else if(isString(word2)){
                    varHolder[word].plus(Var(word2));
                }else if(isBool(word2)){
                    varHolder[word].plus(Var(word2 == "true"));
                }else{
                    throw std::runtime_error("PLUS");
                }
                break;
            case MINUS:
                lineStream >> word;
                lineStream >> word2;
                if (isName(word2)){
                    varHolder[word].minus(varHolder[word2]);
                }else if(isNumber(word2)){
                    varHolder[word].minus(Var(std::stold(word2)));
                }else if(isString(word2)){
                    varHolder[word].minus(Var(word2));
                }else if(isBool(word2)){
                    varHolder[word].minus(Var(word2 == "true"));
                }else{
                    throw std::runtime_error("MINUS");
                }
                break;
            case MOVE:
                lineStream >> word;
                lineStream >> word2;
                if (isName(word2)){
                    varHolder[word].move(varHolder[word2]);
                }else if(isNumber(word2)){
                    varHolder[word].move(Var(std::stold(word2)));
                }else if(isString(word2)){
                    varHolder[word].move(Var(word2));
                }else if(isBool(word2)){
                    varHolder[word].move(Var(word2 == "true"));
                }else{
                    throw std::runtime_error("MOVE");
                }
                break;
            case DELETE:
                lineStream >> word;
                varHolder.erase(word);
                break;
            case PRINT:
                lineStream >> word;
                varHolder[word].print();
                break;
        }
    }
}

bool Runner::isName(const std::string &str) {
    return isIdentifier(str[0]) || str[0] == '$';
}

bool Runner::isNumber(const std::string &str) {
    return SL::isNumber(str[0]);
}

bool Runner::isString(const std::string &str) {
    return isStringMarker(str[0]);
}

bool Runner::isBool(const std::string &str) {
    return str == "true" || str == "false";
}