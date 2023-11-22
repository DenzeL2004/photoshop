#include <stdio.h>
#include <time.h>
#include <stdarg.h>

#include "LogInfo/LogErrors.h"

static FILE *fp_logs = nullptr;

//=======================================================================================================

int OpenLogsFile ()
{    
    fp_logs = fopen("temp/log_info.html", "a");

    if (!fp_logs)
    {
        fprintf (stderr, "Logs file does not open\n");
        return 0;
    }

    fprintf (fp_logs, "<pre>\n");

    fprintf (fp_logs, "\n----------------------------------------------------\n");

    time_t seconds = time (NULL)  + 3 * 60* 60;
    fprintf (fp_logs, "Time open logs file: %s\n\n", asctime(gmtime(&seconds)));

    return 0;
}

//=======================================================================================================

int Process_error_ (const char* error_name, const int error_val, 
                    const char* file_name, const char* func_name, const int line, const char *format, ...) 
{ 
    #ifdef USE_LOG

        fprintf (fp_logs, "==========================================================\n\n");

        fprintf (fp_logs, "Error %s (%d) \n", error_name, error_val);

        fprintf (fp_logs, "In file %s\n", file_name);
        fprintf (fp_logs, "In function %s\n", func_name);
        fprintf (fp_logs, "In line %d\n\n", line);
    
    #endif 

    va_list args = {};
   
    va_start(args, format);

    #ifdef USE_LOG
    
        vfprintf(fp_logs, format, args);
        
        fprintf (fp_logs, "==========================================================\n\n\n");
    
    #endif

    fprintf (stderr, "||ERROR ERROR ERROR||\n");

    fprintf (stderr, "In file %s, ", file_name);
    fprintf (stderr, "In function %s, ", func_name);
    fprintf (stderr, "In line %d: ", line);

    va_start(args, format);

    vfprintf(stderr, format, args);

    fprintf (stderr, "\n\n");
    
    va_end(args);
    
    return error_val; 
}

//=======================================================================================================

int Log_report_ (const char* file_name, const char* func_name, int line, const char *format, ...) 
{ 
    fprintf (fp_logs, "==========================================================\n\n");

    fprintf (fp_logs, "SHORT REFERENCE:\n");

    fprintf (fp_logs, "The program returned an error in\n\n");

    fprintf (fp_logs, "In file %s\n", file_name);
    fprintf (fp_logs, "In function %s\n", func_name);
    fprintf (fp_logs, "In line %d\n\n", line);
    
    va_list args = {};
   
    va_start(args, format);

    vfprintf(fp_logs, format, args);
    
    va_end(args);

    fprintf (fp_logs, "==========================================================\n\n\n");

    return 0;                                                       
}

//=======================================================================================================

int Err_report_ (const char* file_name, const char* func_name, int line, const char *format, ...) 
{ 

    fprintf (stderr, "||ERROR ERROR ERROR||\n");

    fprintf (stderr, "In file %s\n", file_name);
    fprintf (stderr, "In function %s\n", func_name);
    fprintf (stderr, "In line %d\n\n", line);
    
    va_list args = {};
   
    va_start(args, format);

    vfprintf(stderr, format, args);
    
    va_end(args);
    
    return 0;                                                       
}

//=======================================================================================================

FILE *GetLogFilePtr ()
{
    return fp_logs;
}

//=======================================================================================================

int CloseLogsFile ()
{
    time_t seconds = time (NULL)  + 3 * 60* 60;;   

    fprintf (fp_logs, "\n----------------------------------------------------\n");
    fprintf (fp_logs, "Time close logs file: %s\n\n", asctime(gmtime(&seconds)));
    
    if (fclose(fp_logs))
    {
        fprintf (stderr, "Logs file does not close\n");
        return ERR_FILE_OPEN;
    }

    return 0;
}