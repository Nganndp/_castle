#include "SceneManager.h"

SceneManager::SceneManager()
{
	game = CGame::GetInstance();
	camera = new Camera();
	scene = 1;
	//Textures
	CTextures* textures = CTextures::GetInstance();
	textures->Load();

	//Sprites
	CSprites* sprites = CSprites::GetInstance();
	sprites->Load();

	SIMON = new CSimon();

	MS = new CMS();
	MS->GetSimon(SIMON);

	dagger = new CDagger();
	dagger->GetSimon(SIMON);

	Axe = new CAxe();
	Axe->GetSimon(SIMON);

	//push back to list objects
	objects.push_back(SIMON);
	objects.push_back(MS);
	objects.push_back(dagger);
	objects.push_back(Axe);
}
void SceneManager::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (SIMON->GetState() == SIMON_STATE_DIE || SIMON->GetChangeColorTime() != 0 || SIMON->GetAutoWalkingTime() != 0) return;
	switch (KeyCode)
	{
	case DIK_S:
		if (SIMON->GetOnGround())
		{
			SIMON->SetState(SIMON_STATE_JUMP);
			if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))
			{
				SIMON->StartJumpMove();
			}
			else SIMON->StartJump();
		}
		break;
	case DIK_A:
		if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))
		{
			return;
		}
		if (game->IsKeyDown(DIK_UP))
		{
			if (SIMON->GetThrowDagger())
			{
				if (SIMON->GetAttackTime() == 0)
				{
					dagger->StartAttack();
					dagger->SetActive(true);
				}
				dagger->nx = SIMON->nx;
				MS->SetActive(false);
				SIMON->SetState(SIMON_STATE_ATTACK);
				SIMON->StartAttack();
			}
			else if (SIMON->GetThrowAxe())
			{
				if (SIMON->GetAttackTime() == 0)
				{
					Axe->StartAttack();
					Axe->SetActive(true);
				}
				Axe->nx = SIMON->nx;
				MS->SetActive(false);
				SIMON->SetState(SIMON_STATE_ATTACK);
				SIMON->StartAttack();

			}
		}
		if (!game->IsKeyDown(DIK_UP))
		{
			MS->StartAttack();
			MS->SetState(MS_STATE_ATTACK);
			MS->SetActive(true);
			if (game->IsKeyDown(DIK_DOWN))
			{
				SIMON->SetState(SIMON_STATE_SIT);
				SIMON->StartSitAttack();
				SIMON->SetJump(0);
			}
			else {
				SIMON->SetState(SIMON_STATE_ATTACK);
				SIMON->StartAttack();
				SIMON->SetJump(0);
			}
			if (SIMON->GetLevel() == SIMON_LEVEL_MS_2)
			{
				MS->SetState(MS_STATE_ATTACK_2);
			}
			if (SIMON->GetLevel() == SIMON_LEVEL_MS_3)
			{
				MS->SetState(MS_STATE_ATTACK_3);
			}
		}
		break;
	case DIK_Q:
		if (SIMON->GetActive() == true)
		{
			SIMON->SetActive(false);
		}
		else SIMON->SetActive(true);
		break;
	case DIK_R:
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Setbboxcolor();
		}
		for (int i = 0; i < mapobjects.size(); i++)
		{
			mapobjects[i]->Setbboxcolor();
		}
		for (int i = 0; i < stagechanger.size(); i++)
		{
			stagechanger[i]->Setbboxcolor();
		}
		break;
	case DIK_W:
		SIMON->StartAutoWalking();
		break;
	case DIK_T:
		if (SIMON->GetOnStair() == false)
		{
			SIMON->SetOnStair(true);
		}
		else if (SIMON->GetOnStair() == true)
		{
			SIMON->SetOnStair(false);
		}
		return;
	case DIK_Y:
		if (SIMON->GetStairUp() == false)
		{
			SIMON->SetStairUp(true);
		}
		else if (SIMON->GetStairUp() == true)
		{
			SIMON->SetStairUp(false);
		}
		return;
	}
}

