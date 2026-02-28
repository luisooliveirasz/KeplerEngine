#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "graphics/shader.h"
#include "graphics/renderer2D.h"
#include "graphics/texture2D.h"
#include "graphics/sprite.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

#include <string.h>

const char* WINDOW_TITLE = "Game 1";
unsigned int WINDOW_WIDTH = 1366;
unsigned int WINDOW_HEIGHT = 768;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader defaultShader("assets/shaders/default_vertex_shader.vert", "assets/shaders/default_fragment_shader.frag");
    Renderer2D renderer;

    int samplers[16];
    for (int i = 0; i < 16; i++)
        samplers[i] = i;

    glm::mat4 projection =
        glm::ortho(
            0.0f,
            (float)WINDOW_WIDTH,
            0.0f,
            (float)WINDOW_HEIGHT
        );

    glm::mat4 view = glm::mat4(1.0f);

    glm::mat4 viewProjection = projection * view;

    defaultShader.Use();
    defaultShader.SetIntArray("u_Textures", samplers, 16);
    defaultShader.SetMat4("u_ViewProjection", viewProjection);

    auto texture = std::make_shared<Texture2D>("assets/textures/frisk.png");

    Sprite sprite(
        texture,
        { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0.0f },
        { 200.0f, 200.0f }
    );

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        defaultShader.Use();

        renderer.BeginBatch();
        renderer.DrawSprite(sprite);
        renderer.EndBatch();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}