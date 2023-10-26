#ifndef _APP_H_
#define _APP_H_


#include "../widget/window/canvas.h"
#include "../widget/button/button.h"
#include "../widget/window/tools/tools.h"
#include "../widget/window/filters/filter.h"

#include "config.h"

class AddCanvase : public Action
{
    public:
        AddCanvase(CanvasManager *canvase_manager, ToolPalette *palette, FilterPalette *filter_palette): 
                   canvase_manager_(canvase_manager), tool_palette_(*palette), filter_palette_(*filter_palette){};
        ~AddCanvase(){};

        void operator() () const
        {
            canvase_manager_->CreateCanvase(&tool_palette_, &filter_palette_);   
        }

    private:
        CanvasManager *canvase_manager_;
        ToolPalette &tool_palette_; 
        FilterPalette &filter_palette_; 
};

class ChooseTool : public Action
{
    public:
        ChooseTool(ToolPalette::ToolType type, ToolPalette *palette): 
                    palette_(*palette), type_(type){};
        ~ChooseTool(){};

        void operator() () const
        {
            palette_.SetActiveTool(type_);
        }

    private:
        ToolPalette &palette_;
        ToolPalette::ToolType type_;
};

class ChooseColor : public Action
{
    public:
        ChooseColor(sf::Color color, ToolPalette *palette_color): 
                    palette_(*palette_color), color_(color) {};
        ~ChooseColor(){};

        void operator() () const
        {
            palette_.SetActiveColor(color_);   
        }

    private:
        ToolPalette &palette_;
        sf::Color color_;
        
};


class AppWindow: public Window
{
    public:
        AppWindow (const char *path_texture,
                   const Dot &offset, const Vector &scale);

        virtual ~AppWindow()
        {
            delete button_create_;
            delete tools_button_;
            delete colors_button_;
        }

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) override;  

        virtual void PassTime           (const time_t delta_time);

    protected:
        
        CanvasManager canvas_manager_;
        Button *button_create_;
        WidgetContainer *tools_button_;
        ButtonList *colors_button_;

        ToolPalette tool_pallette_;

        FilterPalette filter_pallette_;
};


void UseApp();

#endif