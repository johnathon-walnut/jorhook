#pragma once

#include "../Utils/HookManager/HookManager.h"

#define MAKE_HOOK(name, address, type, callconvention, ...) \
namespace H \
{\
	namespace name\
	{\
		void Initialize();\
		inline CHook Hook(#name, Initialize); \
		using FN = type(callconvention*)(__VA_ARGS__);\
		type callconvention Detour(__VA_ARGS__);\
	}\
}\
void H::name::Initialize() {\
	assert(address != nullptr);\
	Hook.CreateHook(reinterpret_cast<void*>(address), reinterpret_cast<void*>(Detour)); \
}\
type callconvention H::name::Detour(__VA_ARGS__)

#define CALL_ORIGINAL Hook.Original<FN>()