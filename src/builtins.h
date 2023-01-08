#ifndef BUILTINS_H
#define BUILTINS_H

#include "lval.h"
#include "lenv.h"

lval* builtin_add(lval* op, lenv* e);
lval* builtin_sub(lval* op, lenv* e);
lval* builtin_mul(lval* op, lenv* e);
lval* builtin_div(lval* op, lenv* e);

lval* builtin_list(lval* op, lenv* e);
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

lval* builtin_e(lval* op, lenv* e);
lval* builtin_ge(lval* op, lenv* e);
lval* builtin_le(lval* op, lenv* e);
lval* builtin_g(lval* op, lenv* e);
lval* builtin_l(lval* op, lenv* e);

lval* builtin_even_p(lval* op, lenv* e);
lval* builtin_odd_p(lval* op, lenv* e);
lval* builtin_zero_p(lval* op, lenv* e);
lval* builtin_boolean_p(lval* op, lenv* e);
lval* builtin_integer_p(lval* op, lenv* e);
lval* builtin_list_p(lval* op, lenv* e);
lval* builtin_atom_p(lval* op, lenv* e);
lval* builtin_null_p(lval* op, lenv* e);
lval* builtin_pair_p(lval* op, lenv* e);
lval* builtin_procedure_p(lval* op, lenv* e);
lval* builtin_string_p(lval* op, lenv* e);
lval* builtin_symbol_p(lval* op, lenv* e);

lval* builtin_abs(lval* op, lenv* e);
lval* builtin_expt(lval* op, lenv* e);
lval* builtin_modulo(lval* op, lenv* e);
lval* builtin_quotient(lval* op, lenv* e);
lval* builtin_remainder(lval* op, lenv* e);

lval* builtin_begin(lval* op, lenv* e);
lval* builtin_display(lval* op, lenv* e);
lval* builtin_error(lval* op, lenv* e);
lval* builtin_newline(lval* op, lenv* e);

lval* builtin_eq_p(lval* op, lenv* e);
lval* builtin_equal_p(lval* op, lenv* e);
lval* builtin_set(lval* op, lenv* e);
lval* builtin_set_car(lval* op, lenv* e);
lval* builtin_set_cdr(lval* op, lenv* e);

#endif // BUILTINS_H
