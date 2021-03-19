#include "RenderCmd.hpp"

#include <memory>

RenderCmdQueue::RenderCmdQueue()
{
	m_CmdBuffer = new byte[10 * 1024 * 1024];
	m_CmdBufferPtr = m_CmdBuffer;
	memset(m_CmdBuffer, 0, 10 * 1024 * 1024);
}

RenderCmdQueue::~RenderCmdQueue()
{
	delete[] m_CmdBuffer;
}

void* RenderCmdQueue::Allocate(RenderCmdFunc function, uint32_t size)
{
	*reinterpret_cast<RenderCmdFunc*>(m_CmdBufferPtr) = function;
	m_CmdBufferPtr += sizeof(RenderCmdFunc);

	*reinterpret_cast<uint32_t*>(m_CmdBufferPtr) = size;
	m_CmdBufferPtr += sizeof(uint32_t);

	void* memory = m_CmdBufferPtr;
	m_CmdBufferPtr += size;

	m_CmdCount++;
	return memory;
}

void RenderCmdQueue::Execute()
{
	byte* buffer = m_CmdBuffer;

	for (uint32_t i = 0; i < m_CmdCount; i++)
	{
		RenderCmdFunc function = *reinterpret_cast<RenderCmdFunc*>(buffer);
		buffer += sizeof(RenderCmdFunc);

		uint32_t size = *reinterpret_cast<uint32_t*>(buffer);
		buffer += sizeof(uint32_t);
		function(buffer);
		buffer += size;
	}

	m_CmdBufferPtr = m_CmdBuffer;
	m_CmdCount = 0;
}