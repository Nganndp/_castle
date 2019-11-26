#include "GameObject.h"
#include "Simon.h"
#include "Torch.h"
#include "Game.h"
#include "LoadAnimations.h"
#include "define.h"
class CDagger :public CGameObject
{
public:
	bool isAttack;
	int type;
	int attack;
	CGameObject* simon;
	DWORD attack_start;
	int attackStart;
	bool waiting = false;
public:
	CDagger() :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Daggerani.txt", this);
		attack = 0;
		active = false;

	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render(Camera* camera);
	void SetState(int state);
	void AdjustPos();
	void StartAttack() {
		waiting = true;
		attack_start = GetTickCount();
		AdjustPos();
	}
	void SetLevel(int l) { type = l; }
	void GetSimon(CGameObject* Simon) {
		simon = Simon;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

