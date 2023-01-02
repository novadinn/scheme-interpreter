#ifndef LVAL_H
#define LVAL_H

#include "lenv.h"
#include "log.h"

#include <vector>

enum ltype {
    SEXP,
    QEXP,
    FN,
    NUM,
    SYM,
    ERR
};
struct lval;
typedef lval*(*lfn)(lval*, lenv* env);

// TODO: add local env
struct lval {
    ltype type;
    
    std::vector<lval*> list;
    lfn fn;
    long num;
    std::string sym;
    char* err;
};

lval* new_lval_sexp(std::vector<lval*> list = std::vector<lval*>());
lval* new_lval_qexp(std::vector<lval*> list = std::vector<lval*>());
lval* new_lval_fn(lfn fn = nullptr);
lval* new_lval_num(long n = 0);
lval* new_lval_sym(std::string sym);
lval* new_lval_err(std::string msg, ...);
void delete_lval(lval* val);

std::string ltype_to_str(ltype type);

void print_lval(lval* val);
void print_lval_rec(lval* val);

#endif // LVAL_H
