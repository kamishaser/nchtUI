export module GLFWsettings;
import "GLFW/glfw3.h";
import "glad/glad.h";
import <stdlib.h>;
import <iostream>;
import <string>;
import <map>;




export void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // ����������, ��� ���� ��������� ������������� ����� �������� ����. 
    glViewport(0, 0, width, height);
}

