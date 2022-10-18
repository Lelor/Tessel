#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define PI 3.141592653f




int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return -1;
    }

    float cube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 0 0 0
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 1 0 0
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 1 1 0
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 0 1 0

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 0 0 1
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 1 0 1
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 1 1 1
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // 0 1 1

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 0 1 1
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 0 1 0
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 0 0 0
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 0 0 1

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 1 1 1
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 1 1 0
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 1 0 0
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 1 0 1

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 0 0 0
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // 1 0 0
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 1 0 1
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 0 0 1

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 0 1 0
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 1 1 0
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 1 1 1
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // 0 1 1
    };

    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    unsigned int indexBuffer[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    VertexArray va;

    VertexBuffer vb(cube, 5 * 24 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    IndexBuffer ib(indexBuffer, 36);

    Shader shader("res/shaders/Basic.shader");
    Texture texture("res/textures/sample.png");
    texture.Bind(0);
    //shader.Bind();

    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    Renderer renderer;
    /* Loop until the user closes the window */
    GLCall(glEnable(GL_DEPTH_TEST));

    const float cameraSpeed = 2.5f;

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        renderer.Clear();
        /* Render here */
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3((float)glfwGetTime()/2, (float)glfwGetTime() / 2, 0.0f));

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shader.SetUniformMatrix4fv("u_View", glm::value_ptr(view));
        shader.SetUniformMatrix4fv("u_Projection", glm::value_ptr(projection));

        // Camera stuff (to be abstracted)
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;


        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.SetUniformMatrix4fv("u_Model", glm::value_ptr(model));
            renderer.Draw(va, ib, shader);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}