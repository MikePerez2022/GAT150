#include "Object.h"

namespace jojo
{
	void Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);
	}
}