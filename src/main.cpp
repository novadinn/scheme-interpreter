#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <editline/readline.h>
#include <editline/history.h>

#include "lval.cpp"
#include "lenv.cpp"
#include "eval.cpp"
#include "read.cpp"
#include "builtins.cpp"

int main(int argc, char** argv) {
    lenv* global_env = new_lenv();
    
    while (true) {
	char* input = readline("scheme> ");
	add_history(input);
	
	std::istringstream iss(input);
	std::vector<std::string> list(std::istream_iterator<std::string>{iss},
					 std::istream_iterator<std::string>());

	// TODO: ( + 1 2 ) will not work - we need remove those spaced by hand
	std::vector<std::string> results;
	for(int i = 0; i < list.size(); ++i) {
	    std::string exp = list[i];

	    for(int j = 0; j < exp.size(); ++j) {
		if(exp[j] == '(') {
		    exp.erase(j--, 1);
		    results.push_back("(");
		} else if(exp[j] == '\'') {
		    exp.erase(j--, 1);
		    results.push_back("'");
		}
	    }

	    int nc = 0;
	    for(int j = 0; j < exp.size(); ++j) {
		if(exp[j] == ')') {
		    nc++;
		    exp.erase(j--, 1);
		}
	    }
	    
	    results.push_back(exp);

	    for(int j = 0; j < nc; ++j) {
		results.push_back(")");
	    }
	}

	for(int j = 0; j < results.size(); ++j) {
	    printf("%s ", results[j].c_str());
	}
	printf("\n");

	lval* exp = read(results);
	print_lval(exp);
	print_lval(eval(exp, global_env));
	
	free(input);
    }
    
    return 0;
}
