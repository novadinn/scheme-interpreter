#include "builtins.h"

lval* builtin_add(lval* op, lenv* e) {
    llist lst = op->lst;
    double res = 0;
    
    for(int i = 0; i < lst.size(); ++i) {
	lval* val = eval(lst[i], e);
	res += val->num;
    }

    return lval_num(res);
}

lval* builtin_sub(lval* op, lenv* e) {
    llist lst = op->lst;
    double res = eval(lst[0], e)->num;
    if(lst.size() == 1)
	return lval_num(-res);
    
    for(int i = 1; i < lst.size(); ++i) {
	lval* val = eval(lst[i], e);
	res -= val->num;
    }

    return lval_num(res);
}

lval* builtin_mul(lval* op, lenv* e) {
    llist lst = op->lst;
    double res = 1;
    
    for(int i = 0; i < lst.size(); ++i) {
	lval* val = eval(lst[i], e);
	res *= val->num;
    }

    return lval_num(res);
}

lval* builtin_div(lval* op, lenv* e) {
    llist lst = op->lst;
    double res = eval(lst[0], e)->num;
    
    for(int i = 1; i < lst.size(); ++i) {
	lval* val = eval(lst[i], e);
	res /= val->num;
    }

    return lval_num(res);
}

lval* builtin_car(lval* op, lenv* e) {
    lval* exp = op->lst[0];
    
    return eval(exp->lst[0], e);
}

lval* builtin_cdr(lval* op, lenv* e) {
    lval* exp = op->lst[0];
    llist rest(exp->lst.begin() + 1, exp->lst.end());
    
    return lval_qexp(rest);
}

lval* builtin_cons(lval* op, lenv* e) {
    llist lst = op->lst;
    llist res;
    
    lval* h = eval(lst[0], e);
    lval* t = lst[1];
    res.push_back(h);
    for(int i = 0; i < lst.size(); ++i) {
	res.push_back(lst[i]);
    }
    
    return lval_qexp(lst);
}

lval* builtin_define(lval* op, lenv* e) {
    llist lst = op->lst;
    lval* sym = lst[0];
    lval* val = eval(lst[1], e);

    lenv_push(e, sym->sym, val);
    
    return val;
}

lval* builtin_lambda(lval* op, lenv* e) {
    llist lst = op->lst;
    lval* args = lst[0];
    lval* body = lst[1];
    
    lenv* le = lenv_new(e);
    for(int i = 0; i < args->lst.size(); ++i) {
	lenv_push_unb(le, args->lst[i]->sym);
    }
    
    return lval_fun(builtin_lambda_res, le, args, body);
}

lval* builtin_lambda_res(lval* op, lenv* e) {
    lenv* le = op->env;
    llist alst = op->args->lst;
    lval* body = op->body;
    
    for(int i = 0; i < alst.size(); ++i) {
	lenv_set_lval(le, alst[i]->sym, eval(op->lst[i], e));
    }

    return eval(body, le);
}
