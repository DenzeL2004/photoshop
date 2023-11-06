#include <stdio.h>



#include "src/app/app.h"

const double WIDTH = 1600.0; 
const double HEIGHT = 900.0;

int main()
{
     #ifdef USE_LOG
        if (OpenLogsFile())
            return OPEN_FILE_LOG_ERR;
    #endif

    useApp();
    
    #ifdef USE_LOG
        if (CloseLogsFile ())
            return OPEN_FILE_LOG_ERR;
    #endif

    return EXIT_SUCCESS;
}