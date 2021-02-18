#pragma once

namespace boop
{
	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;
		virtual void Execute() = 0;
	private:
		
};
}
