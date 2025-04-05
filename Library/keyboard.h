#ifndef KEYBOARD_H
#define KEYBOARD_H

void KeyboardInit(void); 

enum KeyboardState {RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

enum KeyboardState eKeyboardRead(void);

#endif
