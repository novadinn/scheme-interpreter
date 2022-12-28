#ifndef READ_H
#define READ_H

#include <vector>
#include <string>

#include "lval.h"

lval* read(const std::vector<std::string>& list);

std::vector<std::vector<std::string>> form_lists(const std::vector<std::string>& list);
std::vector<std::string> unwrap_list(const std::vector<std::string>& list);

int rm_occurs(std::string& s, char c);
bool is_number(const std::string& s);

#endif // READ_H
