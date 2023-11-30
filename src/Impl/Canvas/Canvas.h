#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "LogInfo/LogErrors.h"

#include "Plug/Canvas/Canvas.h"

#include "Impl/RenderTarget/SfmlRenderTarget/RenderTarget.h"
#include "Impl/Canvas/SelectionMask.h"

class Canvas : public plug::Canvas
{

    public:
        Canvas(const size_t width, const size_t height, const plug::Color color);
        Canvas(const char *filename);

        ~Canvas()
        {
            delete m_render_texture;
            delete m_render_target;
            delete m_selection_mask;
            delete m_texture;
        }

        virtual void draw(const plug::VertexArray &vertex_array);

        virtual void draw(const plug::VertexArray &vertex_array, const plug::Texture &texture);

        virtual plug::Vec2d getSize(void) const;

        virtual void setSize(const plug::Vec2d &size);

        virtual plug::SelectionMask &getSelectionMask(void);

        virtual plug::Color getPixel(size_t x, size_t y) const;

        virtual void setPixel(size_t x, size_t y, const plug::Color &color);

        virtual const plug::Texture& getTexture(void) const;

    private:
        sf::RenderTexture *m_render_texture;
        plug::RenderTarget *m_render_target;

        plug::SelectionMask *m_selection_mask;

        plug::Texture *m_texture;
};

#endif