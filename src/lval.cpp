#include "lval.h"

#include <iostream>

// NOTE: evaluate expression
void eval(lval* exp) {
    switch(exp->type) {
    case builtin_type::SEXP: {
	
    } break;
    case builtin_type::FN: {

    } break;
    case builtin_type::NUMBER: {

    } break;
    }
}

void print_lval(lval* val) {
    print_lval_rec(val);
    printf("\n");
}

static void print_lval_rec(lval* val) {
    switch(val->type) {
    case builtin_type::SEXP: {
	std::cout << "SEXP(";
	for(int i = 0; i < val->list.size(); ++i) {
	    print_lval_rec(val->list[i]);
	}
	std::cout << ")";
    } break;
    case builtin_type::FN: {
	std::cout << "FN()";
    } break;
    case builtin_type::NUMBER: {
	std::cout << "NUMBER(" << val->num << ")";
    } break;
    }
}

lval* builtin_add(std::vector<lval*> args) {
    return nullptr;
}
