
#include "../../hdr/ab.h"
#include "../../hdr/global.h"
#include <thread>

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
	gameState.modes.filterMode = 0;
	gameState.updateObjs.characterAnimIter = 0;
	gameState.updateObjs.characterAnimIndex = 0;
	gameState.modes.disableBars = false;
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
	AudioCreateVolume(Channels::THIEF_STEP_CHANNEL, 16);
	AudioCreateVolume(Channels::DAGGER_THROW0, 15);
	AudioCreateVolume(Channels::DAGGER_THROW1, 25);
	AudioCreateVolume(Channels::WHIFF, 46);
	AudioCreateVolume(Channels::DAGGER_THROW_ANIM, 30);
	AudioCreateVolume(Channels::SMOKE_THROW, 30);
	AudioCreateVolume(Channels::SMOKE_BOMB, 38);
	AudioCreateVolume(Channels::DAGGER_SLASH, 30);
	AudioCreateVolume(Channels::FLAME_PORT1, 12);
	AudioCreateVolume(Channels::FLAME_PORT2, 58);
	AudioCreateVolume(Channels::FLAME_PORT3, 11);
	AudioCreateVolume(Channels::TURN_START, 45);
	AudioCreateVolume(Channels::FLAME_SLASH, 30);
	AudioCreateVolume(Channels::SELECT, 35);
	AudioCreateVolume(Channels::FLAME_BLAST_EXPLOSION, 30);
	AudioCreateVolume(Channels::FLAME_BLAST_CHARGE, 18);
	AudioCreateVolume(Channels::FLAME_BLAST_LAUNCH, 17);
	AudioCreateVolume(Channels::DEBUFF, 105);
	AudioCreateVolume(Channels::INCINERATE_CHARGE, 20);
	AudioCreateVolume(Channels::INCINERATE_SPIN, 38);
	AudioCreateVolume(Channels::INCINERATE_EXP, 38);
	AudioCreateVolume(Channels::INCINERATE_MOLO, 23);
	AudioCreateVolume(Channels::INCINERATE_EXP_SOUND, 14);
	AudioCreateVolume(Channels::LION_SMACK, 18);
	AudioCreateVolume(Channels::STUN, 80);
	AudioCreateVolume(Channels::PHANTOM_KNIGHT, 125);
	AudioCreateVolume(Channels::ROTATE, 35);
	AudioCreateVolume(Channels::POOF, 28);
	AudioCreateVolume(Channels::LOWER_VOLUME_HIT, 17);
	AudioCreateVolume(Channels::LOWER_VOLUME_WHIFF, 50);
	AudioCreateVolume(Channels::OPPORTUNIRY, 70);
	AudioCreateVolume(Channels::KILL_FADE, 40);
	AudioCreateVolume(Channels::KILL_EXPLOSION0, 100);
	AudioCreateVolume(Channels::HAMMER_SMACK, 22);
	AudioCreateVolume(Channels::SUPPLY, 44);
	AudioCreateVolume(Channels::TOOL_THROW, 19);
	AudioCreateVolume(Channels::BOX_LANDING, 45);
	AudioCreateVolume(Channels::BOX_LANDING2, 67);
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
	gameState.audio.flamePort[0] = Mix_LoadWAV("audio/abilities/flamePort2.wav");
	gameState.audio.flamePort[1] = Mix_LoadWAV("audio/abilities/flamePort3.wav");
	gameState.audio.flamePort[2] = Mix_LoadWAV("audio/abilities/flamePort1.wav");
	gameState.audio.turnStart = Mix_LoadWAV("audio/effects/turnChange.wav");
	gameState.audio.flameSlash = Mix_LoadWAV("audio/abilities/fireAttack.wav");
	gameState.audio.select = Mix_LoadWAV("audio/effects/select.wav");
	gameState.audio.flameBlast[0] = Mix_LoadWAV("audio/abilities/Explosion1.wav");
	gameState.audio.flameBlast[1] = Mix_LoadWAV("audio/abilities/explosionCharge.wav");
	gameState.audio.flameBlast[2] = Mix_LoadWAV("audio/abilities/explosionLaunch.wav");
	gameState.audio.debuff = Mix_LoadWAV("audio/effects/debuff.wav");
	gameState.audio.incinerate[0] = Mix_LoadWAV("audio/abilities/pyro/amp.wav");
	gameState.audio.incinerate[1] = Mix_LoadWAV("audio/abilities/pyro/rotate.wav");
	gameState.audio.incinerate[2] = Mix_LoadWAV("audio/abilities/pyro/exp.wav");
	gameState.audio.incinerate[3] = Mix_LoadWAV("audio/abilities/pyro/molo.wav");
	gameState.audio.incinerate[4] = Mix_LoadWAV("audio/abilities/pyro/expSound.wav");
	gameState.audio.lionSmack = Mix_LoadWAV("audio/abilities/lion/punch.wav");
	gameState.audio.stun = Mix_LoadWAV("audio/abilities/lion/stun.wav");
	gameState.audio.phantomKnight = Mix_LoadWAV("audio/abilities/lion/summon.wav");
	gameState.audio.rotate = Mix_LoadWAV("audio/abilities/lion/rotate.wav");
	gameState.audio.poof = Mix_LoadWAV("audio/abilities/lion/poof.wav");
	gameState.audio.opportunity = Mix_LoadWAV("audio/abilities/opportunity.wav");
	gameState.audio.kills[0] = Mix_LoadWAV("audio/effects/killFade.wav");
	gameState.audio.kills[1] = Mix_LoadWAV("audio/effects/killExplosion.wav");
	gameState.audio.hammerSmack = Mix_LoadWAV("audio/abilities/smith/hammerSmack.wav");
	gameState.audio.supply = Mix_LoadWAV("audio/effects/supply.wav");
	gameState.audio.toolThrow = Mix_LoadWAV("audio/abilities/smith/toolThrow.wav");
	gameState.audio.boxLand = Mix_LoadWAV("audio/abilities/smith/boxLanding.wav");
	gameState.audio.boxLand2 = Mix_LoadWAV("audio/abilities/smith/boxLanding2.wav");
}

