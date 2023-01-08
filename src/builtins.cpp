#include "builtins.h"

#include "log.h"
#include "math.h"

lval* builtin_add(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_NOT_EMPTY("+", lst, 0);
    double res = 0;
    
    for(int i = 0; i < lst.size(); ++i) {
	lval* val = eval(lst[i], e);
	LASSERT_TYPE("+", i, val->type, ltype::NUM);
	res += val->num;
    }

    return lval_num(res);
}

lval* builtin_sub(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_NOT_EMPTY("-", lst, 0);
    
    double res = eval(lst[0], e)->num;
    if(lst.size() == 1)
	return lval_num(-res);
    
    for(int i = 1; i < lst.size(); ++i) {
	lval* val = eval(lst[i], e);
	LASSERT_TYPE("-", i, val->type, ltype::NUM);
	res -= val->num;
    }

    return lval_num(res);
}

lval* builtin_mul(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_NOT_EMPTY("*", lst, 0);
    double res = 1;
    
    for(int i = 0; i < lst.size(); ++i) {
	lval* val = eval(lst[i], e);
	LASSERT_TYPE("*", i, val->type, ltype::NUM);
	res *= val->num;
    }

    return lval_num(res);
}

lval* builtin_div(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_NOT_EMPTY("/", lst, 0);
    double res = eval(lst[0], e)->num;
    
    for(int i = 1; i < lst.size(); ++i) {
	lval* val = eval(lst[i], e);
	LASSERT_TYPE("/", i, val->type, ltype::NUM);
	res /= val->num;
    }

    return lval_num(res);
}

lval* builtin_list(lval* op, lenv* e) {
    llist lst = op->lst;
    llist res;
    
    for(int i = 0; i < lst.size(); ++i) {
	res.push_back(eval(lst[i], e));
    }
    
    return lval_qexp(res);
}

lval* builtin_car(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("car", lst, 1);
    
    lval* exp = eval(lst[0], e);
    LASSERT_TYPE("car", 0, exp->type, ltype::QEXP);
    
    return eval(exp->lst[0], e);
}

lval* builtin_cdr(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("cdr", lst, 1);

    lval* exp = eval(lst[0], e);
    LASSERT_TYPE("cdr", 0, exp->type, ltype::QEXP);
    
    llist elst = exp->lst;
    LASSERT_NOT_EMPTY("cdr", elst, 0);
    
    llist rest(elst.begin() + 1, elst.end());
    
    return lval_qexp(rest);
}

lval* builtin_cons(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("cons", lst, 2);
    
    lval* h = eval(lst[0], e);
    lval* tail = lst[1];
    LASSERT_TYPE("cons", 1, tail->type, ltype::QEXP);
    llist qexp = tail->lst;

    llist res;
    res.push_back(h);
    for(int i = 0; i < qexp.size(); ++i) {
	res.push_back(qexp[i]);
    }
    
    return lval_qexp(res);
}

lval* builtin_define(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("define", lst, 2);
    
    lval* sym = lst[0];
    LASSERT_TYPE("define", 0, sym->type, ltype::VAR);
    lval* val = eval(lst[1], e);

    lenv_push(e, sym->vname, val);
    
    return val;
}

lval* builtin_lambda(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("lambda", lst, 2);
    
    lval* args = lst[0];
    LASSERT_TYPE("lambda", 0, args->type, ltype::SEXP);
    lval* body = lst[1];
    LASSERT_TYPE("lambda", 1, body->type, ltype::SEXP);
    
    lenv* le = lenv_new(e);
    for(int i = 0; i < args->lst.size(); ++i) {
	lval* unb = args->lst[i];
	LASSERT_TYPE("lambda", 0, unb->type, ltype::VAR);
	lenv_push_unb(le, unb->vname);
    }
    
    return lval_fun(builtin_lambda_res, le, args, body);
}

lval* builtin_lambda_res(lval* op, lenv* e) {
    lenv* le = op->env;
    llist alst = op->args->lst;
    lval* body = op->body;

    LASSERT_ARGC("lambda_result", alst, op->lst.size());
    for(int i = 0; i < alst.size(); ++i) {
	lenv_set_lval(le, alst[i]->vname, eval(op->lst[i], e));
    }
    
    return eval(body, le);
}

lval* builtin_if(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("if", lst, 3);

    lval* r = eval(lst[0], e);
    LASSERT_TYPE("if", 0, r->type, ltype::BOOL);
    
    if(r->b)
	return eval(lst[1], e);

    return eval(lst[2], e);
}

lval* builtin_not(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("not", lst, 1);
    lval* exp = eval(lst[0], e);
    LASSERT_TYPE("not", 0, exp->type, ltype::BOOL);
    
    return lval_bool(!exp->b);
}

lval* builtin_and(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_NOT_EMPTY("and", lst, 0);

    for(int i = 0; i < lst.size(); ++i) {
	if(!lst[i]->b)
	    return lval_bool(false);
    }

    return eval(lst[lst.size()-1], e);
}

