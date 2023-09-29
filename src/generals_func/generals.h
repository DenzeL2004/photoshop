#ifndef _GENERALS_H_
#define _GENERALS_H_

#include <assert.h>

#include <errno.h>	

#include <math.h>

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

#include <time.h>

#include <ctype.h>
#include <fcntl.h>


#include <sys/mman.h>
#include <sys/stat.h>

#include <syscall.h>

#include <immintrin.h>


#define MIN(a, b) ((a) < (b) ? (а) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * @def is_error
 * @brief Checks for false input conditions
 * @note This define does not terminate the program in case of an error like assert
*/
#define is_error(condition) {                                           \
    if (!(condition))                                                   \
        printf ("ERROR in %s in line %d in file %s in function %s\n",   \
                #condition, __LINE__, __FILE__, __PRETTY_FUNCTION__);   \
}

#define BYTE 1
#define DWORD 4

#define FALSE 0
#define TRUE 1

const char RESET[]  =     "\033[0m";     ///< Standart colour
const char RED[]    =  "\033[1;31m";     ///< Red colour
const char BLUE[]   =  "\033[1;36m";     ///< Blue colour
const char GREEN[]  =  "\033[1;32m";     ///< Green colour
const char YELLOW[] =  "\033[1;33m";     ///< Yellow colour

static const long double Eps = 1e-10; ///< Global constant equal to \f$\ 10^{-9}\f$

static const int Inf = 1e9+7; 

static const int Init_buffer = 100;

/**
 * @enum Errors
 * @brief Represents the status of errors
*/
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

enum Comparison
{
    DIFFERENT = -1,
    EQUAL     =  0
};


inline bool CheckNullptr  (void *ptr)
{
	return (ptr == nullptr);
}

inline int Dump_func (int val)
{
    return val;
}

void    MyFlush();

bool    CheckNum        (const char *str);

/** 
 * @brief Comparison of double variables
 * @version 1.0.0
 * @param [in] num1 input double parameter
 * @param [in] num2 input double parameter
 * @return False - number is not equal, true - number is equal
*/
bool    EqualityDouble  (double num1, double num2);

/** 
 * @brief Comparing a number to zero
 * @version 1.0.0
 * @param [in] n input parameter
 * @return False - number is not zero, true - number is zero
*/
bool    IsZero          (double num);

/** 
 * @brief Correct zero value
 * @version 1.0.0
 * @param [in] n input parameter
 * @note If the value is zero the program must not return -0.00
 * @return Returns zero if the number is zero, otherwise returns the number itself
*/
double  FixZero         (double num);

int     BinRepresent    (FILE *fpout, size_t elem, uint64_t size_elem);

int     ClearData       (unsigned char *cmd_hash_tabel, size_t size_data);

/** 
 * @brief Paints a line
 * @version 1.0.0
 * @param [in] colour colour you want to paint a string
 * @param [in] str line to be colored
*/
void    PrintColour     (char const colour[], char const *str, ...);

/**
 * @brief Opens a file in a specific mode
 * @param [in] name_file Name of file 
 * @param [in] mode Open file access modes
 * @return Pointer on file 
 */
FILE*   OpenFilePtr     (const char *name_file, const char *mode);

/**
 * @brief Close a file
 * @param [in] fp Pointer of file 
 * @return Zero - if closing happened without error 
 */
char    CloseFilePtr        (FILE *fp);

int     OpenFileDescriptor  (const char *name_file, const int mode);

char    CloseFileDescriptor (int fd);

/**
 * @brief Swaps the values of variables
 * @param obj1 [in] first variable
 * @param obj2 [in] second variable
 * @param size_type [in] size of variables in bytes
 * @return Returns zero if the variables have changed values 
 */
int     MySwap              (void *obj1, void *obj2, size_t size_type);

char*   MyStrndub           (const char *str, const int len);

size_t  Factorial           (const size_t ord);

char*   CreateVirtualBuf    (const int fdin, const int prot, const off_t offset);

int     FreeVirtualBuf      (const int fdin, char *virtual_buf);

char*   CreateAlignedBuffer (const size_t alignment, const size_t size);


#endif
