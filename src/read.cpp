#include "read.h"

#include "builtins.h"

lval* read(const std::vector<std::string>& list) {
    if(list.size() == 0)
	return nullptr;
    
    std::string exp = list[0];

    if(sexp_p(exp)) {
	return read_sexp(list);
    } else if(qexp_p(exp)) {
	return read_qexp(list);
    } else if(fn_p(exp)) {
	return read_fn(exp);
    } else if(num_p(exp)) {
	return read_num(exp);
    } else if(sym_p(exp)) {
	return read_sym(exp);
    }

    return new_lval_err("A syntax error has occured");
}

lval* read_sexp(const std::vector<std::string>& list) {
    std::vector<std::string> unwr(list);
    unwr.erase(unwr.begin());
    unwr.erase(unwr.begin() + unwr.size()-1);

    std::vector<std::vector<std::string>> res;
    std::vector<std::string> cur;
    int nparan = 0;
    bool qexp = false;
    
    for(int i = 0; i < unwr.size(); ++i) {
	std::string exp = unwr[i];

	if(qexp) {
	    qexp = false;
	    --nparan;
	}
	
	if(exp == "'") {
	    qexp = true;
	    ++nparan;
	} else if(exp == "(") {
	    ++nparan;
	} else if(exp == ")") {
	    --nparan;
	}

	cur.push_back(exp);
	
	if(nparan == 0) {
	    res.push_back(cur);
	    cur.clear();
	}
    }

    std::vector<lval*> rest;
    for(int i = 0; i < res.size(); ++i) {
	rest.push_back(read(res[i]));
    }
	
    return new_lval_sexp(rest);
}

lval* read_qexp(const std::vector<std::string>& list) {
    std::vector<std::string> unwr(list);
    unwr.erase(unwr.begin());
    unwr.erase(unwr.begin());
    unwr.erase(unwr.begin() + unwr.size()-1);
    
    std::vector<std::vector<std::string>> res;
    std::vector<std::string> cur;
    int nparan = 0;
    
    for(int i = 0; i < unwr.size(); ++i) {
	std::string exp = unwr[i];
	
	if(exp == "(") {
	    cur.push_back("'");
	    ++nparan;
	} else if(exp == ")") {
	    --nparan;
	}

	cur.push_back(exp);
	
	if(nparan == 0) {
	    res.push_back(cur);
	    cur.clear();
	}
    }

    std::vector<lval*> rest;
    for(int i = 0; i < res.size(); ++i) {
	rest.push_back(read(res[i]));
    }

    return new_lval_qexp(rest);
}

lval* read_fn(const std::string& exp) {
    if(exp == "define") {
	return new_lval_fn(builtin_define);
    } else if(exp == "car") {
	return new_lval_fn(builtin_car);
    } else if(exp == "cdr") {
	return new_lval_fn(builtin_cdr);
    } else if(exp == "+") {
	return new_lval_fn(builtin_add);
    } else if(exp == "-") {
	return new_lval_fn(builtin_sub);
    } else if(exp == "*") {
	return new_lval_fn(builtin_mul);
    } else if(exp == "/") {
	return new_lval_fn(builtin_div);
    }

    return new_lval_err("Unimplemented exception");
}

lval* read_num(const std::string& exp) {
    return new_lval_num(stoi(exp));
}

lval* read_sym(const std::string& exp) {
    return new_lval_sym(exp);
}

bool sexp_p(const std::string& exp) {
    return exp == "(";
}

bool qexp_p(const std::string& exp) {
    return exp == "'";
}

bool fn_p(const std::string& exp) {
    bool res = false;
    if(exp == "define") {
	res = true;
    } else if(exp == "car") {
	res = true;
    } else if(exp == "cdr") {
	res = true;
    } else if(exp == "+") {
	res = true;
    } else if(exp == "-") {
	res = true;
    } else if(exp == "*") {
	res = true;
    } else if(exp == "/") {
	res = true;
    }

    return res;
}

bool num_p(const std::string& exp) {
    std::string::const_iterator it = exp.begin();
    while (it != exp.end() && std::isdigit(*it)) ++it;
    return !exp.empty() && it == exp.end();
}

bool sym_p(const std::string& exp) {
    return true;
}
