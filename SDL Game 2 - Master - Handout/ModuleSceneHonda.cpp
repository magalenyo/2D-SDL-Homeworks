#include "Globals.h"
#include "ModuleSceneHonda.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"


ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 376;
	ground.w = 848;
	ground.h = 64;

	// ceiling
	ceiling.x = 92;
	ceiling.y = 8;
	ceiling.w = 765;
	ceiling.h = 48;

	// Background
	background.x = 216;
	background.y = 176;
	background.w = 544;
	background.h = 130;

	// Bath
	bath.x = 312;
	bath.y = 336;
	bath.w = 336;
	bath.h = 32;

	// Bath top¡
	bathTop.x = 312;
	bathTop.y = 312;
	bathTop.w = 336;
	bathTop.h = 20;

	// Bath flow
	bathFlow.frames.push_back({ 8,   448, 284,  8 });
	bathFlow.frames.push_back({ 296, 448, 284, 12 });
	bathFlow.frames.push_back({ 588, 448, 284, 18 });
	bathFlow.speed = 0.08f;
}

ModuleSceneHonda::~ModuleSceneHonda()
{
}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading honda scene");

	graphics = App->textures->Load("honda_stage.png");

	App->player->Enable();

	//App->audio->PlayMusic("honda.ogg");

	return true;
}

// UnLoad assets
bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading honda scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneHonda::Update()
{
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, -200, 160, &ground);
	App->renderer->Blit(graphics, -200, 0, &ceiling);
	App->renderer->Blit(graphics, -25, 35, &background, 1.45f);
	App->renderer->Blit(graphics, 74, 144, &bath, 1.0f);
	App->renderer->Blit(graphics, 74, 124, &bathTop, 1.0f);
	App->renderer->Blit(graphics, 102, 136, &(bathFlow.GetCurrentFrame()), 1.0f);
	

	return UPDATE_CONTINUE;
}