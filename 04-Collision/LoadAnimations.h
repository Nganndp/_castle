#pragma once
#include <fstream>
#include <string>
#include "GameObject.h"
#include "define.h"
class LoadAnimations
{
public:
	LoadAnimations();
	static void LoadAnimationFromFile(string source, CGameObject* gameobject);
	~LoadAnimations();
};

