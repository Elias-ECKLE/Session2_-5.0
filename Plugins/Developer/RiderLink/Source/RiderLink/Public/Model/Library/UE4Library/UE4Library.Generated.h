//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a RdGen v1.08.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
#ifndef UE4LIBRARY_GENERATED_H
#define UE4LIBRARY_GENERATED_H


#include "protocol/Protocol.h"
#include "types/DateTime.h"
#include "impl/RdSignal.h"
#include "impl/RdProperty.h"
#include "impl/RdList.h"
#include "impl/RdSet.h"
#include "impl/RdMap.h"
#include "base/ISerializersOwner.h"
#include "base/IUnknownInstance.h"
#include "serialization/ISerializable.h"
#include "serialization/Polymorphic.h"
#include "serialization/NullableSerializer.h"
#include "serialization/ArraySerializer.h"
#include "serialization/InternedSerializer.h"
#include "serialization/SerializationCtx.h"
#include "serialization/Serializers.h"
#include "ext/RdExtBase.h"
#include "task/RdCall.h"
#include "task/RdEndpoint.h"
#include "task/RdSymmetricCall.h"
#include "std/to_string.h"
#include "std/hash.h"
#include "std/allocator.h"
#include "util/enum.h"
#include "util/gen_util.h"

#include <cstring>
#include <cstdint>
#include <vector>
#include <ctime>

#include "thirdparty.hpp"
#include "instantiations_UE4Library.h"

#include "UE4TypesMarshallers.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "Runtime/Core/Public/Containers/ContainerAllocationPolicies.h"


#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable:4250 )
#pragma warning( disable:4307 )
#pragma warning( disable:4267 )
#pragma warning( disable:4244 )
#pragma warning( disable:4100 )
#endif

/// <summary>
/// <p>Generated from: UE4Library.kt:10</p>
/// </summary>
namespace JetBrains {
namespace EditorPlugin {

class RIDERLINK_API UE4Library : public rd::RdExtBase {

public:
    struct UE4LibrarySerializersOwner final : public rd::ISerializersOwner {
        void registerSerializersCore(rd::Serializers const& serializers) const override;
    };
    
    static const UE4LibrarySerializersOwner serializersOwner;
    
    

public:
    void connect(rd::Lifetime lifetime, rd::IProtocol const * protocol);
    

private:
    // custom serializers

public:
    // constants

protected:
    // fields

private:
    // initializer
    void initialize();

public:
    
    // default ctors and dtors
    
    UE4Library();
    
    UE4Library(UE4Library &&) = delete;
    
    UE4Library& operator=(UE4Library &&) = delete;
    
    virtual ~UE4Library() = default;
    
    // reader
    
    // writer
    
    // virtual init
    void init(rd::Lifetime lifetime) const override;
    
    // identify
    void identify(const rd::Identities &identities, rd::RdId const &id) const override;
    
    // getters
    
    // intern

private:
    // equals trait

public:
    // equality operators
    friend bool operator==(const UE4Library &lhs, const UE4Library &rhs);
    friend bool operator!=(const UE4Library &lhs, const UE4Library &rhs);
    // hash code trait
    // type name trait
    // static type name trait

private:
    // polymorphic to string
    std::string toString() const override;

public:
    // external to string
    friend std::string to_string(const UE4Library & value);
};

}
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif



#endif // UE4LIBRARY_GENERATED_H
