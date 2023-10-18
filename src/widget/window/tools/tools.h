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
        void OnSecondaryButton  (Button::Button_State key, const Dot &pos, Canvas &canvas){};

        void OnModifier1        (Button::Button_State key, const Dot &pos, Canvas &canvas){};
        void OnModifier2        (Button::Button_State key, const Dot &pos, Canvas &canvas){};
        void OnModifier3        (Button::Button_State key, const Dot &pos, Canvas &canvas){};

        void OnMove             (const Dot &pos, Canvas &canvas);
        void OnConfirm          (const Dot &pos, Canvas &canvas);
        void OnCancel           (const Dot &pos, Canvas &canvas){};

        Widget* GetWidget() const;

    private:
        bool using_;

        Dot start_pos_;
        Dot end_pos_;

        Widget* preview_;
        
        const sf::Color &cur_color_;
};


#endif