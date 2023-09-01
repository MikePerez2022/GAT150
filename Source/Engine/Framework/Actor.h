#pragma once
#include "Object.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Audio/AudioSystem.h"
#include "Components/Component.h"
#include "Components/Box2DPhysicsComponent.h"
#include <memory>

namespace jojo
{
	class Actor : public Object
	{
	public:
		CLASS_DECLARATION(Actor)

		Actor() = default;
		Actor(const jojo::Transform& transform) :
			transform{ transform }
		{}
		Actor(const Actor& other);
		virtual ~Actor() {
			OnDestroy();
		}

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(jojo::Renderer& renderer);


		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();


		virtual void OnCollision(Actor* other) {}

		virtual void OnCollisionEnter(Actor* other) {}
		virtual void OnCollisionExit(Actor* other) {}
		
		class Scene* m_scene = nullptr;
		friend class Scene;
		class Game* m_game = nullptr;

		jojo::Transform transform;
		std::string tag = "";
		float health = 0;
		float lifespan = -1;
		bool persistent = false;
		bool prototype = false;

	public:
		std::vector<std::unique_ptr<Component>> components;
		bool m_destroyed = false;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
}

