#include "GameObject.h"
#include "Simon.h"
#include "Torch.h"
#include "Game.h"
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
		attack = 0;

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
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

