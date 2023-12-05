#ifndef _PLUGIN_UTIL_H_
#define _PLUGIN_UTIL_H_

//#define DEBUG_PALGINS

#include <dlfcn.h>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>


#include "Plug/Plugin.h"
#include "Plug/Tool.h"
#include "Plug/Filter.h"

#include "Container/Container.h"

static const char Load_plug_sym[] = "loadPlugin";
static const char Plugin_dir_name[] = "Plugins\0";
static const size_t Max_path_len = 100;

plug::Plugin* loadPlugin(const char *dll_path);

void loadePlugins(Container<plug::Plugin*> &plugins);

class BaseData : public plug::PluginData
{
    public:
        BaseData(const char *name, const char *texture_path):
        m_name(name), 
        m_texture_path(texture_path){}

        BaseData():BaseData("ERORR", "ERRORR_PATH"){}

    virtual const char *getName(void) const { return m_name;}
    virtual const char *getTexturePath(void) const { return m_texture_path; }

    BaseData(const BaseData &other) = delete;
    BaseData &operator= (const BaseData &other) = delete;

    private:
        const char* m_name;
        const char* m_texture_path;
};

class DefFilter : public plug::Filter
{
    public:
        DefFilter(const char *name, const char *texture_path):
                m_cnt_reference(1), 
                m_data(name, texture_path){}

        virtual plug::Plugin *tryGetInterface(size_t interface_id) 
        {
            switch (interface_id)
            {
                case static_cast<size_t>(plug::PluginGuid::Plugin):
                {
                    addReference();
                    return static_cast<plug::Plugin*>(this);
                }

                case static_cast<size_t>(plug::PluginGuid::Filter):
                {
                    addReference();
                    return static_cast<plug::Filter*>(this);
                }

                default:
                    return nullptr;
            }
        }

        virtual void addReference(void)
        {
            m_cnt_reference++;
        }
        
        virtual void release(void)
        {
            m_cnt_reference--;

            if (m_cnt_reference == 0)
            {
                delete this;
            }
        }

        virtual const plug::PluginData *getPluginData(void) const 
        {
            return &m_data;
        }

        virtual ~DefFilter() = default;

        DefFilter(const DefFilter &other) = delete;
        DefFilter &operator= (const DefFilter &other) = delete;

    private:
        size_t m_cnt_reference;
        const BaseData m_data;
};

class DefTool : public plug::Tool
{
    public:
        DefTool(const char *name, const char *texture_path):
                m_cnt_reference(1), 
                m_data(name, texture_path){}

        virtual plug::Plugin *tryGetInterface(size_t interface_id) 
        {
            switch (interface_id)
            {
                case static_cast<size_t>(plug::PluginGuid::Plugin):
                {
                    addReference();
                    return static_cast<plug::Plugin*>(this);
                }

                case static_cast<size_t>(plug::PluginGuid::Tool):
                {
                    addReference();
                    return static_cast<plug::Tool*>(this);
                }

                default:
                    return nullptr;
            }
        }

        virtual void addReference(void)
        {
            m_cnt_reference++;
        }
        
        virtual void release(void)
        {
            m_cnt_reference--;

            if (m_cnt_reference == 0)
            {
                delete this;
            }
        }

        virtual const plug::PluginData *getPluginData(void) const 
        {
            return &m_data;
        }

        virtual ~DefTool() = default;

        DefTool(const DefTool &other) = delete;
        DefTool &operator= (const DefTool &other) = delete;

    private:
        size_t m_cnt_reference;
        const BaseData m_data;
};


#endif