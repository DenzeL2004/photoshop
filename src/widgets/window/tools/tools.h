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

        Tool& operator= (const Tool &other) = delete;

        virtual void onMainButton       (ControlState state, const Dot &pos, Canvas &canvas) = 0;
        virtual void onSecondaryButton  (ControlState state, const Dot &pos, Canvas &canvas) = 0;

        virtual void onModifier1        (ControlState state, const Dot &pos, Canvas &canvas) = 0;
        virtual void onModifier2        (ControlState state, const Dot &pos, Canvas &canvas) = 0;
        virtual void onModifier3        (ControlState state, const Dot &pos, Canvas &canvas) = 0;

        virtual void onMove             (const Dot &pos, Canvas &canvas) = 0;
        virtual void onConfirm          (Canvas &canvas) = 0;
        virtual void onCancel           () = 0;

        virtual Widget* getWidget() const = 0;
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
            PEN      = 6,
        };

        ToolPalette ();
        ~ToolPalette ();

        ToolPalette(const ToolPalette &other) = delete;
        ToolPalette& operator= (const ToolPalette &other) = delete;

        void setActiveTool  (const ToolType tool_type);
        void setActiveColor (const sf::Color &color);

        sf::Color getActiveColor () const;
        Tool* getActiveTool () const;

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

        virtual void onMainButton       (ControlState state, const Dot &pos, Canvas &canvas);
        virtual void onSecondaryButton  (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void onModifier1        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void onModifier2        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void onModifier3        (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void onMove             (const Dot &pos, Canvas &canvas);
        virtual void onConfirm          (Canvas &canvas);
        virtual void onCancel           ();

        Widget* getWidget() const;

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

        virtual void onMainButton       (ControlState state, const Dot &pos, Canvas &canvas);
        virtual void onSecondaryButton  (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void onModifier1        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void onModifier2        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void onModifier3        (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void onMove             (const Dot &pos, Canvas &canvas);
        virtual void onConfirm          (Canvas &canvas);
        virtual void onCancel           (){}

        Widget* getWidget() const;

    private:
        virtual void drawForm(const Dot &pos, Canvas &canvas);


        bool using_;

        Dot prev_pos_;

        const sf::Color &cur_color_;
};

class PenTool : public Tool
{
    public:
        PenTool(const sf::Color *cur_color);

        ~PenTool(){}

        virtual void onMainButton       (ControlState state, const Dot &pos, Canvas &canvas);
        virtual void onSecondaryButton  (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void onModifier1        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void onModifier2        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void onModifier3        (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void onMove             (const Dot &pos, Canvas &canvas);
        virtual void onConfirm          (Canvas &canvas);
        virtual void onCancel           (){}

        Widget* getWidget() const;

    private:

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

        virtual void onMainButton       (ControlState state, const Dot &pos, Canvas &canvas);
        virtual void onSecondaryButton  (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void onModifier1        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void onModifier2        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void onModifier3        (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void onMove             (const Dot &pos, Canvas &canvas);
        virtual void onConfirm          (Canvas &canvas);
        virtual void onCancel           ();

        Widget* getWidget() const;

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

        virtual void onMainButton       (ControlState state, const Dot &pos, Canvas &canvas);
        virtual void onSecondaryButton  (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void onModifier1        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void onModifier2        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void onModifier3        (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void onMove             (const Dot &pos, Canvas &canvas);
        virtual void onConfirm          (Canvas &canvas);
        virtual void onCancel           ();

        Widget* getWidget() const;

    private:
        bool using_;

        Dot start_pos_;
        Dot end_pos_;

        CircleWidget* preview_;
        
        const sf::Color &cur_color_;
};

// class FillTool : public Tool
// {
//     public:
//         FillTool(const sf::Color *cur_color);

//         ~FillTool(){}

//         virtual void onMainButton       (ControlState state, const Dot &pos, Canvas &canvas);
//         virtual void onSecondaryButton  (ControlState state, const Dot &pos, Canvas &canvas){}

//         virtual void onModifier1        (ControlState state, const Dot &pos, Canvas &canvas){}
//         virtual void onModifier2        (ControlState state, const Dot &pos, Canvas &canvas){}
//         virtual void onModifier3        (ControlState state, const Dot &pos, Canvas &canvas){}

//         virtual void onMove             (const Dot &pos, Canvas &canvas){}
//         virtual void onConfirm          (Canvas &canvas);
//         virtual void onCancel           ();

//         Widget* getWidget() const;

//     private:
//         virtual void Fill(sf::Color &fill_color, const Dot &start_pos, Canvas &canvas, sf::Image *image);


//         bool using_;

//         Dot start_pos_;
        
//         const sf::Color &cur_color_;
// };

class PolyLineWidget;

class PolyLineTool : public Tool
{
    public:
        PolyLineTool(const sf::Color *cur_color);

        ~PolyLineTool(){}

        virtual void onMainButton       (ControlState state, const Dot &pos, Canvas &canvas);
        virtual void onSecondaryButton  (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void onModifier1        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void onModifier2        (ControlState state, const Dot &pos, Canvas &canvas){}
        virtual void onModifier3        (ControlState state, const Dot &pos, Canvas &canvas){}

        virtual void onMove             (const Dot &pos, Canvas &canvas);
        virtual void onConfirm          (Canvas &canvas);
        virtual void onCancel           ();

        Widget* getWidget() const;

    private:
        bool using_;

        Dot start_pos_;
        Dot end_pos_;
        PolyLineWidget* preview_;
        
        const sf::Color &cur_color_;
};

#endif