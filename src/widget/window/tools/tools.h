#ifndef _TOOLS_H_
#define _TOOLS_H_

#include "../canvas.h"


        
class LineTool : public Tool
{
    public:
        LineTool(const sf::Color *cur_color);

        ~LineTool()
        {
            delete preview_;
        };

        void OnMainButton       (Button::Button_State key, const Dot &pos, Canvas &canvas);
        void OnSecondaryButton  (Button::Button_State key, const Dot &pos, Canvas &canvas){}

        void OnModifier1        (Button::Button_State key, const Dot &pos, Canvas &canvas){}
        void OnModifier2        (Button::Button_State key, const Dot &pos, Canvas &canvas){}
        void OnModifier3        (Button::Button_State key, const Dot &pos, Canvas &canvas){}

        void OnMove             (const Dot &pos, Canvas &canvas);
        void OnConfirm          (const Dot &pos, Canvas &canvas);
        void OnCancel           (const Dot &pos, Canvas &canvas){}

        Widget* GetWidget() const;

    private:
        bool using_;

        Dot start_pos_;
        Dot end_pos_;

        Widget* preview_;
        
        const sf::Color &cur_color_;
};


class BrushTool : public Tool
{
    public:
        BrushTool(const sf::Color *cur_color);

        ~BrushTool(){}

        void OnMainButton       (Button::Button_State key, const Dot &pos, Canvas &canvas);
        void OnSecondaryButton  (Button::Button_State key, const Dot &pos, Canvas &canvas){}

        void OnModifier1        (Button::Button_State key, const Dot &pos, Canvas &canvas){}
        void OnModifier2        (Button::Button_State key, const Dot &pos, Canvas &canvas){}
        void OnModifier3        (Button::Button_State key, const Dot &pos, Canvas &canvas){}

        void OnMove             (const Dot &pos, Canvas &canvas);
        void OnConfirm          (const Dot &pos, Canvas &canvas);
        void OnCancel           (const Dot &pos, Canvas &canvas){}

        Widget* GetWidget() const;

    private:
        void DrawForm(const Dot &pos, Canvas &canvas);


        bool using_;

        Dot prev_pos_;

        const sf::Color &cur_color_;
};

class SquareTool : public Tool
{
    public:
        SquareTool(const sf::Color *cur_color);

        ~SquareTool()
        {
            delete preview_;
        };

        void OnMainButton       (Button::Button_State key, const Dot &pos, Canvas &canvas);
        void OnSecondaryButton  (Button::Button_State key, const Dot &pos, Canvas &canvas){}

        void OnModifier1        (Button::Button_State key, const Dot &pos, Canvas &canvas){}
        void OnModifier2        (Button::Button_State key, const Dot &pos, Canvas &canvas){}
        void OnModifier3        (Button::Button_State key, const Dot &pos, Canvas &canvas){}

        void OnMove             (const Dot &pos, Canvas &canvas);
        void OnConfirm          (const Dot &pos, Canvas &canvas);
        void OnCancel           (const Dot &pos, Canvas &canvas){}

        Widget* GetWidget() const;

    private:
        bool using_;

        Dot start_pos_;
        Dot end_pos_;

        Widget* preview_;
        
        const sf::Color &cur_color_;
};


class CircleTool : public Tool
{
    public:
        CircleTool(const sf::Color *cur_color);

        ~CircleTool()
        {
            delete preview_;
        };

        void OnMainButton       (Button::Button_State key, const Dot &pos, Canvas &canvas);
        void OnSecondaryButton  (Button::Button_State key, const Dot &pos, Canvas &canvas){}

        void OnModifier1        (Button::Button_State key, const Dot &pos, Canvas &canvas){}
        void OnModifier2        (Button::Button_State key, const Dot &pos, Canvas &canvas){}
        void OnModifier3        (Button::Button_State key, const Dot &pos, Canvas &canvas){}

