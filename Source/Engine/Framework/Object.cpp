#include "Object.h"

namespace jojo
{
	bool Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);

		return true;
	}
}