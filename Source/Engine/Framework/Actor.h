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
		Actor(const jojo::Transform& transform, const std::shared_ptr<Model> model) :
			m_transform{ transform },
			m_model{ model } 
		{}
		Actor(const jojo::Transform& transform) : m_transform{ transform } {} 

		virtual void Update(float dt);
		virtual void Draw(jojo::Renderer& renderer);


		void AddComponent(std::unique_ptr<Component> component);


		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }
		virtual void OnCollision(Actor* other) {}
	
		void AddForce(vec2 force) { m_velocity += force; }
		void SetDampening(float dampening) { m_dampening = dampening; }
		
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

		std::shared_ptr<Model> m_model;

		vec2 m_velocity;
		float m_dampening = 0;
	};
}

