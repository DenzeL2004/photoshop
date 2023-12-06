#include "PluginUtil.h"
#include "LogInfo/LogErrors.h"

typedef plug::Plugin* (*LoadPlugin)(void);


static void findDLLinDir    (const char *path, Container<plug::Plugin*> &plugins);
static void findDLL         (const char *path, Container<plug::Plugin*> &plugins);
static void checkIsDLL      (const char *path, Container<plug::Plugin*> &plugins);

plug::Plugin* loadPlugin(const char *dll_path)
{
    assert(dll_path != nullptr && "path is nullptr");

    void *library = dlopen(dll_path, RTLD_LAZY | RTLD_LOCAL | RTLD_NODELETE);
    if (!library)
    {
        PROCESS_ERROR(ERR_FILE_OPEN, "failed open dll library by %s", dll_path);
        assert(0 && "failed open dll library");
    }
    
    LoadPlugin load_plug = reinterpret_cast<LoadPlugin>(dlsym(library, Load_plug_sym));
    if (!load_plug)
    {
        PROCESS_ERROR(ERR_FILE_OPEN, "failed get plugin by %s", dll_path);
        assert(0 && "failed get plugin");
    }

    plug::Plugin* plugin = (*load_plug)();
    if (!plugin)
    {
        PROCESS_ERROR(ERR_FILE_OPEN, "plugin is nullptr by %s", dll_path);
        assert(0 && "plugin is nullptr");
    }

    if (dlclose(library) < 0)
    {
        PROCESS_ERROR(ERR_FILE_CLOSE, "failed close library by %s", dll_path);
        assert(0 && "failed close library by");
    }   

    return plugin;
}

void loadePlugins(Container<plug::Plugin*> &plugins)
{
    findDLL(Plugin_dir_name, plugins);    
}

static void findDLLinDir(const char *path, Container<plug::Plugin*> &plugins)
{
    assert(path != NULL && "file's path is nullptr");

    size_t path_len = strlen(path);
    
    char *full_path = static_cast<char*>(calloc(Max_path_len, sizeof(char)));
    if (full_path == nullptr) 
    {
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Allocate memmory failed\n");
        return;
    }
        
    strcat(full_path, path);    

    DIR* dir = opendir(path);
    if (dir == nullptr)
    {
        PROCESS_ERROR(ERR_FILE_OPEN, "Open dir by file: %s, failed, errno = %d\n", path, errno);
        return;
    }

    struct dirent *file = nullptr;
    while ((file = readdir(dir)) != nullptr)
    {
        if (!strcmp(file->d_name, "."))  continue;
        if (!strcmp(file->d_name, "..")) continue;

        sprintf(full_path + path_len, "/%s%c", file->d_name, '\0');
        findDLL(full_path, plugins);
    }

    free(full_path);

    if (closedir(dir))
    {
        PROCESS_ERROR(ERR_FILE_CLOSE, "Failed close dir: %s, errno = %d\n", path, errno);
        return;
    }
}

static void findDLL(const char *path, Container<plug::Plugin*> &plugins)
{
    assert (path != nullptr && "path is nullptr");

    struct stat file_info;
    if (lstat(path, &file_info))
    {
        PROCESS_ERROR(ERR_FILE_READING, "lstat file: \'%s\' failed, errno =  %d\n", path, errno);
    }

    if (S_ISDIR(file_info.st_mode))
        findDLLinDir(path, plugins);
    else
        checkIsDLL(path, plugins);
}

static void checkIsDLL(const char *path, Container<plug::Plugin*> &plugins)
{
    assert (path != nullptr && "path is nullptr");

    size_t len = strlen(path);
    if (path[len - 2] == 's' && path[len - 1] == 'o')
    {
        plugins.pushBack(loadPlugin(path));
    }
}


