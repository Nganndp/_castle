#include "Scene.h"

Scene* Scene::mInstance = NULL;

Scene* Scene::GetInstance()
{
	if (mInstance == NULL)
		mInstance = new Scene();

	return mInstance;
}

Scene* Scene::GetCurrentScene()
{
	return mCurrentScene;
}

Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::KeyState(BYTE* state)
{
}

void Scene::OnKeyDown(int KeyCode)
{
}

void Scene::OnKeyUp(int KeyCode)
{
}

void Scene::LoadResources()
{
}

void Scene::Update(DWORD dt)
{
}

void Scene::Render()
{
}

void Scene::ReplaceScene(Scene* scene)
{
	if (mCurrentScene != NULL)
	{
		delete mCurrentScene;
		mCurrentScene = nullptr;
	}

	mCurrentScene = scene;
}
