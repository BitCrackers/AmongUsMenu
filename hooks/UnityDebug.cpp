#include "pch-il2cpp.h"
#include "_hooks.h"
#include "logger.h"
#include "utility.h"
#include "state.hpp"

void dDebug_Log(Object* message, MethodInfo* method) {
	if (State.ShowUnityLogs)
		Log.Debug("UNITY", ToString(message));
	Debug_Log(message, method);
}

void dDebug_LogError(Object* message, MethodInfo* method) {
	if (State.ShowUnityLogs)
		Log.Error("UNITY", ToString(message));
	Debug_LogError(message, method);
}

void dDebug_LogException(Exception* exception, MethodInfo* method) {
	if (State.ShowUnityLogs)
		Log.Error("UNITY", convert_from_string(exception->fields._message));
	Debug_LogException(exception, method);
}

void dDebug_LogWarning(Object* message, MethodInfo* method) {
	if (State.ShowUnityLogs)
		Log.Info("UNITY", ToString(message));
	Debug_LogWarning(message, method);
}