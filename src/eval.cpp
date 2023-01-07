#include "eval.h"

lval* eval(lval* v, lenv* e) {
    switch(v->type) {
    case ltype::SEXP: {
	return eval_sexp(v, e);
    } break;
    case ltype::QEXP: {
	return eval_qexp(v, e);
    } break;
    case ltype::FUN: {
	return eval_fun(v, e);
    } break;
    case ltype::NUM: {
	return eval_num(v, e);
    } break;
    case ltype::STR: {
	return eval_str(v, e);
    } break;
    case ltype::SYM: {
	return eval_sym(v, e);
    } break;
    case ltype::BOOL: {
	return eval_bool(v, e);
    } break;
    case ltype::ERR: {
	return eval_err(v, e);
    } break;
    }

    return lval_err("Unknown value type %s", ltype_to_str(v->type).c_str());
}

lval* eval_sexp(lval* v, lenv* e) {
    llist lst = v->lst;
    llist args;
    lval* op = eval(lst[0], e);

    for(int i = 1; i < v->lst.size(); ++i) {
	args.push_back(lst[i]);
    }
    op->lst = args;

    return eval(op, e);
}

lval* eval_qexp(lval* v, lenv* e) {
    return v;
}

lval* eval_fun(lval* v, lenv* e) {
    if(v->env && lenv_par_p(e, v->env))
	return v->fun(v, v->env);
    return v->fun(v, e);
}

lval* eval_num(lval* v, lenv* e) {
    return v;
}

lval* eval_str(lval* v, lenv* e) {
    return v;
}

lval* eval_sym(lval* v, lenv* e) {
    return lenv_search(e, v->sym);
}

lval* eval_bool(lval* v, lenv* e) {
    return v;
}

lval* eval_err(lval* v, lenv* e) {
    printf("%s\n", v->err);
    return v;
}
