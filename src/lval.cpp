#include "lval.h"

#include <iostream>
#include <stdarg.h>

// TODO: use local env
lval* eval(lval* exp, lenv* env) {
    switch(exp->type) {
    case ltype::SEXP: {
	std::vector<lval*> args;
	lval* op = exp->list[0];
	
	for(int i = 1; i < exp->list.size(); ++i) {
	    args.push_back(eval(exp->list[i], env));
	}
	op->list = args;

	return eval(op, env);
    } break;
    case ltype::FN: {
	return exp->fn(exp);
    } break;
    case ltype::NUM: {
	return exp;
    } break;
    case ltype::SYM: {
	return eval(search_lenv(env, exp->sym), env);
    } break;
    case ltype::ERR: {
	printf("%s\n", exp->err);
	return exp;
    } break;
    }

    return nullptr;
}

lval* new_lval_sexp(std::vector<lval*> list) {
    lval* val = new lval();
    val->type = ltype::SEXP;
    val->list = list;
    
    return val;
}

lval* new_lval_fn(lfn fn) {
    lval* val = new lval();
    val->type = ltype::FN;
    val->fn = fn;
    
    return val;
}

lval* new_lval_num(long n) {
    lval* val = new lval();
    val->type = ltype::NUM;
    val->num = n;
    
    return val;
}

lval* new_lval_sym(std::string sym) {
    lval* val = new lval();
    val->type = ltype::SYM;
    val->sym = sym;
    
    return val;
}

lval* new_lval_err(std::string msg, ...) {
    lval* v = new lval();
    v->type = ltype::ERR;
    va_list va;
    va_start(va, msg);
    v->err = (char*)malloc(512);
    vsnprintf(v->err, 511, msg.c_str(), va);
    v->err = (char*)realloc(v->err, strlen(v->err)+1);
    va_end(va);
    return v;
}

void delete_lval(lval* val) {
    switch(val->type) {
    case ltype::SEXP: {
	for(int i = 0; i < val->list.size(); ++i) {
	    delete_lval(val->list[i]);
	}
    } break;
    case ltype::FN: {} break;
    case ltype::NUM: {} break;
    case ltype::ERR: {
	free(val->err);
    } break;
    }

    delete val;
}

lval* builtin_add(lval* op) {
    long res = 0;
    
    for(int i = 0; i < op->list.size(); ++i) {
	lval* val = op->list[i];
	LTYPE_ASSERT("+", op, i, ltype::NUM);
	res += val->num;
    }

    return new_lval_num(res);
}

lval* builtin_sub(lval* op) {
    long res = op->list[0]->num;
    if(op->list.size() == 1)
	return new_lval_num(-res);
    
    for(int i = 1; i < op->list.size(); ++i) {
	lval* val = op->list[i];
	LTYPE_ASSERT("-", op, i, ltype::NUM);
	res -= val->num;
    }

    return new_lval_num(res);
}

lval* builtin_div(lval* op) {
    long res = op->list[0]->num;
    
    for(int i = 1; i < op->list.size(); ++i) {
	lval* val = op->list[i];
	LTYPE_ASSERT("/", op, i, ltype::NUM);
	res /= val->num;
    }

    return new_lval_num(res);
}

lval* builtin_mul(lval* op) {
    long res = op->list[0]->num;
    
    for(int i = 1; i < op->list.size(); ++i) {
	lval* val = op->list[i];
	LTYPE_ASSERT("*", op, i, ltype::NUM);
	res *= val->num;
    }

    return new_lval_num(res);
}

std::string ltype_to_str(ltype type) {
    switch(type) {
    case ltype::SEXP: {
	return "S-Expression";
    } break;
    case ltype::FN: {
	return "Function";
    } break;
    case ltype::NUM: {
	return "Number";
    } break;
    case ltype::SYM: {
	return "Symbol";
    } break;
    case ltype::ERR: {
	return "Error";
    } break;
    }

    return "Unknown type";
}

void print_lval(lval* val) {
    print_lval_rec(val);
    printf("\n");
}

void print_lval_rec(lval* val) {
    switch(val->type) {
    case ltype::SEXP: {
	std::cout << "SEXP(";
	for(int i = 0; i < val->list.size(); ++i) {
	    print_lval_rec(val->list[i]);
	}
	std::cout << ")";
    } break;
    case ltype::FN: {
	std::cout << "FN()";
    } break;
    case ltype::NUM: {
	std::cout << "NUM(" << val->num << ")";
    } break;
    case ltype::SYM: {
	std::cout << "SYM(" << val->sym << ")";
    } break;
    case ltype::ERR: {
	std::cout << "ERR(" << val->err << ")";
    } break;
    }
}
