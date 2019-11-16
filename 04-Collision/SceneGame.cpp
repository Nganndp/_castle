#include "SceneGame.h"

SceneGame::SceneGame()
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
void SceneGame::OnKeyDown(int KeyCode)
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
		for (int i = 0; i < stairs.size(); i++)
		{
			stairs[i]->Setbboxcolor();
		}
		break;
	case DIK_W:
		SIMON->StartAutoWalking(SIMON_AUTO_GO_TIME*2);
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
		break;
	case DIK_Y:
		if (SIMON->GetStairUp() == false)
		{
			SIMON->SetStairUp(true);
		}
		else if (SIMON->GetStairUp() == true)
		{
			SIMON->SetStairUp(false);
		}
		break;
	case DIK_2:
		scene = 2;
		stage = 1;
		LoadResources();
		
		break;
	//case DIK_3:
	//	camera->StartCamMove();
	//	camera->SetCamMoving(true);
	//	stage = 2;
	//	break;
	}
}

void  SceneGame::OnKeyUp(int KeyCode)
{
	if (KeyCode == 208) {
		if (SIMON->GetSit() == true)
		SIMON->StandUp();
	}
		DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void  SceneGame::KeyState(BYTE* states)
{
	// disable control key when SIMON die 
		if (SIMON->GetState() == SIMON_STATE_DIE || SIMON->GetChangeColorTime() != 0) return;
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
void SceneGame::LoadResources()
{
	camera->SetCamera(SIMON->x - SCREEN_WIDTH / 2, 0);
	if (scene == 1)
	{
		SIMON->SetPosition(10.0f, 154);
		Tile = new TileMap(L"textures\\entrance.png", ID_TEX_ENTRANCESTAGE, 42, 0);
		Tile->LoadMap("ReadFile\\Map\\entrance.txt");
		LoadSceneObject(1);
	}
	else if (scene == 2)
	{
		stagechanger.clear();
		mapobjects.clear();
		//SIMON->SetPosition(10.0f, 168);
		SIMON->SetPosition(760, 42);
		Tile = new TileMap(L"textures\\castle.png", ID_TEX_CASTLE,42,0);
		Tile->LoadMap("ReadFile\\Map\\castle.txt");
		LoadSceneObject(2);
	}
}
/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void SceneGame::Update(DWORD dt)
{
	//Simon collsion with Invisible Objects
	vector<LPGAMEOBJECT> InvObjects;
	for (UINT i = 0; i < stagechanger.size(); i++)
	{
		if (dynamic_cast<InviObjects*>(stagechanger.at(i)))
			InvObjects.push_back(stagechanger.at(i));
	}
	for (UINT i = 0; i < InvObjects.size(); i++)
	{
		InviObjects* InOb = dynamic_cast<InviObjects*>(InvObjects[i]);
		if (SIMON->CheckOverlap(InOb) != true)
		{
			InOb->SetTouchable(true);
		}
	}
	for (int i = 0; i < InvObjects.size(); i++)
	{
		InviObjects* InOb = dynamic_cast<InviObjects*>(InvObjects[i]);
		if (SIMON->CheckOverlap(InOb))
		{
			if (InOb->type == SC_TYPE_CHANGE_SCENE)
			{
				scene = 2;
				stage = 1;
				LoadResources();
			}
			else if (InOb->type == SC_TYPE_AUTO_HELPER)
			{
				InOb->SetActive(false);
				SIMON->StartAutoWalking(SIMON_AUTO_GO_TIME);
			}
			else if (InOb->type == SC_TYPE_DOOR_1)
			{
				InOb->SetActive(false);
				camera->StartCamMove(3000);
				camera->SetCamMoving(true);
				if (stage == 1)
				{
					stage = 2;
				}
				else if (stage == 2)
				{
					stage = 3;
				}
				SimonMove = true;
			}
			else if (InOb->type == SC_TYPE_AUTO_CLOSE_DOOR)
			{
				InOb->SetActive(false);
				camera->StartCamMove(1750);
				camera->SetCamMoving(true);
				SimonMove = false;
			}
			else if (InvObjects.at(i)->type == STAIR_TYPE_UP_RIGHT && !game->IsKeyDown(DIK_RIGHT) && !game->IsKeyDown(DIK_LEFT))
			{
				InvObjects.at(i)->SetTouchable(false);
				if (SIMON->x >= InOb->x + 2)
				{
					SIMON->StartAutoWalking(SIMON_AUTO_GO_TIME);
					SIMON->SetOnStair(true);
					SIMON->SetStairUp(true);
					SIMON->nx = 1;
				}
				if (game->IsKeyDown(DIK_UP))
				{
					if (SIMON->x > InOb->x && SIMON->x != InOb->x + 2 || InOb->x-SIMON->x <=5)
					{
						SIMON->x = InOb->x + 2;
					}
				
				}
				else if (game->IsKeyDown(DIK_DOWN) )
				{
					SIMON->SetOnStair(false);
					SIMON->SetStairUp(false);
				}
			}
			else if (InOb->type == STAIR_TYPE_DOWN_LEFT)
			{
				InOb->SetTouchable(false);
				if (game->IsKeyDown(DIK_DOWN) && SIMON->GetOnStair() == false)
				{
					if (InOb->x - SIMON->x >= 5)
					{
						SIMON->x = InOb->x - 12;
					}
					SIMON->SetOnStair(true);
					SIMON->SetStairUp(true);
					SIMON->nx = -1;
				}
				else if (game->IsKeyDown(DIK_UP) && SIMON->GetOnStair() == true)
				{
					SIMON->SetOnStair(false);
					SIMON->SetStairUp(false);
				}
			}
			else if (InOb->type == STAIR_TYPE_UP_LEFT && !game->IsKeyDown(DIK_RIGHT) && !game->IsKeyDown(DIK_LEFT))
			{
				InvObjects.at(i)->SetTouchable(false);
				if (SIMON->x == InOb->x - 20)
				{
					SIMON->StartAutoWalking(SIMON_AUTO_GO_TIME);
					SIMON->SetOnStair(true);
					SIMON->SetStairUp(false);
					SIMON->nx = -1;
				}
				if (game->IsKeyDown(DIK_UP))
				{
					if (SIMON->x < InOb->x && SIMON->x != InOb->x - 20 || SIMON->x -InOb->x  <= 5)
					{
						SIMON->x = InOb->x - 20;
					}

				}
				else if (game->IsKeyDown(DIK_DOWN))
				{
					SIMON->SetOnStair(false);
					SIMON->SetStairUp(true);
				}
			}
			else if (InOb->type == STAIR_TYPE_DOWN_RIGHT)
			{
				InOb->SetTouchable(false);
				if (game->IsKeyDown(DIK_DOWN) && SIMON->GetOnStair() == false)
				{
					SIMON->SetOnStair(true);
					SIMON->SetStairUp(false);
					SIMON->nx = 1;
				}
				else if (game->IsKeyDown(DIK_UP) && SIMON->GetOnStair() == true)
				{
					SIMON->SetOnStair(false);
					SIMON->SetStairUp(true);
				}
			}
		}
	}

	//push objects to vectors
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 0; i < mapobjects.size(); i++)
	{
		coObjects.push_back(mapobjects[i]);
	}
	for (int i = mapobjects.size(); i < stagechanger.size(); i++)
	{
		coObjects.push_back(stagechanger[i]);
	}
	for (int i = 0; i < mapobjects.size(); i++)
	{
		mapobjects[i]->Update(dt, &mapobjects);
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	//adjust Simon to Camera
	if (SIMON->x - camera->GetPosition().x <= 90 && SimonMove == true)
	{
		SIMON->StartAutoWalking(SIMON_AUTO_GO_TIME * 2);
	}
	if (camera->GetCamMove() == 0 && SIMON->nx > 0)
	{
		if((SIMON->x+15) - camera->GetPosition().x >= SCREEN_WIDTH/2)
		camera->SetCamera((SIMON->x+15) - SCREEN_WIDTH / 2, 0);
	}
	if (SIMON->nx < 0)
	{
		camera->SetCamera((SIMON->x + 15) - SCREEN_WIDTH / 2, 0);
	}
	 camera->Update(dt, scene, stage);
}

/*
	Render a frame
*/
void SceneGame::Render()
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
		for (int i = 0; i < stairs.size(); i++)
			stairs[i]->Render(camera);
		spriteHandler->End();


		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void SceneGame::LoadObjectFromFile(string source)
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
						InOb = new InviObjects();
						InOb->SetPosition(arr[1], arr[2]);
						InOb->SetType(arr[3]);
						stagechanger.push_back(InOb);
						break;
					}

					flag = 0;
				}
			}
		}
	}
}

void SceneGame::LoadSceneObject(int a)
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
SceneGame::~SceneGame()
{
	delete Tile;
	Tile = nullptr;
}