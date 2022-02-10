export module nereventer;
export import NRevent;
import <functional>;
import <atomic>;
import <mutex>;
import <memory>;
import <vector>;
import <unordered_map>;

export class nereventer //класс, оповещающий слушателей о событиях
{
protected:
	mutable std::mutex mut;
	std::unordered_map<size_t, std::function<void(std::shared_ptr<NRevent>)>> listeners;
	size_t liNum = 0;
public:
	void operator()(const NRevent& newEvent) const;
	size_t addListener(std::function<void(std::shared_ptr<NRevent>)> listener);
	void removeListener(size_t ID);
};

//запуск события
void nereventer::operator()(const NRevent& newEvent) const
{
	std::shared_ptr<NRevent> Event = std::make_shared<NRevent>(newEvent);
	mut.lock();
	for (int i = 0; i < listeners.size(); i++)
	{
		auto iter = listeners.begin();
		for (int i2 = 0; i2 < i; i2++)//supercruch
			++iter;
		auto temp = iter->second;
		mut.unlock();
		temp(std::make_shared<NRevent>(newEvent));
		mut.lock();
	}
	mut.unlock();
}

//добавить слушателя
size_t nereventer::addListener
(std::function<void(std::shared_ptr<NRevent>)> listener)
{
	mut.lock();
	size_t temp = liNum++;
	listeners.emplace(temp, listener);
	mut.unlock();
	return temp;
}
//удавить слушателя по ID
void nereventer::removeListener(size_t ID)
{
	mut.lock();
	listeners.erase(listeners.find(ID));
	mut.unlock();
}

export class listener
{
	nereventer& eventer;
	size_t ID;
	listener(listener& l) = delete;
public:
	listener(nereventer& ev, std::function<void(std::shared_ptr<NRevent>)> func)
		:eventer(ev)
	{
		ID = eventer.addListener(func);
	}
	~listener()
	{
		eventer.removeListener(ID);
	}
};