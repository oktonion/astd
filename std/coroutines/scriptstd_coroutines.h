#ifndef SCRIPTSTD_COROUTINES_H
#define SCRIPTSTD_COROUTINES_H

#ifndef ANGELSCRIPT_H 
// Avoid having to inform include path if header is already include before
#include <angelscript.h>
#endif


BEGIN_AS_NAMESPACE


// This function will determine the configuration of the engine
// and use one of the two functions below to register the functions
void RegisterScriptStd_Coroutines(asIScriptEngine *engine);

// Call this function to register the functions
// using native calling conventions
void RegisterScriptStd_Coroutines_Native(asIScriptEngine *engine);

// Use this one instead if native calling conventions
// are not supported on the target platform
void RegisterScriptStd_Coroutines_Generic(asIScriptEngine *engine);

END_AS_NAMESPACE

#endif
