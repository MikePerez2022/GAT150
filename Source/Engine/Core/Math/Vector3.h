#pragma once
#include <cmath>
#include <sstream>


namespace jojo
{
	class Vector3
	{
	public:
		float x, y, z;

	public:
		Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}
		Vector3(float v) : x{ v }, y{ v }, z{ v } {}
		Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}
		Vector3(int x, int y, int z) : x{ (float)x }, y{ (float)y }, z{ (float)z } {}

		
		Vector3 operator + (const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
		Vector3 operator - (const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
		Vector3 operator / (const Vector3& v) const { return Vector3(x / v.x, y / v.y, z / v.z); }
		Vector3 operator * (const Vector3& v) const { return Vector3(x * v.x, y * v.y, z * v.z); }

		Vector3 operator + (float s) const { return Vector3(x + s, y + s, z + s); }
		Vector3 operator - (float s) const { return Vector3(x - s, y - s, z - s); }
		Vector3 operator / (float s) const { return Vector3(x / s, y / s, z / s); }
		Vector3 operator * (float s) const { return Vector3(x * s, y * s, z * s); }

		Vector3& operator += (const Vector3& v) { x += v.x, y += v.y, z += v.z; return *this; }
		Vector3& operator -= (const Vector3& v) { x -= v.x, y -= v.y, z -= v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { x /= v.x, y /= v.y, z /= v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { x *= v.x, y *= v.y, z *= v.z; return *this; }

		float LengthSqr() const { return (x * x) + (y * y) + (z * z); }
		float Length() const { return sqrt(LengthSqr()); }

		float DistanceSqr(const Vector3& v) { return (v - *this).LengthSqr(); }
		float Distance(const Vector3& v) { return (v - *this).Length(); }

		Vector3 Normalized() const { return *this / Length(); }
		void Normalize() { *this /= Length(); }

		static float Dot(const Vector3& v1, const Vector3& v3);
	};

	inline std::istream& operator >> (std::istream& stream, Vector3& v)
	{
		std::string line;
		std::getline(stream, line);


		std::string xs = line.substr(line.find("{") + 1, line.find(",") - (line.find("{") + 1));
		v.x = std::stof(xs);

		std::string ys = line.substr(line.find(",") + 1, line.find(",") - (line.find(",") + 1));
		v.y = std::stof(ys);

		std::string zs = line.substr(line.find(",") + 1, line.find("}") - (line.find(",") + 1));
		v.z = std::stof(zs);


		return stream;
	}

	// get the dot product beteen v1 and v2 https://www.falstad.com/dotproduct/
	inline float Vector3::Dot(const Vector3& v1, const Vector3& v3)
	{
		return v1.x * v3.x + v1.y * v3.y + v1.z * v3.z;
	}

	using vec3 = Vector3;
}