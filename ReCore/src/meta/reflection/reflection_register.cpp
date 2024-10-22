#include "meta/reflection/reflection_register.h"
#include "meta/reflection/reflection.h"


namespace Reflection
{
    void TypeMetaRegister::metaUnregister() { TypeMetaRegisterinterface::unregisterAll(); }
}