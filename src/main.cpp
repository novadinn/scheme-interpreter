#include <iostream>
#include <string>
#include <vector>

#include "math.cpp"
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

    lenv_push(genv, "list", lval_fun(builtin_list, genv));
    lenv_push(genv, "car", lval_fun(builtin_car, genv));
    lenv_push(genv, "cdr", lval_fun(builtin_cdr, genv));
    lenv_push(genv, "cons", lval_fun(builtin_cons, genv));
    
    lenv_push(genv, "define", lval_fun(builtin_define, genv));
    lenv_push(genv, "lambda", lval_fun(builtin_lambda, genv));
    
    lenv_push(genv, "if", lval_fun(builtin_if, genv));
    lenv_push(genv, "not", lval_fun(builtin_not, genv));
    lenv_push(genv, "and", lval_fun(builtin_and, genv));
    lenv_push(genv, "or", lval_fun(builtin_or, genv));
    
    lenv_push(genv, "=", lval_fun(builtin_e, genv));
    lenv_push(genv, ">=", lval_fun(builtin_ge, genv));
    lenv_push(genv, "<=", lval_fun(builtin_le, genv));
    lenv_push(genv, ">", lval_fun(builtin_g, genv));
    lenv_push(genv, "<", lval_fun(builtin_l, genv));

    lenv_push(genv, "even?", lval_fun(builtin_even_p, genv));
    lenv_push(genv, "odd?", lval_fun(builtin_odd_p, genv));
    lenv_push(genv, "zero?", lval_fun(builtin_zero_p, genv));
    lenv_push(genv, "boolean?", lval_fun(builtin_boolean_p, genv));
    lenv_push(genv, "integer?", lval_fun(builtin_integer_p, genv));
    lenv_push(genv, "list?", lval_fun(builtin_list_p, genv));
    lenv_push(genv, "atom?", lval_fun(builtin_atom_p, genv));
    lenv_push(genv, "null?", lval_fun(builtin_null_p, genv));
    lenv_push(genv, "pair?", lval_fun(builtin_pair_p, genv));
    lenv_push(genv, "procedure?", lval_fun(builtin_procedure_p, genv));
    lenv_push(genv, "string?", lval_fun(builtin_string_p, genv));
    lenv_push(genv, "symbol?", lval_fun(builtin_symbol_p, genv));

    lenv_push(genv, "abs", lval_fun(builtin_abs, genv));
    lenv_push(genv, "expt", lval_fun(builtin_expt, genv));
    lenv_push(genv, "modulo", lval_fun(builtin_modulo, genv));
    lenv_push(genv, "quotient", lval_fun(builtin_quotient, genv));
    lenv_push(genv, "remainder", lval_fun(builtin_remainder, genv));

    lenv_push(genv, "begin", lval_fun(builtin_begin, genv));
    lenv_push(genv, "display", lval_fun(builtin_display, genv));
    lenv_push(genv, "error", lval_fun(builtin_error, genv));
    lenv_push(genv, "newline", lval_fun(builtin_newline, genv));

    lenv_push(genv, "eq?", lval_fun(builtin_eq_p, genv));
    lenv_push(genv, "equal?", lval_fun(builtin_equal_p, genv));
    lenv_push(genv, "set!", lval_fun(builtin_set, genv));
    lenv_push(genv, "set-car!", lval_fun(builtin_set_car, genv));
    lenv_push(genv, "set-cdr!", lval_fun(builtin_set_cdr, genv));
    
    while (true) {
	std::string input;

	printf("scheme> ");
	getline(std::cin, input);
	
	std::vector<std::string> lst = tokenize(input);
	// TODO: check for syntax correctness in here
	lval* ast = read(lst);
	lval* v = eval(ast, genv);
	print_lval(v);
    }

    lenv_del(genv);
    
    return 0;
}

