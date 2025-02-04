//
// Created by a404m on 9/19/21.
//

#include "Var.h"

using namespace SL;

Var::Var(const String &str) : holder(str.substr(1,str.size()-2)), type(STRING) {/*empty*/}

Var::Var(const Number &num) : holder(num), type(NUMBER) {/*empty*/}

Var::Var(Bool b) : holder(b), type(BOOL) {/*empty*/}

Var::Var(const Var &var) : holder(var.holder), type(var.type) {/*empty*/}

void Var::positive() {
    switch (type) {
        case NUMBER:
            holder = +std::get<Number>(holder);
            break;
        default:
            throw std::runtime_error("Var::positive");
    }
}

void Var::negative() {
    switch (type) {
        case NUMBER:
            holder = -std::get<Number>(holder);
            break;
        default:
            throw std::runtime_error("Var::negative");
    }
}

void Var::multiplication(const Var &var) {
    if(type == var.type && type == NUMBER){
        std::get<Number>(holder) *= std::get<Number>(var.holder);
    }else{
        throw std::runtime_error("Var::");
    }
}

void Var::deviation(const Var &var) {
    if(type == var.type && type == NUMBER){
        std::get<Number>(holder) /= std::get<Number>(var.holder);
    }else{
        throw std::runtime_error("Var::");
    }
}

void Var::plus(const Var &var) {
    if(type == var.type){
        if(type == NUMBER){
            std::get<Number>(holder) += std::get<Number>(var.holder);
        }else if(type == STRING){
            std::get<String>(holder) += std::get<String>(var.holder);
        }else{
            goto THROW;
        }
    }else{
        THROW:throw std::runtime_error("Var::");
    }
}

void Var::minus(const Var &var) {
    if(type == var.type && type == NUMBER){
        std::get<Number>(holder) -= std::get<Number>(var.holder);
    }else{
        throw std::runtime_error("Var::");
    }
}

void Var::equal(const Var &var) {
    *this = Var(type == var.type && holder == var.holder);
}

void Var::notEqual(const Var &var) {
    *this = Var(type != var.type || holder != var.holder);
}

void Var::move(const Var &var) {
    holder = var.holder;
    type = var.type;
}

void Var::print() {
    switch (type) {
        case STRING: {
            auto &str = std::get<String>(holder);
            for(auto it = str.begin(),end = str.end();it < end;++it){
                auto& current = *it;
                if(*it == '\\'){
                    ++it;
                    switch (*it) {
                        case 'n':
                            printf("\n");
                            break;
                        case 't':
                            printf("\t");
                            break;
                        case '\\':
                            printf("\\");
                            break;
                        case '\"':
                            printf("\"");
                            break;
                        case '\'':
                            printf("\'");
                            break;
                        default:
                            throw std::runtime_error(std::string("Unknown char \\") + *it);
                    }
                }else {
                    std::cout << current;
                }
            }
        }
            break;
        case NUMBER:
            std::cout << std::get<Number>(holder);
            break;
        case BOOL:
            std::cout << (std::get<Bool>(holder)? "true" : "false");
            break;
        default:
            throw std::runtime_error("Var::print");
    }
}