void  SceneManager::OnKeyUp(int KeyCode)
{
		if (KeyCode == 208) {
			if (SIMON->GetState() == SIMON_STATE_SIT)
			{
				SIMON->StandUp();
			}
		}
		DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void  SceneManager::KeyState(BYTE* states)
{
	// disable control key when SIMON die 
		if (SIMON->GetState() == SIMON_STATE_DIE || SIMON->GetChangeColorTime() != 0 /*|| SIMON->GetAutoWalkingTime() != 0*/) return;
		if (game->IsKeyDown(DIK_RIGHT) && !game->IsKeyDown(DIK_DOWN) && SIMON->GetJumpTime() == 0 && SIMON->GetOnStair() == false)
		{
			if(SIMON->GetAutoWalkingTime() == 0)
			SIMON->SetState(SIMON_STATE_WALKING_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT) && !game->IsKeyDown(DIK_DOWN) && SIMON->GetJumpTime() == 0 && SIMON->GetOnStair() == false)
		{
			if (SIMON->GetAutoWalkingTime() == 0)
			SIMON->SetState(SIMON_STATE_WALKING_LEFT);
		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			if (SIMON->GetAutoWalkingTime() == 0)
			{
				if (SIMON->GetOnStair() == false)
				{
					SIMON->SetState(SIMON_STATE_SIT);
					SIMON->SetSit(true);
				}
				else if (SIMON->GetOnStair() == true)
				{
					SIMON->SetState(SIMON_STATE_WALKING_DOWN_STAIR);
				}
			}
		}
		else if (game->IsKeyDown(DIK_UP))
		{
			if (SIMON->GetAutoWalkingTime() == 0) 
			{
				if (SIMON->GetOnStair() == true)
				{
					SIMON->SetState(SIMON_STATE_WALKING_UP_STAIR);
				}
			}
		}
		else
			SIMON->SetState(SIMON_STATE_IDLE);
}
void SceneManager::LoadResources()
{
	camera->SetCamera(SIMON->x - SCREEN_WIDTH / 2, 0);
	if (scene == 1)
	{
		SIMON->SetPosition(10.0f, 155);
		Tile = new TileMap(L"textures\\entrance.png", ID_TEX_ENTRANCESTAGE, 42, 0);
		Tile->LoadMap("ReadFile\\Map\\entrance.txt");
		LoadSceneObject(1);
	}
	else if (scene == 2)
	{
		stagechanger.clear();
		mapobjects.clear();
		SIMON->SetPosition(10.0f, 168);
		Tile = new TileMap(L"textures\\castle.png", ID_TEX_CASTLE,42,0);
		Tile->LoadMap("ReadFile\\Map\\castle.txt");
		LoadSceneObject(2);
	}
}

void SceneManager::ChangeScene()
{

}
/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void SceneManager::Update(DWORD dt)
{
	for (int i = 0; i < stagechanger.size(); i++)
	{
		if (stagechanger.at(i)->type == SC_TYPE_CHANGE_SCENE)
		{
			if (SIMON->CheckCollision(stagechanger.at(i)))
			{
				scene = 2;
				LoadResources();
				return;
			}
		}
		else if (stagechanger.at(i)->type == SC_TYPE_AUTO_HELPER)
		{
			if (SIMON->CheckCollision(stagechanger.at(i)))
			{
				stagechanger.at(i)->SetActive(false);
				SIMON->StartAutoWalking();
				return;
			}
		}
	}
	for (int i = 0; i < mapobjects.size(); i++)
	{
		mapobjects[i]->Update(dt, &mapobjects);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &mapobjects);
	}
	 camera->SetCamera(SIMON->x - SCREEN_WIDTH / 2, 0);
	 camera->Update(dt, scene);
}

/*
	Render a frame
*/
void SceneManager::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	
		Tile->DrawMap(camera);
		for (int i = 0; i < mapobjects.size(); i++)
			mapobjects[i]->Render(camera);
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render(camera);
		for (int i = 0; i < stagechanger.size(); i++)
			stagechanger[i]->Render(camera);
		spriteHandler->End();


		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void SceneManager::LoadObjectFromFile(string source)
{
	vector<int> numbers;
	int flag = 0;
	int number;
	int arr[4];
	ifstream file_objects(source);
	if (file_objects.is_open())
	{
		while (!file_objects.eof())
		{
			while (file_objects >> number)
			{
				arr[flag] = number;
				flag++;
				if (flag == 4)
				{
					switch (arr[0])
					{
					case BRICK:
						brick = new CBrick();
						brick->SetMulwidth(arr[3]);
						brick->SetPosition(arr[1], arr[2]);
						mapobjects.push_back(brick);
						break;
					case TORCH:
						torch = new CTorch();
						torch->SetPosition(arr[1], arr[2]);
						torch->SetState(arr[3]);
						mapobjects.push_back(torch);
						break;
					case STAGECHANGER:
						SC = new StageChanger();
						SC->SetPosition(arr[1], arr[2]);
						SC->SetType(arr[3]);
						stagechanger.push_back(SC);
					}

					flag = 0;
				}
			}
		}
	}
}

void SceneManager::LoadSceneObject(int a)
{
	if (a == 1)
	{
		LoadObjectFromFile("ReadFile\\Objects\\ObjectsStage1.txt");
	}
	if (a == 2)
	{
		LoadObjectFromFile("ReadFile\\Objects\\ObjectsStage2.txt");
	}
}
SceneManager::~SceneManager()
{
	delete Tile;
	Tile = nullptr;
}