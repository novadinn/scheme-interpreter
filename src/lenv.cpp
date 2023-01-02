#include "lenv.h"

#include "lval.h"

lenv* new_lenv(lenv* par) {
    lenv* e = new lenv();
    e->par = par;
    e->count = 0;

    return e;
}

lval* search_lenv(lenv* e, std::string name) {
    for(int i = 0; i < e->count; ++i) {
	if(e->names[i] == name)
	    return e->vals[i];
    }

    if(e->par)
	return search_lenv(e->par, name);

    return new_lval_err("Unbound symbol %s", name.c_str());
}

void push_lenv(lenv* e, lval* val, std::string name) {
    // TODO: check if val is already in env
    e->vals.push_back(val);
    e->names.push_back(name);
    ++e->count;
}