        void OnMove             (const Dot &pos, Canvas &canvas);
        void OnConfirm          (const Dot &pos, Canvas &canvas);
        void OnCancel           (const Dot &pos, Canvas &canvas){}

        Widget* GetWidget() const;

    private:
        bool using_;

        Dot start_pos_;
        Dot end_pos_;

        Widget* preview_;
        
        const sf::Color &cur_color_;
};

class FillTool : public Tool
{
    public:
        FillTool(const sf::Color *cur_color);

        ~FillTool(){}

        void OnMainButton       (Button::Button_State key, const Dot &pos, Canvas &canvas);
        void OnSecondaryButton  (Button::Button_State key, const Dot &pos, Canvas &canvas){}

        void OnModifier1        (Button::Button_State key, const Dot &pos, Canvas &canvas){}
        void OnModifier2        (Button::Button_State key, const Dot &pos, Canvas &canvas){}
        void OnModifier3        (Button::Button_State key, const Dot &pos, Canvas &canvas){}

        void OnMove             (const Dot &pos, Canvas &canvas){}
        void OnConfirm          (const Dot &pos, Canvas &canvas);
        void OnCancel           (const Dot &pos, Canvas &canvas){}

        Widget* GetWidget() const;

    private:
        void Fill(sf::Color &fill_color, const Dot &start_pos, Canvas &canvas, sf::Image &image);


        bool using_;

        Dot start_pos_;
        
        const sf::Color &cur_color_;
};


class PollyLineWidget : public Widget
{
    public:
        PollyLineWidget(const Dot *end_pos, const sf::Color *cur_color):
                        end_pos_(*end_pos), cur_color_(*cur_color){}

        ~PollyLineWidget(){}

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform) {return true;};
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform) {return true;}
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform){return true;}

        bool OnKeyboardPressed  (const KeyboardKey){return true;}
        bool OnKeyboardReleased (const KeyboardKey){return true;}

        void PassTime           (const time_t delta_time){}

        void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform)
        {
            Transform last_trf = stack_transform.GetBack();
            size_t size = arr_.getVertexCount();

            if (size == 0)
                return;

            Dot cur(0.0, 0.0); 
            Dot next = Dot(arr_[size - 1].position.x, arr_[size - 1].position.y);

            for (size_t it = 0; it < size - 1; it++)
            {
                cur  = Dot(arr_[it].position.x, arr_[it].position.y);
                next = Dot(arr_[it + 1].position.x, arr_[it + 1].position.y);
                DrawLine(targert, cur + last_trf.offset, next + last_trf.offset, cur_color_);
            }

            DrawLine(targert, next + last_trf.offset,  end_pos_ + last_trf.offset, cur_color_);

        }
    
        sf::Color GetColor() const {return cur_color_;}

        sf::VertexArray arr_;
    private:
        const Dot &end_pos_;
       
       const sf::Color &cur_color_;
};

class PollyLineTool : public Tool
{
    public:
        PollyLineTool(const sf::Color *cur_color);

        ~PollyLineTool(){}

        void OnMainButton       (Button::Button_State key, const Dot &pos, Canvas &canvas);
        void OnSecondaryButton  (Button::Button_State key, const Dot &pos, Canvas &canvas){}

        void OnModifier1        (Button::Button_State key, const Dot &pos, Canvas &canvas){}
        void OnModifier2        (Button::Button_State key, const Dot &pos, Canvas &canvas){}
        void OnModifier3        (Button::Button_State key, const Dot &pos, Canvas &canvas){}

        void OnMove             (const Dot &pos, Canvas &canvas);
        void OnConfirm          (const Dot &pos, Canvas &canvas);
        void OnCancel           (const Dot &pos, Canvas &canvas){}

        Widget* GetWidget() const;

    private:
        bool using_;

        Dot start_pos_;
        Dot end_pos_;
        PollyLineWidget* preview_;
        
        const sf::Color &cur_color_;
};

#endif