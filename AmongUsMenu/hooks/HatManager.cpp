#include "_hooks.hpp"

using namespace app;

HatBehaviour__Array* dHatManager_GetUnlockedHats(HatManager* __this, MethodInfo* method) {
	return __this->fields.AllHats->fields._items;
}

PetBehaviour__Array* dHatManager_GetUnlockedPets(HatManager* __this, MethodInfo* method) {
	return __this->fields.AllPets->fields._items;
}

SkinData__Array* dHatManager_GetUnlockedSkins(HatManager* __this, MethodInfo* method) {
	return __this->fields.AllSkins->fields._items;
}