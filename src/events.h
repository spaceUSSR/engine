#ifndef EVENTS_H
#define EVENTS_H

struct GLFWwindow;

class Events{
public:
	static void initialize();
	static void finalize();
	static void cursorPosCallBack(GLFWwindow* window, double xpos, double ypos);
	static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void pollEvents();

private:
	static float m_lastXpos;
	static float m_lastYpos;
	static float m_lastFrame;

	static bool* m_key;
};



#endif //EVENTS_H
