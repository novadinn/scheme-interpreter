#ifndef EVAL_H
#define EVAL_H

#include "lval.h"
#include "lenv.h"

lval* eval(lval* exp, lenv* env);

lval* eval_sexp(lval* exp, lenv* env);
lval* eval_qexp(lval* exp, lenv* env);
lval* eval_fn(lval* exp, lenv* env);
lval* eval_num(lval* exp, lenv* env);
lval* eval_sym(lval* exp, lenv* env);
lval* eval_err(lval* exp, lenv* env);

#endif // EVAL_H
