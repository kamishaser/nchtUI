export module loader;
import <fstream>;
import <filesystem>;
import <functional>;
import <sstream>;
import <string>;
import <map>;
import <utility>;
import <cassert>;




export class loader
{
	std::fstream fileStream;
public:

	std::map<std::string, std::function<void(std::string)>> saveTypes;//тип - (имя - значение)[])
	
	void save(std::filesystem::path filepath); //сохранение в файл по набору функций сохранения для каждого типа объекта
	void load(std::filesystem::path filepath); //загрузка из файла по набору функций сохранения для каждого типа объекта

	void add(std::string typeName, std::function<void(std::string)> st); //добавление набора объектов для сохранения
	void clear() { saveTypes.clear();}  //очищение
};

void loader::add(std::string typeName, std::function<void(std::string)> st)
{
	auto i = saveTypes.find(typeName);
	if (i == saveTypes.end())
		saveTypes.emplace(typeName, st);
	else
		i->second = st;
}
void loader::load(std::filesystem::path filepath) //загрузка из файла по набору функций сохранения для каждого типа объекта
{
	fileStream.open(filepath, std::ios::in, std::ios::binary);
	assert(fileStream);//если файл не открылся
	enum stages { text, space };//состояния чтения
	stages stage = space;//начальное состояние -пробел
	std::stringstream tostring; //строковый поток для сохранения
	char t;//временный символ
	std::map<std::string, std::function<void(std::string)>>::iterator i;
	while (fileStream)//цикл пока файл открыт
	{
		fileStream.read(&t, 1);//з
		switch (stage)//действия в зависимости от состояния
		{
		case space:
			if (t != ' ' && t != '\n')
			{
				tostring.put(t);
				stage = text;
			}
			break;
		case text:
			if (t == ':')//изменение текущего типа
			{
				std::string name = tostring.str();
				i = saveTypes.find(name);
				tostring.str("");
				stage = space;
			}
			else if (t == ';')//добавление элемента
			{
				if (!(i == saveTypes.end()))
					i->second(tostring.str());
				tostring.str("");
				stage = space;
			}
			else
				tostring.put(t);//заполнение строкового потока
			break;
		}
	}
	fileStream.close();
}

export class lovector
{
	mutable int i = 0;
	std::vector<std::string>& slv;
public:
	const std::function<void(std::string)> load = [&](std::string value)->void
	{
		slv.push_back(value);
	};
	

	void restart() { i = 0; }
	lovector(std::vector<std::string>& saloVector)
		:slv(saloVector){}		
};