#include "pch-il2cpp.h"
#include "_hooks.h"
#include "logger.h"
#include "utility.h"

void dDebug_Log(Object* message, MethodInfo* method) {
#ifdef _DEBUG
	Log.Debug("UNITY", ToString(message));
#endif
	Debug_Log(message, method);
}

void dDebug_LogError(Object* message, MethodInfo* method) {
	Log.Error("UNITY", ToString(message));
	Debug_LogError(message, method);
}

void dDebug_LogException(Exception* exception, MethodInfo* method) {
	Log.Error("UNITY", convert_from_string(exception->fields._message));
	Debug_LogException(exception, method);
}

void dDebug_LogWarning(Object* message, MethodInfo* method) {
	Log.Info("UNITY", ToString(message));
	Debug_LogWarning(message, method);
}