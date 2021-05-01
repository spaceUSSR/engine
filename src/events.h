#ifndef EVENTS_H
#define EVENTS_H

#include <string>

struct GLFWwindow;

class Events{
public:
	static void cursorPosCallBack(GLFWwindow* window, double xpos, double ypos);
	static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	static float m_lastXpos;
	static float m_lastYpos;
	static float m_lastFrame;

    static bool* m_key;
};


class Event {
public:
    enum class EventType : uint8_t
    {
        MOUSE_MOVED_EVENT = 1,
        MOUSE_BUTTON_PRESSED_EVENT,
        MOUSE_BUTTON_RELEASED_EVENT,
        MOUSE_SCROLLED_EVENT,
        KEYBOARD_BUTTON_PRESSED_EVENT,
        KEYBOARD_BUTTON_RELEASED_EVENT
    };
protected:
    std::string m_name;
    EventType m_type;
protected:
    Event(const std::string& name, EventType type) :
        m_name(name), m_type(type) {}
protected:
    virtual ~Event() = default;
public:
    inline EventType getType() const {return m_type;}
    inline std::string getName() const {return m_name;}
    virtual std::string format() const = 0;
};



#endif //EVENTS_H
