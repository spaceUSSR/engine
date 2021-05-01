#ifndef MOUSE_EVENTS_H
#define MOUSE_EVENTS_H
#include "events.h"

class MouseMovedEvent : public Event
{
private:
    int x, y;
public:
    MouseMovedEvent(int x, int y) :
        Event("Mouse moved event: ", EventType::MOUSE_MOVED_EVENT), x(x), y(y)  {}

public:
    std::string format() const override
    {
        return m_name + std::to_string(x) + " : " + std::to_string(y);
    }
};


class MouseScrolledEvent : public Event {
private:
    double m_offset;
public:
    MouseScrolledEvent(double offset) :
        Event("Mouse scrolled event: ", EventType::MOUSE_SCROLLED_EVENT), m_offset(offset){}

public:
    std::string format() const override
    {
        return m_name + std::to_string(m_offset);
    }
};

#endif //MOUSE_EVENTS_H
