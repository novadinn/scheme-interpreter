#include "lval.h"

#include "math.h"

#include <cstring>
#include <stdarg.h>

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

lval* lval_var(std::string vname) {
    lval* v = new lval();
    v->type = ltype::VAR;
    v->vname = vname;

    return v;
}

lval* lval_sym(std::string sym) {
    lval* v = new lval();
    v->type = ltype::SYM;
    v->sym = sym;

    return v;
}

lval* lval_bool(bool b) {
    lval* v = new lval();
    v->type = ltype::BOOL;
    v->b = b;

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

bool lval_equal_e(lval* l, lval* r) {
    if(l->type != r->type) return false;
    switch(l->type) {
    case ltype::QEXP: {
	llist llst = l->lst;
	llist rlst = r->lst;
	if(llst.size() != rlst.size()) return false;
	
	for(int i = 0; i < llst.size(); ++i) {
	    bool r = lval_equal_e(llst[i], rlst[i]);
	    if(!r) return false;
	}

	return true;
    } break;
    case ltype::FUN: {
	if(l->body && l->args && l->env)
	    return l->body == r->body && l->args == r->args && l->env == r->env;
	else
	    return l->fun == r->fun;
    } break;
    case ltype::NUM: {
	return l->num == r->num;
    } break;
    case ltype::STR: {
	return l->str == r->str;
    } break;
    case ltype::SYM: {
	return l->sym == r->sym;
    } break;
    case ltype::BOOL: {
	return l->b == r->b;
    } break;
    case ltype::ERR: {
	return l->err == r->err;
    } break;
    }

    return false;
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
    case ltype::VAR: {} break;
    case ltype::SYM: {} break;
    case ltype::BOOL: {} break;
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
    case ltype::VAR: { return "Variable"; } break;
    case ltype::SYM: { return "Symbol"; } break;
    case ltype::BOOL: { return "Boolean"; } break;
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
	printf("(");
	for(int i = 0; i < val->lst.size(); ++i) {
	    print_lval_rec(val->lst[i]);
	    if(i != val->lst.size()-1)
		printf(" ");
	}
	printf(")");
    } break;
    case ltype::QEXP: {
	printf("'(");
	for(int i = 0; i < val->lst.size(); ++i) {
	    print_lval_rec(val->lst[i]);
	    if(i != val->lst.size()-1)
		printf(" ");
	}
	printf(")");
    } break;
    case ltype::FUN: {
	printf("(lambda");
	if(val->args && val->body) {
	    print_lval_rec(val->args);
	    print_lval_rec(val->body);
	}
	printf(")");
    } break;
    case ltype::NUM: {
	if(int_p(val->num)) printf("%d", (int)val->num);
	else printf("%lf", val->num);
    } break;
    case ltype::STR: {
	printf("\"%s\"", val->str.c_str());
    } break;
    case ltype::VAR: {
	printf("%s", val->vname.c_str());
    } break;
    case ltype::SYM: {
	printf("'%s", val->sym.c_str());
    } break;
    case ltype::BOOL: {
	printf("%s", val->b ? "true" : "false");
    } break;
    case ltype::ERR: {
	printf("%s", val->err);
    } break;
    }    
}

void print_lval_t(lval* val) {
    print_lval_t_rec(val);
    printf("\n");
}

void print_lval_t_rec(lval* val) {
    switch(val->type) {
    case ltype::SEXP: {
	printf("SEXP(");
	for(int i = 0; i < val->lst.size(); ++i) {
	    print_lval_t_rec(val->lst[i]);
	}
	printf(")");
    } break;
    case ltype::QEXP: {
	printf("QEXP(");
	for(int i = 0; i < val->lst.size(); ++i) {
	    print_lval_t_rec(val->lst[i]);
	}
	printf(")");
    } break;
    case ltype::FUN: {
	printf("FUN(");
	if(val->args && val->body) {
	    printf("ARGS("); print_lval_t_rec(val->args); printf(")");
	    printf("BODY("); print_lval_t_rec(val->body); printf(")");
	}
	printf(")");
    } break;
    case ltype::NUM: {
	if(int_p(val->num)) printf("NUM(%d)", (int)val->num);
	else printf("NUM(%lf)", val->num);
    } break;
    case ltype::STR: {
	printf("STR(%s)", val->str.c_str());
    } break;
    case ltype::VAR: {
	printf("VAR(%s)", val->vname.c_str());
    } break;
    case ltype::SYM: {
	printf("SYM(%s)", val->sym.c_str());
    } break;
    case ltype::BOOL: {
	printf("BOOL(%s)", val->b ? "true" : "false");
    } break;
    case ltype::ERR: {
	printf("ERR(%s)", val->err);
    } break;
    }
}
