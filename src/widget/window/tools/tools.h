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

#endif