#include "pch-il2cpp.h"
#include "il2cpp-init.h"

#define DO_API(r, n, p) r (*n) p
#include "il2cpp-api-functions.h"
#undef DO_API

#define DO_APP_FUNC(r, n, p, s) r (*n) p
namespace app {
	#include "il2cpp-functions.h"
}
#undef DO_APP_FUNC

#define DO_APP_CLASS(n, s) n ## __Class* n ## __TypeInfo
namespace app {
	#include "il2cpp-classes.h"
}
#undef DO_APP_CLASS

void init_il2cpp()
{
	HMODULE moduleHandle = GetModuleHandleW(L"GameAssembly.dll");

	#define DO_API(r, n, p) n = (r (*) p)(GetProcAddress(moduleHandle, #n))
	#include "il2cpp-api-functions.h"
	#undef DO_API

	using namespace app;

	#define DO_APP_FUNC(r, n, p, s) n = reinterpret_cast<decltype(n)>(get_method(s))
	#include "il2cpp-functions.h"
	#undef DO_APP_FUNC

	#define DO_APP_CLASS(n, s) n ## __TypeInfo = reinterpret_cast<decltype(n ## __TypeInfo)>(get_class(s))
	#include "il2cpp-classes.h"
	#undef DO_APP_CLASS
}