#include <iostream>
#include <string>
#include <vector>

#include "lval.cpp"
#include "lenv.cpp"
#include "read.cpp"
#include "eval.cpp"
#include "builtins.cpp"

int main(int argc, char** argv) {
    // TODO: builtin functions should also be declared in here
    lenv* genv = lenv_new();
    lenv_push(genv, "true", lval_num(1));
    lenv_push(genv, "false", lval_num(0));

    lenv_push(genv, "+", lval_fun(builtin_add, genv));
    lenv_push(genv, "-", lval_fun(builtin_sub, genv));
    lenv_push(genv, "*", lval_fun(builtin_mul, genv));
    lenv_push(genv, "/", lval_fun(builtin_div, genv));
    lenv_push(genv, "car", lval_fun(builtin_car, genv));
    lenv_push(genv, "cdr", lval_fun(builtin_cdr, genv));
    lenv_push(genv, "cons", lval_fun(builtin_cons, genv));
    lenv_push(genv, "define", lval_fun(builtin_define, genv));
    lenv_push(genv, "lambda", lval_fun(builtin_lambda, genv));
   
    while (true) {
	std::string input;

	printf("scheme> ");
	getline(std::cin, input);

	// TODO: rn it can only read sexp - just trying to read any primitive element will not work
	std::vector<std::string> lst;
	std::string wrd;
	for(int i = 0; i < input.size(); ++i) {
	    if(input[i] == '\'') {
		lst.push_back("'");
	    } else if(input[i] == '(') {
		lst.push_back("(");
	    } else if(input[i] == ')') {
		if(!wrd.empty()) {
		    lst.push_back(wrd);
		    wrd.clear();
		}
		lst.push_back(")");
	    } else if(input[i] == ' ') {
		if(!wrd.empty()) {
		    lst.push_back(wrd);
		    wrd.clear();
		}
	    } else {
		wrd += input[i];
	    }
	}

	for(int i = 0; i < lst.size(); ++i) {
	    printf("%s ", lst[i].c_str());
	}
	printf("\n");

	lval* ast = read(lst);
	print_lval(ast);
	print_lval(eval(ast, genv));
    }

    lenv_del(genv);
    
    return 0;
}

