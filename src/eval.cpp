#include "eval.h"

// TODO: use local env
lval* eval(lval* exp, lenv* env) {
    switch(exp->type) {
    case ltype::SEXP: {
	return eval_sexp(exp, env);
    } break;
    case ltype::QEXP: {
	return eval_qexp(exp, env);
    } break;
    case ltype::FN: {
	return eval_fn(exp, env);
    } break;
    case ltype::NUM: {
	return eval_num(exp, env);
    } break;
    case ltype::SYM: {
	return eval_sym(exp, env);
    } break;
    case ltype::ERR: {
	return eval_err(exp, env);
    } break;
    }

    return new_lval_err("Unimplemented exception");
}

lval* eval_sexp(lval* exp, lenv* env) {
    std::vector<lval*> args;
    lval* op = exp->list[0];
    LTYPE_ASSERT("eval_sexp", op->type, 0, ltype::FN);
	
    for(int i = 1; i < exp->list.size(); ++i) {
	LNTYPE_ASSERT("eval_sexp", exp->list[i]->type, i, ltype::FN);
	args.push_back(exp->list[i]->type == ltype::SEXP ?
		       eval(exp->list[i], env) :
		       exp->list[i]);
    }
    op->list = args;

    return eval(op, env);
}

lval* eval_qexp(lval* exp, lenv* env) {
    return exp;
}

lval* eval_fn(lval* exp, lenv* env) {
    // TODO: if(exp->evn)
    return exp->fn(exp, env);
}

lval* eval_num(lval* exp, lenv* env) {
    return exp;
}

lval* eval_sym(lval* exp, lenv* env) {
    return eval(search_lenv(env, exp->sym), env);
}

lval* eval_err(lval* exp, lenv* env) {
    printf("%s\n", exp->err);
    return exp;
}
