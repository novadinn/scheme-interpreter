#ifndef LVAL_H
#define LVAL_H

#include <vector>

enum builtin_type {
    SEXP,
    FN,
    NUMBER
};
struct lval;
typedef lval*(*lfn)(lval*);

struct lval {
    builtin_type type;
    
    std::vector<lval*> list;
    lfn fn;
    long num;
};

lval* eval(lval* exp);

lval* new_lval_sexp(std::vector<lval*> list = std::vector<lval*>());
lval* new_lval_fn(lfn fn = nullptr);
lval* new_lval_number(long n = 0);

lval* builtin_add(lval* op);
lval* builtin_sub(lval* op);
lval* builtin_div(lval* op);
lval* builtin_mul(lval* op);

void print_lval(lval* val);
void print_lval_rec(lval* val);

#endif // LVAL_H
