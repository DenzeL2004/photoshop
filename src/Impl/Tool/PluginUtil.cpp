#include "PluginUtil.h"
#include "LogInfo/LogErrors.h"

typedef plug::Plugin* (*LoadPlugin)(void);

plug::Plugin* loadPlugin(const char *dll_path)
{
    assert(dll_path != nullptr && "path is nullptr");

    void *library = dlopen(dll_path, RTLD_LAZY | RTLD_LOCAL | RTLD_NODELETE);
    if (!library)
    {
        PROCESS_ERROR(ERR_FILE_OPEN, "failed open dll library by %s", dll_path);
        assert(0);
    }
    
    LoadPlugin load_plug = reinterpret_cast<LoadPlugin>(dlsym(library, Load_plug_sym));
    if (!load_plug)
    {
        PROCESS_ERROR(ERR_FILE_OPEN, "failed get plugin by %s", dll_path);
        assert(0);
    }

    plug::Plugin* plugin = (*load_plug)();
    if (!plugin)
    {
        PROCESS_ERROR(ERR_FILE_OPEN, "plugin is nullptr by %s", dll_path);
        assert(0);
    }

    if (dlclose(library) < 0)
    {
        PROCESS_ERROR(ERR_FILE_CLOSE, "failed close library by %s", dll_path);
        assert(0);
    }   

    return plugin;
}