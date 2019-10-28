#include "LoadAnimations.h"

void LoadAnimations::LoadAnimationFromFile(string source, CGameObject* object)
{

	int idani, time, idsprite;
	string all;
	ifstream infile;
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* anis = CAnimations::GetInstance();
	LPANIMATION ani;

	idani = 0;
	infile.open(source);
	while (!infile.eof())
	{
		int num_sprite;
		infile >> idani;
		ani = new CAnimation(100);
		infile >> num_sprite;
		for (int k = 0; k < num_sprite; k++)
		{
			infile >> idsprite >> time;
			ani->Add(idsprite, time);
		}
		anis->Add(idani, ani);

		object->AddAnimation(idani);
	}
	infile.close();
}

