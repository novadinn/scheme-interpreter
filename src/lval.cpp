#include "lval.h"

#include <cstring>
#include <stdarg.h>
#include <math.h>

lval* lval_sexp(llist lst) {
    lval* v = new lval();
    v->type = ltype::SEXP;
    v->lst = lst;

    return v;
}

lval* lval_qexp(llist lst) {
    lval* v = new lval();
    v->type = ltype::QEXP;
    v->lst = lst;

    return v;
}

lval* lval_fun(lfun fun, lenv* e, lval* args, lval* body) {
    lval* v = new lval();
    v->type = ltype::FUN;
    v->fun = fun;
    v->env = e;
    v->args = args;
    v->body = body;

    return v;
}

lval* lval_num(double n) {
    lval* v = new lval();
    v->type = ltype::NUM;
    v->num = n;

    return v;
}

lval* lval_str(std::string str) {
    lval* v = new lval();
    v->type = ltype::STR;
    v->str = str;

    return v;
}

lval* lval_sym(std::string sym) {
    lval* v = new lval();
    v->type = ltype::SYM;
    v->sym = sym;

    return v;
}

lval* lval_err(std::string err, ...) {
    lval* v = new lval();
    v->type = ltype::ERR;
    
    va_list va;
    va_start(va, err);
    v->err = (char*)malloc(512);
    vsnprintf(v->err, 511, err.c_str(), va);
    v->err = (char*)realloc(v->err, strlen(v->err)+1);
    va_end(va);
    
    return v;
}

void lval_del(lval* v) {
    switch(v->type) {
    case ltype::SEXP: {
	for(int i = 0; i < v->lst.size(); ++i) {
	    lval_del(v->lst[i]);
	}
    } break;
    case ltype::QEXP: {
	for(int i = 0; i < v->lst.size(); ++i) {
	    lval_del(v->lst[i]);
	}
    } break;
    case ltype::FUN: {
	if(v->env)
	    lenv_del(v->env);
    } break;
    case ltype::NUM: {} break;
    case ltype::STR: {} break;
    case ltype::SYM: {} break;
    case ltype::ERR: {
	free(v->err);
    } break;
    }

    delete v;
}

std::string ltype_to_str(ltype type) {
    switch(type) {
    case ltype::SEXP: { return "S-Expression"; } break;
    case ltype::QEXP: { return "Q-Expression"; } break;
    case ltype::FUN: { return "Function"; } break;
    case ltype::NUM: { return "Number"; } break;
    case ltype::STR: { return "String"; } break;
    case ltype::SYM: { return "Symbol"; } break;
    case ltype::ERR: { return "Error"; } break;
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
	printf("SEXP(");
	for(int i = 0; i < val->lst.size(); ++i) {
	    print_lval_rec(val->lst[i]);
	}
	printf(")");
    } break;
    case ltype::QEXP: {
	printf("QEXP(");
	for(int i = 0; i < val->lst.size(); ++i) {
	    print_lval_rec(val->lst[i]);
	}
	printf(")");
    } break;
    case ltype::FUN: {
	printf("FUN(");
	if(val->args && val->body) {
	    printf("ARGS("); print_lval_rec(val->args); printf(")");
	    printf("BODY("); print_lval_rec(val->body); printf(")");
	}
	printf(")");
    } break;
    case ltype::NUM: {
	double ab = abs(val->num);
	if(ab == floor(ab)) printf("NUM(%ld)", (long)val->num);
	else printf("NUM(%lf)", val->num);
    } break;
    case ltype::STR: {
	printf("STR(%s)", val->str.c_str());
    } break;
    case ltype::SYM: {
	printf("SYM(%s)", val->sym.c_str());
    } break;
    case ltype::ERR: {
	printf("ERR(%s)", val->err);
    } break;
    }
}
