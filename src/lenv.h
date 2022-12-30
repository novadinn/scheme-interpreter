#ifndef LENV_H
#define LENV_H

#include <string>
#include <vector>

struct lval;

struct lenv {
    lenv* par;
    int count;
    std::vector<std::string> names;
    std::vector<lval*> vals;
};

lenv* new_lenv(lenv* par = nullptr);
lval* search_lenv(lenv* e, std::string name);
void push_lenv(lenv* e, lval* val);

#endif // LENV_H
