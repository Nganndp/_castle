#include "SceneManager.h"

SceneManager* SceneManager::mInstance = NULL;

SceneManager* SceneManager::GetInstance()
{
	if (mInstance == NULL)
		mInstance = new SceneManager();

	return mInstance;
}

SceneManager* SceneManager::GetCurrentScene()
{
	return mCurrentScene;
}

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::KeyState(BYTE* state)
{
}

void SceneManager::OnKeyDown(int KeyCode)
{
}

void SceneManager::OnKeyUp(int KeyCode)
{
}

void SceneManager::LoadResources()
{
}

void SceneManager::Update(DWORD dt)
{
}

void SceneManager::Render()
{
}
void SceneManager::ChangeScene()
{
}
void SceneManager::ReplaceScene(SceneManager* scene)
{
	if (mCurrentScene != NULL)
	{
		delete mCurrentScene;
		mCurrentScene = nullptr;
	}

	mCurrentScene = scene;
}
