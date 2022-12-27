#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <editline/readline.h>
#include <editline/history.h>

enum builtin_type {
    NUMBER,
    FN
};

struct lval;

typedef lval*(*lfn)(lval*);

struct lval {
    builtin_type type;
    
    long num;
    lfn fn;

    lval** rest;
};

void eval(lval* exp);
lval* read(const std::vector<std::string>& list);

int rm_occurs(std::string& s, char c);
bool is_number(const std::string& s);

int main(int argc, char** argv) {
    while (true) {
	char* input = readline("scheme> ");
	add_history(input);
	
	std::istringstream iss(input);
	std::vector<std::string> list(std::istream_iterator<std::string>{iss},
					 std::istream_iterator<std::string>());

	std::vector<std::string> result;
	for(int i = 0; i < list.size(); ++i) {
	    std::string exp = list[i];
	    
	    int paran = rm_occurs(exp, '(');
	    for(int j = 0; j < paran; ++j) {
		result.push_back("(");
	    }

	    paran = rm_occurs(exp, ')');
	    result.push_back(exp);

	    for(int j = 0; j < paran; ++j) {
		result.push_back(")");
	    }
	}

	eval(read(result));
	
	free(input);
    }
    
    return 0;
}

void eval(lval* exp) {
    
}

lval* read(const std::vector<std::string>& list) {
    lval* res = new lval();

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
