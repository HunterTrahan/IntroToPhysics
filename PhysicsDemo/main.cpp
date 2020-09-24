#include "PhysicsDemoApp.h"

int main() 
{
	///
	/// Allocation
	///
	auto app = new PhysicsDemoApp();

	///
	/// Initialise and loop
	///
	app->run("Hunter Physics Demo", 1280, 720, false);

	///
	/// Deallocation
	///
	delete app;

	return 0;
}