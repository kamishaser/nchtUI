export module GUIelement;
import NRevent;
import <vector>;
import <array>;
import <memory>;
import <functional>;
import <iostream>;
import "GLM/glm.hpp";

size_t nextID = 0;
export class GUIelement
{
protected:
	std::array<float, 4> getBorders();
	std::array<glm::vec2, 4> getVerticles();
public:
	GUIelement(std::weak_ptr<GUIelement> tc, int pfix, int tfix, glm::vec2 ot, glm::vec2 sz)
		:ID(++nextID), trunk(tc), pFixPoint(pfix), tFixPoint(tfix), offset(ot), size(sz){}
	const size_t ID;
	int pFixPoint; //точка родительского элемента, относительно которой происходит фиксация
	int tFixPoint; //зафиксированная относительно родителя точка, этого элемента
	glm::vec2 offset; //смещение фиксации
	glm::vec2 size; //размер элемента
	std::vector <std::shared_ptr<GUIelement>> details;
	std::weak_ptr<GUIelement> trunk; //родитель элемента
	glm::vec2 parPointPos; //позиция вершины родителя, относительно которой была произведена фиксация
	std::vector<size_t> allID()
	{//после этой вида этой функции у всех любителей оптимизации поедет крыша
		std::vector<size_t> ALLID;
		for (auto i = details.begin(); i != details.end(); i++)
		{
			std::vector<size_t> temp = (*i)->allID();
			ALLID.insert(ALLID.end(), temp.begin(), temp.end());
		}
		return ALLID;
	}

	virtual bool isPointIn(glm::vec2 mPos)
	{
		std::array<float, 4> borders = getBorders();
		return (mPos.y > borders[0] && mPos.y < borders[1] && mPos.x > borders[2] && mPos.x < borders[3]);
	};
	virtual void draw(){};
};

std::array<float, 4> GUIelement::getBorders()
{
	std::array<float, 4> borders;
	parPointPos += offset;

	//вычисление наличия смещения по оси с помощью побитового "и" с номером
	bool x = static_cast<unsigned short>(tFixPoint) & static_cast<unsigned short>(1); //00 01
	bool y = static_cast<unsigned short>(tFixPoint) & static_cast<unsigned short>(2); //10 11

	// 0 !0! 1
	//!2![ ]!3!
	// 2 !1! 3
	borders[0] = parPointPos.y - (y) ? size.y : 0;
	borders[1] = parPointPos.y + (y) ? 0 : size.y;

	borders[2] = parPointPos.x - (x) ? size.x : 0;
	borders[3] = parPointPos.x + (x) ? 0 : size.x;
	return borders;
}

std::array<glm::vec2, 4> GUIelement::getVerticles()
{
	std::array<glm::vec2, 4> verticles;
	parPointPos += offset;

	//вычисление наличия смещения по оси с помощью побитового "и" с номером
	bool x = static_cast<unsigned short>(tFixPoint) & static_cast<unsigned short>(1); //00 01
	bool y = static_cast<unsigned short>(tFixPoint) & static_cast<unsigned short>(2); //10 11
	
	// 0     1
	//   [ ]   
	// 2     3
	verticles[0].x = parPointPos.x - ((x) ? size.x : 0);
	verticles[0].y = parPointPos.y + ((y) ? size.y : 0);

	verticles[1].x = parPointPos.x + ((x) ? 0 : size.x);
	verticles[1].y = parPointPos.y + ((y) ? size.y : 0);

	verticles[2].x = parPointPos.x - ((x) ? size.x : 0);
	verticles[2].y = parPointPos.y - ((y) ? 0 : size.y);

	verticles[3].x = parPointPos.x + ((x) ? 0 : size.x);
	verticles[3].y = parPointPos.y - ((y) ? 0 : size.y);
	for (int i = 0; i < 4; i++)
		std::cout << verticles[i].x << " " << verticles[i].y << std::endl;
	std::cout << std::endl;
	return verticles;
}