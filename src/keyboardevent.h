#ifndef KEYBOARD_EVENT_H
#define KEYBOARD_EVENT_H
#include "events.h"
class KeyboardButtonEvent : public Event
{
private:
    int x, y;
public:
    KeyboardButtonEvent(int x, int y) :
        Event("Keyboard button: ", EventType::KEYBOARD_BUTTON_PRESSED_EVENT), x(x), y(y)  {}

public:
    std::string format() const override
    {
        return m_name + std::to_string(x) + " : " + std::to_string(y);
    }
};
#endif
