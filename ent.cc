#include <string>
#include "ent.h"

namespace ent
{
	bool Entity::Enabled() const { return enabled; }
	bool Entity::Enabled(bool toggle) { return enabled = toggle; }
	std::string Entity::Tag() const { return tag; }
	std::string Entity::Tag(std::string t) { return tag = t; }
}