void getFonts()
{
	gameState.fonts.googleFont = TTF_OpenFont("sprites/fonts/text.ttf", 64);
	gameState.fonts.googleBold = TTF_OpenFont("sprites/fonts/textBold.ttf", 64);
	gameState.fonts.fire = TTF_OpenFont("sprites/fonts/fire.ttf", 64);
	gameState.fonts.neue = TTF_OpenFont("sprites/fonts/Neue.ttf", 64);
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
	use = get_texture_and_surface_with_scale_mode(rend, "sprites/ground/objects/bushLeft.png", SDL_ScaleModeNearest);
	gameState.textures.treesLeft[0] = use.text;
	gameState.surfaces.treesLeft[0] = use.sur;
	use = get_texture_and_surface_with_scale_mode(rend, "sprites/ground/objects/deadTreeLeft.png", SDL_ScaleModeNearest);
	gameState.textures.treesLeft[1] = use.text;
	gameState.surfaces.treesLeft[1] = use.sur;
	use = get_texture_and_surface_with_scale_mode(rend, "sprites/ground/objects/stumpLeft.png", SDL_ScaleModeNearest);
	gameState.textures.treesLeft[2] = use.text;
	gameState.surfaces.treesLeft[2] = use.sur;
	use = get_texture_and_surface_with_scale_mode(rend, "sprites/ground/objects/TreeLeft.png", SDL_ScaleModeNearest);
	gameState.textures.treesLeft[3] = use.text;
	gameState.surfaces.treesLeft[3] = use.sur;
	use = get_texture_and_surface_with_scale_mode(rend, "sprites/ground/objects/bushRight.png", SDL_ScaleModeNearest);
	gameState.textures.treesRight[0] = use.text;
	gameState.surfaces.treesRight[0] = use.sur;
	use = get_texture_and_surface_with_scale_mode(rend, "sprites/ground/objects/deadTreeRight.png", SDL_ScaleModeNearest);
	gameState.textures.treesRight[1] = use.text;
	gameState.surfaces.treesRight[1] = use.sur;
	use = get_texture_and_surface_with_scale_mode(rend, "sprites/ground/objects/stumpRight.png", SDL_ScaleModeNearest);
	gameState.textures.treesRight[2] = use.text;
	gameState.surfaces.treesRight[2] = use.sur;
	use = get_texture_and_surface_with_scale_mode(rend, "sprites/ground/objects/TreeRight.png", SDL_ScaleModeNearest);
	gameState.textures.treesRight[3] = use.text;
	gameState.surfaces.treesRight[3] = use.sur;
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
	use = get_texture_and_surface(rend, "sprites/characters/pyro_idle1.png");
	gameState.textures.chars.pyroIdle1 = use.text;
	gameState.surfaces.pyroIdle1 = use.sur;
	use = get_texture_and_surface(rend, "sprites/characters/pyro_idle2.png");
	gameState.textures.chars.pyroIdle2 = use.text;
	gameState.surfaces.pyroIdle2 = use.sur;
	gameState.textures.stands.pyroStand = get_texture(rend, "sprites/characters/pyro_idle1_stand.png");
	gameState.textures.pyroAbilities[0] = get_texture(rend, "sprites/UI/abilities/flamePort.png");
	gameState.textures.MISS = get_texture(rend, "sprites/UI/miss.png");
	gameState.textures.chars.flameSlash[0] = get_texture(rend, "sprites/characters/pyroFlameSlash.png");
	gameState.textures.chars.flameSlash[1] = get_texture(rend, "sprites/effects/flameSlashEffect.png");
	gameState.textures.pyroAbilities[1] = get_texture(rend, "sprites/UI/abilities/flameSlash.png");
	gameState.textures.pyroAbilities[2] = get_texture(rend, "sprites/UI/abilities/fireBlast.png");
	gameState.textures.marker = get_texture(rend, "sprites/UI/marker.png");
	gameState.textures.attacks.fireBall[0] = get_texture(rend, "sprites/attacks/flameBallBlast1.png");
	gameState.textures.attacks.fireBall[1] = get_texture(rend, "sprites/attacks/flameBallBlast2.png");
	gameState.textures.attacks.fireBallExplosion = get_texture(rend, "sprites/attacks/flameBallExplosion.png");
	gameState.textures.attacks.fireBallAura = get_texture(rend, "sprites/effects/pyro_blast_effect.png");
	gameState.textures.chars.pyroFlameBlast = get_texture(rend, "sprites/characters/pyro_blast.png");
	gameState.textures.ascii.whiteNumbers[0] = get_texture(rend, "sprites/UI/numbers/w0.png");
	gameState.textures.ascii.whiteNumbers[1] = get_texture(rend, "sprites/UI/numbers/w1.png");
	gameState.textures.ascii.whiteNumbers[2] = get_texture(rend, "sprites/UI/numbers/w2.png");
	gameState.textures.ascii.whiteNumbers[3] = get_texture(rend, "sprites/UI/numbers/w3.png");
	gameState.textures.ascii.whiteNumbers[4] = get_texture(rend, "sprites/UI/numbers/w4.png");
	gameState.textures.ascii.whiteNumbers[5] = get_texture(rend, "sprites/UI/numbers/w5.png");
	gameState.textures.ascii.whiteNumbers[6] = get_texture(rend, "sprites/UI/numbers/w6.png");
	gameState.textures.ascii.whiteNumbers[7] = get_texture(rend, "sprites/UI/numbers/w7.png");
	gameState.textures.ascii.whiteNumbers[8] = get_texture(rend, "sprites/UI/numbers/w8.png");
	gameState.textures.ascii.whiteNumbers[9] = get_texture(rend, "sprites/UI/numbers/w9.png");
	gameState.textures.ascii.normalNumbers[0] = get_texture(rend, "sprites/UI/numbers/n0.png");
	gameState.textures.ascii.normalNumbers[1] = get_texture(rend, "sprites/UI/numbers/n1.png");
	gameState.textures.ascii.normalNumbers[2] = get_texture(rend, "sprites/UI/numbers/n2.png");
	gameState.textures.ascii.normalNumbers[3] = get_texture(rend, "sprites/UI/numbers/n3.png");
	gameState.textures.ascii.normalNumbers[4] = get_texture(rend, "sprites/UI/numbers/n4.png");
	gameState.textures.ascii.normalNumbers[5] = get_texture(rend, "sprites/UI/numbers/n5.png");
	gameState.textures.ascii.normalNumbers[6] = get_texture(rend, "sprites/UI/numbers/n6.png");
	gameState.textures.ascii.normalNumbers[7] = get_texture(rend, "sprites/UI/numbers/n7.png");
	gameState.textures.ascii.normalNumbers[8] = get_texture(rend, "sprites/UI/numbers/n8.png");
	gameState.textures.ascii.normalNumbers[9] = get_texture(rend, "sprites/UI/numbers/n9.png");
	gameState.textures.ascii.slash = get_texture(rend, "sprites/UI/slash.png");
	gameState.textures.smallerBar = get_texture_with_scale_mode(rend, "sprites/UI/smallerBar.png", SDL_ScaleModeNearest);
	gameState.textures.statuses.burns[0] = get_texture(rend, "sprites/attacks/burn.png");
	gameState.textures.statuses.burns[1] = get_texture(rend, "sprites/attacks/whiteBurn.png");
	use = get_texture_and_surface(rend, "sprites/attacks/burn2.png");
	gameState.textures.statuses.burns[2] = use.text;
	gameState.surfaces.statuses.burn = use.sur;
	use = get_texture_and_surface(rend, "sprites/env/counter.png");
	gameState.textures.counter = use.text;
	gameState.surfaces.counter = use.sur;
	gameState.textures.pyroAbilities[3] = get_texture(rend, "sprites/UI/abilities/Immolate.png");
	gameState.textures.attacks.incExplosion = gameState.textures.attacks.fireBallExplosion;
	gameState.textures.attacks.incinerate[0] = get_texture(rend, "sprites/attacks/flameBall.png");
	gameState.textures.attacks.incinerate[1] = get_texture(rend, "sprites/attacks/flameBallAura.png");
	gameState.textures.chars.pyroAttack[0] = get_texture(rend, "sprites/characters/pyro_attack.png");
	gameState.textures.chars.pyroAttack[1] = get_texture(rend, "sprites/characters/pyro_attack2.png");
	gameState.textures.chars.pyroAttackParts = get_texture(rend, "sprites/characters/pyro_attack2_kipin.png");
	use = get_texture_and_surface(rend, "sprites/characters/lion/lionIdle1.png");
	gameState.textures.chars.lionIdle[0] = use.text;
	gameState.surfaces.lionIdle1 = use.sur;
	use = get_texture_and_surface(rend, "sprites/characters/lion/lionIdle2.png");
	gameState.textures.chars.lionIdle[1] = use.text;
	gameState.surfaces.lionIdle2 = use.sur;
	gameState.textures.stands.lionStand = get_texture(rend, "sprites/characters/lion/lionStand.png");
	gameState.textures.lionAbilities[0] = get_texture(rend, "sprites/UI/abilities/smack.png");
	gameState.textures.lionAbilities[1] = get_texture(rend, "sprites/UI/abilities/PhantomKnight.png");
	gameState.textures.lionAbilities[2] = get_texture(rend, "sprites/UI/abilities/rotate.png");
	gameState.textures.chars.lionSmack = get_texture(rend, "sprites/characters/lion/lionSmack.png");
	gameState.textures.attacks.lionTrail = get_texture(rend, "sprites/characters/lion/lionSmackTrail.png");
	use = get_texture_and_surface(rend, "sprites/UI/questionMark.png");
	gameState.textures.questionMark = use.text;
	gameState.surfaces.statuses.questionMark = use.sur;
	gameState.textures.control = get_texture(rend, "sprites/env/control.png");
	gameState.textures.everyColor = get_texture(rend, "sprites/env/everyColor.png");
	gameState.textures.stands.smithStand = get_texture(rend, "sprites/characters/blacksmith/blacksmithStand.png");
	use = get_texture_and_surface(rend, "sprites/characters/blacksmith/blacksmith.png");
	gameState.textures.chars.smithIdle[0] = use.text;
	gameState.surfaces.smithIdle1 = use.sur;
	use = get_texture_and_surface(rend, "sprites/characters/blacksmith/blacksmith2.png");
	gameState.textures.chars.smithIdle[1] = use.text;
	gameState.surfaces.smithIdle2 = use.sur;
	gameState.textures.chars.handTools[0] = get_texture(rend, "sprites/characters/blacksmith/handBox1.png");
	gameState.textures.chars.handTools[1] = get_texture(rend, "sprites/characters/blacksmith/handBox2.png");
	gameState.textures.chars.handTools[2] = get_texture(rend, "sprites/characters/blacksmith/handBoxSmack.png");
	gameState.textures.smithAbilities[0] = get_texture(rend, "sprites/UI/abilities/hammerSmack.png");
	gameState.textures.attacks.hammerSmack[0] = get_texture(rend, "sprites/characters/blacksmith/blacksmithSmack.png");
	gameState.textures.attacks.hammerSmack[1] = get_texture(rend, "sprites/characters/blacksmith/blacksmithSmackTrail.png");
	gameState.textures.supplySymbol = get_texture(rend, "sprites/effects/suplySymbol.png");
	gameState.textures.smithAbilities[1] = get_texture(rend, "sprites/UI/abilities/throwToolBox.png");
	gameState.textures.smithAbilities[2] = get_texture(rend, "sprites/UI/abilities/handSuplies.png");
	gameState.textures.smithAbilities[3] = get_texture(rend, "sprites/UI/abilities/pickUpToolBox.png");
	gameState.textures.chars.toolBox = get_texture(rend, "sprites/characters/blacksmith/toolBox.png");
	gameState.textures.attacks.toolThrow[0] = get_texture(rend, "sprites/characters/blacksmith/blackSmithToolThrow.png");
	gameState.textures.attacks.toolThrow[1] = get_texture(rend, "sprites/characters/blacksmith/blackSmithToolTrail.png");
	gameState.textures.throwObj = get_texture(rend, "sprites/UI/abilities/throwObject.png");
	gameState.textures.reSupply = get_texture(rend, "sprites/UI/abilities/resuply.png");
}

