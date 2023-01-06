#include "lenv.h"

#include "lval.h"

lenv* lenv_new(lenv* par) {
    lenv* e = new lenv();
    e->par = par;
    e->c = 0;
    
    return e;
}

lval* lenv_search(lenv* e, std::string s) {
    for(int i = 0; i < e->c; ++i) {
	if(e->syms[i] == s)
	    return e->vals[i];
    }

    if(e->par)
	return lenv_search(e->par, s);

    return lval_err("Unbound symbol %s", s.c_str());
}

void lenv_push(lenv* e, std::string s, lval* v) {
    e->syms.push_back(s);
    e->vals.push_back(v);
    ++e->c;
}

void lenv_push_unb(lenv* e, std::string s) {
    e->syms.push_back(s);
    e->vals.push_back(nullptr);
    ++e->c;
}

void lenv_set_lval(lenv* e, std::string s, lval* v) {
    for(int i = 0; i < e->c; ++i) {
	if(e->syms[i] == s) {
	    e->vals[i] = v;
	    return;
	}
    }

    if(e->par)
	lenv_set_lval(e->par, s, v);
}

bool lenv_par_p(lenv* p, lenv* c) {
    if(c == nullptr)
	return false;

    return c->par == p || lenv_par_p(p, c->par);
}

void lenv_del(lenv* e) {
    for(int i = 0; i < e->c; ++i)
	lval_del(e->vals[i]);

    delete e;
}
