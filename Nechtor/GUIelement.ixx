export module GUIelement;
import <cassert>;
import <vector>;
import <memory>;
import <functional>;
import <iostream>;
import <SFML/Graphics.hpp>;

export class GUIelement
{
	//std::array<float, 4> getBorders();
	//std::array<sf::Vector2f, 4> getVerticles();
public:

	struct detData
	{
		std::shared_ptr<GUIelement> element;
		int fixPoint;
	};

	int fixPoint;
	//std::weak_ptr<GUIelement> parent; //родитель элемента
	std::vector <detData> details;//детали (дочернии элементы)

	virtual void draw(sf::Window window, sf::Vector2f startPos);
	virtual bool isPointIn(sf::Vector2f mPos);
	
	class geometricShape
	{
	public:
		using triangle = sf::Vector2f[3];

		virtual sf::Vector2f getFixPoint(int number);
		virtual bool isPointIn(sf::Vector2f mPos);

		virtual std::vector<triangle> getTriangles();
	};
	geometricShape shape;

	class iterator
	{
		struct wayPoint
		{
			std::shared_ptr<GUIelement> element;
			size_t number;
			sf::Vector2f position;
		};
	public:
		std::vector<wayPoint> way;

		bool stepIn(const int num = 0)
		{
			auto current = way.end()-1;
			if (current->element->details.size() <= num)
				return false;
			way.push_back(wayPoint(current->element->details[num].element, num));
			return true;
		}
		bool stepOut()
		{
			if (way.size() <= 1)
				return false;
			way.pop_back();
			return true;
		}
		bool stepFor()
		{
			assert(way.size() > 1);
			auto current = way.end() - 1;
			if ((current-1)->element->details.size()<=current->number+1)
				return false;
			current->number++;
			current->element = (current - 1)->element->details[current->number].element;
			current->position =
				(current - 1)->element->shape.
				getFixPoint((current-1)->element->details[current->number].fixPoint);
			return true;
		}
		bool operator++()
		{
			if (stepIn())
				return true;
			if (stepFor())
				return true;
			if (way.size() == 1)
				return false;
			do
			{
				stepOut(); 
				if (way.size() == 1)
					return true;
			}
			while (way[way.size() - 1].number >= 
				(way[way.size() - 2].element->details.size()-1));
			stepFor();
			return true;
		}
		sf::Vector2f position()
		{
			return way.back().position;
		}
		GUIelement* operator-> ()
		{
			return way.back().element.get();
		}
		iterator(std::shared_ptr<GUIelement> first)
			:way(1, wayPoint(first, 0, sf::Vector2f(-1, -1)))
		{}
	};
};

//std::array<float, 4> GUIelement::getBorders()
//{
//	std::array<float, 4> borders;
//	parPointPos += offset;
//
//	//вычисление наличия смещения по оси с помощью побитового "и" с номером
//	bool x = static_cast<unsigned short>(tFixPoint) & static_cast<unsigned short>(1); //00 01
//	bool y = static_cast<unsigned short>(tFixPoint) & static_cast<unsigned short>(2); //10 11
//
//	// 0 !0! 1
//	//!2![ ]!3!
//	// 2 !1! 3
//	borders[0] = parPointPos.y - (y) ? size.y : 0;
//	borders[1] = parPointPos.y + (y) ? 0 : size.y;
//
//	borders[2] = parPointPos.x - (x) ? size.x : 0;
//	borders[3] = parPointPos.x + (x) ? 0 : size.x;
//	return borders;
//}
//
//std::array<sf::Vector2f, 4> GUIelement::getVerticles()
//{
//	std::array<sf::Vector2f, 4> verticles;
//	parPointPos += offset;
//
//	//вычисление наличия смещения по оси с помощью побитового "и" с номером
//	bool x = static_cast<unsigned short>(tFixPoint) & static_cast<unsigned short>(1); //00 01
//	bool y = static_cast<unsigned short>(tFixPoint) & static_cast<unsigned short>(2); //10 11
//	
//	// 0     1
//	//   [ ]   
//	// 2     3
//	verticles[0].x = parPointPos.x - ((x) ? size.x : 0);
//	verticles[0].y = parPointPos.y + ((y) ? size.y : 0);
//
//	verticles[1].x = parPointPos.x + ((x) ? 0 : size.x);
//	verticles[1].y = parPointPos.y + ((y) ? size.y : 0);
//
//	verticles[2].x = parPointPos.x - ((x) ? size.x : 0);
//	verticles[2].y = parPointPos.y - ((y) ? 0 : size.y);
//
//	verticles[3].x = parPointPos.x + ((x) ? 0 : size.x);
//	verticles[3].y = parPointPos.y - ((y) ? 0 : size.y);
//	for (int i = 0; i < 4; i++)
//		std::cout << verticles[i].x << " " << verticles[i].y << std::endl;
//	std::cout << std::endl;
//	return verticles;
//}