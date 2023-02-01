#pragma once

#include "pch.h"

typedef uint32_t joaat_t;

constexpr joaat_t joaat(const char* String)
{
	// Helper functions
	// constexpr version of tolower from CRT
	constexpr auto ToLower = [](char c) -> char
	{
		return ((c >= 'A' && c <= 'Z') ? c - ('A' - 'a') : c);
	};

	joaat_t Hash = 0;

	while (*String)
	{
		Hash += ToLower(*(String++));
		Hash += (Hash << 10);
		Hash ^= (Hash >> 6);
	}

	Hash += (Hash << 3);
	Hash ^= (Hash >> 11);
	Hash += (Hash << 15);

	return Hash;
}
