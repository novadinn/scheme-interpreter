#ifndef LENV_H
#define LENV_H

#include <string>
#include <vector>

struct lval;

struct lenv {
    lenv* par;
    int c;
    std::vector<std::string> syms;
    std::vector<lval*> vals;
};

lenv* lenv_new(lenv* par = nullptr);
lval* lenv_search(lenv* e, std::string s);
void lenv_push(lenv* e, std::string s, lval* v);
void lenv_push_unb(lenv* e, std::string s);
void lenv_set_lval(lenv* e, std::string s, lval* v);
bool lenv_par_p(lenv* p, lenv* c);
void lenv_del(lenv* e);

#endif // LENV_H
