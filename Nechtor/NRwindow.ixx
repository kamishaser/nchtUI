export module NRwindow;
import "GLFW/glfw3.h";
import "glad/glad.h";
import "GLM/glm.hpp";
import "image_loader.h";
import <memory>;
import <functional>;
import <utility>;
import <iostream>;
import <string>;
import <vector>;
import GLFWsettings;
import Texture;
import sprite;
import Shader;
import nereventer;
import GUIelement;


const glm::vec2 temp1(0.0f, 0.0f);
const glm::vec2 temp2(0.5f, 0.5f);
const std::weak_ptr<GUIelement> temp3;
const NRevent temp4;

export class NRwindow
{
	GLFWwindow* window;
	std::vector<std::pair<size_t, std::weak_ptr<GUIelement>>> displayed;
	
	std::weak_ptr<GUIelement> mOverElement;

	void display()//отображение всех элементов на экране
	{
		glfwMakeContextCurrent(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		for (auto iter = displayed.begin(); iter != displayed.end(); iter++)
		{
			//if (!iter->second.expired())
				iter->second.lock()->draw();
			//else
			//	displayed.erase(iter);
		}

		
		glfwSwapBuffers(window);
	}
	
	void findMouseOveredElement()
	{
		mOverElement.reset();
		glm::vec2 mousePos(0, 0); //условное положение мыши
		if (!displayed.empty())
		{
			auto iter = displayed.end();
			do
			{
				iter--;
				if (iter->second.lock()->isPointIn(mousePos))
				{
					mOverElement = iter->second;
					break;
				}
			} while (iter != displayed.begin());
		}
	}
	auto find(size_t ID)
	{
		for (auto iter = displayed.begin(); iter != displayed.end(); iter++)
			if (iter->first == ID)
				return iter;
		return displayed.end();
	}
public:
	
	bool update()
	{
		if (glfwWindowShouldClose(window))
			return false;
		display();
		//поиск элемента, на который наведён курсор мыши
		//findMouseOveredElement();

		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
			return false;
		}
		return true;
	}
	NRwindow(int windowSizeX, int windowSizeY)
		:window(glfwCreateWindow(windowSizeX, windowSizeY, "Nechtor", NULL, NULL))
	{
		if (!window) throw(0);
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw(-1);
		}
	}

	void insert(std::weak_ptr<GUIelement> newElem)
	{
		if (!contains(newElem.lock()->ID))
			displayed.emplace_back(newElem.lock()->ID, newElem);
	}
	void insert(std::vector < std::weak_ptr<GUIelement>> els)
	{
		for (auto i = els.begin(); i != els.end(); i++)
			insert(*i);
	}
	void erase(size_t ID)
	{
		if(contains(ID))
			displayed.erase(find(ID));
	}
	void erase(std::weak_ptr<GUIelement> el)
	{
		erase(el.lock()->ID);
	}
	void erase(std::vector<size_t> els)
	{
		for (auto i = els.begin(); i != els.end(); i++)
			erase(*i);
	}
	bool contains(size_t ID)
	{
		for (auto iter = displayed.begin(); iter != displayed.end(); iter++)
			if (iter->first == ID)
				return true;
		return false;
	}
	
};