#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class Scene
{
private:
	static Scene* mInstance;
	Scene* mCurrentScene;

public:
	Scene();

	static Scene* GetInstance();
	Scene* GetCurrentScene();

	virtual void KeyState(BYTE* state);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	virtual void LoadResources();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void ChangeScene();

	void ReplaceScene(Scene* scene);

	~Scene();
};
