/* Template by Quentin Perez : https://github.com/QuentinPerez */

#ifndef M_ERROR_HPP
# define M_ERROR_HPP

# include <stdarg.h>
# include <iostream>
# include <execinfo.h>
# include <sstream>
# include <string>

# define M_ERROR(ret, fmt, args...)	mf_error(ret, __func__, __FILE__, __LINE__, fmt, ##args)

template <typename T>
T
mf_error(T ret, const char *func, const char *file, const int line, const char *fmt, ...) {
    va_list ap;
    void    *stack[40];
    size_t  size;
    char    **trace;

    size = backtrace(stack, 40);
    if ((trace = backtrace_symbols(stack, size)) != NULL) {
        for (size_t i = 2; i < size - 1; ++i) {
            std::istringstream  value;
            std::string         string;

            string = trace[i];
            value.str(string);
            value >> string; value >> string; value >> string; value >> string;
            std::cout << "\t→\t"<< string << "()" << std::endl;
        }
        delete trace;
    }
    va_start(ap, fmt);
    std::cerr << "\033[0;37m" << file << ", line \033[1;33m" << line << ": \033[1;37m" << func << "()" << std::endl << "\033[1;31m→\t" << std::flush;
    vfprintf(stderr, fmt, ap);
    std::cerr << ".\033[0;0m" << std::endl;
    va_end(ap);
    return (ret);
}

#endif
