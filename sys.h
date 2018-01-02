#ifndef __SYS
#define __SYS

#include "ent.h"
#include "util.h"

namespace ent
{
	class System
	{
		public:
		virtual void Update(const float dt, std::vector<Entity>& ents);
		virtual ~System();
	};
}

#endif /* __SYS */
