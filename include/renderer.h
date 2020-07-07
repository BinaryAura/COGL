#ifndef COGL_RENDERER_H
#define COGL_RENDERER_H

#include <GL/glew.h>
#include <iostream>
#include <signal.h>

#define ASSERT(x) if (!(x)) raise(SIGABRT);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void display_error_message(int code, const char* library, const char* description, const char* function = nullptr, const char* file = nullptr, int32_t line = -1);

void GLClearError();

bool GLLogCall(const char* function, const char* file, int32_t line);

class Renderer {

};


#endif //COGL_RENDERER_H