lval* builtin_or(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_NOT_EMPTY("or", lst, 0);

    for(int i = 0; i < lst.size(); ++i) {
	if(lst[i]->b)
	    return eval(lst[i], e);
    }

    return lval_bool(false);
}

lval* builtin_e(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_NOT_EMPTY("=", lst, 0);

    for(int i = 0; i < lst.size()-1; ++i) {
	lval* l = eval(lst[i], e);
	lval* r = eval(lst[i+1], e);
	LASSERT_TYPE("=", i, l->type, ltype::NUM);
	LASSERT_TYPE("=", i+1, r->type, ltype::NUM);
	if(!(l->num == r->num))
	    return lval_bool(false);
    }

    return lval_bool(true);
}

lval* builtin_ge(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_NOT_EMPTY(">=", lst, 0);
    
    for(int i = 0; i < lst.size()-1; ++i) {
	lval* l = eval(lst[i], e);
	lval* r = eval(lst[i+1], e);
	LASSERT_TYPE(">=", i, l->type, ltype::NUM);
	LASSERT_TYPE(">=", i+1, r->type, ltype::NUM);
	if(!(l->num >= r->num))
	    return lval_bool(false);
    }

    return lval_bool(true);
}

lval* builtin_le(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_NOT_EMPTY("<=", lst, 0);

    for(int i = 0; i < lst.size()-1; ++i) {
	lval* l = eval(lst[i], e);
	lval* r = eval(lst[i+1], e);
	LASSERT_TYPE("<=", i, l->type, ltype::NUM);
	LASSERT_TYPE("<=", i+1, r->type, ltype::NUM);
	if(!(l->num <= r->num))
	    return lval_bool(false);
    }

    return lval_bool(true);
}

lval* builtin_g(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_NOT_EMPTY(">", lst, 0);

    for(int i = 0; i < lst.size()-1; ++i) {
	lval* l = eval(lst[i], e);
	lval* r = eval(lst[i+1], e);
	LASSERT_TYPE(">", i, l->type, ltype::NUM);
	LASSERT_TYPE(">", i+1, r->type, ltype::NUM);
	if(!(l->num > r->num))
	    return lval_bool(false);
    }

    return lval_bool(true);
}

lval* builtin_l(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_NOT_EMPTY("<", lst, 0);

    for(int i = 0; i < lst.size()-1; ++i) {
	lval* l = eval(lst[i], e);
	lval* r = eval(lst[i+1], e);
	LASSERT_TYPE("<", i, l->type, ltype::NUM);
	LASSERT_TYPE("<", i+1, r->type, ltype::NUM);
	if(!(l->num < r->num))
	    return lval_bool(false);
    }

    return lval_bool(true);
}

lval* builtin_even_p(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("even?", lst, 1);
    
    lval* el = eval(lst[0], e);
    LASSERT_TYPE("even?", 0, el->type, ltype::NUM);
    
    return lval_bool((int)el->num % 2 == 0);
}

lval* builtin_odd_p(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("odd?", lst, 1);
    
    lval* el = eval(lst[0], e);
    LASSERT_TYPE("odd?", 0, el->type, ltype::NUM);
    
    return lval_bool((int)el->num % 2 != 0);
}

lval* builtin_zero_p(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("zero?", lst, 1);

    lval* el = eval(lst[0], e);
    LASSERT_TYPE("zero?", 0, el->type, ltype::NUM);
    
    return lval_bool(el->num == 0);
}

lval* builtin_boolean_p(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("boolean?", lst, 1);

    lval* v = eval(lst[0], e);
    LASSERT_W_ERROR(v);
    return lval_bool(v->type == ltype::BOOL);
}

lval* builtin_integer_p(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("integer?", lst, 1);

    lval* v = eval(lst[0], e);
    LASSERT_W_ERROR(v);
    return lval_bool(v->type == ltype::NUM);
}

lval* builtin_list_p(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("list?", lst, 1);

    lval* v = eval(lst[0], e);
    LASSERT_W_ERROR(v);
    return lval_bool(v->type == ltype::QEXP);
}

lval* builtin_atom_p(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("list?", lst, 1);

    lval* v = eval(lst[0], e);
    LASSERT_W_ERROR(v);
    ltype t = v->type;
    return lval_bool(t == ltype::BOOL || t == ltype::NUM ||
		     t == ltype::SYM || t == ltype::STR ||
		     (t == ltype::QEXP && v->lst.size() == 0));
}

lval* builtin_null_p(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("null?", lst, 1);

    lval* v = eval(lst[0], e);
    LASSERT_W_ERROR(v);
    return lval_bool(v->type == ltype::QEXP && v->lst.size() == 0);
}

lval* builtin_pair_p(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("pair?", lst, 1);

    lval* v = eval(lst[0], e);
    LASSERT_W_ERROR(v);
    return lval_bool(v->type == ltype::QEXP && v->lst.size() != 0);
}

lval* builtin_procedure_p(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("procedure?", lst, 1);

    lval* v = eval(lst[0], e);
    LASSERT_W_ERROR(v);
    return lval_bool(v->type == ltype::FUN);
}

