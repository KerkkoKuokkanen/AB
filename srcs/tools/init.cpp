
#include "../../hdr/ab.h"
#include "../../hdr/global.h"

void initKeys()
{
	gameState.keys.w = 0;
	gameState.keys.a = 0;
	gameState.keys.s = 0;
	gameState.keys.d = 0;
	gameState.keys.space = 0;
	gameState.keys.click = 0;
	gameState.keys.rightClick = 0;
	gameState.keys.middleMouse = 0;
	gameState.camera.clickTimePosX = 0;
	gameState.camera.clickTimePosY = 0;
}

void initScreen(int width, int height)
{
	gameState.screen.width = width;
	gameState.screen.height = height;
	gameState.screen.aspectRatio = (float)gameState.screen.width / (float)gameState.screen.height;
	gameState.screen.midPointX = gameState.screen.width / 2;
	gameState.screen.midPointY = gameState.screen.height / 2;
	gameState.camera.x = 0;
	gameState.camera.y = 0;
	gameState.camera.zoom = 0.0f;
	gameState.screen.unit = 1.0f / 100000.0f;
	gameState.screen.xPixelUnit = (1.0f / gameState.screen.unit) / gameState.screen.width;
	gameState.screen.yPixelUnit = (1.0f / gameState.screen.unit) / gameState.screen.height;
}

void getAudio()
{
	Mix_Volume(THIEF_STEP_CHANNEL, 16);
	gameState.audio.TFootStep[0] = Mix_LoadWAV("audio/footsteps/step0.wav");
	gameState.audio.TFootStep[1] = Mix_LoadWAV("audio/footsteps/step1.wav");
	gameState.audio.TFootStep[2] = Mix_LoadWAV("audio/footsteps/step2.wav");
}

void getTextures(SDL_Renderer *rend)
{
	gameState.textures.thiefIdle1 = get_texture(rend, "sprites/characters/hood_idle1.png");
	gameState.textures.thiefIdle2 = get_texture(rend, "sprites/characters/hood_idle2.png");
	gameState.textures.skeleIdle1 = get_texture(rend, "sprites/characters/skele.png");
	gameState.textures.skeleIdle2 = get_texture(rend, "sprites/characters/skele2.png");
	gameState.textures.dust = get_texture(rend, "sprites/effects/dust.png");
	gameState.textures.turnOrder[0] = get_texture(rend, "sprites/env/turnOrder.png");
	gameState.textures.turnOrder[1] = get_texture(rend, "sprites/env/turnOrderBackGround.png");
	gameState.textures.turnIndicator = get_texture(rend, "sprites/env/indicator.png");
	gameState.textures.KillParticle[0] = get_texture(rend, "sprites/env/killPart1.png");
	gameState.textures.KillParticle[1] = get_texture(rend, "sprites/env/killPart2.png");
}

void	init(t_wr *wr)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(8);
	SDL_CreateWindowAndRenderer(1280, 720, 0, &wr->win, &wr->rend);
	SDL_SetRenderDrawBlendMode(wr->rend, SDL_BLENDMODE_BLEND);
	initScreen(1280, 720);
	initKeys();
	static Renderer render(wr->rend);
	render.CreateLayer(LAYER_REVERSE_YSORT); //battleground layer
	render.CreateLayer(LAYER_YSORT); //battleground layer
	render.CreateLayer(LAYER_YSORT); //turnorder layer
	render.CreateLayer(LAYER_YSORT);
	render.CreateLayer(LAYER_YSORT);
	gameState.render = &render;
	static BattleGround battle(BATTLEGROUND_LAYER, wr->rend);
	gameState.battle.ground = &battle;
	gameState.battle.xDist = 6000;
	gameState.battle.yDist = 6000;
	gameState.battle.defaultYAdd = 1850;
	gameState.battle.yHeightAdd = 2300;
	gameState.updateObjs.turnOrder = NULL;
	gameState.updateObjs.fadeIter = 0.0f;
	getTextures(wr->rend);
	getAudio();
	static TurnIndicator ind;
	gameState.updateObjs.indicator = &ind;
	static Kill killer;
	gameState.updateObjs.killer = &killer;
	//SDL_SetWindowFullscreen(wr->win, 1);
	//SDL_ShowCursor(SDL_DISABLE);
}
