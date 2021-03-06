﻿#include "Common.h"
#include "MyBotModule.h"

using namespace BWAPI;
using namespace MyBot;

// BWAPIClient 와 connect 성공할 때까지 계속 connect 를 시도하는 함수
void reconnect()
{
	while (!BWAPIClient.connect())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds{ 1000 });
	}
}

int main(int argc, const char* argv[])
{
	// 디버그는 std::cout 을 이용해서 한다
	std::cout << "Connecting..." << std::endl;;
	reconnect();

	std::cout << "Waiting for a match..." << std::endl;
	while (!Broodwar->isInGame())
	{
		BWAPI::BWAPIClient.update();
		if (!BWAPI::BWAPIClient.isConnected())
		{
			std::cout << "Reconnecting..." << std::endl;;
			reconnect();
		}
	}
	std::cout << "Match started" << std::endl;

	MyBotModule* myBotModule = new MyBotModule();

	while (Broodwar->isInGame())
	{
		for (auto &e : Broodwar->getEvents())
		{
			switch (e.getType())
			{
			case EventType::MatchStart:
				myBotModule->onStart();
				break;
			case EventType::MatchEnd:
				myBotModule->onEnd(e.isWinner());
				break;
			case EventType::MatchFrame:
std::cout << "Match started" << std::endl;
				myBotModule->onFrame();
				break;
			case EventType::SendText:
				myBotModule->onSendText(e.getText());
				break;
			case EventType::ReceiveText:
				myBotModule->onReceiveText(e.getPlayer(), e.getText());
				break;
			case EventType::PlayerLeft:
				myBotModule->onPlayerLeft(e.getPlayer());
				break;
			case EventType::NukeDetect:
				myBotModule->onNukeDetect(e.getPosition());
				break;
			case EventType::UnitCreate:
				myBotModule->onUnitCreate(e.getUnit());
				break;
			case EventType::UnitDestroy:
				myBotModule->onUnitDestroy(e.getUnit());
				break;
			case EventType::UnitMorph:
				myBotModule->onUnitMorph(e.getUnit());
				break;
			case EventType::UnitShow:
				myBotModule->onUnitShow(e.getUnit());
				break;
			case EventType::UnitHide:
				myBotModule->onUnitHide(e.getUnit());
				break;
			case EventType::UnitComplete :
				myBotModule->onUnitComplete(e.getUnit());
				break;
			case EventType::UnitDiscover:
				myBotModule->onUnitDiscover(e.getUnit());
				break;
			case EventType::UnitEvade:
				myBotModule->onUnitEvade(e.getUnit());
				break;
			case EventType::UnitRenegade:
				myBotModule->onUnitRenegade(e.getUnit());
				break;
			case EventType::SaveGame:
				myBotModule->onSaveGame(e.getText());
				break;
			}
		}

		if (!BWAPI::BWAPIClient.isConnected())
		{
			std::cout << "Reconnecting..." << std::endl;
			reconnect();
		}

		BWAPI::BWAPIClient.update();
	}

	std::cout << "Match ended" << std::endl;

	delete myBotModule;
	return 0;
}
