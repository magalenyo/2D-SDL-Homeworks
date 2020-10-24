#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"
#include "ModuleSceneHonda.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

// Reference at https://youtu.be/OEhmUuehGOA?t=72

ModuleSceneKen::ModuleSceneKen(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// TODO 2 : setup the foreground (red ship) with
	// coordinates x,y,w,h from ken_stage.png
	foreground.x = 8;
	foreground.y = 24;
	foreground.w = 528;
	foreground.h = 180;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.frames.push_back({848, 208, 40, 40});
	flag.frames.push_back({848, 256, 40, 40});
	flag.frames.push_back({848, 304, 40, 40});
	flag.speed = 0.08f;

	// TODO 4: Setup Girl Animation from coordinates from ken_stage.png
	girl.frames.push_back({ 624, 16,  32, 56 });
	girl.frames.push_back({ 624, 80,  32, 56 });
	girl.frames.push_back({ 624, 144, 32, 56 });
	girl.frames.push_back({ 624, 80,  32, 56 });
	girl.speed = 0.08f;

	// ship animation -> does not work
	/*ship.frames.push_back({ 8, 20, 521, 181 });
	ship.frames.push_back({ 8, 24, 528, 190 });
	ship.frames.push_back({ 8, 24, 521, 181 });
	ship.speed = 2.0f;*/
	shipYPosition = 0;
	shipMultiplier = 1;
}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("ken_stage.png");

	// TODO 7: Enable the player module
	App->player->Enable();
	// TODO 0: trigger background music
	App->audio->PlayMusic("ken.ogg");
	
	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	// TODO 5: make sure the ship goes up and down
	// App->renderer->Blit(graphics, 0, 0, &(ship.GetCurrentFrame()), 4.0f); // this does not work
	shipYPosition += (1 * shipMultiplier);
	if (shipYPosition == 60) {
		shipMultiplier = -1;
	}
	else if (shipYPosition == 0) {
		shipMultiplier = 1;
	}

	// Draw everything --------------------------------------
	// TODO 1: Tweak the parallax movement speed of the sea&sky + flag to your taste
	App->renderer->Blit(graphics, 0, 0, &background, 2.0f); // sea and sky
	App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 2.0f); // flag animation

	// TODO 3: Draw the ship. Be sure to tweak the speed.
	App->renderer->Blit(graphics, 0, shipMultiplier, &foreground, 4.0f);
	//App->renderer->Blit(graphics, 0, 0, &(ship.GetCurrentFrame()), 4.0f); // this does not work

	// TODO 6: Draw the girl. Make sure it follows the ship movement!
	App->renderer->Blit(graphics, 192, 104 + shipMultiplier, &(girl.GetCurrentFrame()), 4.0f);
	App->renderer->Blit(graphics, 0, 170, &ground);

	// TODO 10: Build an entire new scene "honda", you can find its
	// and music in the Game/ folder

	// TODO 11: Make that pressing space triggers a switch to honda logic module
	if (App->input->GetKey(SDL_SCANCODE_SPACE)) {
		App->fade->FadeToBlack(App->scene_honda, this, 3.0f);
	}
	
	// using FadeToBlack module

	return UPDATE_CONTINUE;
}