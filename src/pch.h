#pragma once

// C++ standard library
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cassert>

// Windows
#include <Windows.h>
#include <Psapi.h>

// MinHook
#include <MinHook.h>

// Global variables
inline HMODULE g_Module; // DLL handle (used to exit thread)
inline HMODULE g_GameModule; // Game handle
inline uintptr_t g_BaseAddress; // Game base address
inline HANDLE g_MainThread; // Main thread handle (must be closed before exiting)
inline std::atomic_bool g_Running = true; // Set to false to eject

// Enable literal macros
using namespace std::chrono_literals;
