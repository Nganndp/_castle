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
	if (SIMON->GetState() == SIMON_STATE_DIE || SIMON->GetChangeColorTime() != 0 || SIMON->GetAutoWalkingTime() != 0 || camera->GetCamMove() == true) return;
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
			MS->SetState(MS_STATE_ATTACK);
			MS->SetActive(true);
			if (game->IsKeyDown(DIK_DOWN))
			{
				SIMON->SetState(SIMON_STATE_SIT);
				SIMON->StartSitAttack();
				MS->StartAttack();
				SIMON->SetJump(0);
			}
			else {
				SIMON->SetState(SIMON_STATE_ATTACK);
				SIMON->StartAttack();
				MS->StartAttack();
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
		SIMON->StartAutoWalking(SIMON_AUTO_GO_TIME * 2);
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
		case DIK_3:
			stage = 3;
			SIMON->SetPosition(1931, 212);
			SIMON->SetOnStair(true);
			SIMON->SetStairUp(false);
			break;
		case DIK_4:
			stage = 2;
			//SIMON->SetPosition(1574, 183);
			SIMON->SetPosition(1901, 190);
			SIMON->SetOnStair(true);
			SIMON->SetStairUp(false);
			SIMON->nx = -1;
			break;
		case DIK_5:
			SIMON->SetEatCross(true);
			//isChangeColor = true;
			break;
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
	if (game->IsKeyDown(DIK_RIGHT) && !game->IsKeyDown(DIK_DOWN) && SIMON->GetJumpTime() == 0 && SIMON->GetOnStair() == false && camera->GetCamMove() == false)
	{
		if (SIMON->GetAutoWalkingTime() == 0)
			SIMON->SetState(SIMON_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT) && !game->IsKeyDown(DIK_DOWN) && SIMON->GetJumpTime() == 0 && SIMON->GetOnStair() == false && camera->GetCamMove() == false)
	{
		if (SIMON->GetAutoWalkingTime() == 0)
			SIMON->SetState(SIMON_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_DOWN) && camera->GetCamMove() == false)
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
	else if (game->IsKeyDown(DIK_UP) && camera->GetCamMove() == false)
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
	camera->SetCamera(0, 0);
	grid = new Grid();

	if (scene == 1)
	{
		SIMON->SetPosition(10.0f, 154);
		Tile = new TileMap(L"textures\\entrance_tilemap.png", ID_TEX_ENTRANCESTAGE, 42, 0);
		Tile->LoadMap("ReadFile\\Map\\entrance.txt");
		LoadSceneObject(1);
		for (UINT i = 0; i < mapobjects.size(); i++)
		{
			grid->InsertIntoGrid(mapobjects.at(i));
		}
		for (UINT i = 0; i < stagechanger.size(); i++)  //list invisible objects
		{
			grid->InsertIntoGrid(stagechanger.at(i));
		}
	}
	else if (scene == 2)
	{
		stagechanger.clear();
		mapobjects.clear();
		//SIMON->SetPosition(10.0f, 168);
		SIMON->SetPosition(1470, 42);
		Tile = new TileMap(L"textures\\castle_tilemap.png", ID_TEX_CASTLE, 42, 0);
		Tile->LoadMap("ReadFile\\Map\\castle.txt");
		LoadSceneObject(2);
		for (UINT i = 0; i < mapobjects.size(); i++)
		{
			grid->InsertIntoGrid(mapobjects.at(i));
		}
		for (UINT i = 0; i < stagechanger.size(); i++)
		{
			grid->InsertIntoGrid(stagechanger.at(i));
		}


	}
	int tmp = 0;
}
/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void SceneGame::Update(DWORD dt)
{
	//
	vector<LPGAMEOBJECT> coObjects;
	grid->GetListCollisionFromGrid(camera, ObjectsFromGrid);
	mapobjects.clear();
	stagechanger.clear();
	for (int i = 0; i < ObjectsFromGrid.size(); i++)
	{
		coObjects.push_back(ObjectsFromGrid[i]);
	}

	for (int i = 0; i < coObjects.size(); i++)
	{
		if(coObjects.at(i)->type == TORCH || coObjects.at(i)->type == BRICK)
		mapobjects.push_back(coObjects[i]);
		else {
			stagechanger.push_back(coObjects[i]);
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
			else if (InOb->type == SC_TYPE_DOOR)
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
			else if (InOb->type == SC_TYPE_UNDER_GROUND)
			{
				if (stage == 2)
				{
					stage = 3;
					SIMON->SetPosition(1611, 212);
				}
				else if (stage == 3)
				{
					stage = 2;
					SIMON->SetPosition(1581, 190);
				}
			}
			else if (InOb->type == SC_TYPE_AUTO_CLOSE_DOOR)
			{
				InOb->SetActive(false);
				camera->StartCamMove(1750);
				camera->SetCamMoving(true);
				SimonMove = false;
			}
			else if (InOb->type == STAIR_TYPE_RIGHT_UP_HELPER)
			{
				if (game->IsKeyDown(DIK_UP) && SIMON->GetOnStair() == false)
				{
					SIMON->SetState(SIMON_STATE_WALKING_LEFT);
				}
			}
			else if (InOb->type == STAIR_TYPE_LEFT_UP_HELPER)
			{
				if (game->IsKeyDown(DIK_UP) && SIMON->GetOnStair() == false)
				{
					SIMON->SetState(SIMON_STATE_WALKING_RIGHT);
				}
			}
			else if (InOb->type == STAIR_TYPE_UP_RIGHT)
			{
				InOb->SetTouchable(false);
				if (game->IsKeyDown(DIK_UP))
				{
					if (InOb->x - SIMON->x <= 5)
					{
						SIMON->x = InOb->x + 2;
					}
					if (SIMON->x >= InOb->x + 2)
					{
						SIMON->SetState(SIMON_STATE_WALKING_UP_STAIR);
						SIMON->StartAutoWalking(SIMON_AUTO_GO_TIME);
						SIMON->SetOnStair(true);
						SIMON->SetStairUp(true);
						SIMON->nx = 1;
					}
				}
				else if (game->IsKeyDown(DIK_DOWN))
				{
					SIMON->SetOnStair(false);
					SIMON->SetStairUp(false);
				}
			}
			else if (InOb->type == STAIR_TYPE_DOWN_LEFT)
			{
				InOb->SetTouchable(false);
				if (game->IsKeyDown(DIK_DOWN))
				{
					if (SIMON->x >= InOb->x - 14 || SIMON->x < InOb->x - 14 && SIMON->GetOnStair() == false)
					{
						SIMON->x = InOb->x - 14;
					}
					if (SIMON->x >= InOb->x - 14 || SIMON->x <= InOb->x -16)
					{
						SIMON->SetState(SIMON_STATE_WALKING_DOWN_STAIR);
						SIMON->SetOnStair(true);
						SIMON->SetStairUp(true);
						SIMON->nx = -1;
					}
				}
				else if (game->IsKeyDown(DIK_UP))
				{
					if (SIMON->y + SIMON_IDLE_BBOX_HEIGHT > InOb->y + INVI_HEIGHT)
					{
						SIMON->y = InOb->y + INVI_HEIGHT*2 - SIMON_IDLE_BBOX_HEIGHT;
					}
					SIMON->SetOnStair(false);
					SIMON->SetStairUp(false);
				}
			}
			else if (InOb->type == STAIR_TYPE_UP_LEFT)
			{
				InOb->SetTouchable(false);

				if (game->IsKeyDown(DIK_UP))
				{
					if(InOb->x - SIMON->x >= 20)
					{
						SIMON->x = InOb->x - 23;
					}
					if (SIMON->x <= InOb->x - 23)
					{
						SIMON->SetState(SIMON_STATE_WALKING_UP_STAIR);
						SIMON->StartAutoWalking(SIMON_AUTO_GO_TIME);
						SIMON->SetOnStair(true);
						SIMON->SetStairUp(false);
						SIMON->nx = -1;
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
					if (SIMON->x >= InOb->x - 7 || SIMON->x < InOb->x - 7 && SIMON->GetOnStair() == false)
					{
						SIMON->x = InOb->x - 7;
					}
					if (SIMON->x == InOb->x - 7)
					SIMON->SetState(SIMON_STATE_WALKING_DOWN_STAIR);
					SIMON->SetOnStair(true);
					SIMON->SetStairUp(false);
					SIMON->nx = 1;
				}
				else if (game->IsKeyDown(DIK_UP) && SIMON->GetOnStair() == true)
				{
					if (SIMON->y + SIMON_IDLE_BBOX_HEIGHT > InOb->y + INVI_HEIGHT)
					{
						SIMON->y = InOb->y + INVI_HEIGHT * 2 - SIMON_IDLE_BBOX_HEIGHT;
					}
					SIMON->SetOnStair(false);
					SIMON->SetStairUp(true);
				}
			}
		}
	}

	//adjust Simon to Camera
	if (SIMON->x - camera->GetPosition().x <= 100 && SimonMove == true)
	{
		SIMON->StartAutoWalking(SIMON_AUTO_GO_TIME * 2);
	}
	if (camera->GetCamMove() == 0 && SIMON->nx > 0)
	{
		if ((SIMON->x + 15) - camera->GetPosition().x >= SCREEN_WIDTH / 2)
			camera->SetCamera((SIMON->x + 15) - SCREEN_WIDTH / 2, 0);
	}
	if (SIMON->nx < 0)
	{
		camera->SetCamera((SIMON->x + 15) - SCREEN_WIDTH / 2, 0);
	}
	if (stage == 3)
	{
		camera->SetCamera((SIMON->x + 15) - SCREEN_WIDTH / 2, 207);
	}
	camera->Update(dt, scene, stage);

	//adjust Simon to map
	if (camera->GetCamMoving() == false)
	{
		if (scene == 1)
		{
			if (SIMON->x < 0)
				SIMON->x = 0;
			if (SIMON->x > 750)
				SIMON->x = 750;
		}
		if (scene == 2)
		{
			if (stage == 1)
			{
				if (SIMON->x < 0)
					SIMON->x = 0;
				if (SIMON->x > 1502)
					SIMON->x = 1502;
			}
			if (stage == 2)
			{
				if (SIMON->x < 1530)
					SIMON->x = 1530;
				if (SIMON->x > 2014)
					SIMON->x = 2014;
			}
			if (stage == 3)
			{
				if (SIMON->x < 1570)
					SIMON->x = 1570;
				if (SIMON->x > 2082)
					SIMON->x = 2082;
			}
		}
	}

	//Item that effect the scene
	if (SIMON->GetEatCross() == true)
	{
		isChangeColor = true;
		SIMON->SetEatCross(false);
	}
	if (isChangeColor)
	{
		if (timerChangeColor < 90)
		{
			isGrey = true;
			timerChangeColor += dt;
		}
		else
		{
			isGrey = false;
			timerChangeColor = 0;
			countChangeColor++;
		}
		if (countChangeColor >= 7)
		{
			isChangeColor = false;
			countChangeColor = 0;
		}
	}
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
		if (isGrey)
			d3ddv->ColorFill(bb, NULL, D3DCOLOR_XRGB(128, 128, 128));
		else
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		Tile->DrawMap(camera);

		//for (int i = 0; i < coObjects.size(); i++)
		//	coObjects[i]->Render(camera);
		for (int i = 0; i < mapobjects.size(); i++)
		{
			mapobjects[i]->Render(camera);
		}
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