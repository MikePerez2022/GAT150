#pragma once
#include "Factory.h"
#include "Core/Json.h"
#include <string>

#define CLASS_DECLARATION(classname) \
virtual const char* GetClassName() { return #classname; } \
virtual void Read(const rapidjson::Value& value); \
virtual std::unique_ptr<Object> Clone() { return std::make_unique<classname>(*this); }\
class Register \
{ \
public: \
	Register() \
	{ \
		Factory::Instance().Register<classname>(#classname); \
	} \
};

#define CLASS_DEFINITION(classname) classname::Register register_class;


namespace jojo
{

	class Object
	{
	public:
		CLASS_DECLARATION(Object);


		Object() = default;
		Object(const std::string& name) : name{ name } {}
		virtual ~Object() { OnDestroy(); }


		virtual bool Initialize() { return true; }
		virtual void OnDestroy() {}

	public:
		std::string name;
		bool active = true;
	};

}