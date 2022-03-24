#include "DXUT.h"
#include "Include.h"

void Director::DirectorInit()
{
	_currentScene = nullptr;
	Camera::GetInstance()->CameraInit();
}

void Director::ChangeScene(Scene* s)
{
	if (_currentScene != nullptr)
		_currentScene->OnExit();
	_currentScene = s;
	_currentScene->Init();
}

void Director::SceneUpdate()
{
	if (_currentScene)
	{
		_currentScene->Update();
	}
	Camera::GetInstance()->CameraUpdate();
	Renderer::GetInstance()->Render();
}
