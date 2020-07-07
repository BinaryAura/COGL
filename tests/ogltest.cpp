#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <inttypes.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <signal.h>

#include <renderer.h>
#include <vertexBuffer.h>
#include <indexBuffer.h>

//struct ShaderProgramSource {
//    std::string VertexSource;
//    std::string FragmentSource;
//};

static std::string ParseShader(const std::string& filepath) {
//static ShaderProgramSource ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
//    enum class ShaderType {
//        NONE = -1,
//        VERTEX = 0,
//        FRAGMENT = 1
//    };
//
    std::string line;
    std::stringstream ss;
//    std::stringstream ss[2];
//    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line)) {
//        if (line.find("#shader") != std::string::npos) {
//            if (line.find("vertex") != std::string::npos)
//                type = ShaderType::VERTEX;
//            else if (line.find("fragement") != std::string::npos)
//                type = ShaderType::FRAGMENT;
//        } else {
//            ss[(int32_t)type] << line << '\n';
            ss << line << '\n';
//        }
    }
//
//    return {ss[0].str(), ss[1].str()};
    return ss.str();
}

static uint32_t CompileShader(uint32_t type, const std::string& source) {
    uint32_t id;
    GLCall(id = glCreateShader(type))
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr))
    GLCall(glCompileShader(id))

    int32_t result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result))
    if (result == GL_FALSE) {
        int32_t length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length))
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message))
        fprintf(stderr, "Failed to compile %s shader\n", type == GL_VERTEX_SHADER ? "vertex" : "fragment");
        fprintf(stderr, "%s\n", message);
        GLCall(glDeleteShader(id))
        return 0;
    }

    return id;
}

static uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    uint32_t program;
    GLCall(program = glCreateProgram())
    uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

int32_t main(void) {

    int32_t major = 0, minor = 0, rev = 0, code = GLFW_NO_ERROR, l;
    const char* desc = NULL;

    if (!glfwInit()) { l = __LINE__;
        code = glfwGetError(&desc);
        display_error_message(code, "GLFW", desc, "glfwInit()", __FILE__, l);
        return code;
    }
    glfwGetVersion(&major, &minor, &rev);
    fprintf(stdout, "GLFW %s\n", glfwGetVersionString());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(640, 480, "Test", NULL, NULL); l = __LINE__;
    if (!window) {
        code = glfwGetError(&desc);
        display_error_message(code, "GLFW", desc, "glfwCreateWindow()", __FILE__, l);
        glfwTerminate();
        return code;
    }
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    int32_t err = glewInit(); l = __LINE__;
    if (GLEW_OK != err) {
        display_error_message(err, "GLEW", (const char*)glewGetErrorString(err), "glewInit()", __FILE__, l);
        return err;
    }
    fprintf(stdout, "GLEW %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout, "OpenGL %s\n", glGetString(GL_VERSION));

    float positions[] = {
        -0.5, -0.5,
         0.5, -0.5,
         0.5,  0.5,
        -0.5,  0.5,
    };

    uint32_t indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    uint32_t vao;
    GLCall(glGenVertexArrays(1, &vao))
    GLCall(glBindVertexArray(vao))

    VertexBuffer vbo(positions, 4 * 2 * sizeof(float));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0));

    IndexBuffer ibo(indices, 6);

    std::string vs = ParseShader("assets/shaders/basic.vs.glsl");
    std::string fs = ParseShader("assets/shaders/basic.fs.glsl");

    uint32_t shader = CreateShader(vs, fs);
    GLCall(glUseProgram(shader));

    int32_t loc;
    GLCall(loc = glGetUniformLocation(shader, "u_Color"))
    ASSERT(loc != -1)
    GLCall(glUniform4f(loc, 0.8, 0.3, 0.8, 1.0))

    GLCall(glUseProgram(0))
    GLCall(glBindVertexArray(0))
    ibo.unbind();
    vbo.unbind();

    float r = 0.0;
    float inc = 0.05;
    while (!glfwWindowShouldClose(window)) {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glUseProgram(shader))
        GLCall(glUniform4f(loc, r, 0.3, 0.8, 1.0))

        GLCall(glBindVertexArray(vao))
        ibo.bind();

        GLCall(glDrawElements(GL_TRIANGLES, 3 * 2, GL_UNSIGNED_INT, nullptr))

        if (r > 1.0)
            inc = -0.05;
        else if (r < 0.0)
            inc = 0.05;

        r += inc;

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}