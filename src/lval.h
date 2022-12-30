#ifndef LVAL_H
#define LVAL_H

#include "lenv.h"

#include <vector>

#define LVAL_ASSERT(arg, cond, fmt, ...)				\
    if (!(cond)) {							\
	lval* err = new_lval_err(fmt, ##__VA_ARGS__);			\
	return err;							\
    }

#define LTYPE_ASSERT(func, arg, index, expect)				\
    LVAL_ASSERT(arg, arg->list[index]->type == expect,		\
		"Function '%s' passed incorrect type for argument %i. Got %s, Expected %s.", \
		func, index, ltype_to_str(arg->list[index]->type).c_str(), \
		ltype_to_str(expect).c_str())

enum ltype {
    SEXP,
    FN,
    NUM,
    SYM,
    ERR
};
struct lval;
typedef lval*(*lfn)(lval*);

// TODO: add local env
struct lval {
    ltype type;
    
    std::vector<lval*> list;
    lfn fn;
    long num;
    std::string sym;
    char* err;
};

lval* eval(lval* exp, lenv* env);

lval* new_lval_sexp(std::vector<lval*> list = std::vector<lval*>());
lval* new_lval_fn(lfn fn = nullptr);
lval* new_lval_num(long n = 0);
lval* new_lval_sym(std::string sym);
lval* new_lval_err(std::string msg, ...);
void delete_lval(lval* val);

lval* builtin_add(lval* op);
lval* builtin_sub(lval* op);
lval* builtin_div(lval* op);
lval* builtin_mul(lval* op);

std::string ltype_to_str(ltype type);

void print_lval(lval* val);
void print_lval_rec(lval* val);

#endif // LVAL_H
