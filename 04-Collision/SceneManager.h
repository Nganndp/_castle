#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class SceneManager
{
private:
	static SceneManager* mInstance;
	SceneManager* mCurrentScene;

public:
	SceneManager();

	static SceneManager* GetInstance();
	SceneManager* GetCurrentScene();

	virtual void KeyState(BYTE* state);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	virtual void LoadResources(LPCWSTR picturePath, int idTex, const char* filepath, int scene);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void ChangeScene();

	void ReplaceScene(SceneManager* scene);

	~SceneManager();
};
