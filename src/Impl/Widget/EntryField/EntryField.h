#ifndef _ENTRY_FIELD_WIDGET_H_
#define _ENTRY_FIELD_WIDGET_H_

#include "Impl/Widget/ContainerWidget/ContainerWidget.h"
#include "Impl/Widget/TextBox/TextBox.h"
#include "Impl/Widget/Window/Window.h"
#include "Impl/LayoutBox/BaseLayoutBox/BaseLayoutBox.h"

#include "App/AppConfig.h"

class EntryField: public ContainerWidget
{
    public:
        EntryField(const plug::LayoutBox &box);
        virtual ~EntryField(){}

        virtual void onEvent(const plug::Event &event, plug::EHC &context);

        const char* const getString(void);

    private:
        size_t m_text_box_id;
};

#endif
