#include "LogInfo/LogErrors.h"
#include "App/App.h"

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