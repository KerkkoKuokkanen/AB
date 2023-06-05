
#include "../../hdr/ab.h"
#include "../../hdr/global.h"

void initKeys()
{
	gameState.keys.w = 0;
	gameState.keys.a = 0;
	gameState.keys.s = 0;
	gameState.keys.d = 0;
	gameState.keys.left = 0;
	gameState.keys.right = 0;
	gameState.keys.up = 0;
	gameState.keys.down = 0;
	gameState.keys.shift = 0;
	gameState.keys.space = 0;
	gameState.keys.click = 0;
	gameState.keys.rightClick = 0;
	gameState.keys.middleMouse = 0;
	gameState.camera.clickTimePosX = 0;
	gameState.camera.clickTimePosY = 0;
	gameState.keys.smX = 0;
	gameState.keys.smY = 0;
	gameState.keys.staticMouseX = 0;
	gameState.keys.staticMouseY = 0;
	gameState.keys.mouseX = 0;
	gameState.keys.mouseY = 0;
	gameState.updateObjs.hover.overAnything = false;
	gameState.updateObjs.hover.overCharacterUI = false;
	gameState.updateObjs.hover.overMenu = false;
	gameState.updateObjs.hover.overTurnOrder = false;
	gameState.updateObjs.hover.overCharacter = false;
	gameState.updateObjs.chosen = NULL;
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
	gameState.screen.xStaticUnit = (1.0f / gameState.screen.unit) / gameState.screen.width;
	gameState.screen.yStaticUnit = (1.0f / gameState.screen.unit) / gameState.screen.height;
}

void getAudio()
{
	Mix_Volume(Channels::THIEF_STEP_CHANNEL, 16);
	Mix_Volume(Channels::DAGGER_THROW0, 15);
	Mix_Volume(Channels::DAGGER_THROW1, 25);
	Mix_Volume(Channels::MISSED_THROW, 128);
	Mix_Volume(Channels::DAGGER_THROW_ANIM, 30);
	gameState.audio.TFootStep[0] = Mix_LoadWAV("audio/footsteps/step0.wav");
	gameState.audio.TFootStep[1] = Mix_LoadWAV("audio/footsteps/step1.wav");
	gameState.audio.TFootStep[2] = Mix_LoadWAV("audio/footsteps/step2.wav");
	gameState.audio.daggerThrow[0] = Mix_LoadWAV("audio/abilities/dagger1.wav");
	gameState.audio.daggerThrow[1] = Mix_LoadWAV("audio/abilities/dagger2.wav");
	gameState.audio.missedThrow = Mix_LoadWAV("audio/abilities/miss.wav");
	gameState.audio.throwAnim = Mix_LoadWAV("audio/abilities/throw.wav");
}

void getTextures(SDL_Renderer *rend)
{
	t_TextAndSur use;
	use = get_texture_and_surface(rend, "sprites/characters/hood_idle1.png");
	gameState.textures.thiefIdle1 = use.text;
	gameState.surfaces.thiefIdle1 = use.sur;
	use = get_texture_and_surface(rend, "sprites/characters/hood_idle2.png");
	gameState.textures.thiefIdle2 = use.text;
	gameState.surfaces.thiefIdle2 = use.sur;
	use = get_texture_and_surface(rend, "sprites/characters/skele.png");
	gameState.textures.skeleIdle1 = use.text;
	gameState.surfaces.skeleIdle1 = use.sur;
	use = get_texture_and_surface(rend, "sprites/characters/skele2.png");
	gameState.textures.skeleIdle2 = use.text;
	gameState.surfaces.skeleIdle2 = use.sur;
	gameState.textures.dust = get_texture(rend, "sprites/effects/dust.png");
	use = get_texture_and_surface(rend, "sprites/env/turnOrder.png");
	gameState.textures.turnOrder[0] = use.text;
	gameState.surfaces.turnOrder[0] = use.sur;
	use = get_texture_and_surface(rend, "sprites/env/turnOrderBackGround.png");
	gameState.textures.turnOrder[1] = use.text;
	gameState.surfaces.turnOrder[1] = use.sur;
	gameState.textures.turnIndicator = get_texture(rend, "sprites/env/indicator.png");
	gameState.textures.KillParticle[0] = get_texture(rend, "sprites/env/part.png");
	gameState.textures.KillParticle[1] = get_texture(rend, "sprites/env/killPart1.png");
	use = get_texture_and_surface_with_scale_mode(rend, "sprites/UI/bar.png", SDL_ScaleModeNearest);
	gameState.textures.bar[0] = use.text;
	gameState.surfaces.bar[0] = use.sur;
	use = get_texture_and_surface_with_scale_mode(rend, "sprites/UI/barBackGround.png", SDL_ScaleModeNearest);
	gameState.textures.bar[1] = use.text;
	gameState.surfaces.bar[1] = use.sur;
	gameState.textures.barFiller = get_texture(rend, "sprites/UI/everyColor.png");
	gameState.textures.turnDone = get_texture(rend, "sprites/UI/button.png");
	gameState.textures.thiefAbilites[0] = get_texture(rend, "sprites/UI/abilities/daggerThrow.png");
	use = get_texture_and_surface(rend, "sprites/UI/energyStand.png");
	gameState.textures.energy[0] = use.text;
	gameState.surfaces.energy[0] = use.sur;
	use = get_texture_and_surface(rend, "sprites/UI/energy.png");
	gameState.textures.energy[1] = use.text;
	gameState.surfaces.energy[1] = use.sur;
	gameState.textures.weaponObjs[DAGGER_OBJ] = get_texture(rend, "sprites/weapon/dagger.png");
	gameState.textures.thiefDaggerThrow = get_texture(rend, "sprites/characters/hood_throw.png");
}

void	init(t_wr *wr)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(8);
	SDL_CreateWindowAndRenderer(2560, 1600, 0, &wr->win, &wr->rend);
	SDL_SetRenderDrawBlendMode(wr->rend, SDL_BLENDMODE_BLEND);
	initScreen(2560, 1600);
	initKeys();
	static Renderer render(wr->rend);
	render.CreateLayer(LAYER_DEPTH_SORT); //battleground layer
	render.CreateLayer(LAYER_YSORT); //battleground layer
	render.CreateLayer(LAYER_NO_SORT); //particle layer
	render.CreateLayer(LAYER_NO_SORT); //object layer
	render.CreateLayer(LAYER_YSORT); //turnorder layer
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
	gameState.updateObjs.characterAnimIter = 0;
	getTextures(wr->rend);
	getAudio();
	static TurnIndicator ind;
	gameState.updateObjs.indicator = &ind;
	static Kill killer;
	gameState.updateObjs.killer = &killer;
	static ParticleManager parts;
	gameState.updateObjs.partManager = &parts;
	static CharacterUI bars;
	gameState.updateObjs.UI = &bars;
	static GroundColoring groundColoring;
	gameState.updateObjs.groundColoring = &groundColoring;
	static AbilityManager abilityManager;
	gameState.updateObjs.abilityManager = &abilityManager;
	static DamageCreator createDamage;
	gameState.updateObjs.createDamage = &createDamage;
	static ObjectManager objectManager;
	gameState.updateObjs.objectManager = &objectManager;
	static AnimationManager animationManager;
	gameState.updateObjs.animationManager = &animationManager;
	SDL_SetWindowFullscreen(wr->win, 1);
	//SDL_ShowCursor(SDL_DISABLE);
}
