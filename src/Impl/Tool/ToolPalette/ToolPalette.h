#ifndef _TOOL_PALETTE_H_
#define _TOOL_PALETTE_H_

#include "Container/Container.h"
#include "Plug/Tool.h"
#include "Impl/Tool/PluginUtil.h"

class ToolPalette
{
    public:

        enum ToolType
        {
            UNKNOWN = -1,
            LAST = 10001,
        };

        ToolPalette():m_tools(){}
        
        ~ToolPalette()
        {
            size_t cnt = m_tools.getSize();
            for (size_t it = 0; it < cnt; it++)
            {
                if (m_tools[it]) m_tools[it]->release();
            }
        }

        void loadPlugins(Container<plug::Plugin*> &plugin_list);

        plug::Tool* getTool(const size_t tool_id);

        size_t getSize(){ return m_tools.getSize(); }

        ToolPalette(const ToolPalette &other) = delete;
        ToolPalette &operator= (const ToolPalette &other) = delete;
        
    private:
        Container<plug::Tool*> m_tools;

};

#endif