export module NechtorCore;
import NRwindow;
import nereventer;
import <SFML/Graphics.hpp>;
import <vector>;
import <memory>;
import <string>;
import <filesystem>;
import <iostream>;
import <map>;
import Texture;
import Shader;
import sprite;



export class NechtorCore
{
	std::unique_ptr<NRwindow> window; //группа окон, обрабатывающихся из одного потока
	nereventer eventer;
	TexturePack textures;
	std::map<std::string, std::unique_ptr<Shader>> shaders;
	//Nechto(система управления группой интерпретаторов в одном потоке)
	//loader
	std::shared_ptr<sprite> background;
	void startLoad();
	
	
public:
	NechtorCore()
	{
		window = std::make_unique<NRwindow>(1000, 1000);
		startLoad();
		background = make_shared<sprite>(background, 0, 0, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(2.0f, 2.0f), textures.getID("notFound"));
		background->parPointPos = sf::Vector2f(-1.0f, 1.0f);
		window->insert(background);
	}
	bool update()
	{

		return window->update();
	}
};

