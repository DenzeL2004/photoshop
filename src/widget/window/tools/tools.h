#ifndef _TOOLS_H_
#define _TOOLS_H_

#include "../canvas.h"


class LineWidget;
        
class LineTool : public Tool
{
    public:
        LineTool(const sf::Color *cur_color);

        ~LineTool()
        {
            delete preview_;
        }

        virtual void OnMainButton       (ButtonState key, const Dot &pos, Canvas &canvas);
        virtual void OnSecondaryButton  (ButtonState key, const Dot &pos, Canvas &canvas){}

        virtual void OnModifier1        (ButtonState key, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier2        (ButtonState key, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier3        (ButtonState key, const Dot &pos, Canvas &canvas){}

        virtual void OnMove             (const Dot &pos, Canvas &canvas);
        virtual void OnConfirm          (const Dot &pos, Canvas &canvas);
        virtual void OnCancel           (const Dot &pos, Canvas &canvas){}

        Widget* GetWidget() const;

    private:
        bool using_;

        Dot start_pos_;
        Dot end_pos_;

        LineWidget* preview_;
        
        const sf::Color &cur_color_;
};


class BrushTool : public Tool
{
    public:
        BrushTool(const sf::Color *cur_color);

        ~BrushTool(){}

        virtual void OnMainButton       (ButtonState key, const Dot &pos, Canvas &canvas);
        virtual void OnSecondaryButton  (ButtonState key, const Dot &pos, Canvas &canvas){}

        virtual void OnModifier1        (ButtonState key, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier2        (ButtonState key, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier3        (ButtonState key, const Dot &pos, Canvas &canvas){}

        virtual void OnMove             (const Dot &pos, Canvas &canvas);
        virtual void OnConfirm          (const Dot &pos, Canvas &canvas);
        virtual void OnCancel           (const Dot &pos, Canvas &canvas){}

        Widget* GetWidget() const;

    private:
        virtual void DrawForm(const Dot &pos, Canvas &canvas);


        bool using_;

        Dot prev_pos_;

        const sf::Color &cur_color_;
};

class SquareWidget;

class SquareTool : public Tool
{
    public:
        SquareTool(const sf::Color *cur_color);

        ~SquareTool()
        {
            delete preview_;
        }

        virtual void OnMainButton       (ButtonState key, const Dot &pos, Canvas &canvas);
        virtual void OnSecondaryButton  (ButtonState key, const Dot &pos, Canvas &canvas){}

        virtual void OnModifier1        (ButtonState key, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier2        (ButtonState key, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier3        (ButtonState key, const Dot &pos, Canvas &canvas){}

        virtual void OnMove             (const Dot &pos, Canvas &canvas);
        virtual void OnConfirm          (const Dot &pos, Canvas &canvas);
        virtual void OnCancel           (const Dot &pos, Canvas &canvas){}

        Widget* GetWidget() const;

    private:
        bool using_;

        Dot start_pos_;
        Dot end_pos_;

        Widget* preview_;
        
        const sf::Color &cur_color_;
};


class CircleWidget;

class CircleTool : public Tool
{
    public:
        CircleTool(const sf::Color *cur_color);

        ~CircleTool()
        {
            delete preview_;
        }

        virtual void OnMainButton       (ButtonState key, const Dot &pos, Canvas &canvas);
        virtual void OnSecondaryButton  (ButtonState key, const Dot &pos, Canvas &canvas){}

        virtual void OnModifier1        (ButtonState key, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier2        (ButtonState key, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier3        (ButtonState key, const Dot &pos, Canvas &canvas){}

        virtual void OnMove             (const Dot &pos, Canvas &canvas);
        virtual void OnConfirm          (const Dot &pos, Canvas &canvas);
        virtual void OnCancel           (const Dot &pos, Canvas &canvas){}

        Widget* GetWidget() const;

    private:
        bool using_;

        Dot start_pos_;
        Dot end_pos_;

        CircleWidget* preview_;
        
        const sf::Color &cur_color_;
};

class FillTool : public Tool
{
    public:
        FillTool(const sf::Color *cur_color);

        ~FillTool(){}

        virtual void OnMainButton       (ButtonState key, const Dot &pos, Canvas &canvas);
        virtual void OnSecondaryButton  (ButtonState key, const Dot &pos, Canvas &canvas){}

        virtual void OnModifier1        (ButtonState key, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier2        (ButtonState key, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier3        (ButtonState key, const Dot &pos, Canvas &canvas){}

        virtual void OnMove             (const Dot &pos, Canvas &canvas){}
        virtual void OnConfirm          (const Dot &pos, Canvas &canvas);
        virtual void OnCancel           (const Dot &pos, Canvas &canvas){}

        Widget* GetWidget() const;

    private:
        virtual void Fill(sf::Color &fill_color, const Dot &start_pos, Canvas &canvas, sf::Image &image);


        bool using_;

        Dot start_pos_;
        
        const sf::Color &cur_color_;
};

class PolyLineWidget;

class PolyLineTool : public Tool
{
    public:
        PolyLineTool(const sf::Color *cur_color);

        ~PolyLineTool(){}

        virtual void OnMainButton       (ButtonState key, const Dot &pos, Canvas &canvas);
        virtual void OnSecondaryButton  (ButtonState key, const Dot &pos, Canvas &canvas){}

        virtual void OnModifier1        (ButtonState key, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier2        (ButtonState key, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier3        (ButtonState key, const Dot &pos, Canvas &canvas){}

        virtual void OnMove             (const Dot &pos, Canvas &canvas);
        virtual void OnConfirm          (const Dot &pos, Canvas &canvas);
        virtual void OnCancel           (const Dot &pos, Canvas &canvas){}

        Widget* GetWidget() const;

    private:
        bool using_;

        Dot start_pos_;
        Dot end_pos_;
        PolyLineWidget* preview_;
        
        const sf::Color &cur_color_;
};

// class EreaserTool : public BrushTool
// {
//     public:
//         EreaserTool() = delete;

//         EreaserTool(const sf::Color *cur_color);

//         ~EreaserTool(){}

//         virtual void OnMainButton       (ButtonState key, const Dot &pos, Canvas &canvas);
//         virtual void OnSecondaryButton  (ButtonState key, const Dot &pos, Canvas &canvas){}

//         virtual void OnModifier1        (ButtonState key, const Dot &pos, Canvas &canvas){}
//         virtual void OnModifier2        (ButtonState key, const Dot &pos, Canvas &canvas){}
//         virtual void OnModifier3        (ButtonState key, const Dot &pos, Canvas &canvas){}

//         virtual void OnMove             (const Dot &pos, Canvas &canvas);
//         virtual void OnConfirm          (const Dot &pos, Canvas &canvas);
//         virtual void OnCancel           (const Dot &pos, Canvas &canvas){}

//         Widget* GetWidget() const;

//     private:
//         virtual void DrawForm(const Dot &pos, Canvas &canvas);

//         bool using_;
//         Dot prev_pos_;

//         const sf::Color &cur_color_;
// };

#endif