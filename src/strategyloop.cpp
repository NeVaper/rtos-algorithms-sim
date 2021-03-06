#include "strategyloop.h"

#include <iostream>

StrategyLoop::StrategyLoop(std::vector<Process>& processes)
	: mProcesses{ processes }
{ }

bool StrategyLoop::add(std::chrono::milliseconds timeAlive)
{
	std::function<void(int)> callUpdate = [this](int id) { finishCallback(id); };

	int i = (mLastAvaible < 0) ? 0 : mLastAvaible;
	int j = 0;
	for (; j < mProcesses.size(); ++i, ++j)
	{
		if (i >= mProcesses.size())
		{
			i = 0;
		}

		++mComparations;
		if (!mProcesses[i].isAlive())
		{
			mProcesses[i] = { i, timeAlive, callUpdate };
			
			mLastAvaible = i + 1;
			
			return true;
		}
	}

	return false;
}

void StrategyLoop::drawInLine() const
{
	std::cout << "Loop: \t\t[";
	for (const auto& p : mProcesses)
	{
		if (p.isAlive())
		{
			std::cout << 'O';
		}
		else
		{
			std::cout << '-';
		}
	}
	std::cout << ']'
		<< " Comparations: "
		<< mComparations
		<< '\n';
}

void StrategyLoop::finishCallback(int id)
{
	if (mLastAvaible < 0)
	{
		mLastAvaible = id;
	}
	else if ((id > mLastAvaible)
		&& (mProcesses.size() - mLastAvaible + id < mProcesses.size() / 2))
	{
		mLastAvaible = id;
	}
	else if ((id < mLastAvaible)
		&& (mProcesses.size() - id + mLastAvaible < mProcesses.size() / 2))
	{
		mLastAvaible = id;
	}
}
