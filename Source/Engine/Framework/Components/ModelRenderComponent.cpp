#include "ModelRenderComponent.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace jojo
{
	CLASS_DEFINITION(ModelRenderComponent)

	bool ModelRenderComponent::Initialize()
	{
		if (modelName.empty()) return false;

		m_model = GET_RESOURCE(Model, modelName);
		
		return true;
	}

	void jojo::ModelRenderComponent::Update(float dt)
	{
	}

	void jojo::ModelRenderComponent::Draw(Renderer& renderer)
	{
		return m_model->Draw(renderer, m_owner->transform);
	}

	void jojo::ModelRenderComponent::Read(const json_t& value)
	{
		READ_DATA(value, modelName);
	}
}

