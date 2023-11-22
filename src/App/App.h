#ifndef _APP_H_
#define _APP_H_

#include "Plug/Math.h"

#include "Impl/Graphics/RenderTarget/SfmlRenderTarget/RenderTarget.h"
#include "Impl/Graphics/Graphic.h"

#include "Impl/Widget/Widget.h"

#include "Impl/LayoutBox/BaseLayoutBox/BaseLayoutBox.h"

#include "Impl/TransformStack/TransformStack.h"

#include "AppConfig.h"

#include "Impl/Widget/Window/Window.h"
#include "Impl/Widget/Frame/Frame.h"
#include "Impl/Widget/Button/Button.h"

// class AddCanvase : public Action
// {
//     public:
//         AddCanvase(CanvasManager *canvase_manager, ToolPalette *palette, FilterPalette *filter_palette): 
//                    canvase_manager_(canvase_manager), tool_palette_(*palette), filter_palette_(*filter_palette){};
//         ~AddCanvase(){};

//         void operator() () const
//         {
//             canvase_manager_->createCanvas(&tool_palette_, &filter_palette_);   
//         }

//     private:
//         CanvasManager *canvase_manager_;
//         ToolPalette &tool_palette_; 
//         FilterPalette &filter_palette_; 
// };

// class ChooseTool : public Action
// {
//     public:
//         ChooseTool(ToolPalette::ToolType type, ToolPalette *palette): 
//                     palette_(*palette), type_(type){};
//         ~ChooseTool(){};

//         void operator() () const
//         {
//             palette_.setActiveTool(type_);
//         }

//     private:
//         ToolPalette &palette_;
//         ToolPalette::ToolType type_;
// };

// class ChooseColor : public Action
// {
//     public:
//         ChooseColor(sf::Color color, ToolPalette *palette_color): 
//                     palette_(*palette_color), color_(color) {};
//         ~ChooseColor(){};

//         void operator() () const
//         {
//             palette_.setActiveColor(color_);   
//         }

<<<<<<< HEAD
// class ChangeBrightness : public Action
// {
//     public:
//         ChangeBrightness(FilterPalette *filter_palette, CanvasManager *manager, const float delta): 
//                     filter_palette_(*filter_palette), canvas_manager_(*manager), delta_(delta) {};
//         ~ChangeBrightness(){};

//         void operator() () const
//         {
//              Canvas *active_canvas = canvas_manager_.getActiveCanvas();
//              if (active_canvas == nullptr) return;

//             FilterBrightness *filter  = (FilterBrightness*)filter_palette_.getFilter(FilterPalette::FilterType::LIGHT);
//             filter_palette_.setLastFilter(FilterPalette::FilterType::LIGHT);

=======
//     private:
//         ToolPalette &palette_;
//         sf::Color color_;    
// };

// class ChangeBrightness : public Action
// {
//     public:
//         ChangeBrightness(FilterPalette *filter_palette, CanvasManager *manager, const float delta): 
//                     filter_palette_(*filter_palette), canvas_manager_(*manager), delta_(delta) {};
//         ~ChangeBrightness(){};

//         void operator() () const
//         {
//              Canvas *active_canvas = canvas_manager_.getActiveCanvas();
//              if (active_canvas == nullptr) return;

//             FilterBrightness *filter  = (FilterBrightness*)filter_palette_.getFilter(FilterPalette::FilterType::LIGHT);
//             filter_palette_.setLastFilter(FilterPalette::FilterType::LIGHT);

>>>>>>> 57116ed (widget drawing by standart)
//             filter->setDelta(delta_);

           
//             filter->applyFilter(*active_canvas, active_canvas->getFilterMask());

//         }


//     private:
//         FilterPalette &filter_palette_;
//         CanvasManager &canvas_manager_;
       
//         float delta_;
        
// };

// class UseFilter : public Action
// {
//     public:
//         UseFilter(FilterPalette *filter_palette, CanvasManager *manager, const FilterPalette::FilterType type): 
//                     filter_palette_(*filter_palette), canvas_manager_(*manager), type_(type) {};
//         ~UseFilter(){};

//         void operator() () const
//         {
//              Canvas *active_canvas = canvas_manager_.getActiveCanvas();
//              if (active_canvas == nullptr) return;

<<<<<<< HEAD
            Filter *filter  = (Filter*)filter_palette_.getFilter(type_);
            filter_palette_.setLastFilter(type_);
           
            if (filter) filter->applyFilter(*active_canvas);
        }
=======
//             FilterBrightness *filter  = (FilterBrightness*)filter_palette_.getFilter(type_);
//             filter_palette_.setLastFilter(type_);
           
//             if (filter) filter->applyFilter(*active_canvas, active_canvas->getFilterMask());
//         }
>>>>>>> 57116ed (widget drawing by standart)


//     private:
//         FilterPalette &filter_palette_;
//         CanvasManager &canvas_manager_;
       
//         FilterPalette::FilterType type_;
        
// };


// class AppWindow: public Window
// {
//     public:
//         AppWindow(  const char *path_texture,
//                     const Vec2d &size, const Vec2d &pos, 
//                     const Widget *parent, const Vec2d &parent_size = Vec2d(1.0, 1.0), 
//                     const Vec2d &origin = Vec2d(0.0, 0.0), const Vec2d &scale = Vec2d(1.0, 1.0));

//         virtual ~AppWindow()
//         {
//             size_t size = widgets_.getSize(); 
//             for (size_t it = 0; it < size; it++)
//             {
//                 delete widgets_[it];
//             }
//         }

//         virtual bool onMousePressed     (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform);
//         virtual bool onMouseMoved       (const Vec2d &pos, Container<Transform> &stack_transform);
//         virtual bool onMouseReleased    (const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform);

//         virtual bool onKeyboardPressed  (const KeyboardKey);
//         virtual bool onKeyboardReleased (const KeyboardKey);

//         virtual void draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) override;  

//         virtual bool onTick             (const float delta_time);

//     protected:
        
//         bool switchTool(const KeyboardKey key);

//         Container <Widget*> widgets_;

//         CanvasManager canvas_manager_;
        
//         ToolPalette tool_pallette_;

//         FilterPalette filter_pallette_;

//         ColorPalette colors_;
// };


void useApp();

#endif