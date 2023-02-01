#pragma once

#include "pch.h"

class Signature
{
public:
	Signature(const char* IDASignature);
	Signature& Scan();

	Signature& Add(ptrdiff_t n);
	Signature& Sub(ptrdiff_t n);
	Signature& Rip();

	template <typename T>
	inline T Get()
	{
		assert(m_Result);
		return reinterpret_cast<T>(m_Result);
	}

private:
	std::vector<uint32_t> m_Bytes;
	uintptr_t m_Result = 0;
};
