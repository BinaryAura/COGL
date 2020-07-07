#include <renderer.h>

void display_error_message(int code, const char* library, const char* description, const char* function, const char* file, int32_t line) {
    if (function == nullptr || file == nullptr || line == -1) {
        fprintf(stderr, "%s Error: (%#x) %s\n", library, code, description);
    } else {
        fprintf(stderr, "%s Error in %s at %s:%d\n\t(%#x) %s\n", library, function, file, line, code, description);
    }
}

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int32_t line) {
    while(int32_t error = glGetError()) {
        const char* desc;
        switch(error) {
            case GL_INVALID_ENUM:
                desc = "Invalid Enum";
                break;
            case GL_INVALID_VALUE:
                desc = "Invalid Value";
                break;
            case GL_INVALID_OPERATION:
                desc = "Invalid Operation";
                break;
            case GL_STACK_OVERFLOW:
                desc = "Stack Overflow";
                break;
            case GL_STACK_UNDERFLOW:
                desc = "Stack Underflow";
                break;
            case GL_OUT_OF_MEMORY:
                desc = "Out of Memory";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                desc = "Invalid Framebuffer Operation";
                break;
            case GL_CONTEXT_LOST:
                desc = "Context Lost";
                break;
            case GL_TABLE_TOO_LARGE:
                desc = "Table Too Large";
                break;
        }
        display_error_message(error, "OpenGL", desc, function, file, line);
        return false;
    }
    return true;
}
