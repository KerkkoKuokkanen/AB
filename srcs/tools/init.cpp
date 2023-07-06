
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
	gameState.screenShake.shakeCounter = 0;
	gameState.screenShake.xShake = 0;
	gameState.screenShake.yShake = 0;
	gameState.screenShake.shakeVolume = 0;
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
	Mix_Volume(Channels::WHIFF, 70);
	Mix_Volume(Channels::DAGGER_THROW_ANIM, 30);
	Mix_Volume(Channels::SMOKE_THROW, 30);
	Mix_Volume(Channels::SMOKE_BOMB, 38);
	Mix_Volume(Channels::DAGGER_SLASH, 30);
	gameState.audio.TFootStep[0] = Mix_LoadWAV("audio/footsteps/step0.wav");
	gameState.audio.TFootStep[1] = Mix_LoadWAV("audio/footsteps/step1.wav");
	gameState.audio.TFootStep[2] = Mix_LoadWAV("audio/footsteps/step2.wav");
	gameState.audio.daggerThrow[0] = Mix_LoadWAV("audio/abilities/dagger1.wav");
	gameState.audio.daggerThrow[1] = Mix_LoadWAV("audio/abilities/dagger2.wav");
	gameState.audio.throwAnim = Mix_LoadWAV("audio/abilities/throw.wav");
	gameState.audio.smokeBomb = Mix_LoadWAV("audio/abilities/smoke.wav");
	gameState.audio.smokeThrow = Mix_LoadWAV("audio/abilities/throw1.wav");
	gameState.audio.daggerSlash = Mix_LoadWAV("audio/abilities/slash.wav");
	gameState.audio.whiff = Mix_LoadWAV("audio/effects/whiff.wav");
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
	gameState.textures.thiefAbilites[1] = get_texture(rend, "sprites/UI/abilities/smokeBomb.png");
	use = get_texture_and_surface(rend, "sprites/UI/energyStand.png");
	gameState.textures.energy[0] = use.text;
	gameState.surfaces.energy[0] = use.sur;
	use = get_texture_and_surface(rend, "sprites/UI/energy.png");
	gameState.textures.energy[1] = use.text;
	gameState.surfaces.energy[1] = use.sur;
	gameState.textures.weaponObjs[DAGGER_OBJ] = get_texture(rend, "sprites/weapon/dagger.png");
	gameState.textures.thiefDaggerThrow = get_texture(rend, "sprites/characters/hood_throw.png");
	use = get_texture_and_surface(rend, "sprites/ground/objects/bush.png");
	gameState.textures.trees[0] = use.text;
	gameState.surfaces.trees[0] = use.sur;
	use = get_texture_and_surface(rend, "sprites/ground/objects/deadTree.png");
	gameState.textures.trees[1] = use.text;
	gameState.surfaces.trees[1] = use.sur;
	use = get_texture_and_surface(rend, "sprites/ground/objects/smallTree.png");
	gameState.textures.trees[2] = use.text;
	gameState.surfaces.trees[2] = use.sur;
	use = get_texture_and_surface(rend, "sprites/ground/objects/stump.png");
	gameState.textures.trees[3] = use.text;
	gameState.surfaces.trees[3] = use.sur;
	use = get_texture_and_surface(rend, "sprites/ground/objects/Tree.png");
	gameState.textures.trees[4] = use.text;
	gameState.surfaces.trees[4] = use.sur;
	gameState.textures.blocks[0] = get_texture(rend, "sprites/env/fullBlock.png");
	gameState.textures.blocks[1] = get_texture(rend, "sprites/env/halfBlock.png");
	gameState.textures.thiefSmokeThrow[0] = get_texture(rend, "sprites/characters/hood_smoke.png");
	gameState.textures.thiefSmokeThrow[1] = get_texture(rend, "sprites/effects/hood_smoke_trail.png");
	gameState.textures.smokes[0] = get_texture(rend, "sprites/env/smoke1-1.png");
	gameState.textures.smokes[1] = get_texture(rend, "sprites/env/smoke1-2.png");
	gameState.textures.smokes[2] = get_texture(rend, "sprites/env/smoke2-1.png");
	gameState.textures.smokes[3] = get_texture(rend, "sprites/env/smoke2-2.png");
	gameState.textures.stands.thiefIdle1Stand = get_texture(rend, "sprites/characters/hood_idle1_stand.png");
	gameState.textures.stands.thiefIdle2Stand = get_texture(rend, "sprites/characters/hood_idle2_stand.png");
	gameState.textures.stands.skeleIdle1Stand = get_texture(rend, "sprites/characters/skele_stand.png");
	gameState.textures.stands.skeleIdle2Stand = get_texture(rend, "sprites/characters/skele2_stand.png");
	gameState.textures.smokeBomb = get_texture(rend, "sprites/weapon/smokeBomb.png");
	gameState.textures.thiefSlash[0] = get_texture(rend, "sprites/characters/hood_slash.png");
	use = get_texture_and_surface(rend, "sprites/effects/hood_slash_trail.png");
	gameState.textures.thiefSlash[1] = use.text;
	gameState.surfaces.slashTrail = use.sur;
	gameState.textures.thiefAbilites[2] = get_texture(rend, "sprites/UI/abilities/daggerSlash.png");
}

void	init(t_wr *wr)
{
	srand((unsigned int)clock() + time(0));
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(20);
	SDL_CreateWindowAndRenderer(1280, 720, 0, &wr->win, &wr->rend);
	SDL_SetRenderDrawBlendMode(wr->rend, SDL_BLENDMODE_BLEND);
	initScreen(1280, 720);
	initKeys();
	static Renderer render(wr->rend);
	render.CreateLayer(LAYER_DEPTH_SORT); //battleground layer
	render.CreateLayer(LAYER_YSORT); //dust layer
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
	static Abilities abilities;
	gameState.updateObjs.abilities = &abilities;
	static OBJ_Update objUpdate;
	gameState.updateObjs.objUpdate = &objUpdate;
	//SDL_SetWindowFullscreen(wr->win, 1);
	//SDL_ShowCursor(SDL_DISABLE);
}
