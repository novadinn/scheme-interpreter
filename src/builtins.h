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

lval* builtin_if(lval* op, lenv* e);
lval* builtin_not(lval* op, lenv* e);
lval* builtin_not(lval* op, lenv* e);
lval* builtin_and(lval* op, lenv* e);
lval* builtin_or(lval* op, lenv* e);

lval* builtin_even(lval* op, lenv* e);
lval* builtin_odd(lval* op, lenv* e);
lval* builtin_zero(lval* op, lenv* e);
lval* builtin_e(lval* op, lenv* e);
lval* builtin_ge(lval* op, lenv* e);
lval* builtin_le(lval* op, lenv* e);
lval* builtin_g(lval* op, lenv* e);
lval* builtin_l(lval* op, lenv* e);

lval* builtin_boolean(lval* op, lenv* e);
lval* builtin_integer(lval* op, lenv* e);
lval* builtin_list(lval* op, lenv* e);
lval* builtin_atom(lval* op, lenv* e);
lval* builtin_null(lval* op, lenv* e);
lval* builtin_pair(lval* op, lenv* e);
lval* builtin_procedure(lval* op, lenv* e);
lval* builtin_string(lval* op, lenv* e);
lval* builtin_symbol(lval* op, lenv* e);

#endif // BUILTINS_H
