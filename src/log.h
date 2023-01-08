#ifndef LOG_H
#define LOG_H

#define LASSERT(cond, fmt, ...)						\
    if (!(cond)) { lval* err = lval_err(fmt, ##__VA_ARGS__); return err; }
#define LASSERT_TYPE(func, index, got, expect)				\
    LASSERT(got == expect,						\
	    "Function '%s' passed incorrect type for argument %i. Got %s, Expected %s", \
	    func, index, ltype_to_str(got).c_str(), ltype_to_str(expect).c_str())
#define LASSERT_ARGC(func, lst, num)					\
    LASSERT(lst.size() == num,						\
	    "Function '%s' passed incorrect number of arguments. Got %i, Expected %i", \
	    func, lst.size(), num)
#define LASSERT_NOT_EMPTY(func, lst, index)				\
    LASSERT(lst.size() != 0,						\
	    "Function '%s' passed () for argument %i", func, index)
#define LASSERT_W_ERROR(val)			\
    if(val->type == ltype::ERR)			\
	return val;

#endif // LOG_H
