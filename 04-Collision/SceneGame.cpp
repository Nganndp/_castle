#include "SceneGame.h"

SceneGame::SceneGame()
{
	game = CGame::GetInstance();
	camera = new Camera();

	//Textures
	CTextures* textures = CTextures::GetInstance();
	textures->Load();
	//Sprites
	CSprites* sprites = CSprites::GetInstance();
	sprites->Load();

	grid = new Grid();
	//LoadSceneElement(1);
	SIMON = new CSimon();

	MS = new CMS();
	MS->GetSimon(SIMON);
	
	//tokens
	dagger = new CDagger(camera, SIMON->nx);
	Axe = new CAxe(SIMON->GetPosition().x, camera, SIMON->nx);
	Holywater = new CHolyWater(SIMON->GetPosition().x, camera, SIMON->nx);

	//Hidden money
    hiddenmoney = new CTorch();
	hiddenmoney->SetState(TORCH_STATE_MONEY4);
	hiddenmoney->SetActive(false);
}
void SceneGame::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (SIMON->GetState() == SIMON_STATE_DIE || SIMON->GetChangeColorTime() != 0 || SIMON->GetAutoWalkingTime() != 0 || camera->GetCamMove() == true || SIMON->GetIsDamaged() != 0) return;
	switch (KeyCode)
	{
	case DIK_S:
		if (SIMON->GetOnStair() == false)
		{
			if (SIMON->GetOnGround())
			{
				SIMON->SetState(SIMON_STATE_JUMP);
				if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))
				{
					SIMON->StartJumpMove();
				}
				else SIMON->StartJump();
			}
		}
		break;
	case DIK_A:
		if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))
		{
			return;
		}
		if (game->IsKeyDown(DIK_UP))
		{
			if (SIMON->GetThrowDagger() && weapon.size() < SIMON->GetNumWeapon())
			{
				dagger = new CDagger(camera, SIMON->nx);
				if (SIMON->nx > 0)
				{
					dagger->SetPosition(SIMON->x+ 20, SIMON->y+5);
				}
				else 
					dagger->SetPosition(SIMON->x, SIMON->y+5);
				weapon.push_back(dagger);
				MS->SetActive(false);
				SIMON->SetState(SIMON_STATE_ATTACK);
				SIMON->StartAttack();
			}
			else if (SIMON->GetThrowAxe() && weapon.size() <SIMON->GetNumWeapon())
			{
				Axe = new CAxe(SIMON->GetPosition().x + 8, camera, SIMON->nx);
				if (SIMON->nx > 0)
				{
					Axe->SetPosition(SIMON->x+ 8, SIMON->y);
				}
				else
					Axe->SetPosition(SIMON->x + 24, SIMON->y);
				weapon.push_back(Axe);
				MS->SetActive(false);
				SIMON->SetState(SIMON_STATE_ATTACK);
				SIMON->StartAttack();
            }
			else if (SIMON->GetThrowHolyWater() && weapon.size() <SIMON->GetNumWeapon())
			{
				if (SIMON->nx > 0)
				{
					Holywater = new CHolyWater(SIMON->GetPosition().x + 20, camera, SIMON->nx);
					Holywater->SetPosition(SIMON->x + 20, SIMON->y);
				}
				else 
				{
					Holywater = new CHolyWater(SIMON->GetPosition().x, camera, SIMON->nx);
					Holywater->SetPosition(SIMON->x + 8, SIMON->y);
				}
				weapon.push_back(Holywater);
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
		for (int i = 0; i < weapon.size(); i++)
		{
			weapon[i]->Setbboxcolor();
		}
		for (int i = 0; i < torches.size(); i++)
		{
			torches[i]->Setbboxcolor();
		}
		for (int i = 0; i < invisibleobjects.size(); i++)
		{
			invisibleobjects[i]->Setbboxcolor();
		}
		for (int i = 0; i < bricks.size(); i++)
		{
			bricks[i]->Setbboxcolor();
		}
		SIMON->Setbboxcolor();
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
	    LoadResources(SOURCE_CASTLE_PNG, ID_TEX_CASTLE, SOURCE_CASTLE_TXT, 2);
        break;
	case DIK_3:
			stage = 3;
			SIMON->SetStartPoint(startstage3);
			SIMON->SetEndPoint(endstage3);
			camera->SetStartPoint(startstage3);
			camera->SetEndPoint(endstage3);
			SIMON->SetPosition(simonposlandtounderground1x, simonposlandtounderground1y);
			break;
	case DIK_4:
			stage = 2;
			SIMON->SetPosition(1901, 190);
			SIMON->SetOnStair(true);
			SIMON->SetStairUp(false);
			SIMON->nx = -1;
			break;
	case DIK_5:
		StopEnemyStart();
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
	if (game->IsKeyDown(DIK_RIGHT) && !game->IsKeyDown(DIK_DOWN) && SIMON->GetJumpTime() == 0 && SIMON->GetOnStair() == false && camera->GetCamMove() == false && SIMON->GetIsDamaged() == 0)
	{
		if (SIMON->GetAutoWalkingTime() == 0)
			SIMON->SetState(SIMON_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT) && !game->IsKeyDown(DIK_DOWN) && SIMON->GetJumpTime() == 0 && SIMON->GetOnStair() == false && camera->GetCamMove() == false && SIMON->GetIsDamaged() == 0)
	{
		if (SIMON->GetAutoWalkingTime() == 0)
			SIMON->SetState(SIMON_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_DOWN) && camera->GetCamMove() == false && SIMON->GetIsDamaged() == 0)
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
	else if (game->IsKeyDown(DIK_UP) && camera->GetCamMove() == false && SIMON->GetIsDamaged() == 0)
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
void SceneGame::LoadResources(LPCWSTR picturePath, int idTex, const char* filepath, int scene)
{
	camera->SetCamera(0, 0);
	grid->ClearGrid();
	LoadSceneElement(scene);
	LoadSceneObject(scene);
	SIMON->SetPosition(simonposstartx, simonposstarty);
	hiddenmoney->SetPosition(hiddenmoneyposx, hiddenmoneyposy);
	Tile = new TileMap(picturePath, idTex, 42, 0);
	Tile->LoadMap(filepath);
	SIMON->SetStartPoint(startstage1);
	SIMON->SetEndPoint(endstage1);
	camera->SetStartPoint(startstage1);
	camera->SetEndPoint(endstage1);
}
/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void SceneGame::Update(DWORD dt)
{
	//Push Objects
	vector<LPGAMEOBJECT> coObjects;
	grid->GetListCollisionFromGrid(camera, ObjectsFromGrid);
	torches.clear();
	invisibleobjects.clear();
	bricks.clear();
	for (int i = 0; i < ObjectsFromGrid.size(); i++)
	{
		coObjects.push_back(ObjectsFromGrid[i]);
	}

	for (int i = 0; i < coObjects.size(); i++)
	{
		if (coObjects.at(i)->type == BRICK)
			bricks.push_back(coObjects[i]);
		else if (coObjects.at(i)->type == TORCH)
			torches.push_back(coObjects[i]);
		else
			invisibleobjects.push_back(coObjects[i]);
	}

	//Simon collision with torch
	for (int i = 0; i < torches.size(); i++)
	{
		CTorch* torch = dynamic_cast<CTorch*>(torches[i]);
		if (SIMON->CheckCollision(torch))
		{
			switch (torch->GetState())
			{
			case TORCH_STATE_CANDLE:
			case TORCH_STATE_NORMAL:
					break;
			case TORCH_STATE_LHEART:
				torch->SetActive(false);
				break;
			case TORCH_STATE_SHEART:
				torch->SetActive(false);
				break;
			case TORCH_STATE_CHIKEN:
				torch->SetActive(false);
				break;
			case TORCH_STATE_CROSS:
				torch->SetActive(false);
				SIMON->SetEatCross(true);
				enemy.clear();
				break;
			case TORCH_STATE_CLOCK:
				torch->SetActive(false);
				StopEnemyStart();
				break;
			case TORCH_STATE_MONEY1:
				torch->SetActive(false);
				break;
			case TORCH_STATE_MONEY2:
				torch->SetActive(false);
				break;
			case TORCH_STATE_MONEY3:
				torch->SetActive(false);
				break;
			case TORCH_STATE_MONEY4:
				torch->SetActive(false);
				break;
			case TORCH_STATE_MSUP:
				torch->SetActive(false);
				SIMON->StartChangeColor();
				if (SIMON->GetLevel() == SIMON_LEVEL_MS_1)
				{
					SIMON->SetLevel(SIMON_LEVEL_MS_2);
				}
				else if (SIMON->GetLevel() == SIMON_LEVEL_MS_2)
				{
					SIMON->SetLevel(SIMON_LEVEL_MS_3);
				}
				break;
			case TORCH_STATE_DAGGER:
				torch->SetActive(false);
				SIMON->SetThrowDagger(true);
				SIMON->SetThrowAxe(false);
				SIMON->SetThrowHolyWater(false);
				break;
			case TORCH_STATE_AXE:
				torch->SetActive(false);
				SIMON->SetThrowDagger(false);
				SIMON->SetThrowAxe(true);
				SIMON->SetThrowHolyWater(false);
				break;
			case TORCH_STATE_HOLYWATER:
				torch->SetActive(false);
				SIMON->SetThrowDagger(false);
				SIMON->SetThrowAxe(false);
				SIMON->SetThrowHolyWater(true);
				break;
			case TORCH_STATE_DOUBLE_SHOOT:
				torch->SetActive(false);
				SIMON->SetNumWeapon(2);
			}
		}
	}

	//Simon collison with breakabkle brick
	for (int i = 0; i < bricks.size(); i++)
	{
		if (bricks.at(i)->GetState() != BRICK_STATE_NORMAL)
		{
			if (SIMON->CheckCollision(bricks.at(i)))
			{
				if (bricks.at(i)->GetState() == BBRICK_STATE_CHIKEN)
				{
					bricks.at(i)->SetActive(false);
				}
				if (bricks.at(i)->GetState() == BBRICK_STATE_DOUBLE_SHOOT)
				{
					SIMON->SetNumWeapon(2);
					bricks.at(i)->SetActive(false);
				}
				if (bricks.at(i)->GetState() == BBRICK_STATE_MONEY)
				{
					bricks.at(i)->SetActive(false);
				}
			}
		}
	}
	if (SIMON->CheckCollision(hiddenmoney) && hiddenmoney->GetActive() == true)
	{
		hiddenmoney->SetActive(false);
	}

	//Simon collision with Invisible Objects
	for (int i = 0; i < invisibleobjects.size(); i++)
	{
		InviObjects* InOb = dynamic_cast<InviObjects*>(invisibleobjects[i]);
		if (SIMON->CheckCollision(InOb))
		{
			if (InOb->type == SC_TYPE_CHANGE_SCENE)
			{
				if (SIMON->GetAutoWalkingTime() == 0)
				{
					LoadResources(SOURCE_CASTLE_PNG, ID_TEX_CASTLE, SOURCE_CASTLE_TXT, 2);
				}
			}
			else if (InOb->type == SC_TYPE_AUTO_HELPER)
			{
				InOb->SetActive(false);
				SIMON->StartAutoWalking(SIMON_AUTO_GO_SCENE1);
			}
			else if (InOb->type == SC_TYPE_DOOR)
			{
				InOb->SetActive(false);
				if (SIMON->x >= InOb->x - 24)
					SIMON->x = InOb->x - 24;
				effect = new CEffect(camera);
				effect->SetType(EFFECT_TYPE_DOOR);
				effect->SetPosition(InOb->x, effectdoory);
				effects.push_back(effect);
				camera->StartCamMove(CAM_MOVE_TIME1);
				camera->SetCamMoving(true);
				if (SIMON->GetStartPoint() == 0)
				{
					stage = 2;
					SIMON->SetEndPoint(endstage2);
					camera->SetEndPoint(endstage2);
				}
				else if (SIMON->GetStartPoint() == startstage2)
				{
					SIMON->SetEndPoint(endstage4);
					camera->SetEndPoint(endstage4);
				}
				SimonMove = true;
			}
			else if (InOb->type == SC_TYPE_AUTO_CLOSE_DOOR)
			{
				InOb->SetActive(false);
				camera->StartCamMove(CAM_MOVE_TIME2);
				camera->SetCamMoving(true);
				SimonMove = false;
				if (SIMON->GetStartPoint() == 0)
				{
					SIMON->SetStartPoint(startstage2);
					camera->SetStartPoint(startstage2);
					endpoint = endstage2;
				}
			}
			else if (InOb->type == SC_TYPE_UNDER_GROUND)
			{
				if (SIMON->GetStartPoint() == startstage2)
				{
					SIMON->SetStartPoint(startstage3);
					SIMON->SetEndPoint(endstage3);
					camera->SetStartPoint(startstage3);
					camera->SetEndPoint(endstage3);
					SIMON->SetPosition(simonposlandtounderground1x, simonposlandtounderground1y);
				}
				else if (SIMON->GetStartPoint() == startstage3)
				{
					SIMON->SetStartPoint(startstage2);
					SIMON->SetEndPoint(endstage2);
					camera->SetStartPoint(startstage2);
					camera->SetEndPoint(endstage2);
					SIMON->SetPosition(simonposundergroundtoland1x, simonposundergroundtoland1y);
				}
			}
			else if (InOb->type == SC_TYPE_UNDER_TO_LAND)
			{
				if (SIMON->GetStartPoint() == startstage2)
				{
					SIMON->SetStartPoint(startstage3);
					SIMON->SetEndPoint(endstage3);
					camera->SetStartPoint(startstage3);
					camera->SetEndPoint(endstage3);
					SIMON->SetPosition(simonposlandtounderground2x, simonposlandtounderground2y);
				}
				else if (SIMON->GetStartPoint() == startstage3)
				{
					SIMON->SetStartPoint(startstage2);
					SIMON->SetEndPoint(endstage2);
					camera->SetStartPoint(startstage2);
					camera->SetEndPoint(endstage2);
					SIMON->SetPosition(simonposundergroundtoland2x, simonposundergroundtoland2y);
				}
			}
			else if (InOb->type == MONEY_SPAWNER)
			{
				InOb->SetActive(false);
				hiddenmoney->SetActive(true);
			}
			else if (InOb->type == GHOUL_SPAWNER)
			{
				if (spawndelayghoul == 0)
				{
					int a;
					srand(time(NULL));
					a = rand() % 4 + 1;
					for (int i = 0; i < a; i++)
					{
						ghoul = new CGhoul();
						ghoul->nx = 1;
						ghoul->SetPosition(camera->GetPosition().x - 20 - i * 20, ghouly);
						enemy.push_back(ghoul);
					}
					for (int i = 0; i < (4 - a); i++)
					{
						ghoul = new CGhoul();
						ghoul->nx = -1;
						ghoul->SetPosition(camera->GetPosition().x + SCREEN_WIDTH + i * 20, ghouly);
						enemy.push_back(ghoul);
					}
					SpawnDelayGhoulStart();
				}

			}
			else if (InOb->type == PANTHER_SPAWNER)
			{
				if (spawndelaypanther == 0)
				{
					panther = new CPanther(SIMON, camera, panther1x);
					panther->nx = -1;
					panther->SetPosition(panther1x, panther1y);
					enemy.push_back(panther);
					panther = new CPanther(SIMON, camera, panther2x);
					panther->nx = -1;
					panther->SetPosition(panther2x, panther2y);
					enemy.push_back(panther);
					panther = new CPanther(SIMON, camera, panther3x);
					panther->nx = -1;
					panther->SetPosition(panther3x, panther3y);
					enemy.push_back(panther);
					SpawnDelayPantherStart();
				}
			}
			else if (InOb->type == BAT_SPAWNER)
			{
				if (spawndelaybat == 0)
				{
					bat = new CBat(D3DXVECTOR2(SIMON->GetPosition().x, SIMON->GetPosition().y - 5));
					bat->nx = -1;
					bat->SetPosition(camera->GetPosition().x + SCREEN_WIDTH, SIMON->GetPosition().y - 50);
					enemy.push_back(bat);
					SpawnDelayBatStart();
				}

			}
			else if (InOb->type == FISHMAN_SPAWNER)
			{
				if (spawndelayfishman == 0)
				{
					fishman = new CFishman(SIMON, camera, InOb->x - 50);
					fishman->nx = -1;
					fishman->SetPosition(InOb->x - 50, InOb->y + 120);
					enemy.push_back(fishman);
					effect = new CEffect(camera);
					effect->SetType(EFFECT_TYPE_WATER);
					effect->SetPosition(InOb->x - 60, InOb->y + 50);
					effects.push_back(effect);

					fishman = new CFishman(SIMON, camera, InOb->x + 40);
					fishman->nx = 1;
					fishman->SetPosition(InOb->x + 40, InOb->y + 120);
					enemy.push_back(fishman);
					effect = new CEffect(camera);
					effect->SetType(EFFECT_TYPE_WATER);
					effect->SetPosition(InOb->x + 50, InOb->y + 50);
					effects.push_back(effect);
					SpawnDelayFishmanStart();
				}

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
				if (game->IsKeyDown(DIK_DOWN))
				{
					if (SIMON->x >= InOb->x - 14 || SIMON->x < InOb->x - 14 && SIMON->GetOnStair() == false)
					{
						SIMON->x = InOb->x - 14;
					}
					if (SIMON->x >= InOb->x - 14 || SIMON->x <= InOb->x - 16)
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
						SIMON->y = InOb->y + 1 + INVI_HEIGHT * 2 - SIMON_IDLE_BBOX_HEIGHT;
					}
					SIMON->SetOnStair(false);
					SIMON->SetStairUp(false);
				}
			}
			else if (InOb->type == STAIR_TYPE_UP_LEFT)
			{
				if (game->IsKeyDown(DIK_UP))
				{
					if (InOb->x - SIMON->x >= 20)
					{
						SIMON->x = InOb->x - 23.5;
					}
					if (SIMON->x <= InOb->x - 23.5)
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
				if (game->IsKeyDown(DIK_DOWN) && SIMON->GetOnStair() == false)
				{
					if (SIMON->x >= InOb->x - 5 || SIMON->x < InOb->x - 6 && SIMON->GetOnStair() == false)
					{
						SIMON->x = InOb->x - 5;
					}
					if (SIMON->x == InOb->x - 5)
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

	//Simon Collision with enemy
	for (int i = 0; i < enemy.size(); i++)
	{
		if (SIMON->CheckCollision(enemy.at(i)))
		{
			if (enemy.at(i)->GetState() == ENEMY_STATE_MOVING)
			{
				if (SIMON->GetUntouchable() == 0)
				{
					if (enemy.at(i)->nx > 0)
					{
						SIMON->nx = -1;
					}
					else SIMON->nx = 1;
					if (SIMON->GetOnStair() == false)
					{
						SIMON->StartIsDamaged();
					}
					SIMON->StartIsUnTouchable();
				}
				if (enemy.at(i)->type == BAT)
				{
					enemy.at(i)->StartDieTime();
					enemy.at(i)->SetState(ENEMY_STATE_DIE);
				}
			}
			else if (enemy.at(i)->GetState() == ENEMY_STATE_SHEART)
			{
				enemy.erase(enemy.begin() + i);
			}
		}
	}

	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy.at(i)->type == FISHMAN)
		{
			CFishman* fish = dynamic_cast<CFishman*>(enemy[i]);
			if (SIMON->CheckCollision(fish->firebullet))
			{
				if (SIMON->GetUntouchable() == 0)
				{
					if (enemy.at(i)->nx > 0)
					{
						SIMON->nx = -1;
					}
					else SIMON->nx = 1;
					if (SIMON->GetOnStair() == false)
					{
						SIMON->StartIsDamaged();
					}
					SIMON->StartIsUnTouchable();
				}

			}
		}
	}

	//Weapon collision with torch
	for (int i = 0; i < torches.size(); i++)
	{
		CTorch* torch = dynamic_cast<CTorch*>(torches[i]);
		if (MS->CheckCollision(torch) || dagger->CheckCollision(torch))
		{
			if (torch->GetState() == TORCH_STATE_NORMAL || torch->GetState() == TORCH_STATE_CANDLE)
			{
				torch->StartDieTime();
				torch->FirstX = torch->x;
				dagger->SetActive(false);
				MS->MSUpDropTime++;
				int a;
				srand(time(NULL));
				a = rand() % 30 + 1;
				if (MS->MSUpDropTime < 3)
				{
					torch->SetState(TORCH_STATE_MSUP);
				}
				else
					switch (a)
					{
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
					case 8:
					case 9:
					case 10:
					case 11:
					case 12:
					case 13:
					case 14:
					case 15:
					case 16:
					case 17:
					case 18:
					case 19:
					case 20:
					case 21:
					case 22:
					case 23:
					case 24:
					case 25:
						torch->SetState(TORCH_STATE_SHEART); break;
					case 26:
						torch->SetState(TORCH_STATE_LHEART); break;
					case 27:
						torch->SetState(TORCH_STATE_DAGGER); break;
					case 28:
						torch->SetState(TORCH_STATE_HOLYWATER); break;
					case 29:
						torch->SetState(TORCH_STATE_CROSS); break;
					case 30:
						torch->SetState(TORCH_STATE_AXE); break;
					}
			}
		}
	}

	//Morning Star collsion with breackable brick
	for (int i = 0; i < bricks.size(); i++)
	{
		if (MS->CheckCollision(bricks.at(i)))
		{
			if (bricks.at(i)->state != BRICK_STATE_NORMAL)
			{
				effect = new CEffect(camera);
				effect->SetPosition(bricks.at(i)->x - 30, bricks.at(i)->y - 20);
				effect->SetType(EFFECT_TYPE_BRICK);
				effects.push_back(effect);
				if (bricks.at(i)->GetState() == BBRICK_STATE_NORMAL)
				{
					bricks.at(i)->SetActive(false);
				}
				else if (bricks.at(i)->GetState()== BBRICK_STATE_CHIKEN_BRICK)
				{
					bricks.at(i)->SetState(BBRICK_STATE_CHIKEN);
				}
				else if (bricks.at(i)->GetState() == BBRICK_STATE_MONEY_BRICK)
				{
					bricks.at(i)->SetState(BBRICK_STATE_MONEY);
				}
				else if (bricks.at(i)->GetState() == BBRICK_STATE_DOUBLE_SHOOT_BRICK)
				{
					bricks.at(i)->SetState(BBRICK_STATE_DOUBLE_SHOOT);
				}
			}
		}
	}

	//Weapon collision with enemy
	for (int i = 0; i < enemy.size(); i++)
	{
		if (MS->CheckCollision(enemy.at(i))
			|| dagger->CheckCollision(enemy.at(i)) && dagger->active == true
			|| Axe->CheckCollision(enemy.at(i)) && Axe->active == true
			|| Holywater->CheckCollision(enemy.at(i)) && Holywater->isOnGround)
		{
			dagger->SetActive(false);
			Axe->SetActive(false);
			enemy.at(i)->FirstX = enemy.at(i)->x;
			if (enemy.at(i)->GetState() == ENEMY_STATE_MOVING)
			{
				enemy.at(i)->StartDieTime();
				enemy.at(i)->SetState(ENEMY_STATE_DIE);
			}
		}
	}

	//Delete object when unactive
	for (int i = 0; i < weapon.size(); i++)
	{
		if (weapon.at(i)->GetActive() == false)
		{
			weapon.erase(weapon.begin() + i);
		}
	}
	for (int i = 0; i < effects.size(); i++)
	{
		if (effects.at(i)->GetActive() == false)
		{
			effects.erase(effects.begin() + i);
		}
	}
	for (int i = 0; i < bricks.size(); i++)
	{
		if (bricks.at(i)->GetActive() == false)
		{
			bricks.erase(bricks.begin() + i);
		}
	}
	for (int i = 0; i < torches.size(); i++)
	{
		if (torches.at(i)->GetActive() == false)
		{
			torches.erase(torches.begin() + i);
		}
	}
	for (int i = 0; i < invisibleobjects.size(); i++)
	{
		if (invisibleobjects.at(i)->GetActive() == false)
		{
			invisibleobjects.erase(invisibleobjects.begin() + i);
		}
	}

	//Adjust Simon to Camera
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
	if (SIMON->GetStartPoint() == 1579)
	{
		camera->SetCamera((SIMON->x + 15) - SCREEN_WIDTH / 2, 200);
	}

	//Map boundary

	//Deleate enemy when out of camera
	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy.at(i)->x < camera->GetPosition().x - (enemy.at(i)->GetBound().right - enemy.at(i)->GetBound().left)  && enemy.at(i)->nx < 0)
		{
			if (enemy.at(i)->type == PANTHER)
				return;
			else enemy.erase(enemy.begin() + i);
		}
	    else if (enemy.at(i)->x > camera->GetPosition().x + SCREEN_WIDTH && enemy.at(i)->nx > 0)
		{
			enemy.erase(enemy.begin() + i);
		}
	}

	//Update Objects
	for (int i = 0; i < torches.size(); i++)
	{
		torches[i]->Update(dt, &bricks);
	}
	for (int i = 0; i < weapon.size(); i++)
	{
		weapon[i]->Update(dt, &bricks);
	}
	for (int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->Update(dt, &bricks);
	}
	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Update(dt, &bricks);
	}
	for (int i = 0; i < bricks.size(); i++)
	{
		bricks[i]->Update(dt, &bricks);
	}
	camera->Update(dt, startpoint, endpoint);
	SIMON->Update(dt, &bricks);
	MS->Update(dt, &bricks);
	hiddenmoney->Update(dt, &bricks);

	//functiions that affect the scene
	if (GetTickCount() - spawndelayghoultimer_start > SPAWN_DELAY_TIMER)
	{
		spawndelayghoultimer_start = 0;
		spawndelayghoul = 0;
    }
	if (GetTickCount() - spawndelaybattimer_start > SPAWN_DELAY_TIMER)
	{
		spawndelaybattimer_start = 0;
		spawndelaybat = 0;
	}
	if (GetTickCount() - spawndelayfishmantimer_start > SPAWN_DELAY_TIMER)
	{
		spawndelayfishmantimer_start = 0;
		spawndelayfishman = 0;
	}
	if (GetTickCount() - spawndelaypanthertimer_start > SPAWN_DELAY_TIMER)
	{
		spawndelaypanthertimer_start = 0;
		spawndelaypanther = 0;
	}
	if (GetTickCount() - stopenemytimer_start > STOP_ENEMY_TIMER)
	{
		stopenemytimer_start = 0;
		stopenemy = 0;
	}
	if (stopenemy != 0)
	{
		for (int i = 0; i < enemy.size(); i++)
		{
			enemy.at(i)->isStop = true;
		}
	}
	if (stopenemy == 0)
	{
		for (int i = 0; i < enemy.size(); i++)
		{
			enemy.at(i)->isStop = false;
		}
	}
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
		for (int i = 0; i < torches.size(); i++)
			torches[i]->Render(camera);
		for (int i = 0; i < invisibleobjects.size(); i++)
			invisibleobjects[i]->Render(camera);
		for (int i = 0; i < enemy.size(); i++)
			enemy[i]->Render(camera);
		for (int i = 0; i < weapon.size(); i++)
			weapon[i]->Render(camera);
		for (int i = 0; i < effects.size(); i++)
			effects[i]->Render(camera);
		for (int i = 0; i < bricks.size(); i++)
			bricks[i]->Render(camera);
		hiddenmoney->Render(camera);
		SIMON->Render(camera);
		MS->Render(camera);
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
	int arr[10];
	ifstream file_objects(source);
	if (file_objects.is_open())
	{
		while (!file_objects.eof())
		{
			while (file_objects >> number)
			{
				arr[flag] = number;
				flag++;
				if (flag == 10)
				{
					switch (arr[0])
					{
					case BRICK:
						brick = new CBrick();
						brick->SetMulwidth(arr[3]);
						brick->SetPosition(arr[1], arr[2]);
						grid->InsertIntoGrid(brick, arr[6], arr[7], arr[8], arr[9]);
						break;
					case TORCH:
						torch = new CTorch();
						torch->SetPosition(arr[1], arr[2]);
						torch->SetState(arr[3]);
						grid->InsertIntoGrid(torch, arr[6], arr[7], arr[8], arr[9]);
						break;
					case STAGECHANGER:
						InObj = new InviObjects();
						InObj->SetPosition(arr[1], arr[2]);
						InObj->SetType(arr[3]);
						grid->InsertIntoGrid(InObj, arr[6], arr[7], arr[8], arr[9]);
						break;
					case BREAKABLE_BRICK:
						brick = new CBrick();
						brick->SetMulwidth(1);
						brick->SetState(arr[3]);
						brick->SetPosition(arr[1], arr[2]);
						grid->InsertIntoGrid(brick, arr[6], arr[7], arr[8], arr[9]);
					}

					flag = 0;
				}
			}
		}
	}
}

void SceneGame::LoadSceneObject(int scene)
{
	if (scene == 1)
	{
		LoadObjectFromFile("ReadFile\\Objects\\ObjectsScene1.txt");
		grid->maprow = 3;
		grid->mapcol = 9;
	}
	if (scene == 2)
	{
		LoadObjectFromFile("ReadFile\\Objects\\ObjectsScene2.txt");
		grid->maprow = 6;
		grid->mapcol = 35;
	}
}

void SceneGame::LoadElementFromFile(string source)
{
	vector<int> numbers;
	int flag = 0;
	int number;
	int arr[29];
	int simonstartx;
	int simonstarty;
	ifstream file_objects(source);
	if (file_objects.is_open())
	{
		while (!file_objects.eof())
		{
			while (file_objects >> number)
			{
				arr[flag] = number;
				flag++;
				if (flag == 28)
				{
					simonposstartx = arr[0];
				    simonposstarty = arr[1];
					simonposlandtounderground1x = arr[2];
					simonposlandtounderground1y = arr[3];
					simonposundergroundtoland1x = arr[4];
					simonposundergroundtoland1y = arr[5];
					simonposlandtounderground2x = arr[6];
					simonposlandtounderground2y = arr[7];
					simonposundergroundtoland2x = arr[8];
					simonposundergroundtoland2y = arr[9];
					hiddenmoneyposx = arr[10];
					hiddenmoneyposy = arr[11];
				    ghouly = arr[12];
					panther1x = arr[13];
					panther1y = arr[14];
					panther2x = arr[15];
					panther2y = arr[16];
					panther3x = arr[17];
					panther3y = arr[18];
					startstage1 = arr[19];
					endstage1 = arr[20];
					startstage2 = arr[21];
					endstage2 = arr[22];
					startstage3 = arr[23];
					endstage3 = arr[24];
					startstage4 = arr[25];
					endstage4 = arr[26];
					effectdoory = arr[27];
					end = arr[28];
				}
			}
		}
	}
}

void SceneGame::LoadSceneElement(int scene)
{
	if (scene == 1)
	{
		LoadElementFromFile(SOURCE_ENTRANCE_ELEMENT_TXT);
	}
	if (scene == 2)
	{
		LoadElementFromFile(SOURCE_CASTLE_ELEMENT_TXT);
	}
}

SceneGame::~SceneGame()
{
	delete Tile;
	Tile = nullptr;
}