#include "read.h"

lval* read(const std::vector<std::string>& list) {
    if(list.size() == 0)
	return nullptr;
    
    std::string exp = list[0];
    
    if(exp == "(") {
	std::vector<std::vector<std::string>> lists = form_lists(unwrap_list(list));
	std::vector<lval*> rest;
	for(int i = 0; i < lists.size(); ++i) {
	    rest.push_back(read(lists[i]));
	}
	
	return new_lval_sexp(rest);
    } else if(exp == "+") { // TODO: if symbol
	return new_lval_fn(builtin_add);
    } else if(exp == "-") {
	return new_lval_fn(builtin_sub);
    } else if(exp == "*") {
	return new_lval_fn(builtin_mul);
    } else if(exp == "/") {
	return new_lval_fn(builtin_div);
    } else if(is_number(exp)) {
	return new_lval_num(stoi(exp));
    }

    return new_lval_sym(exp);
}


std::vector<std::vector<std::string>> form_lists(const std::vector<std::string>& list) {
    std::vector<std::vector<std::string>> res;
    std::vector<std::string> cur;
    int nparan = 0;
    
    for(int i = 0; i < list.size(); ++i) {
	std::string exp = list[i];
	cur.push_back(exp);
	
	if(exp == "(") {
	    ++nparan;
	} else if(exp == ")") {
	    --nparan;
	}

	if(nparan == 0) {
	    res.push_back(cur);
	    cur.clear();
	}
    }

    return res;
}

std::vector<std::string> unwrap_list(const std::vector<std::string>& list) {
    std::vector<std::string> res(list);
    res.erase(res.begin());
    res.erase(res.begin() + res.size()-1);
    
    return res;
}

int rm_occurs(std::string& s, char c) {
    int n = 0;
    for(int i = 0; i < s.size(); ++i) {
	if(s[i] == c) {
	    s.erase(i--, 1);
	    ++n;
	}
    }

    return n;
}

bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
