#ifndef BUILTINS_H
#define BUILTINS_H

#include "lval.h"
#include "lenv.h"

lval* builtin_add(lval* op, lenv* e);
lval* builtin_sub(lval* op, lenv* e);
lval* builtin_mul(lval* op, lenv* e);
lval* builtin_div(lval* op, lenv* e);
lval* builtin_car(lval* op, lenv* e);
lval* builtin_cdr(lval* op, lenv* e);
lval* builtin_cons(lval* op, lenv* e);
lval* builtin_define(lval* op, lenv* e);
lval* builtin_lambda(lval* op, lenv* e);
lval* builtin_lambda_res(lval* op, lenv* e);

#endif // BUILTINS_H