void CraeteAudioThread()
{
	static std::thread soundThread([]()
	{
		while (true)
		{
			AudioUpdate();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	});
}

void	init(t_wr *wr)
{
	srand((unsigned int)clock() + time(0));
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	AudioCreateChannels(120);
	SDL_CreateWindowAndRenderer(1280, 720, 0, &wr->win, &wr->rend);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_SetRenderDrawBlendMode(wr->rend, SDL_BLENDMODE_BLEND);
	initScreen(1280, 720);
	initKeys();
	static Renderer render(wr->rend);
	render.CreateLayer(LAYER_DEPTH_SORT); //battleground layer
	render.CreateLayer(LAYER_ORDER_SORT); //line layer
	render.CreateLayer(LAYER_NO_SORT); //dust layer
	render.CreateLayer(LAYER_NO_SORT); //particle layer
	render.CreateLayer(LAYER_NO_SORT); //object layer
	render.CreateLayer(LAYER_DEPTH_SORT); //info layer
	render.CreateLayer(LAYER_ORDER_SORT); //turn order layer
	render.CreateLayer(LAYER_ORDER_SORT); //flying texts;
	render.CreateLayer(LAYER_ORDER_SORT); //counter layer
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
	getFonts();
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
	static Info info;
	gameState.updateObjs.info = &info;
//	SDL_SetWindowFullscreen(wr->win, 1);
//	SDL_ShowCursor(SDL_DISABLE);
	CraeteAudioThread();
}
