// Copyright (c) 2019, Martin Linklater
// All rights reserved.
//
// See file 'LICENSE' for license details

#include "command.h"
#include "log.h"

#define LOGGING 0

CommandCenter* CommandCenter::pInstance = 0;

CommandCenter::CommandCenter()
	: writeQueueIndex(0)
	, readQueueIndex(1)
{
}

CommandCenter::~CommandCenter()
{
}

void CommandCenter::Update()
{
	// toggle queue indexes
	readQueueIndex = 1-readQueueIndex;
	writeQueueIndex = 1-readQueueIndex;
	// empty the read queue
	
	while(!commandList[readQueueIndex].empty())
	{
		Command thisCommand = commandList[readQueueIndex].front();
		commandList[readQueueIndex].pop();
		
		if(dispatchMap.find(thisCommand.name) != dispatchMap.end())
		{
			std::vector<ICommandProcessor*> handlers = dispatchMap[thisCommand.name];
			for( ICommandProcessor* handler : handlers)
			{
				handler->HandleCommand(thisCommand);
			}
		}
	}
}

void CommandCenter::QueueForBroadcast(Command& command)
{
<<<<<<< HEAD
#if LOGGING
	LOGINFOF("CommandCenter::QueueForBroadcast %s(%s,%s)", command.name.c_str(), command.payload.c_str(), command.payload2.c_str());
#endif
=======
//	LOGINFOF("CommandCenter::QueueForBroadcast %s(%s,%s)", command.name.c_str(), command.payload.c_str(), command.payload2.c_str());
>>>>>>> e2b251f5ed66a49b7c279716060d7e7e142eb316
	commandList[writeQueueIndex].push(command);
}

void CommandCenter::BroadcastNow(Command& thisCommand)
{
<<<<<<< HEAD
#if LOGGING
	LOGINFOF("CommandCenter::BroadcastNow %s(%s,%s)", thisCommand.name.c_str(), thisCommand.payload.c_str(), thisCommand.payload2.c_str());
#endif
=======
//	LOGINFOF("CommandCenter::BroadcastNow %s(%s,%s)", thisCommand.name.c_str(), thisCommand.payload.c_str(), thisCommand.payload2.c_str());
>>>>>>> e2b251f5ed66a49b7c279716060d7e7e142eb316
	if(dispatchMap.find(thisCommand.name) != dispatchMap.end())
	{
		std::vector<ICommandProcessor*> handlers = dispatchMap[thisCommand.name];
		for( ICommandProcessor* handler : handlers)
		{
			handler->HandleCommand(thisCommand);
		}
	}
}

CommandCenter * CommandCenter::Instance()
{
	if(pInstance == nullptr)
	{
		pInstance = new CommandCenter();
	}
	return pInstance;
}

void CommandCenter::Subscribe(std::string commandName, ICommandProcessor* handler)
{
	dispatchMap[commandName].push_back(handler);
}

void SharedCommands::ToggleWindow(std::string windowName)
{
#if LOGGING
	LOGINFOF("Commands::ToggleWindow %s", windowName.c_str());
#endif
	Command cmd;
	cmd.name = kToggleWindowCommand;
	cmd.payload = windowName;
	CommandCenter::Instance()->QueueForBroadcast(cmd);
}

void SharedCommands::Quit(void)
{
#if LOGGING
	LOGINFO("Commands::Quit");
#endif
	Command cmd;
	cmd.name = kQuitCommand;
	CommandCenter::Instance()->QueueForBroadcast(cmd);
}
