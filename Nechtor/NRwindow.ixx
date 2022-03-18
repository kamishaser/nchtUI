export module NRwindow;
import <SFML/Graphics.hpp>;
import <vector>;
import <algorithm>;
import GUIelement;

//костыль для glfw::window
class NRwindow;
std::vector<NRwindow*> allWindows;

export class NRwindow
{
	sf::Window window;
	GUIelement::iterator iter;
	

	int windowSizeX;
	int windowSizeY;
public:
	
	void display()//отображение всех элементов на экране
	{
		
		do
			iter->draw(iter.position());
		while (++iter);
	}
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

	NRwindow(int WindowSizeX, int WindowSizeY, std::shared_ptr<GUIelement> mainElement)
		:windowSizeX(WindowSizeX), windowSizeY(WindowSizeY),
		window(glfwCreateWindow(windowSizeX, windowSizeY, "Nechtor", NULL, NULL)),
		iter(mainElement)
	{
		if (!window) throw(0);
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw(-1);
			allWindows.push_back(this);
		}
	}
};

