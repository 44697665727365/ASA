﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: IrisStub

#include "Basic.hpp"

#include "CoreUObject_classes.hpp"


namespace SDK
{

// Class IrisStub.DataStream
// 0x0000 (0x0028 - 0x0028)
class UDataStream final : public UObject
{
public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"DataStream">();
	}
	static class UDataStream* GetDefaultObj()
	{
		return GetDefaultObjImpl<UDataStream>();
	}
};

// Class IrisStub.IrisObjectReferencePackageMap
// 0x0000 (0x0028 - 0x0028)
class UIrisObjectReferencePackageMap final : public UObject
{
public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"IrisObjectReferencePackageMap">();
	}
	static class UIrisObjectReferencePackageMap* GetDefaultObj()
	{
		return GetDefaultObjImpl<UIrisObjectReferencePackageMap>();
	}
};

// Class IrisStub.NetBlobHandler
// 0x0000 (0x0028 - 0x0028)
class UNetBlobHandler : public UObject
{
public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"NetBlobHandler">();
	}
	static class UNetBlobHandler* GetDefaultObj()
	{
		return GetDefaultObjImpl<UNetBlobHandler>();
	}
};

// Class IrisStub.NetObjectPrioritizerConfig
// 0x0000 (0x0028 - 0x0028)
class UNetObjectPrioritizerConfig : public UObject
{
public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"NetObjectPrioritizerConfig">();
	}
	static class UNetObjectPrioritizerConfig* GetDefaultObj()
	{
		return GetDefaultObjImpl<UNetObjectPrioritizerConfig>();
	}
};

// Class IrisStub.NetObjectCountLimiterConfig
// 0x0000 (0x0028 - 0x0028)
class UNetObjectCountLimiterConfig : public UNetObjectPrioritizerConfig
{
public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"NetObjectCountLimiterConfig">();
	}
	static class UNetObjectCountLimiterConfig* GetDefaultObj()
	{
		return GetDefaultObjImpl<UNetObjectCountLimiterConfig>();
	}
};

// Class IrisStub.NetObjectFilterConfig
// 0x0000 (0x0028 - 0x0028)
class UNetObjectFilterConfig final : public UObject
{
public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"NetObjectFilterConfig">();
	}
	static class UNetObjectFilterConfig* GetDefaultObj()
	{
		return GetDefaultObjImpl<UNetObjectFilterConfig>();
	}
};

// Class IrisStub.NetObjectFilter
// 0x0000 (0x0028 - 0x0028)
class UNetObjectFilter final : public UObject
{
public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"NetObjectFilter">();
	}
	static class UNetObjectFilter* GetDefaultObj()
	{
		return GetDefaultObjImpl<UNetObjectFilter>();
	}
};

// Class IrisStub.NetObjectPrioritizer
// 0x0000 (0x0028 - 0x0028)
class UNetObjectPrioritizer final : public UObject
{
public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"NetObjectPrioritizer">();
	}
	static class UNetObjectPrioritizer* GetDefaultObj()
	{
		return GetDefaultObjImpl<UNetObjectPrioritizer>();
	}
};

// Class IrisStub.ReplicationBridge
// 0x0000 (0x0028 - 0x0028)
class UReplicationBridge : public UObject
{
public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"ReplicationBridge">();
	}
	static class UReplicationBridge* GetDefaultObj()
	{
		return GetDefaultObjImpl<UReplicationBridge>();
	}
};

// Class IrisStub.ObjectReplicationBridge
// 0x0000 (0x0028 - 0x0028)
class UObjectReplicationBridge : public UReplicationBridge
{
public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"ObjectReplicationBridge">();
	}
	static class UObjectReplicationBridge* GetDefaultObj()
	{
		return GetDefaultObjImpl<UObjectReplicationBridge>();
	}
};

// Class IrisStub.SequentialPartialNetBlobHandlerConfig
// 0x0000 (0x0028 - 0x0028)
class USequentialPartialNetBlobHandlerConfig final : public UObject
{
public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"SequentialPartialNetBlobHandlerConfig">();
	}
	static class USequentialPartialNetBlobHandlerConfig* GetDefaultObj()
	{
		return GetDefaultObjImpl<USequentialPartialNetBlobHandlerConfig>();
	}
};

// Class IrisStub.SequentialPartialNetBlobHandler
// 0x0000 (0x0028 - 0x0028)
class USequentialPartialNetBlobHandler final : public UNetBlobHandler
{
public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"SequentialPartialNetBlobHandler">();
	}
	static class USequentialPartialNetBlobHandler* GetDefaultObj()
	{
		return GetDefaultObjImpl<USequentialPartialNetBlobHandler>();
	}
};

// Class IrisStub.SphereWithOwnerBoostNetObjectPrioritizerConfig
// 0x0000 (0x0028 - 0x0028)
class USphereWithOwnerBoostNetObjectPrioritizerConfig final : public UNetObjectPrioritizerConfig
{
public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"SphereWithOwnerBoostNetObjectPrioritizerConfig">();
	}
	static class USphereWithOwnerBoostNetObjectPrioritizerConfig* GetDefaultObj()
	{
		return GetDefaultObjImpl<USphereWithOwnerBoostNetObjectPrioritizerConfig>();
	}
};

}

