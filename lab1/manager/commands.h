#ifndef COMMANDS_
#define COMMANDS_

enum commands {
    MOVE, 
    SCALE,
    ROTATE,
    DRAW,
    LOAD,
    SAVE,
    QUIT,
    UNKNOWN,
};

using commands_t = enum commands;

#endif // COMMANDS_
