#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include "util.h"
#include "ent.h"
#include "sys.h"

using namespace std;
using namespace ent;

int countTicks(const float dt, vector<Entity>&)
{
	static int count = 0;
	count++;
	printf("Tick %d, deltaTime: %f\n", count, dt);
	return 0;
}

int main()
{
	return runGame({&countTicks});
}
