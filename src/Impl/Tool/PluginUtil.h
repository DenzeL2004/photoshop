#ifndef _PLUGIN_UTIL_H_
#define _PLUGIN_UTIL_H_

//#define DEBUG_PALGINS

#include <dlfcn.h>
#include <cassert>
#include <iostream>
#include <cstdio>

#include "Plug/Plugin.h"
#include "Plug/Tool.h"
#include "Plug/Filter.h"


static const char* Load_plug_sym = "loadPlugin";

plug::Plugin* loadPlugin(const char *dll_path);

class BaseData : public plug::PluginData
{
    public:
        BaseData(const char *name, const char *texture_path):
        m_name(name), 
        m_texture_path(texture_path){}

        BaseData():BaseData("ERORR", "ERRORR_PATH"){}

    virtual const char *getName(void) const { return m_name;}
    virtual const char *getTexturePath(void) const { return m_texture_path; }

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

    private:
        size_t m_cnt_reference;
        const BaseData m_data;
};


#endif