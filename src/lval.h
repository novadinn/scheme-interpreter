#ifndef LVAL_H
#define LVAL_H

#include <vector>

enum builtin_type {
    SEXP,
    FN,
    NUMBER
};
struct lval;
typedef lval*(*lfn)(std::vector<lval*>);

struct lval {
    builtin_type type;
    
    long num;
    lfn fn;

    std::vector<lval*> list;
};

void eval(lval* exp);

void print_lval(lval* val);
static void print_lval_rec(lval* val);

lval* builtin_add(std::vector<lval*> args);

#endif // LVAL_H
