#include "memory.h"
#include <thread>

namespace offsets
{
	constexpr auto dwLocalPlayer = 0xDB65EC;
	constexpr auto m_fFlags = 0x104;
	constexpr auto dwForceJump = 0x527BC98;
}

int main()
{
	auto mem = Memory("csgo.exe");

	std::cout << "Process id: " << mem.GetProcessId() << std::endl;

	const auto client = mem.GetModuleAddress("client.dll");
	std::cout << "client.dll -> " << "0x" << std::hex << client << std::dec << std::endl;

	while (true)
	{
		const auto localplayer = mem.Read<uintptr_t>(client + offsets::dwLocalPlayer);

		if (localplayer)
		{
			const auto onGround = mem.Read<bool>(localplayer + offsets::m_fFlags);

			if (GetAsyncKeyState(VK_SPACE) && onGround & (1 << 0))
				mem.Write<BYTE>(client + offsets::dwForceJump, 6);

		}

		std::this_thread::sleep_for(std::chrono::microseconds(5));
	}
}
