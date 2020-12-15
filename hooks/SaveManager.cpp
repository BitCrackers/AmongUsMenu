#include "_hooks.hpp"

void dSaveManager_set_BodyColor(uint8_t value, MethodInfo* method)
{
	std::cout << "SaveManager_set_BodyColor " << value << std::endl;
	SaveManager_set_BodyColor(value, method);
}

uint8_t dSaveManager_get_BodyColor(MethodInfo* method)
{
	uint8_t value = SaveManager_get_BodyColor(method);
	std::cout << "SaveManager_get_BodyColor " << value << std::endl;
	return value;
}