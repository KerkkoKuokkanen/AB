
#ifndef KEYS_H
# define KEYS_H

typedef struct s_Keys
{
	int w, a, s, d;
	int left, right, up, down;
	int click;
	int rightClick;
	int middleMouse;
	int wheel;
	int mouseX;
	int mouseY;
	int staticMouseX;
	int staticMouseY;
	int smX;
	int smY;
	int space;
	int shift;
	int control;
	int tab;
}				t_Keys;

#endif
