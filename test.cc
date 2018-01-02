#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include "util.h"
#include "ent.h"
#include "sys.h"

using namespace std;
using namespace ent;

class TestComponent : public Component
{
	public:
	string name;
};

class TestSystem : public System
{
	public:
	void Update(float dt, vector<Entity>& ents)
	{
		int count_test = 0;
		for(Entity& ent : ents) 
		{
			if(ent.checkComponents<TestComponent>())
			{
				printf("TestComponent has name %s", ent.getComponent<TestComponent>()->name.c_str());
				count_test++;
			}
		}
		printf("%d entities have TestComponent", count_test);
	}
};

int main()
{
	vector<Entity> ents;
	TestSystem sys;

	for(int i = 0; i < 5; i++)
	{
		ents.emplace_back();
		Entity& mEnt = *(ents.end() - 1);
		mEnt.addComponent<TestComponent>();
		mEnt.getComponent<TestComponent>()->name = "Apples";
	}

	for(int i = 0; i < 7; i++)
	{
		ents.emplace_back();
	}

	sys.Update(0.0, ents);
}
