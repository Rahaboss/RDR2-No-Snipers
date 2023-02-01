#pragma once

#include "pch.h"

class Signature
{
public:
	Signature(const char* IDASignature);

private:
	std::vector<uint32_t> m_Bytes;
};
