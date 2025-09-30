#ifndef SCRIPTFMT_H
#define SCRIPTFMT_H

#ifndef ANGELSCRIPT_H 
// Avoid having to inform include path if header is already include before
#include <angelscript.h>
#endif


BEGIN_AS_NAMESPACE

// This function will determine the configuration of the engine
// and use one of the two functions below to register the math functions
void RegisterScriptFmt(asIScriptEngine *engine);

// Call this function to register the math functions
// using native calling conventions
void RegisterScriptFmt_Native(asIScriptEngine *engine);

// Use this one instead if native calling conventions
// are not supported on the target platform
void RegisterScriptFmt_Generic(asIScriptEngine *engine);

END_AS_NAMESPACE

#endif
