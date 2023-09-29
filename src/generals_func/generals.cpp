#include "generals.h"

//======================================================================================

bool CheckNum (const char *str)
{
	assert (str != nullptr && "str is nullptr");

	if (str[0] == '-') str++;
	while (*str != '\0')
	{
		if (isdigit (*str) || *str == '.')
			str++;
		else
			return 0;
	}

	return 1;
}

//======================================================================================

void MyFlush ()
{
	char ch = 0;
	while ((ch = (char)getchar()) != EOF && ch != '\n')
			continue;

	return;
}

//======================================================================================

bool EqualityDouble (double num1, double num2){
    is_error (isfinite (num1));
    is_error (isfinite (num2));

    return fabs (num1-num2) < Eps;
}

bool IsZero (double num){
    is_error (isfinite (num));

    return EqualityDouble (num, 0);
}

//======================================================================================

double FixZero (double num){
    is_error (isfinite (num));

    if (IsZero (num))
        return 0.0;
    return num;
}

//======================================================================================

int ClearData (unsigned char *data, size_t size_data)
{
    assert (data != nullptr && "data is nullptr");

    for (size_t ip = 0; ip < size_data; ++ip)
        data[ip] = 0;

    return 0;
}

//======================================================================================

int BinRepresent(FILE *fpout, size_t elem, uint64_t size_elem)
{
	assert (fpout != nullptr && "fpot is nullptr");
	
    for (uint64_t num_bit = size_elem * 4; num_bit > 0; num_bit--) {
        fprintf(fpout, "%d", (elem & (1 << (num_bit-1))) ? 1 : 0);
    }

    return 0;
}

//======================================================================================

void PrintColour (char const colour[], char const *str, ...){
    printf ("%s", colour);

    va_list arg_ptr;

    va_start (arg_ptr, str);
    vprintf (str, arg_ptr);
    va_end (arg_ptr);

    printf ("%s", RESET);
}

//======================================================================================

FILE *OpenFilePtr (const char *name_file, const char *mode)
{
	assert (name_file != nullptr && "name open file is nullptr");
	assert (mode != nullptr && "specifier mod open file is nullptr");

    FILE *fp = fopen (name_file, mode);
    if (!fp){
		errno = ENOENT;
        fprintf (stderr, "Could't open file %s with mode: %s\n", name_file, mode);
		perror ("\n");

		return nullptr;
    }

    return fp;
}

//======================================================================================

char CloseFilePtr (FILE *fp)
{
	assert (fp != nullptr && "FILE is nullptr");

	if (fclose(fp)){
		fprintf (stderr, "FILE does not close %p\n", fp);
		return ERR_FILE_CLOSE;
	}

    return 0;
}

//======================================================================================

int OpenFileDescriptor (const char *name_file, const int mode)
{
	assert (name_file != nullptr && "name open file is nullptr");

	int fd = open (name_file, mode);
    if (fd < 0){
		errno = ENOENT;
        fprintf (stderr, "Could't get handel of file %s with mode: %d\n", name_file, mode);
		perror ("\n");

		return ERR_FILE_OPEN;
    }

    return fd;
}

//======================================================================================

char CloseFileDescriptor (int fd)
{
	assert (fd  >= 0 && "discriptor is a negative number");

	if (close(fd)){
		fprintf (stderr, "FILE does not close %d\n", fd);
		return ERR_FILE_CLOSE;
	}

    return 0;
}

//======================================================================================

int MySwap (void *obj1, void *obj2, size_t size_type)
{                         
    assert (obj1 != NULL && "obj1 is NULL");
	assert (obj2 != NULL && "obj2 is NULL");

	char* _obj1  = (char*) obj1;
	char* _obj2  = (char*) obj2;

	while (size_type >= sizeof (int64_t)) {
		int64_t temp       = *(int64_t*) _obj1;
		*(int64_t*) _obj1  = *(int64_t*) _obj2;
		*(int64_t*) _obj2  = temp;

		_obj1 += sizeof (int64_t);
		_obj2 += sizeof (int64_t);

		size_type -= sizeof (int64_t);
	}

	while (size_type >= sizeof (int32_t)) {
		int32_t temp       = *(int32_t*) _obj1;
		*(int32_t*) _obj1  = *(int32_t*) _obj2;
		*(int32_t*) _obj2  = temp;

		_obj1 += sizeof (int32_t);
		_obj2 += sizeof (int32_t);

		size_type -= sizeof (int32_t);
	}

	while (size_type >= sizeof (int16_t)) {
		int16_t temp       = *(int16_t*) _obj1;
		*(int16_t*) _obj1  = *(int16_t*) _obj2;
		*(int16_t*) _obj2  = temp;

		_obj1 += sizeof (int16_t);
		_obj2 += sizeof (int16_t);

		size_type -= sizeof (int16_t);
	}

	while (size_type >= sizeof (int8_t)) {
		int8_t temp       = *(int8_t*) _obj1;
		*(int8_t*) _obj1  = *(int8_t*) _obj2;
		*(int8_t*) _obj2  = temp;

		_obj1 += sizeof (int8_t);
		_obj2 += sizeof (int8_t);

		size_type -= sizeof (int8_t);
	}

	return 0;
}


//======================================================================================

char* MyStrndub (const char *str, const int len)
{
	assert (str != nullptr && "str is nullptr");
	assert (len > 0 && "len is not positive number");

	char *dup = (char*) calloc (len + 1, sizeof (char));

	if (!CheckNullptr (dup))
		dup = strncpy (dup, str, len);

	return dup;
}

//======================================================================================

size_t Factorial (const size_t ord)
{
	if (ord == 0)
		return 1;
	
	return ord * Factorial (ord - 1);
}

//========================================================================================

char* CreateVirtualBuf (const int fdin, const int prot, const off_t offset)
{
    assert (fdin > 0 && "file name is nullptr");   

    struct stat file_info = {};
    fstat (fdin, &file_info);

	off_t pa_offset  = offset * sysconf(_SC_PAGE_SIZE);
	size_t file_size = file_info.st_size;
	char *buf_ptr = (char*) mmap(nullptr, (file_size - offset) * sizeof (char), 
                                 prot, MAP_SHARED, fdin, pa_offset);

    if (buf_ptr == MAP_FAILED)
    {
        fprintf (stderr, "craete virtual buffer failed. "
                          "Buf_ptr = MAP_FAILED.\nDiscriptor: %d\n", fdin);
        return nullptr;
    }

    return buf_ptr;
}

//========================================================================================

int FreeVirtualBuf (const int fdin, char *virtual_buf)
{
    assert (virtual_buf != nullptr && "virtual_buf is nullptr");
    assert (fdin > 0 && "file name is nullptr");   
    

    struct stat file_info = {};
    fstat (fdin, &file_info);

    if (munmap (virtual_buf, file_info.st_size))
    {
        fprintf (stderr, "free virtual buffer failed.\nDiscriptor: %d\n", fdin);
		return ERR_FREE_VIRTUAL_BUF;
	}

    return 0;
}

//========================================================================================

char *CreateAlignedBuffer(const size_t alignment, const size_t size)
{
	char *buffer = (char*) aligned_alloc(alignment, size);
    if (CheckNullptr(buffer))
    {
        fprintf (stderr, "dynamic memory allocation by size = %lu, alignment = %lu- failed", 
													   size,	   alignment);
		return nullptr;
    }

    for (size_t id = 0; id < size; id++)
	{
        buffer[id] = 0;
	}
	
	return buffer;
}

//========================================================================================
