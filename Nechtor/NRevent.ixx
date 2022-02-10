export module NRevent;
import <bitset>;
import <memory>;

export struct NRevent
{//событие Nechtor
	enum class T
	{
		exception, //исключение
		end, //событие приводит к завершению операции
		file, //операция с файлами
		user, //действие пользователя
		enumEND //последний элемент (не может быть использован)
	};

	std::weak_ptr<void> initiatorID;
	std::weak_ptr<NRevent> reason;
	std::bitset<8> type;
};

