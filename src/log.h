#ifndef LOG_H
#define LOG_H

#define LVAL_ASSERT(cond, fmt, ...)			\
    if (!(cond)) {					\
	lval* err = new_lval_err(fmt, ##__VA_ARGS__);	\
	return err;					\
    }
#define LTYPE_ASSERT(func, cur, index, expect)				\
    LVAL_ASSERT(cur == expect,						\
		"Function '%s' passed incorrect type for argument %i. Got %s, Expected %s.", \
		func, index, ltype_to_str(cur).c_str(),			\
		ltype_to_str(expect).c_str())
#define LNTYPE_ASSERT(func, cur, index, expect)				\
    LVAL_ASSERT(cur != expect,						\
		"Function '%s' passed incorrect type for argument %i.", \
		func, index)						\

#endif
