export module Texture;
import "image_loader.h";
import "GLFW/glfw3.h";
import "glad/glad.h";
import <filesystem>;
import <functional>;
import <string>;
import <memory>;
import <map>;
import <vector>;
import <iostream>;
import <cassert>;
import stringOp;

unsigned int newTexture(const std::filesystem::path& path,
	GLint pWRAP_S, GLint pWRAP_T, GLint pMIN_FILTER, GLint pMAG_FILTER);

export class TexturePack
{
	std::map<std::string, unsigned int> texturesNames;	
public:
	
	//ВНИМАНИЕ надо добавить деструктор
	unsigned int add(const std::string name, const std::filesystem::path& path,
		GLint pWRAP_S = GL_REPEAT, GLint pWRAP_T = GL_REPEAT, 
		GLint pMIN_FILTER = GL_LINEAR, GLint pMAG_FILTER = GL_LINEAR)
	{
		unsigned int ID = newTexture(path, pWRAP_S, pWRAP_T, 
			pMIN_FILTER, pMAG_FILTER);
		texturesNames.emplace(name, ID);
		return ID;
	}

	static void use(const unsigned int ID)
	{
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	void use(const std::string& name) const
	{
		if (texturesNames.contains(name))
			glBindTexture(GL_TEXTURE_2D, texturesNames.at(name));
		else if (texturesNames.contains("notFound"))
			glBindTexture(GL_TEXTURE_2D, texturesNames.at("notFound"));
		else
			throw - 1;
	}

	const unsigned int getID(const std::string& name) const
	{
		if (texturesNames.contains(name))
			return texturesNames.at(name);
		else if (texturesNames.contains("notFound"))
			texturesNames.at("notFound");
		else
			throw -1;
		
	}
};


unsigned int newTexture(const std::filesystem::path& path,
	GLint pWRAP_S, GLint pWRAP_T, GLint pMIN_FILTER, GLint pMAG_FILTER)
{
	
	unsigned int ID;
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* tex = stbi_load(path.generic_string().c_str(), 
		&width, &height, &nrChannels, 0);
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, pWRAP_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, pWRAP_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pMIN_FILTER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pMAG_FILTER);
	if (tex)
	{
		if (nrChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, 
				GL_RGBA, GL_UNSIGNED_BYTE, tex);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, 
				GL_RGB, GL_UNSIGNED_BYTE, tex);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		throw(0);
	}
	stbi_image_free(tex);
	return ID;
}
