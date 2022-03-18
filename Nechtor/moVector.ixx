export module moVector;
import <SFML/Graphics.hpp>;
import <functional>;
import <chrono>;
import <memory>;
import <cassert>;
import <cmath>;

using namespace std::chrono;
using namespace std;

const float minValueDiapason = 0.001f; //минимальный диапазон значений при котором
//имеет смысл устремлять одно к другому


float func(float present, float future, float speed, milliseconds timeInterval)
{//простейшай функция реализующая смещение одного значения с стророну другого
	float valueInterval = std::abs(future - present);
	for (milliseconds i = 0ms; i < timeInterval; i++)
	{
		valueInterval *= speed;
		if (valueInterval < minValueDiapason)
		{
			present = future;
			return present;
		}
	}
	present += valueInterval;
	return present;
}

export class moValue //2 значения типа float одно из которых стремится к другому со временем
{//проще говоря анимированное значение
	static float speedTransformFromSecToMillisec(float speed) //ТЫ НЕ ПОЙМЁШЬ!
	{//преобразование из "во сколько раз значение уменьшится за секунду" 
		//			   в "во сколько раз значение уменьшится за милисекунду"
		return static_cast<float>(1 - (std::pow((1 - (1 / speed)), 1000)));
	}

	float value;//текущее значение
	float speed;//скорость смещения
	milliseconds lastUp;//время последнего обновления
public:
	moValue(float newValue, float Speed = 2)
		:value(newValue),
		lastUp(duration_cast<milliseconds>(system_clock::now().time_since_epoch()))
	{
		assert(Speed > 1);
		speed = speedTransformFromSecToMillisec(Speed);
	}

	void setSpeed(float Speed)
	{
		assert(Speed > 1);
		speed = speedTransformFromSecToMillisec(Speed);
	}

	float operator()(float future)
	{
		milliseconds nowUp = duration_cast<milliseconds>
			(system_clock::now().time_since_epoch());
		value = func(value, future, speed, nowUp - lastUp);
		lastUp = nowUp; 
		return value;
	}
};

export class moVector //вектор из 2 moValue
{
	moValue x;
	moValue y;
public:

	moVector(float X, float Y, float speed)
		:x(X, speed), y(Y, speed) {}
	moVector(sf::Vector2f value)
		:x(value.x),
		 y(value.y){}

	sf::Vector2f operator()(sf::Vector2f future)
	{
		return sf::Vector2f(x(future.x), y(future.y));
	}

	void setSpeed(float speed)
	{
		x.setSpeed(speed);
		y.setSpeed(speed);
	}
};

export class ptrVector //вектор с 2 shared_ptr(float)
{
public:
	std::shared_ptr<float> x;
	std::shared_ptr<float> y;

	ptrVector(std::shared_ptr<float> nx, std::shared_ptr<float> ny)
		:x(nx), y(ny) {}
	ptrVector(float nx, float ny)
		:x(std::make_shared<float>(nx)), y(std::make_shared<float>(ny)) {}
	ptrVector(sf::Vector2f n)
		:x(std::make_shared<float>(n.x)), y(std::make_shared<float>(n.y)) {}

	ptrVector& operator= (sf::Vector2f n)
	{
		x = std::make_shared<float>(n.x);
		y = std::make_shared<float>(n.y);
		return *this;
	}

	operator sf::Vector2f()
	{
		return sf::Vector2f(*x, *y);
	}
};