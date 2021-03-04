#pragma once
#include "Command.h"

namespace boop
{
	class TestCommand final : public Command
	{
	public:
		void Execute() override;
	};
}