lval* builtin_string_p(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("string?", lst, 1);
    
    lval* v = eval(lst[0], e);
    LASSERT_W_ERROR(v);
    return lval_bool(v->type == ltype::STR);
}

lval* builtin_symbol_p(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("symbol?", lst, 1);

    lval* v = eval(lst[0], e);
    LASSERT_W_ERROR(v);
    return lval_bool(v->type == ltype::SYM);
}

lval* builtin_abs(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("abs", lst, 1);

    lval* v = eval(lst[0], e);
    LASSERT_TYPE("abs", 0, v->type, ltype::NUM);

    return lval_num(absolute(v->num));
}

lval* builtin_expt(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("expt", lst, 2);

    lval* l = eval(lst[0], e);
    LASSERT_TYPE("expt", 0, l->type, ltype::NUM);
    lval* r = eval(lst[1], e);
    LASSERT_TYPE("expt", 0, r->type, ltype::NUM);

    return lval_num(expt(l->num, r->num));
}

lval* builtin_modulo(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("modulo", lst, 2);

    lval* l = eval(lst[0], e);
    LASSERT_TYPE("modulo", 0, l->type, ltype::NUM);
    lval* r = eval(lst[1], e);
    LASSERT_TYPE("modulo", 0, r->type, ltype::NUM);

    return lval_num(mod(l->num, r->num));
}

lval* builtin_quotient(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("quotient", lst, 2);

    lval* l = eval(lst[0], e);
    LASSERT_TYPE("quotient", 0, l->type, ltype::NUM);
    lval* r = eval(lst[1], e);
    LASSERT_TYPE("quotient", 0, r->type, ltype::NUM);

    return lval_num(quot(l->num, r->num));
}

lval* builtin_remainder(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("remainder", lst, 2);

    lval* l = eval(lst[0], e);
    LASSERT_TYPE("remainder", 0, l->type, ltype::NUM);
    lval* r = eval(lst[1], e);
    LASSERT_TYPE("remainder", 0, r->type, ltype::NUM);

    return lval_num(rem(l->num, r->num));
}

lval* builtin_begin(lval* op, lenv* e) {
    llist lst = op->lst;

    for(int i = 0; i < lst.size() - 1; ++i) {
	eval(lst[i], e);
    }

    return eval(lst[lst.size()-1], e);
}

lval* builtin_display(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("display", lst, 1);

    lval* v = eval(lst[0], e);
    print_lval(v);
    
    return nullptr;
}

lval* builtin_error(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("error", lst, 1);

    lval* v = eval(lst[0], e);
    LASSERT_TYPE("error", 0, v->type, ltype::STR);
    
    return lval_err(v->str);
}

lval* builtin_newline(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("newline", lst, 0);
    
    printf("\n");
    
    return nullptr;
}

lval* builtin_eq_p(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("eq?", lst, 2);

    lval* l = eval(lst[0], e);
    lval* r = eval(lst[1], e);

    if(l == r) return lval_bool(true);

    return lval_bool(lval_equal_e(l, r));
}

lval* builtin_equal_p(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("eq?", lst, 2);

    lval* l = eval(lst[0], e);
    lval* r = eval(lst[1], e);

    return lval_bool(lval_equal_e(l, r));
}

lval* builtin_set(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("set!", lst, 2);

    lval* l = lst[0];
    LASSERT_TYPE("set!", 0, l->type, ltype::VAR);
    lval* r = eval(lst[1], e);

    lenv_set_lval(e, l->vname, r);
    lval_del(l);
    
    return r;
}

lval* builtin_set_car(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("set-car!", lst, 2);

    lval* l = lst[0];
    LASSERT_TYPE("set-car!", 0, l->type, ltype::VAR);
    lval* le = eval(l, e);
    LASSERT_TYPE("set-car!", 0, le->type, ltype::QEXP);
    lval* r = eval(lst[1], e);

    std::vector<lval*> qexp;
    qexp.push_back(r);
    for(int i = 1; i < le->lst.size(); ++i) {
	qexp.push_back(le->lst[i]);
    }
    
    lval* res = lval_qexp(qexp);
    lenv_set_lval(e, l->vname, res);
    lval_del(l);
    
    return res;
}

lval* builtin_set_cdr(lval* op, lenv* e) {
    llist lst = op->lst;
    LASSERT_ARGC("set-cdr!", lst, 2);

    lval* l = lst[0];
    LASSERT_TYPE("set-cdr!", 0, l->type, ltype::VAR);
    lval* le = eval(l, e);
    LASSERT_TYPE("set-cdr!", 0, le->type, ltype::QEXP);
    lval* r = eval(lst[1], e);
    
    std::vector<lval*> qexp;
    if(r->type == ltype::QEXP) {
	qexp.push_back(le->lst[0]);
	for(int i = 0; i < r->lst.size(); ++i) {
	    qexp.push_back(r->lst[i]);
	}
    } else {
	qexp.push_back(le->lst[0]);
	qexp.push_back(r);
    }

    lval* res = lval_qexp(qexp);
    lenv_set_lval(e, l->vname, res);
    lval_del(l);
    
    return res;
}
