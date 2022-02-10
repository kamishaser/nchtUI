import <string>;
import <iostream>;
import <fstream>;
import "GLM/glm.hpp";
import <GLM/gtc/matrix_transform.hpp>;
import <GLM/gtc/type_ptr.hpp>;
import NechtorCore;

import "GLFW/glfw3.h";
import "glad/glad.h";

import Shader;
import Texture;

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: вс€кий раз, когда измен€ютс€ размеры окна (пользователем или операционной системой), вызываетс€ данна€ callback-функци€
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // ”беждаемс€, что окно просмотра соответствует новым размерам окна.
    // ќбратите внимание, высота окна на Retina-диспле€х будет значительно больше, чем указано в программе
    glViewport(0, 0, width, height);
}

int main()
{
    try
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        NechtorCore a;
        while (a.update());
    }
    catch (std::exception& exception)
    {
        std::cerr << "Standard exception: " << exception.what() << '\n';
    }

    glfwTerminate();
    return 0;
}