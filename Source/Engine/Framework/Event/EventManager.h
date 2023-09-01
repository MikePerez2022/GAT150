#pragma once
#include "Event.h"
#include "Framework/Singleton.h"
#include <map>
#include <list>
#include <functional>

#define EVENT_SUBSCRIBE(id, function)	jojo::EventManager::Instance().Subscribe(id, this, std::bind(&function, this, std::placeholders::_1));
#define EVENT_UNSUBSCRIBE(id)			jojo::EventManager::Instance().Unsubscribe(id, this);
#define EVENT_DISPATCH(id, data)		jojo::EventManager::Instance().DispatchEvent(id,data)

namespace jojo
{
	class IEventListener
	{
		//
	};

	class EventManager : public Singleton<EventManager>
	{
	public:
		using eventFunction = std::is_function<void(const Event&)>;

		struct EventDispacher
		{
			IEventListener* listener = nullptr;// object that can listen to events
			eventFunction function; // function that is called on event
		};

	public:
		void Update(float dt);

		void Subscribe(Event::id_t id, IEventListener* listener, eventFunction function);
		void Unsubscribe(Event::id_t id, IEventListener* listener);

		void DispatchEvent(Event::id_t id, Event::data_t data, void* sender = nullptr, float time = 0);

		friend class singleton;

	private:
		EventManager() = default; 

	public:
		std::map<Event::id_t, std::list<EventDispacher>> m_dispachers;
	};
}
