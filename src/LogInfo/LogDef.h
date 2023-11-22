#ifndef _LOG_DEF_H_
#define _LOG_DEF_H_

#define LOG_ARGS                                            \
    __FILE__, __PRETTY_FUNCTION__, __LINE__

#define LOG_PARAMETERS                                        \
    const char* file_name, const char* func_name, const int line

#define LOG_VAR                                             \
    file_name, func_name, line

#endif