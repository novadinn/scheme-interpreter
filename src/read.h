#ifndef READ_H
#define READ_H

#include "lval.h"

#include <vector>
#include <string>

lval* read(const std::vector<std::string>& list);

lval* read_sexp(const std::vector<std::string>& list);
lval* read_qexp(const std::vector<std::string>& list);
lval* read_fn(const std::string& exp);
lval* read_num(const std::string& exp);
lval* read_sym(const std::string& exp);

bool sexp_p(const std::string& exp);
bool qexp_p(const std::string& exp);
bool fn_p(const std::string& exp);
bool num_p(const std::string& exp);
bool sym_p(const std::string& exp);

#endif // READ_H
