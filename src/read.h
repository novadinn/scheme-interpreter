#ifndef READ_H
#define READ_H

#include "lval.h"

#include <vector>
#include <string>

lval* read(const std::vector<std::string>& lst);

lval* read_sexp(const std::vector<std::string>& lst);
lval* read_qexp(const std::vector<std::string>& lst);
lval* read_num(const std::string& exp);
lval* read_sym(const std::string& exp);
lval* read_str(const std::string& exp);

bool sexp_p(const std::string& exp);
bool qexp_p(const std::string& exp);
bool num_p(const std::string& exp);
bool sym_p(const std::string& exp);
bool str_p(const std::string& exp);

std::vector<std::string> next_token(const std::vector<std::string>& lst, int s, int m);

#endif // READ_H
