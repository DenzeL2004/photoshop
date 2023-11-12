#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "window.h"
#include "../button/button.h"
#include "../decorator/decorator.h"

#include "../../app/config.h"


class ToolPalette;
class Tool;

class FilterMask;
class FilterPalette;
class Filter;

class Canvas : public Window
{
    public:
        
        Canvas( ToolPalette *tool_palette, FilterPalette *filter_palette, 
                const Vec2d &canvas_size,
                const Vec2d &size, const Vec2d &pos, 
                const Widget *parent, const Vec2d &parent_size = Vec2d(1.0, 1.0),  
                const Vec2d &origin = Vec2d(0.0, 0.0), const Vec2d &scale = Vec2d(1.0, 1.0));
        
        virtual ~Canvas()
        {
            delete &filter_mask_;
        }

        virtual bool onMousePressed     (const Vec2d& pos, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool onMouseMoved       (const Vec2d& pos, Container<Transform> &stack_transform);
        virtual bool onMouseReleased    (const Vec2d& pos, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool onKeyboardPressed  (const KeyboardKey);
        virtual bool onKeyboardReleased (const KeyboardKey);

        virtual void draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform);
        virtual bool onTick             (const float delta_time);  

        Vec2d  getRealPos      () const;
        void    setRealPos      (const Vec2d &new_pos);   
        Vec2d  getCanvasSize   () const;

        void correctCanvasRealPos(const Vec2d &abs_size);
        
        sf::RenderTexture& getBackground();
        FilterMask& getFilterMask();

    private:
        void getDrawFormat(sf::VertexArray &vertex_array, Transform &trf) const;
        Dot getCanvaseCoord(const Vec2d &pos) const;

        bool applyFilter(const KeyboardKey key);

        sf::RenderTexture background_;

        ToolPalette &tool_palette_;
        FilterMask &filter_mask_;

        FilterPalette &filter_palette_;

        Vec2d canvas_size_;
        Dot real_pos_;
};

class CanvasManager : public Window
{

    public:

        CanvasManager( const char *path_texture,
                        const Vec2d &size, const Vec2d &pos, 
                        const Widget *parent, const Vec2d &parent_size = Vec2d(1.0, 1.0),  
                        const Vec2d &origin = Vec2d(0.0, 0.0), const Vec2d &scale = Vec2d(1.0, 1.0));
    
        ~CanvasManager()
        {
            size_t size = canvases_.getSize();
            for (size_t it = 0; it < size; it++)
                delete canvases_[it];
        };

        virtual bool onMousePressed     (const Vec2d& pos, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool onMouseMoved       (const Vec2d& pos, Container<Transform> &stack_transform);
        virtual bool onMouseReleased    (const Vec2d& pos, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool onKeyboardPressed  (const KeyboardKey);
        virtual bool onKeyboardReleased (const KeyboardKey);

        virtual void draw               (sf::RenderTarget &target, Container<Transform> &stack_transform);
        
        bool onTick                     (const float delta_time);

        void createCanvas(ToolPalette *tool_palette, FilterPalette *filter_palette);
        
        Canvas* getActiveCanvas();
    private:
         Container<Widget*> widgets_;
        bool delete_canvas_;

        Container<Canvas*> canvases_;

        size_t cnt_;
}; 

class ScrollCanvas : public Action
{
    public:
        ScrollCanvas(const Vec2d &delta, Canvas *ptr): 
                delta_(delta), canvas_(ptr){};
        ~ScrollCanvas(){};

        void operator() () const
        {
            canvas_->setRealPos(delta_ + canvas_->getRealPos());
        }

    private:
        Dot delta_;
        Canvas *canvas_;
};

class Scrollbar: public Widget
{

    public:
        enum Type
        {
            HORIZONTAL,
            VERTICAL,
        };

        Scrollbar(  Canvas *canvas, const Type type,
                    const Vec2d &size, const Vec2d &pos, 
                    const Widget *parent, const Vec2d &parent_size = Vec2d(1.0, 1.0),  
                    const Vec2d &origin = Vec2d(0.0, 0.0), const Vec2d &scale = Vec2d(1.0, 1.0));

        virtual ~Scrollbar()
        {
            delete top_button_;
            delete bottom_button_;
            delete center_button_;
        }

        virtual bool onMousePressed     (const Vec2d& pos, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool onMouseMoved       (const Vec2d& pos, Container<Transform> &stack_transform);
        virtual bool onMouseReleased    (const Vec2d& pos, const MouseKey key, Container<Transform> &stack_transform);

        virtual void draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform);  

        virtual bool onKeyboardPressed  (const KeyboardKey);
        virtual bool onKeyboardReleased (const KeyboardKey);

        virtual void onUpdate           (const LayoutBox &parent_layout);

        void addButtons(Button *top_button, Button *bottom_button, Button *center_button);

    private:

        void moveCenter();
        void resizeCenter();
        

        Button *top_button_, *bottom_button_, *center_button_;
        Canvas *canvas_;

        Vec2d hold_pos_;
        Vec2d prev_canvas_real_pos_;
        
        Type type_;
};

#endif