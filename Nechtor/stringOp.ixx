export module stringOp;
import <string>;
import <filesystem>;
import <functional>;
import <sstream>;
import <cassert>;
import <vector>;
import <utility>;
import <map>;

import <iostream>;

//получение правильного пути из сущействующего каталога
export std::filesystem::path getRightPath
	(const std::vector<std::string>& pathset, const std::string filename)
{
	for (int i = 0; i < pathset.size(); i++)
		if (std::filesystem::exists(std::filesystem::path(pathset[i]) / 
			std::filesystem::path(filename)))
		{
			return std::filesystem::path(pathset[i]) / 
				std::filesystem::path(filename);
		}
	std::cout << filename << " not found" << std::endl;
	assert(false);
}

//получение набора написанных через запятую параметров из строки
export std::vector<std::string> 
getParametrs(const std::string& text, char separator = ',')
{
	std::vector<std::string> parametrs;
	std::stringstream sstream;
	bool space = true;
	for (size_t i = 0; i < text.size(); i++)
	{
		if (space)
		{
			if ((text[i] != ' ') && (text[i] != '\n'))
			{
				sstream.put(text[i]);
				space = false;
			}
		}
		else
		{
			if (text[i] == separator)
			{
				space = true;
				parametrs.push_back(sstream.str());
				sstream.str("");
			}
			else
			{
				sstream.put(text[i]);
			}
		}
	}
	parametrs.push_back(sstream.str());
	//for(int i = 0; i < parametrs.size(); i++)
	return parametrs;
}

//glad define из строк в число и из числа в строки
//export int GLADdefine(std::string define)
//{
//	if(define == std::string("GL_TRUE"))
//		return GL_TRUE;
//	if(define == std::string("GL_FALSE"))
//		return GL_FALSE;
//	if(define == std::string("GL_FLOAT"))
//		return GL_FLOAT;
//	if(define == std::string("GL_INT"))
//		return GL_INT;
//	if(define == std::string("GL_UNSIGNED_INT"))
//		return GL_UNSIGNED_INT;
//	if(define == std::string("GL_SHORT"))
//		return GL_SHORT;
//	if(define == std::string("GL_UNSIGNED_SHORT"))
//		return GL_UNSIGNED_SHORT;
//	if(define == std::string("GL_BYTE"))
//		return GL_BYTE;
//	if(define == std::string("GL_UNSIGNED_BYTE"))
//		return GL_UNSIGNED_BYTE;
//	if(define == std::string("GL_REPEAT"))
//		return GL_REPEAT;
//	if(define == std::string("GL_MIRRORED_REPEAT"))
//		return GL_MIRRORED_REPEAT;
//	if(define == std::string("GL_CLAMP_TO_EDGE"))
//		return GL_CLAMP_TO_EDGE;
//	if(define == std::string("GL_CLAMP_TO_BORDER"))
//		return GL_CLAMP_TO_BORDER;
//	if(define == std::string("GL_NEAREST"))
//		return GL_NEAREST;
//	if(define == std::string("GL_LINEAR"))
//		return GL_LINEAR;
//	try
//	{
//		return std::stoi(define);
//	}
//	catch (std::exception e)
//	{
//		std::cout << "GLAD define " << define << " not found" << std::endl;
//		throw e;
//	}
//}
//export std::string GLADdefine(int define)
//{
//	if(define == GL_TRUE)
//		return "GL_TRUE";
//	if(define == GL_FALSE)
//		return "GL_FALSE";
//	if(define == GL_FLOAT)
//		return "GL_FLOAT";
//	if(define == GL_INT)
//		return "GL_INT";
//	if(define == GL_UNSIGNED_INT)
//		return "GL_UNSIGNED_INT";
//	if(define == GL_SHORT)
//		return "GL_SHORT";
//	if(define == GL_UNSIGNED_SHORT)
//		return "GL_UNSIGNED_SHORT";
//	if(define == GL_BYTE)
//		return "GL_BYTE";
//	if(define == GL_UNSIGNED_BYTE)
//		return "GL_UNSIGNED_BYTE";
//	if (define == GL_REPEAT)
//		return "GL_REPEAT";
//	if (define == GL_MIRRORED_REPEAT)
//		return "GL_MIRRORED_REPEAT";
//	if (define == GL_CLAMP_TO_EDGE)
//		return "GL_CLAMP_TO_EDGE";
//	if (define == GL_CLAMP_TO_BORDER)
//		return "GL_CLAMP_TO_BORDER";
//	if (define == GL_NEAREST)
//		return "GL_NEAREST";
//	if (define == GL_LINEAR)
//		return "GL_LINEAR";
//
//	return std::to_string(define);
//}