#ifndef _APP_H_
#define _APP_H_


#include "../widget/window/window.h"
#include "../widget/button/button.h"

#include "config.h"

class AddCanvase : public Action
{
    public:
        AddCanvase(CanvaseManager *canvase_manager, Tool *tool): 
                   canvase_manager_(canvase_manager), tool_(tool){};
        ~AddCanvase(){};

        void operator() () const
        {
            canvase_manager_->CreateCanvase(tool_);   
        }

    private:
        CanvaseManager *canvase_manager_;
        Tool *tool_; 
};

class ChooseTool : public Action
{
    public:
        ChooseTool(Tool::Type type, Tool *tool): 
                type_(type), tool_(tool){};
        ~ChooseTool(){};

        void operator() () const
        {
            tool_->type_ = type_;   
        }

    private:
        Tool::Type type_;
        Tool *tool_; 
};

class ChooseColor : public Action
{
    public:
        ChooseColor(sf::Color color, Tool *tool): 
                color_(color), tool_(tool){};
        ~ChooseColor(){};

        void operator() () const
        {
            tool_->color_ = color_;   
        }

    private:
        sf::Color color_;
        Tool *tool_; 
};


class AppWindow: public Window
{
    public:
        AppWindow (const char *path_texture,
                   const Dot &offset, const Vector &scale);

        virtual ~AppWindow()
        {
            delete button_create_;
            delete tools_button_;
            delete colors_button_;
        }

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) override;  

        virtual void PassTime           (const time_t delta_time);

    protected:
        
        CanvaseManager canvas_manager_;
        Button *button_create_;
        ButtonList *tools_button_;
        ButtonList *colors_button_;

        Tool tool_;
};


void UseApp();

#endif