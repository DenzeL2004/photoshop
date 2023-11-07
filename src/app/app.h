#ifndef _APP_H_
#define _APP_H_

#include "../widgets/widget/widget.h"
#include "../widgets/window/window.h"
#include "../widgets/button/button.h"
#include "../widgets/decorator/decorator.h"

#include "../widgets/window/tools/tools.h"
#include "../widgets/window/filters/filter.h"
#include "../widgets/window/color_palette/color_palatte.h"

#include "../widgets/window/canvas.h"

#include "config.h"

class AddCanvase : public Action
{
    public:
        AddCanvase(CanvasManager *canvase_manager, ToolPalette *palette, FilterPalette *filter_palette): 
                   canvase_manager_(canvase_manager), tool_palette_(*palette), filter_palette_(*filter_palette){};
        ~AddCanvase(){};

        void operator() () const
        {
            canvase_manager_->createCanvas(&tool_palette_, &filter_palette_);   
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
            palette_.setActiveTool(type_);
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
            palette_.setActiveColor(color_);   
        }

    private:
        ToolPalette &palette_;
        sf::Color color_;    
};

class ChangeBrightness : public Action
{
    public:
        ChangeBrightness(FilterPalette *filter_palette, CanvasManager *manager, const float delta): 
                    filter_palette_(*filter_palette), canvas_manager_(*manager), delta_(delta) {};
        ~ChangeBrightness(){};

        void operator() () const
        {
            FilterBrightness *filter  = (FilterBrightness*)filter_palette_.getFilter(FilterPalette::FilterType::LIGHT);
            filter_palette_.setLastFilter(FilterPalette::FilterType::LIGHT);

            filter->setDelta(delta_);

            Canvas *active_canvas = canvas_manager_.getActiveCanvas();
            filter->applyFilter(*active_canvas, active_canvas->getFilterMask());

        }


    private:
        FilterPalette &filter_palette_;
        CanvasManager &canvas_manager_;
       
        float delta_;
        
};


class AppWindow: public Window
{
    public:
        AppWindow(  const char *path_texture,
                    const Vector &size, const Vector &pos, 
                    const Widget *parent, const Vector &parent_size = Vector(1.0, 1.0), 
                    const Vector &origin = Vector(0.0, 0.0), const Vector &scale = Vector(1.0, 1.0));

        virtual ~AppWindow()
        {
            delete button_create_;
            delete tools_button_;
            delete colors_button_;
        }

        virtual bool onMousePressed     (const Vector &pos, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool onMouseMoved       (const Vector &pos, Container<Transform> &stack_transform);
        virtual bool onMouseReleased    (const Vector &pos, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool onKeyboardPressed  (const KeyboardKey);
        virtual bool onKeyboardReleased (const KeyboardKey);

        virtual void draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) override;  

        virtual bool onTick             (const time_t delta_time);

    protected:
        
        CanvasManager canvas_manager_;
        Button *button_create_;

        ButtonList *tools_button_;
        ButtonList *colors_button_;

        ToolPalette tool_pallette_;

        ButtonList *filters_button_;
        FilterPalette filter_pallette_;

        ColorPalette *colors_;
};


void useApp();

#endif