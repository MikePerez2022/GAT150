#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Audio/AudioSystem.h"
#include "Components/Component.h"
#include <memory>

namespace jojo
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const jojo::Transform& transform) :
			m_transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(jojo::Renderer& renderer);


		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();


		float GetRadius() { return 5.0f; }
		virtual void OnCollision(Actor* other) {}
		
		class Scene* m_scene = nullptr;
		friend class Scene;
		class Game* m_game = nullptr;

		jojo::Transform m_transform;
		std::string m_tag;
		float m_health = 0;
		float m_lifespan = -1;

	protected:
		std::vector<std::unique_ptr<Component>> m_components;
		bool m_destroyed = false;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
}

