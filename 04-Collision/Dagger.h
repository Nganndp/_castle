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
	boolean active = false;
	boolean waiting = false;
public:
	CDagger() :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ani\\Daggerani.txt", this);
		attack = 0;

	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
    void Render(Camera * camera);
	void SetState(int state);
	void SetActive(boolean a)
	{
		active = a;
	}
	void AdjustPos();
	void StartAttack() {
		active = true;
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

