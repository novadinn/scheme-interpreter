#ifndef LVAL_H
#define LVAL_H

#include "lenv.h"

enum ltype {
    SEXP,
    QEXP,
    FUN,
    NUM,
    STR,
    SYM,
    BOOL,
    ERR
};
struct lval;
typedef lval*(*lfun)(lval*, lenv*);
typedef std::vector<lval*> llist;

struct lval {
    ltype type;

    llist lst;
    
    lfun fun;
    lenv* env;
    lval* args;
    lval* body;
    
    double num;
    
    std::string str;
    
    std::string sym;

    bool b;
    
    char* err;
};

lval* lval_sexp(llist lst = llist());
lval* lval_qexp(llist lst = llist());
lval* lval_fun(lfun fun = nullptr, lenv* e = nullptr, lval* args = nullptr, lval* body = nullptr);
lval* lval_num(double n = 0.0);
lval* lval_str(std::string str = "");
lval* lval_sym(std::string sym = "");
lval* lval_bool(bool b = false);
lval* lval_err(std::string err = "", ...);
void lval_del(lval* v);

std::string ltype_to_str(ltype type);

void print_lval(lval* val);
void print_lval_rec(lval* val);

#endif // LVAL_H
