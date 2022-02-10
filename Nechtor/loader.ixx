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

	std::map<std::string, std::function<void(std::string)>> saveTypes;//��� - (��� - ��������)[])
	
	void save(std::filesystem::path filepath); //���������� � ���� �� ������ ������� ���������� ��� ������� ���� �������
	void load(std::filesystem::path filepath); //�������� �� ����� �� ������ ������� ���������� ��� ������� ���� �������

	void add(std::string typeName, std::function<void(std::string)> st); //���������� ������ �������� ��� ����������
	void clear() { saveTypes.clear();}  //��������
};

void loader::add(std::string typeName, std::function<void(std::string)> st)
{
	auto i = saveTypes.find(typeName);
	if (i == saveTypes.end())
		saveTypes.emplace(typeName, st);
	else
		i->second = st;
}
void loader::load(std::filesystem::path filepath) //�������� �� ����� �� ������ ������� ���������� ��� ������� ���� �������
{
	fileStream.open(filepath, std::ios::in, std::ios::binary);
	assert(fileStream);//���� ���� �� ��������
	enum stages { text, space };//��������� ������
	stages stage = space;//��������� ��������� -������
	std::stringstream tostring; //��������� ����� ��� ����������
	char t;//��������� ������
	std::map<std::string, std::function<void(std::string)>>::iterator i;
	while (fileStream)//���� ���� ���� ������
	{
		fileStream.read(&t, 1);//�
		switch (stage)//�������� � ����������� �� ���������
		{
		case space:
			if (t != ' ' && t != '\n')
			{
				tostring.put(t);
				stage = text;
			}
			break;
		case text:
			if (t == ':')//��������� �������� ����
			{
				std::string name = tostring.str();
				i = saveTypes.find(name);
				tostring.str("");
				stage = space;
			}
			else if (t == ';')//���������� ��������
			{
				if (!(i == saveTypes.end()))
					i->second(tostring.str());
				tostring.str("");
				stage = space;
			}
			else
				tostring.put(t);//���������� ���������� ������
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