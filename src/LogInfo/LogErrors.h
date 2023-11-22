#ifndef _LOG_ERRORS_H_
#define _LOG_ERRORS_H_

#include <stdio.h>

#include "LogDef.h"

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



enum Errors 
{
    ERR_MEMORY_ALLOC        = -1,          ///< Memory is not allocated
    ERR_INIT_BUF            = -2,          ///< Buffer has not been initialized
    ERR_FILE_READING        = -3,          ///< Not all data was read from the file
    ERR_INIT_LINES          = -4,          ///< Lines does not initialize
    ERR_TEXT_READING        = -5,          ///< Text does not initialize
    
    ERR_FILE_OPEN           = -6,          ///< File is not open
    ERR_FILE_CLOSE          = -7,          ///< File is not close
    
    ERR_WRITING             = -8,          ///< Data writing failed
    ERR_READ                = -15,
    
    ERR_MANY_ARGUMENTS      = -9,          ///< Too many values on the command line
    ERR_PARSING             = -10,         ///< Parsing does not succeeded
    ERR_RE_ClEARING_MEMORY  = -13,
    ERR_NULLPTR             = -11,
    ERR_FREE_MEMORY         = -14,
    

    ERR_CREATE_VIRTUAL_BUF  = -16,
    ERR_FREE_VIRTUAL_BUF    = -17,
};

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