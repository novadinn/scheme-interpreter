#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <editline/readline.h>
#include <editline/history.h>

#include "lval.cpp"
#include "read.cpp"
#include "lenv.cpp"

int main(int argc, char** argv) {
    while (true) {
	char* input = readline("scheme> ");
	add_history(input);
	
	std::istringstream iss(input);
	std::vector<std::string> list(std::istream_iterator<std::string>{iss},
					 std::istream_iterator<std::string>());

	std::vector<std::string> results;
	for(int i = 0; i < list.size(); ++i) {
	    std::string exp = list[i];
	    
	    int paran = rm_occurs(exp, '(');
	    for(int j = 0; j < paran; ++j) {
		results.push_back("(");
	    }

	    paran = rm_occurs(exp, ')');
	    results.push_back(exp);

	    for(int j = 0; j < paran; ++j) {
		results.push_back(")");
	    }
	}

	lenv* global_env = new_lenv();
	lval* num = new_lval_num(15);
	push_lenv(global_env, num, "x");
	lval* exp = read(results);
	print_lval(exp);
	std::cout << eval(exp, global_env)->num << std::endl;
	
	free(input);
    }
    
    return 0;
}
