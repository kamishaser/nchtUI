export module NRevent;
import <bitset>;
import <memory>;

export struct NRevent
{//������� Nechtor
	enum class T
	{
		exception, //����������
		end, //������� �������� � ���������� ��������
		file, //�������� � �������
		user, //�������� ������������
		enumEND //��������� ������� (�� ����� ���� �����������)
	};

	std::weak_ptr<void> initiatorID;
	std::weak_ptr<NRevent> reason;
	std::bitset<8> type;
};

