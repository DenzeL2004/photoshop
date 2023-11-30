#ifndef _PLUGIN_UTIL_H_
#define _PLUGIN_UTIL_H_

#include <dlfcn.h>
#include <cassert>

#include "Plug/Plugin.h"

static const char* Load_plug_sym = "loadPlugin";

plug::Plugin* loadPlugin(const char *dll_path);

#endif