#pragma once
#include "Command.h"

namespace boop
{
	class DieCommand final : public Command
	{
	public:
		void Execute() override;
	};
}

