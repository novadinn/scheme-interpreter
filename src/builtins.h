#ifndef BUILTINS_H
#define BUILTINS_H

lval* builtin_add(lval* op, lenv* env);
lval* builtin_sub(lval* op, lenv* env);
lval* builtin_div(lval* op, lenv* env);
lval* builtin_mul(lval* op, lenv* env);
lval* builtin_define(lval* op, lenv* env);
lval* builtin_car(lval* op, lenv* env);
lval* builtin_cdr(lval* op, lenv* env);

#endif // BUILTINS_H
