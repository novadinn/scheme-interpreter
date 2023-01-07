#include <iostream>
#include <string>
#include <vector>

#include "lval.cpp"
#include "lenv.cpp"
#include "read.cpp"
#include "eval.cpp"
#include "builtins.cpp"

int main(int argc, char** argv) {
    lenv* genv = lenv_new();

    lenv_push(genv, "+", lval_fun(builtin_add, genv));
    lenv_push(genv, "-", lval_fun(builtin_sub, genv));
    lenv_push(genv, "*", lval_fun(builtin_mul, genv));
    lenv_push(genv, "/", lval_fun(builtin_div, genv));
    
    lenv_push(genv, "car", lval_fun(builtin_car, genv));
    lenv_push(genv, "cdr", lval_fun(builtin_cdr, genv));
    lenv_push(genv, "cons", lval_fun(builtin_cons, genv));
    
    lenv_push(genv, "define", lval_fun(builtin_define, genv));
    lenv_push(genv, "lambda", lval_fun(builtin_lambda, genv));
    
    lenv_push(genv, "if", lval_fun(builtin_if, genv));
    lenv_push(genv, "not", lval_fun(builtin_not, genv));
    lenv_push(genv, "and", lval_fun(builtin_and, genv));
    lenv_push(genv, "or", lval_fun(builtin_or, genv));
    
    lenv_push(genv, "even?", lval_fun(builtin_even, genv));
    lenv_push(genv, "odd?", lval_fun(builtin_odd, genv));
    lenv_push(genv, "zero?", lval_fun(builtin_zero, genv));
    lenv_push(genv, "=", lval_fun(builtin_e, genv));
    lenv_push(genv, ">=", lval_fun(builtin_ge, genv));
    lenv_push(genv, "<=", lval_fun(builtin_le, genv));
    lenv_push(genv, ">", lval_fun(builtin_g, genv));
    lenv_push(genv, "<", lval_fun(builtin_l, genv));

    lenv_push(genv, "boolean?", lval_fun(builtin_boolean, genv));
    lenv_push(genv, "integer?", lval_fun(builtin_integer, genv));
    lenv_push(genv, "list?", lval_fun(builtin_list, genv));
    lenv_push(genv, "atom?", lval_fun(builtin_atom, genv));
    lenv_push(genv, "null?", lval_fun(builtin_null, genv));
    lenv_push(genv, "pair?", lval_fun(builtin_pair, genv));
    lenv_push(genv, "procedure?", lval_fun(builtin_procedure, genv));
    lenv_push(genv, "string?", lval_fun(builtin_string, genv));
    lenv_push(genv, "symbol?", lval_fun(builtin_symbol, genv));    
   
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

