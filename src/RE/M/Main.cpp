#include "RE/M/Main.h"

namespace RE
{
	Main* Main::GetSingleton()
	{
		REL::Relocation<Main**> singleton{ Offset::Main::Singleton };
		return *singleton;
	}

	float Main::QFrameAnimTime()
	{
		REL::Relocation<float*> data{ RELOCATION_ID(516940, 403447) };
		return *data;
	}
}
