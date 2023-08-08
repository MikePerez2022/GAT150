#include "Model.h"
#include "Renderer.h"
#include <sstream>

namespace jojo
{
	bool Model::Load(const std::string& fileName)
	{
		std::string buffer = "";

		jojo::readFile(fileName, buffer);
		
		std::stringstream stream(buffer);

		stream >> m_color;
		
		std::string line;
		std::getline(stream, line);

		int numpoints = std::stoi(line);

		for (int i = 0; i < numpoints; i++) {
			vec2 point; 
			
			stream >> point;

			m_points.push_back(point);
		}

		GetRadius();

		return true;
	}
	void Model::Draw(Renderer& renderer, const vec2& position, float rotation, float scale)
	{
		if (m_points.empty()) return;

		jojo::g_renderer.SetColor(Color::ToInt(m_color.r), Color::ToInt(m_color.g), Color::ToInt(m_color.b), Color::ToInt(m_color.a));
		for (int i = 0; i < m_points.size() - 1; i++)
		{
			vec2 p1 = (m_points[i] * scale).Rotate(rotation) + position;
			vec2 p2 = (m_points[i + 1] * scale).Rotate(rotation) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Model::Draw(Renderer& renderer, const Transform& transform)
	{		
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}

	float Model::GetRadius() 
	{
		if (this == nullptr) return 0;

		if (m_radius) return m_radius;

		for (auto& point : m_points)
		{
			float length = point.Length();
			m_radius = Max(m_radius, length);
		}

		return m_radius;
	}

	bool Model::Create(std::string filename, ...)
	{
		return Load(filename);
	}
}