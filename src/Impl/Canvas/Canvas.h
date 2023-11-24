#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "LogInfo/LogErrors.h"

#include "Plug/Canvas/Canvas.h"

#include "Impl/RenderTarget/SfmlRenderTarget/RenderTarget.h"
#include "Impl/Canvas/SelectionMask.h"



class Canvas : public plug::Canvas
{

    public:
        Canvas(const size_t width, const size_t height);
        Canvas(const char *filename);

        ~Canvas()
        {
            delete render_texture_;
            delete render_target_;
            delete selection_mask_;
        }

        virtual void draw(const plug::VertexArray &vertex_array);

        virtual void draw(const plug::VertexArray &vertex_array, const plug::Texture &texture);

        virtual unsigned int getNativeHandle(void) const;

        virtual plug::Vec2d getSize(void) const;

        virtual void setSize(const plug::Vec2d &size);

        virtual plug::SelectionMask &getSelectionMask(void) = 0;

        virtual plug::Color getPixel(size_t x, size_t y) const = 0;

        virtual void setPixel(size_t x, size_t y, const plug::Color &color) = 0;

        virtual const plug::Texture& getTexture(void) const = 0;

    private:
        sf::RenderTexture *render_texture_;
        plug::RenderTarget *render_target_;

        plug::SelectionMask *selection_mask_;
};


#endif