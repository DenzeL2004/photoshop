#include "ToolPalette.h"

void ToolPalette::loadPlugins(Container<plug::Plugin*> &plugin_list)
{
    size_t cnt_plugins = plugin_list.getSize();
    for (size_t it = 0; it < cnt_plugins; it++)
    {
        plug::Tool *tool = static_cast<plug::Tool*>(plugin_list[it]->tryGetInterface(static_cast<size_t>(plug::PluginGuid::Tool)));
        if (tool)
        {
            m_tools.pushBack(tool);
        }
    }
}


plug::Tool* ToolPalette::getTool(const size_t tool_id)
{
    size_t cnt = m_tools.getSize();
    if (tool_id >= cnt) return nullptr;

    plug::Plugin *ret_tool = m_tools[tool_id]->tryGetInterface(static_cast<size_t>(plug::PluginGuid::Tool));
    return reinterpret_cast<plug::Tool*>(ret_tool);
}
