#include "builtins.h"

lval* builtin_add(lval* op, lenv* env) {
    long res = 0;
    
    for(int i = 0; i < op->list.size(); ++i) {
	lval* val = eval(op->list[i], env);
	LTYPE_ASSERT("+", val->type, i, ltype::NUM);
	res += val->num;
    }

    return new_lval_num(res);
}

lval* builtin_sub(lval* op, lenv* env) {
    long res = eval(op->list[0], env)->num;
    if(op->list.size() == 1)
	return new_lval_num(-res);
    
    for(int i = 1; i < op->list.size(); ++i) {
	lval* val = eval(op->list[i], env);
	LTYPE_ASSERT("-", val->type, i, ltype::NUM);
	res -= val->num;
    }

    return new_lval_num(res);
}

lval* builtin_div(lval* op, lenv* env) {
    long res = eval(op->list[0], env)->num;
    
    for(int i = 1; i < op->list.size(); ++i) {
	lval* val = eval(op->list[i], env);
	LTYPE_ASSERT("/", val->type, i, ltype::NUM);
	res /= val->num;
    }

    return new_lval_num(res);
}

lval* builtin_mul(lval* op, lenv* env) {
    long res = eval(op->list[0], env)->num;
    
    for(int i = 1; i < op->list.size(); ++i) {
	lval* val = eval(op->list[i], env);
	LTYPE_ASSERT("*", val->type, i, ltype::NUM);
	res *= val->num;
    }

    return new_lval_num(res);
}

lval* builtin_define(lval* op, lenv* env) {
    std::string sym = op->list[0]->sym;
    lval* val = eval(op->list[1], env);
    push_lenv(env, val, sym);
    
    return new_lval_sym(sym);
}

lval* builtin_car(lval* op, lenv* env) {
    lval* exp = op->list[0];
    LTYPE_ASSERT("car", exp->type, 0, ltype::QEXP);
    return exp->list[0];
}

lval* builtin_cdr(lval* op, lenv* env) {
    lval* exp = op->list[0];
    LTYPE_ASSERT("car", exp->type, 0, ltype::QEXP);
    // TODO: assert if size is < 1
    std::vector<lval*> rest(exp->list.begin() + 1, exp->list.end());
    return new_lval_qexp(rest);
}
