#ifndef _TOOLS_H_
#define _TOOLS_H_

#include "../canvas.h"

struct ControlState
{
    enum ButtonState
    {
       PRESSED, 
    } state;
};


class Tool
{
    public:
        virtual void OnMainButton       (ControlState state, const Dot &pos, Canvas &canvas) = 0;
        virtual void OnSecondaryButton  (ControlState state, const Dot &pos, Canvas &canvas) = 0;

        virtual void OnModifier1        (ControlState state, const Dot &pos, Canvas &canvas) = 0;
        virtual void OnModifier2        (ControlState state, const Dot &pos, Canvas &canvas) = 0;
        virtual void OnModifier3        (ControlState state, const Dot &pos, Canvas &canvas) = 0;

        virtual void OnMove             (const Dot &pos, Canvas &canvas) = 0;
        virtual void OnConfirm          (Canvas &canvas) = 0;
        virtual void OnCancel           () = 0;

        virtual Widget* GetWidget() const = 0;
};

class ToolPalette
{
    public:
        enum ColorType
        {
            BACKGROUND,
            FOREGROUND,
        };

        enum ToolType
        {
            NOTHING  = -1,
            LINE     = 0, 
            BRUSH    = 1,    
            SQUARE   = 2, 
            CIRCLE   = 3,
            POLYLINE = 4,
            ERASER   = 5,
            FILL     = 6,
        };

        ToolPalette ();
        ~ToolPalette ();

        void SetActiveTool  (const ToolType tool_type);
        void SetActiveColor (const sf::Color &color);

        sf::Color GetActiveColor () const;

        Tool* GetActiveTool () const;

    private:
        ToolType active_tool_;

        Container<Tool*>  tools_;

        ColorType color_type_;

        sf::Color foreground_color_;
        sf::Color background_color_;

};

class LineWidget;
        
class LineTool : public Tool
{
    public:
        LineTool(const sf::Color *cur_color);

        ~LineTool()
        {
            delete preview_;
        }

        virtual void OnMainButton       (ControlState state, const Dot &pos, Canvas &canvas);
        virtual void OnSecondaryButton  (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void OnModifier1        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier2        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier3        (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void OnMove             (const Dot &pos, Canvas &canvas);
        virtual void OnConfirm          (Canvas &canvas);
        virtual void OnCancel           ();

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

        virtual void OnMainButton       (ControlState state, const Dot &pos, Canvas &canvas);
        virtual void OnSecondaryButton  (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void OnModifier1        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier2        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier3        (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void OnMove             (const Dot &pos, Canvas &canvas);
        virtual void OnConfirm          (Canvas &canvas);
        virtual void OnCancel           (){}

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

        virtual void OnMainButton       (ControlState state, const Dot &pos, Canvas &canvas);
        virtual void OnSecondaryButton  (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void OnModifier1        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier2        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier3        (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void OnMove             (const Dot &pos, Canvas &canvas);
        virtual void OnConfirm          (Canvas &canvas);
        virtual void OnCancel           ();

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

        virtual void OnMainButton       (ControlState state, const Dot &pos, Canvas &canvas);
        virtual void OnSecondaryButton  (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void OnModifier1        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier2        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier3        (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void OnMove             (const Dot &pos, Canvas &canvas);
        virtual void OnConfirm          (Canvas &canvas);
        virtual void OnCancel           ();

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

        virtual void OnMainButton       (ControlState state, const Dot &pos, Canvas &canvas);
        virtual void OnSecondaryButton  (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void OnModifier1        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier2        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier3        (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void OnMove             (const Dot &pos, Canvas &canvas){}
        virtual void OnConfirm          (Canvas &canvas);
        virtual void OnCancel           ();

        Widget* GetWidget() const;

    private:
        virtual void Fill(sf::Color &fill_color, const Dot &start_pos, Canvas &canvas, sf::Image *image);


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

        virtual void OnMainButton       (ControlState state, const Dot &pos, Canvas &canvas);
        virtual void OnSecondaryButton  (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void OnModifier1        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier2        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void OnModifier3        (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void OnMove             (const Dot &pos, Canvas &canvas);
        virtual void OnConfirm          (Canvas &canvas);
        virtual void OnCancel           ();

        Widget* GetWidget() const;

    private:
        bool using_;

        Dot start_pos_;
        Dot end_pos_;
        PolyLineWidget* preview_;
        
        const sf::Color &cur_color_;
};

#endif