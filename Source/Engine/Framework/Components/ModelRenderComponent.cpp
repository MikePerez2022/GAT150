#include "ModelRenderComponent.h"
#include "Framework/Actor.h"

namespace jojo
{

	void jojo::ModelRenderComponent::Update(float dt)
	{
	}

	void jojo::ModelRenderComponent::Draw(Renderer& renderer)
	{
		return m_model->Draw(renderer, m_owner->m_transform);
	}
}

