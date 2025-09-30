#ifndef SCRIPTSTD_RATIO_H
#define SCRIPTSTD_RATIO_H

#include <cstring>

#ifndef ANGELSCRIPT_H 
// Avoid having to inform include path if header is already include before
#include <angelscript.h>
#endif


BEGIN_AS_NAMESPACE



// This function will determine the configuration of the engine
// and use one of the two functions below to register the functions
int RegisterScriptStd_Ratio(asIScriptEngine *engine);

// Call this function to register the functions
// using native calling conventions
int RegisterScriptStd_Ratio_Native(asIScriptEngine *engine);

// Use this one instead if native calling conventions
// are not supported on the target platform
int RegisterScriptStd_Ratio_Generic(asIScriptEngine *engine);

END_AS_NAMESPACE

#endif
