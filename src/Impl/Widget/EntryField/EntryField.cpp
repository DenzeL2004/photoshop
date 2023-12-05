#include "EntryField.h"

EntryField::EntryField( const plug::LayoutBox &box):
                        ContainerWidget(box), m_text_box_id(0)
{
    Window *window = new Window(getPlugTexture(Entry_window_texture),
                                Title(Filt_path_title_pos, File_path_name, Entry_title_scale, Canvas_dialog_title_color),
                                BaseLayoutBox(Entry_window_pos, Entry_window_size, Dialog_window_size, false, false));

    Window *entry_field = new Window(getPlugTexture(Entry_field_texture), Title(),
                                     BaseLayoutBox(Entry_field_pos, Entry_field_size, Dialog_window_size, false, false));

    TextBox *text_box = new TextBox(Entry_field_symbol_limit, Entry_title_scale, 
                                    BaseLayoutBox(Entry_field_pos + plug::Vec2d(40, 25), Entry_field_size, Entry_field_size, false, false));
    
    text_box->setColor(Entry_field_color);

    insertWidget(window);
    insertWidget(entry_field);
    insertWidget(text_box);

    m_text_box_id = m_widgets.getSize() - 1;
}

void EntryField::onEvent(const plug::Event &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);    
    context.stack.enter(trf);

    int size = static_cast<int>(m_widgets.getSize());
    for (int it = size - 1; it >= 0; it--)
    {
        m_widgets[it]->onEvent(event, context);   
    }
  
    context.stopped = true;

    context.stack.leave();
}

const char* const EntryField::getString(void)
{
    TextBox *text_box = static_cast<TextBox*>(getWidget(m_text_box_id));
    return text_box->getString();
}
