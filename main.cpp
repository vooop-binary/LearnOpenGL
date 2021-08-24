
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main(int argc, const char** argv) {
    GLFWwindow* window;

    // initialize glfw
    if (!glfwInit()) {
        spdlog::error("Failed to initialize GLFW.");
        return -1;
    }
    spdlog::info(glfwGetVersionString());

    // configure glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // create window
    window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);

    if (!window) {
        spdlog::error("Failed to initialize Window.");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback); // resize

    // initialize all opengl function pointers
    if (glewInit() != GLEW_OK) {
        spdlog::error("Failed to initialize Glew.");
        return -1;
    }

    spdlog::info(glGetString(GL_VERSION));

    // create opengl viewport
    glViewport(0, 0, 800, 600);

    // vertex shader object
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // fragment shader object
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // shader program object
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // add vertex and fragment shader
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // triangle vertices
    float vertices[] = {
        // x    y     z
        -0.5f, -0.5f, 0.0f, // 1
        0.5f, -0.5f, 0.0f,  // 2
        0.0f, 0.5f, 0.0f};  // 3

    unsigned int VBO; // vertex buffer object 
    unsigned int VAO; // vertex array object

    // create vertex array and buffer objects
    glGenVertexArrays(1, &VAO); // vertex array first
    glGenBuffers(1, &VBO);

    // bind objects
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
   
   // add data to buffer object
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // tell opengl how to interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 

    glEnableVertexAttribArray(GL_FALSE);

    // main loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window); // keyboard input

        // add color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // io
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    spdlog::debug("{} {}", width, height);
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}