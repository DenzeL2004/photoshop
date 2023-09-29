#ifndef _LOG_ERRORS_H_
#define _LOG_ERRORS_H_

#include <stdio.h>

#include "log_def.h"

enum Log_errors
{
    OPEN_FILE_LOG_ERR  = -1, 
    CLOSE_FILE_LOG_ERR = -2    
};

#define USE_LOG


#ifdef USE_LOG
        
    #define LOG_REPORT(...)                            \
        Log_report_ (LOG_ARGS, __VA_ARGS__)


#else

    #define LOG_REPORT(...)           

#endif


#define ERR_REPORT(...)                                             \
        Err_report_ (LOG_ARGS, __VA_ARGS__)

#define PROCESS_ERROR(error, ...)                                   \
        Process_error_ (#error, error, LOG_ARGS, __VA_ARGS__)                              


int OpenLogsFile ();

int CloseLogsFile ();

FILE *GetLogFilePtr ();


int Log_report_ (const char* file_name, const char* func_name, 
                 int line, const char *format, ...);


int Err_report_ (const char* file_name, const char* func_name, 
                 int line, const char *format, ...);

int Process_error_ (const char* error_name, const int error_val, 
                    const char* file_name, const char* func_name, const int line, const char *format, ...);


#endif // #endif _LOG_ERRORS_H_