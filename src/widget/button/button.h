#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "../graphic.h"
#include "../../container/container.h"

//================================================================================

class Action
{
    public:
        Action(){};
        
        virtual ~Action() = default;

        virtual bool operator() () const = 0;
    
};

//================================================================================

enum Buttons_err
{
    LOAD_TEXTURE_TO_STAT,
    LOAD_TEXTURE_TO_POINT,
    LOAD_TEXTURE_TO_PRESS,  
};

class Button
{

    public:
        Button  (const char *released_texture_file, const char *covered_texture_file, 
                 const char *pressed_texture_file,  const char *disabled_texture_file,
                 const Dot &pos, const Action *action);

        Button(const Button &other) = default;

        virtual Button& operator= (const Button &other)
        {
            released_texture_  = other.released_texture_;
            covered_texture_   = other.covered_texture_;
            pressed_texture_   = other.pressed_texture_;
            disabled_texture_  = other.disabled_texture_;

            delete action_;
            action_ = other.action_;

            return *this;
        }

        virtual ~Button()
        {
            released_texture_.~Texture();
            covered_texture_.~Texture();
            pressed_texture_.~Texture();
            disabled_texture_.~Texture();

            delete action_;
        }


        virtual void Draw(sf::RenderWindow &window) const;

        virtual bool CheckCursorOnButton () const;

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
