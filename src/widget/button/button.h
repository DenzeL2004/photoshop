#ifndef _BUTTON_H_
#define _BUTTON_H_


#include "../../container/container.h"
#include "../widget.h"
//================================================================================

class Action
{
    public:
        Action(){};
        
        virtual ~Action() = default;

        virtual bool operator() () const = 0;
    
};

//================================================================================


class Button : public Widget
{

    public:
        Button  (const char *released_texture_file, const char *covered_texture_file, 
                 const char *pressed_texture_file,  const char *disabled_texture_file,
                 const Dot &pos, const Action *action);

        Button(const Button &other) = delete;

        virtual Button& operator= (const Button &other) = delete;

        virtual ~Button()
        {
            delete action_;
        }


        
        virtual bool OnMousePressed     (const MouseKey key);
        virtual bool OnMouseMoved       (const int x, const int y);
        virtual bool OnMouseReleased    (const MouseKey key);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw(sf::RenderTarget &target) const;  


        bool CheckPressed()  const {return flag_pressed_;}
        bool CheckDisabled() const {return flag_disabled_;}
        
        void SetState(const bool flag) 
        {
            if (!flag) return;

            flag_pressed_ = !flag_pressed_;
            return;
        }

        const Action *action_;

    protected:
        const sf::Texture* DefineTexture() const;

        sf::Texture released_texture_, covered_texture_, 
                    pressed_texture_, disabled_texture_;
                    
        Dot left_up_;

        bool flag_pressed_, flag_disabled_;
};


class ButtonsManager
{

    public:
        ButtonsManager (): buttons_(){}

        ~ButtonsManager ()
        {
            size_t size = buttons_.GetSize();
            for (size_t it = 0; it < size; it++)
            {
                if (buttons_[it] != nullptr)
                    delete buttons_[it];
            }
                return;
        }

        void AddButton (Button *button)
        {
            buttons_.PushBack(button);
            return;
        }

        void ShowButtons (sf::RenderWindow &window) const;

        void DetectPresse(const sf::Event event) const;

        bool GetButtonState(const size_t it) const {return buttons_[it]->CheckPressed();}


    protected:
        Container<Button*> buttons_;
};



#endif
