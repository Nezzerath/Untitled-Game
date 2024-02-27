// Fill out your copyright notice in the Description page of Project Settings.


#include "SAOGameInstance.h"
#include "WebSocketsModule.h"

void USAOGameInstance::Init()
{
	Super::Init();

	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}

	WebSocket = FWebSocketsModule::Get().CreateWebSocket("ws://70.191.209.217:7777");

	WebSocket->Connect();

	WebSocket->OnConnected().AddLambda([]()
		{
			UE_LOG(LogTemp, Log, TEXT("[WebSocket] Connected"));
		});
}

void USAOGameInstance::Shutdown()
{
	if (WebSocket->IsConnected())
	{
		WebSocket->Close();
	}

	Super::Shutdown();
}