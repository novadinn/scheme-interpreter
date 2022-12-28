#include "lval.h"

#include <iostream>

// NOTE: evaluate expression
lval* eval(lval* exp) {
    switch(exp->type) {
    case builtin_type::SEXP: {
	std::vector<lval*> args;
	lval* op = exp->list[0];
	
	for(int i = 1; i < exp->list.size(); ++i) {
	    args.push_back(exp->list[i]);
	}

	op->list = args;
	return eval(op);
    } break;
    case builtin_type::FN: {
	return exp->fn(exp);
    } break;
    case builtin_type::NUMBER: {
	return exp;
    } break;
    }

    // TODO: error
    return nullptr;
}

lval* new_lval_sexp(std::vector<lval*> list) {
    lval* val = new lval();
    val->type = builtin_type::SEXP;
    val->list = list;
    
    return val;
}

lval* new_lval_fn(lfn fn) {
    lval* val = new lval();
    val->type = builtin_type::FN;
    val->fn = fn;
    
    return val;
}

lval* new_lval_number(long n) {
    lval* val = new lval();
    val->type = builtin_type::NUMBER;
    val->num = n;
    
    return val;
}

lval* builtin_add(lval* op) {
    long res = 0;
    
    for(int i = 0; i < op->list.size(); ++i) {
	lval* val = eval(op->list[i]);
	// TODO: assert for type
	res += val->num;
    }

    return new_lval_number(res);
}

lval* builtin_sub(lval* op) {
    long res = op->list[0]->num;
    if(op->list.size() == 1)
	return new_lval_number(-res);
    
    for(int i = 1; i < op->list.size(); ++i) {
	lval* val = eval(op->list[i]);
	// TODO: assert for type
	res -= val->num;
    }

    return new_lval_number(res);
}

lval* builtin_div(lval* op) {
    long res = op->list[0]->num;
    
    for(int i = 1; i < op->list.size(); ++i) {
	lval* val = eval(op->list[i]);
	// TODO: assert for type
	res /= val->num;
    }

    return new_lval_number(res);
}

lval* builtin_mul(lval* op) {
    long res = op->list[0]->num;
    
    for(int i = 1; i < op->list.size(); ++i) {
	lval* val = eval(op->list[i]);
	// TODO: assert for type
	res *= val->num;
    }

    return new_lval_number(res);
}

void print_lval(lval* val) {
    print_lval_rec(val);
    printf("\n");
}

void print_lval_rec(lval* val) {
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
