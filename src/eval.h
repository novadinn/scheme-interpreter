#ifndef EVAL_H
#define EVAL_H

#include "lval.h"

lval* eval(lval* v, lenv* e);

lval* eval_sexp(lval* v, lenv* e);
lval* eval_qexp(lval* v, lenv* e);
lval* eval_fun(lval* v, lenv* e);
lval* eval_num(lval* v, lenv* e);
lval* eval_str(lval* v, lenv* e);
lval* eval_var(lval* v, lenv* e);
lval* eval_sym(lval* v, lenv* e);
lval* eval_bool(lval* v, lenv* e);
lval* eval_err(lval* v, lenv* e);

#endif // EVAL_H
