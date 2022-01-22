//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a RdGen v1.08.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
#include "UE4Library.Generated.h"

#include "UE4Library/StringRange.Generated.h"
#include "UE4Library/PlayState.Generated.h"
#include "UE4Library/RequestSucceed.Generated.h"
#include "UE4Library/RequestFailed.Generated.h"
#include "UE4Library/LogMessageInfo.Generated.h"
#include "UE4Library/UnrealLogEvent.Generated.h"
#include "UE4Library/UClass.Generated.h"
#include "UE4Library/BlueprintFunction.Generated.h"
#include "UE4Library/ScriptCallStackFrame.Generated.h"
#include "UE4Library/EmptyScriptCallStack.Generated.h"
#include "UE4Library/ScriptCallStack.Generated.h"
#include "UE4Library/UnableToDisplayScriptCallStack.Generated.h"
#include "UE4Library/ScriptMsgException.Generated.h"
#include "UE4Library/ScriptMsgCallStack.Generated.h"
#include "UE4Library/BlueprintHighlighter.Generated.h"
#include "UE4Library/BlueprintReference.Generated.h"
#include "UE4Library/NotificationType.Generated.h"
#include "UE4Library/RequestResultBase_Unknown.Generated.h"
#include "UE4Library/IScriptCallStack_Unknown.Generated.h"
#include "UE4Library/IScriptMsg_Unknown.Generated.h"

#include "UE4Library/UE4Library.Generated.h"
#include "UE4Library/UE4Library.Generated.h"

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable:4250 )
#pragma warning( disable:4307 )
#pragma warning( disable:4267 )
#pragma warning( disable:4244 )
#pragma warning( disable:4100 )
#endif

namespace JetBrains {
namespace EditorPlugin {
// companion

UE4Library::UE4LibrarySerializersOwner const UE4Library::serializersOwner;

void UE4Library::UE4LibrarySerializersOwner::registerSerializersCore(rd::Serializers const& serializers) const
{
    serializers.registry<StringRange>();
    serializers.registry<RequestSucceed>();
    serializers.registry<RequestFailed>();
    serializers.registry<LogMessageInfo>();
    serializers.registry<UnrealLogEvent>();
    serializers.registry<UClass>();
    serializers.registry<BlueprintFunction>();
    serializers.registry<ScriptCallStackFrame>();
    serializers.registry<EmptyScriptCallStack>();
    serializers.registry<ScriptCallStack>();
    serializers.registry<UnableToDisplayScriptCallStack>();
    serializers.registry<ScriptMsgException>();
    serializers.registry<ScriptMsgCallStack>();
    serializers.registry<BlueprintHighlighter>();
    serializers.registry<BlueprintReference>();
    serializers.registry<RequestResultBase_Unknown>();
    serializers.registry<IScriptCallStack_Unknown>();
    serializers.registry<IScriptMsg_Unknown>();
}

void UE4Library::connect(rd::Lifetime lifetime, rd::IProtocol const * protocol)
{
    UE4Library::serializersOwner.registry(protocol->get_serializers());
    
    identify(*(protocol->get_identity()), rd::RdId::Null().mix("UE4Library"));
    bind(lifetime, protocol, "UE4Library");
}

// constants
// initializer
void UE4Library::initialize()
{
    serializationHash = 652350108289200731L;
}
// primary ctor
// secondary constructor
// default ctors and dtors
UE4Library::UE4Library()
{
    initialize();
}
// reader
// writer
// virtual init
void UE4Library::init(rd::Lifetime lifetime) const
{
    rd::RdExtBase::init(lifetime);
}
// identify
void UE4Library::identify(const rd::Identities &identities, rd::RdId const &id) const
{
    rd::RdBindableBase::identify(identities, id);
}
// getters
// intern
// equals trait
// equality operators
bool operator==(const UE4Library &lhs, const UE4Library &rhs) {
    return &lhs == &rhs;
}
bool operator!=(const UE4Library &lhs, const UE4Library &rhs){
    return !(lhs == rhs);
}
// hash code trait
// type name trait
// static type name trait
// polymorphic to string
std::string UE4Library::toString() const
{
    std::string res = "UE4Library\n";
    return res;
}
// external to string
std::string to_string(const UE4Library & value)
{
    return value.toString();
}
}
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

