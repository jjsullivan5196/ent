#include <cstdio>
#include <functional>
using namespace std;

template <class F, class... Args>
struct gen {
	gen(F& f) : container(f) {}

	function<void(Args...)> container;
	void operator()(Args... args) {
		return container(args...);
	}
};

void func(int, float, int) {
	printf("Hello!\n");
}

int main() {
	auto run = gen(func);
	run(0, 0.0, 0);
}
