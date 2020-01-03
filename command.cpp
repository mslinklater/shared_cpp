// Copyright (c) 2019, Martin Linklater
// All rights reserved.
//
// See file 'LICENSE' for license details

#include "command.h"
#include "log.h"

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

void CommandCenter::Broadcast(Command& command)
{
	commandList[writeQueueIndex].push(command);
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
	LOGINFOF("Commands::ToggleWindow %s", windowName.c_str());
	Command cmd;
	cmd.name = kToggleWindowCommand;
	cmd.payload = windowName;
	CommandCenter::Instance()->Broadcast(cmd);
}

void SharedCommands::Quit(void)
{
	LOGINFO("Commands::Quit");
	Command cmd;
	cmd.name = kQuitCommand;
	CommandCenter::Instance()->Broadcast(cmd);
}
