#ifndef _BUTTON_H_
#define _BUTTON_H_


#include "../widget.h"


//================================================================================

class Action
{
    public:
        Action(){};
        
        virtual ~Action(){};

        virtual void operator() () const = 0;
    
};

//================================================================================

class Button : public Widget
{
    public:
        Button (const char *released_texture_file, const char *covered_texture_file, 
                const char *pressed_texture_file,  const char *disabled_texture_file,
                const Action *action, 
                const Dot &offset, const Vector &scale);

        virtual ~Button()
        {
            delete action_;
        }


        Button(const Button &other) = delete;

        virtual Button& operator= (const Button &other) = delete;

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) override;    
        
        virtual void PassTime           (const time_t delta_time);

        void SetTransform (const Transform &trannsform);

        Transform GetTransform() const {return transform_;}

        const Action *action_;

        enum Button_State
        {
            Released, 
            Covered,
            Pressed,
            Disabled,
        };

        Button_State state_;
        Button_State prev_state_;

    protected:

        const sf::Texture* DefineTexture() const;
        void GetNewSize(sf::VertexArray &vertex_array, const Transform &transform) const;

        sf::Texture released_texture_, covered_texture_, 
                    pressed_texture_, disabled_texture_;
                    
        Transform transform_;
        double width_, hieght_;
        
        time_t covering_time_;


};

class ButtonList : public Button
{
    public:
        ButtonList (const char *released_texture_file, const char *covered_texture_file, 
                    const char *pressed_texture_file,  const char *disabled_texture_file,
                    const Action *action, 
                    const Dot &offset, const Vector &scale):
                    Button(released_texture_file, covered_texture_file, 
                           pressed_texture_file, disabled_texture_file, 
                           action, offset, scale), buttons_(){}

        virtual ~ButtonList()
        {
            size_t size = buttons_.GetSize();
            for (size_t it = 0; it < size; it++)
                delete buttons_[it];

            delete action_;
        }


        ButtonList(const ButtonList &other) = delete;

        virtual ButtonList& operator= (const ButtonList &other) = delete;

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) override;    
        
        virtual void PassTime           (const time_t delta_time);

        Transform GetTransform() const {return transform_;}

        const Action *action_;
        Container<Button*> buttons_;

    protected:
        
};

//================================================================================

class Click : public Action
{
    public:
        Click(bool *ptr): flag_(ptr){};
        ~Click(){};

        void operator() () const
        {
            *flag_ = true;
        }

    private:
        bool *flag_; 
};

//================================================================================

class ShowButtonList : public Action
{
    public:
        ShowButtonList(Container<Button*> *buttons): buttons_(buttons){};
        ~ShowButtonList(){};

        void operator() () const
        {
            size_t size = buttons_->GetSize();
            for (size_t it = 0; it < size; it++)
                (*buttons_)[it]->state_ = (*buttons_)[it]->prev_state_;
        }

    private:
        Container<Button*> *buttons_; 
};

//================================================================================

#endif