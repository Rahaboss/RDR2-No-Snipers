#include "pch.h"
#include "Signature.h"

Signature::Signature(const char* IDASignature)
{
	// Helper functions
	constexpr auto ToHex = [](char c) -> uint32_t
	{
		// constexpr version of toupper from CRT
		constexpr auto ToUpper = [](char c) -> char
		{
			return ((c >= 'a' && c <= 'z') ? c + ('A' - 'a') : c);
		};

		switch (ToUpper(c))
		{
		case '0': return 0x0;
		case '1': return 0x1;
		case '2': return 0x2;
		case '3': return 0x3;
		case '4': return 0x4;
		case '5': return 0x5;
		case '6': return 0x6;
		case '7': return 0x7;
		case '8': return 0x8;
		case '9': return 0x9;
		case 'A': return 0xA;
		case 'B': return 0xB;
		case 'C': return 0xC;
		case 'D': return 0xD;
		case 'E': return 0xE;
		case 'F': return 0xF;
		}

		return 0;
	};

	// Loop through pattern
	for (size_t i = 0; i < strlen(IDASignature); i++)
	{
		// Skip gaps
		if (IDASignature[i] == ' ')
			continue;

		// Unknown byte
		if (IDASignature[i] == '?')
		{
			// Check for double question mark
			if (IDASignature[i + 1] == '?')
				i++;

			// Use -1 as unknown byte
			m_Bytes.push_back(0xFFFFFFFF);
			continue;
		}

		// Skip last byte if incomplete
		if (i == (strlen(IDASignature) - 1))
			break;

		// Construct whole byte from two characters
		uint32_t c1 = ToHex(IDASignature[i]);
		uint32_t c2 = ToHex(IDASignature[i + 1]);
		m_Bytes.push_back((c1 * 0x10) + c2);

		// Skip over the second part of the byte
		i++;
	}

	// Perform the scan
	Scan();
}

Signature& Signature::Scan()
{
	// Helper function to scan for pattern
	auto CheckPattern = [this](uintptr_t Location) -> bool
	{
		for (size_t i = 0; i < m_Bytes.size(); i++)
		{
			if (m_Bytes[i] != 0xFFFFFFFF && m_Bytes[i] != *reinterpret_cast<uint8_t*>(Location + i))
				return false;
		}
		return true;
	};

	// Check if already scanned
	if (m_Result)
		return *this;
	
	// Get information about process
	MODULEINFO ModuleInfo;
	GetModuleInformation(GetCurrentProcess(), g_GameModule, &ModuleInfo, sizeof(MODULEINFO));
	MEMORY_BASIC_INFORMATION Mbi;

	const auto Begin = g_BaseAddress; // Begin location of scan (base address)
	const auto Size = ModuleInfo.SizeOfImage; // Total size of process (area to be scanned)

	// Loop through memory regions
	for (uintptr_t Curr = Begin; Curr < Begin + Size; Curr += Mbi.RegionSize)
	{
		// Check if current region is invalid
		if (!VirtualQuery(reinterpret_cast<LPCVOID>(Curr), &Mbi, sizeof(Mbi)) || Mbi.State != MEM_COMMIT || Mbi.Protect == PAGE_NOACCESS)
			continue;

		// Loop through current region
		for (size_t i = 0; i < Size; ++i)
		{
			// Check if pattern matches at current location
			if (CheckPattern(Curr + i))
			{
				m_Result = Curr + i;
				return *this;
			}
		}
	}

	// At this point the scan has failed so m_Result is 0
	assert(m_Result);
	return *this;
}

Signature& Signature::Add(ptrdiff_t n)
{
	m_Result += n;
	return *this;
}

Signature& Signature::Sub(ptrdiff_t n)
{
	m_Result -= n;
	return *this;
}

Signature& Signature::Rip()
{
	return Add(*Get<int32_t*>()).Add(4);
}
