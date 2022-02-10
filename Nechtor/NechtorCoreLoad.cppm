import NechtorCore;
import <functional>;
import <fstream>;
import <string>;
import <vector>;
import <iostream>;
import <cassert>;
import Shader;
import loader;
import sprite;
import stringOp;



void NechtorCore::startLoad()
{
	std::vector<std::string> shaderPaths;
	lovector saloShaderPaths(shaderPaths);
	std::vector<std::string> texturePaths;
	lovector svtexturePaths(texturePaths);
	const std::function<void(std::string)> shaderLoad = [&](std::string text)->void
	{
		std::stringstream shs; //строковый поток
		std::string name; //имя шэйдера

		std::vector<Shader::vertexAtrib>vatrib;

		std::vector<std::string> parametrs = getParametrs(text);
		assert(parametrs.size() > 2);
		name = parametrs[0];
		std::filesystem::path vshader = getRightPath(shaderPaths, parametrs[1]);
		std::filesystem::path fshader = getRightPath(shaderPaths, parametrs[2]);

		shaders.emplace(name, std::make_unique<Shader>(vshader.generic_string(),
			fshader.generic_string()));
	};

	const std::function<void(std::string)> textureLoad = [&](std::string text)->void
	{
		std::vector<std::string> parametrs = getParametrs(text);
		assert(parametrs.size() > 1);
		std::filesystem::path path = getRightPath(texturePaths, parametrs[1]);
		std::string name = parametrs[0];
		switch (parametrs.size())
		{
		case 2:
			textures.add(name, path);
			break;
		case 3:
			textures.add(name, path, std::stoi(parametrs[2]));
			break;
		case 4:
			textures.add(name, path, std::stoi(parametrs[2]),
				std::stoi(parametrs[3]));
			break;
		case 5:
			textures.add(name, path, std::stoi(parametrs[2]),
				std::stoi(parametrs[3]), std::stoi(parametrs[4]));
			break;
		case 6:
			textures.add(name, path, std::stoi(parametrs[2]),
				std::stoi(parametrs[3]), std::stoi(parametrs[4]),
				std::stoi(parametrs[5]));
			break;
		default:
			assert(false);
		}
	};

	loader lo;
	lo.add("console", [](std::string text)->void
		{
			std::cout << text << std::endl;
		});
	lo.add("texturePath", svtexturePaths.load);
	lo.add("shaderPath", saloShaderPaths.load);
	lo.add("shader", shaderLoad);
	lo.add("texture", textureLoad);
	lo.load("startLoad.txt");

	sprite::activate(shaders.at("sprite").get());

}

