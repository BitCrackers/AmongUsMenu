#pragma once
#include <cstdint>

using byte = uint8_t;

class RenderCmdQueue
{
public:
	using RenderCmdFunc = void(*)(void*);

	RenderCmdQueue();
	~RenderCmdQueue();

	void* Allocate(RenderCmdFunc function, uint32_t size);

	void Execute();
private:
	byte* m_CmdBuffer;
	byte* m_CmdBufferPtr;
	uint32_t m_CmdCount = 0;
};