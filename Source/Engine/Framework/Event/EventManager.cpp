#include "EventManager.h"
#include "Core/Logger.h"

namespace jojo
{
	void EventManager::Update(float dt)
	{
	}

	void EventManager::Subscribe(Event::id_t id, IEventListener* listener, eventFunction function)
	{
		EventDispacher dispatcher;

		dispatcher.listener = listener;
		dispatcher.function = function;

		INFO_LOG("Event subscribed: " << id);

		m_dispachers[id].push_back(dispatcher);
	}

	void EventManager::Unsubscribe(Event::id_t id, IEventListener* listener)
	{

		auto& dispatchers = m_dispachers[id];


		for (auto iter = dispatchers.begin(); iter != dispatchers.end(); iter++)
		{
			if (iter->listener == listener)
			{
				INFO_LOG("Event unsubscribed: " << id);

				dispatchers.erase(iter);
				break;
			}
		}
	}

	void EventManager::DispatchEvent(Event::id_t id, Event::data_t data, void* sender, float time)
	{
		Event event{ id, data };

		if (m_dispachers.find(id) != m_dispachers.end())
		{
			auto& dispatchers = m_dispachers[id];

			for (auto& dispatcher : dispatchers)
			{
				dispatcher.function();
			}
		}
	}
}