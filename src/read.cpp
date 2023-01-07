#include "read.h"

#include "builtins.h"

lval* read(const std::vector<std::string>& lst) {

    const std::string exp = lst[0];

    if(sexp_p(exp)) return read_sexp(lst);
    else if(qexp_p(exp)) return read_qexp(lst);
    else if(num_p(exp)) return read_num(exp);
    else if(str_p(exp)) return read_str(exp);
    else if(bool_p(exp)) return read_bool(exp);
    else if(sym_p(exp)) return read_sym(exp);
    else if(var_p(exp)) return read_var(exp);

    return lval_err("A syntax error has occured while reading expression %s", exp.c_str());
}

lval* read_sexp(const std::vector<std::string>& lst) {    
    return lval_sexp(read_exp(lst));
}

lval* read_qexp(const std::vector<std::string>& lst) {
    return lval_qexp(read_exp(lst));
}

lval* read_num(const std::string& exp) {
    return lval_num(stoi(exp));
}

lval* read_str(const std::string& exp) {
    return lval_str(exp);
}

lval* read_var(const std::string& exp) {
    return lval_var(exp);
}

lval* read_sym(const std::string& exp) {
    return lval_sym(exp.substr(1));
}

lval* read_bool(const std::string& exp) {
    return lval_bool(exp == "true");
}

bool sexp_p(const std::string& exp) {
    return exp == "(";
}

bool qexp_p(const std::string& exp) {
    return exp == "'(";
}

bool num_p(const std::string& exp) {
    std::string::const_iterator it = exp.begin();
    while (it != exp.end() && std::isdigit(*it)) ++it;
    return !exp.empty() && it == exp.end();
}

bool str_p(const std::string& exp) {
    return exp[0] == '"' && exp[exp.size()-1] == '"';
}

bool var_p(const std::string& exp) {
    return true;
}

bool sym_p(const std::string& exp) {
    return exp[0] == '\'';
}

bool bool_p(const std::string& exp) {
    return exp == "true" || exp == "false";
}

std::vector<lval*> read_exp(const std::vector<std::string>& lst) {
    std::vector<lval*> rest;
    
    for(int i = 1; i < lst.size()-1; ++i) {
	std::vector<std::string> t = next_token(lst, i, lst.size()-1);
	i += t.size()-1;
	if(t.size() > 0) rest.push_back(read(t));
    }

    return rest;
}

std::vector<std::string> next_token(const std::vector<std::string>& lst, int s, int m) {
    std::vector<std::string> res;
    int np = 0;
    bool qexp = false;
    
    for(int i = s; i < m; ++i) {
	std::string exp = lst[i];

	if(exp == "'(" && !qexp) {
	    ++np;
	    qexp = true;
	} else if(exp == "(") {
	    ++np;
	    if(qexp) exp = "'" + exp;
	} else if(exp == ")") {
	    --np;
	}

	if(np < 0) break;
	res.push_back(exp);
	if(np == 0) break;
    }
    
    return res;
}
