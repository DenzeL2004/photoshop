

#ifndef _PLUGIN_H_
#define _PLUGIN_H_

#include "../widgets/widget/widget.h"
#include "../widgets/window/canvas.h"

enum class PluginGuid 
{
    PLUGIN  = 0,
    TOOL    = 1,
    FILTER  = 2
};


class PluginData 
{
    public:
        
    virtual const char *getName() const = 0;
    virtual const char *getTexturePath() const = 0;
};


class Plugin 
{
    public:

    virtual Plugin *tryGetInterface(PluginGuid guid) = 0;
    virtual void addRef() = 0;
    virtual void release() = 0;
    virtual const PluginData *getPluginData() const = 0;
    virtual ~Plugin() = default;
};


class Filter : public Plugin 
{
    public:

    virtual void applyFilter(Canvas &canvas) const = 0;
    virtual Widget *getWidget() = 0;
};


#endif