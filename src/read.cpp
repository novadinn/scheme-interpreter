#include "read.h"

// NOTE: form lval bindings
lval* read(const std::vector<std::string>& list) {
    if(list.size() == 0)
	return nullptr;
    
    lval* res = new lval();
    std::string exp = list[0];
    // std::vector<std::string> tail(list.begin() + 1, list.end());
    
    if(exp == "(") {
	res->type = builtin_type::SEXP;
	std::vector<std::vector<std::string>> lists = form_lists(unwrap_list(list));
	std::vector<lval*> rest;
	for(int i = 0; i < lists.size(); ++i) {
	    rest.push_back(read(lists[i]));
	}
	res->list = rest;

	lval* op = res->list[0];
	if(op->type != builtin_type::FN) {
	    // TODO: assert
	}

	std::vector<lval*> args;
	for(int i = 1; i < res->list.size(); ++i) {
	    args.push_back(res->list[i]);
	}
	op->list = args;
    } else if(exp == "+") {
	res->type = builtin_type::FN;
	res->fn = builtin_add;
    } else if(is_number(exp)) {
	res->type = builtin_type::NUMBER;
	res->num = stoi(exp);
    }
    
    return res;
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
    // TODO: assert that list[0] == "(" and list[list.size()-1] == ")"
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

