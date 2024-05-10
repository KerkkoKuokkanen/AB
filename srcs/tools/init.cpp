
#include "../../hdr/ab.h"
#include "../../hdr/global.h"
#include "../../hdr/render/camera.h"
#include "../../hdr/ow/owHeader.h"
#include "../../hdr/ow/owKeys.h"
#include <thread>

t_Camera gameCamera;
t_owState owState;
t_Keys owKeys;

void InitHovers()
{
	gameState.updateObjs.hover.overAnything = false;
	gameState.updateObjs.hover.overCharacterUI = false;
	gameState.updateObjs.hover.overMenu = false;
	gameState.updateObjs.hover.overTurnOrder = false;
	gameState.updateObjs.hover.overCharacter = false;
	gameState.updateObjs.chosen = NULL;
	gameState.modes.filterMode = 0;
	gameState.updateObjs.characterAnimIter = 0;
	gameState.updateObjs.characterAnimIndex = 0;
	gameState.modes.disableBars = false;
	gameState.delayer = 0;
}

void initKeys(t_Keys &keys)
{
	keys.w = 0;
	keys.a = 0;
	keys.s = 0;
	keys.d = 0;
	keys.tab = 0;
	keys.left = 0;
	keys.right = 0;
	keys.up = 0;
	keys.down = 0;
	keys.shift = 0;
	keys.space = 0;
	keys.click = 0;
	keys.rightClick = 0;
	keys.middleMouse = 0;
	keys.smX = 0;
	keys.smY = 0;
	keys.staticMouseX = 0;
	keys.staticMouseY = 0;
	keys.mouseX = 0;
	keys.mouseY = 0;
}

void initScreen(int width, int height)
{
	gameCamera.screenShake.shakeCounter = 0;
	gameCamera.screenShake.xShake = 0;
	gameCamera.screenShake.yShake = 0;
	gameCamera.screenShake.shakeVolume = 0;
	gameCamera.screen.aspectRatio = (float)gameCamera.screen.width / (float)gameCamera.screen.height;
	gameCamera.screen.midPointX = gameCamera.screen.width / 2;
	gameCamera.screen.midPointY = gameCamera.screen.height / 2;
	gameCamera.x = 0;
	gameCamera.y = 0;
	gameCamera.clickTimePosX = 0;
	gameCamera.clickTimePosY = 0;
	gameCamera.zoom = 0.0f;
	gameCamera.screen.unit = 1.0f / 100000.0f;
	gameCamera.screen.xPixelUnit = (1.0f / gameCamera.screen.unit) / gameCamera.screen.width;
	gameCamera.screen.yPixelUnit = (1.0f / gameCamera.screen.unit) / gameCamera.screen.height;
	gameCamera.screen.xStaticUnit = (1.0f / gameCamera.screen.unit) / gameCamera.screen.width;
	gameCamera.screen.yStaticUnit = (1.0f / gameCamera.screen.unit) / gameCamera.screen.height;
}

void getAudio()
{
	AudioCreateVolume(Channels::THIEF_STEP_CHANNEL, 16);
	AudioCreateVolume(Channels::DAGGER_THROW0, 7);
	AudioCreateVolume(Channels::DAGGER_THROW1, 11);
	AudioCreateVolume(Channels::WHIFF, 24);
	AudioCreateVolume(Channels::DAGGER_THROW_ANIM, 30);
	AudioCreateVolume(Channels::SMOKE_THROW, 30);
	AudioCreateVolume(Channels::SMOKE_BOMB, 28);
	AudioCreateVolume(Channels::DAGGER_SLASH, 30);
	AudioCreateVolume(Channels::FLAME_PORT1, 10);
	AudioCreateVolume(Channels::FLAME_PORT2, 33);
	AudioCreateVolume(Channels::FLAME_PORT3, 9);
	AudioCreateVolume(Channels::TURN_START, 34);
	AudioCreateVolume(Channels::FLAME_SLASH, 30);
	AudioCreateVolume(Channels::SELECT, 35);
	AudioCreateVolume(Channels::FLAME_BLAST_EXPLOSION, 23);
	AudioCreateVolume(Channels::FLAME_BLAST_CHARGE, 14);
	AudioCreateVolume(Channels::FLAME_BLAST_LAUNCH, 13);
	AudioCreateVolume(Channels::DEBUFF, 105);
	AudioCreateVolume(Channels::INCINERATE_CHARGE, 20);
	AudioCreateVolume(Channels::INCINERATE_MOLO, 15);
	AudioCreateVolume(Channels::INCINERATE_EXP_SOUND, 58);
	AudioCreateVolume(Channels::LION_SMACK, 12);
	AudioCreateVolume(Channels::STUN, 40);
	AudioCreateVolume(Channels::PHANTOM_KNIGHT, 125);
	AudioCreateVolume(Channels::ROTATE, 25);
	AudioCreateVolume(Channels::POOF, 28);
	AudioCreateVolume(Channels::LOWER_VOLUME_HIT, 10);
	AudioCreateVolume(Channels::LOWER_VOLUME_WHIFF, 30);
	AudioCreateVolume(Channels::OPPORTUNIRY, 70);
	AudioCreateVolume(Channels::KILL_FADE, 40);
	AudioCreateVolume(Channels::KILL_EXPLOSION0, 100);
	AudioCreateVolume(Channels::HAMMER_SMACK, 22);
	AudioCreateVolume(Channels::SUPPLY, 44);
	AudioCreateVolume(Channels::TOOL_THROW, 19);
	AudioCreateVolume(Channels::BOX_LANDING, 45);
	AudioCreateVolume(Channels::BOX_LANDING2, 67);
	AudioCreateVolume(Channels::PICK_TOOLS, 22);
	AudioCreateVolume(Channels::BUFF_EFFECT, 16);
	AudioCreateVolume(Channels::MAGE_CAST, 28);
	AudioCreateVolume(Channels::LIGHTNING, 26);
	AudioCreateVolume(Channels::METEOR1, 22);
	AudioCreateVolume(Channels::METEOR2, 2);
	AudioCreateVolume(Channels::METEOR3, 5);
	AudioCreateVolume(Channels::HOST_EYES1, 66);
	AudioCreateVolume(Channels::HOST_EYES2, 23);
	AudioCreateVolume(Channels::HOST_EYES3, 7);
	CreateVolumeChannels();
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
	gameState.audio.incinerate[0] = Mix_LoadWAV("audio/abilities/pyro/molo.wav");
	gameState.audio.incinerate[1] = Mix_LoadWAV("audio/abilities/pyro/expSound.wav");
	gameState.audio.lionSmack = Mix_LoadWAV("audio/abilities/lion/punch.wav");
	gameState.audio.stun = Mix_LoadWAV("audio/abilities/lion/stun.wav");
	gameState.audio.phantomKnight = Mix_LoadWAV("audio/abilities/lion/summon.wav");
	gameState.audio.rotate = Mix_LoadWAV("audio/abilities/lion/rotate.wav");
	gameState.audio.poof = Mix_LoadWAV("audio/abilities/lion/poof.wav");
	gameState.audio.opportunity = Mix_LoadWAV("audio/abilities/opportunity.wav");
	gameState.audio.kills[0] = Mix_LoadWAV("audio/effects/killFade.wav");
	gameState.audio.kills[1] = Mix_LoadWAV("audio/effects/killExplosion.wav");
	gameState.audio.kills[2] = Mix_LoadWAV("audio/effects/killAshes.wav");
	gameState.audio.hammerSmack = Mix_LoadWAV("audio/abilities/smith/hammerSmack.wav");
	gameState.audio.supply = Mix_LoadWAV("audio/effects/supply.wav");
	gameState.audio.toolThrow = Mix_LoadWAV("audio/abilities/smith/toolThrow.wav");
	gameState.audio.boxLand = Mix_LoadWAV("audio/abilities/smith/boxLanding.wav");
	gameState.audio.boxLand2 = Mix_LoadWAV("audio/abilities/smith/boxLanding2.wav");
	gameState.audio.pickTools = Mix_LoadWAV("audio/abilities/smith/pickTools.wav");
	gameState.audio.deBuffEffect = Mix_LoadWAV("audio/effects/deBuffEffect.wav");
	gameState.audio.BuffEffect = Mix_LoadWAV("audio/effects/buffEffect.wav");
	gameState.audio.mageCast = Mix_LoadWAV("audio/abilities/mage/cast.wav");
	gameState.audio.lightning = Mix_LoadWAV("audio/abilities/mage/lightning.wav");
	gameState.audio.meteors[0] = Mix_LoadWAV("audio/abilities/mage/meteorSummon.wav");
	gameState.audio.meteors[1] = Mix_LoadWAV("audio/abilities/mage/meteorImpact1.wav");
	gameState.audio.meteors[2] = Mix_LoadWAV("audio/abilities/mage/meteorImpact2.wav");
	gameState.audio.hostEyes[0] = Mix_LoadWAV("audio/abilities/mage/spellEffect.wav");
	gameState.audio.hostEyes[1] = Mix_LoadWAV("audio/abilities/mage/mindStart.wav");
	gameState.audio.hostEyes[2] = Mix_LoadWAV("audio/abilities/mage/mindEnd.wav");
	gameState.audio.axeSwing = Mix_LoadWAV("audio/abilities/raider/axeSwing.wav");
	gameState.audio.jumpScream = Mix_LoadWAV("audio/abilities/raider/jumpScream.wav");
	gameState.audio.raiderJump = Mix_LoadWAV("audio/abilities/raider/jumpstart.wav");
	gameState.audio.hitEffect = Mix_LoadWAV("audio/effects/newHitEffect2.wav");
	gameState.audio.poison = Mix_LoadWAV("audio/effects/poison.wav");
	gameState.audio.toxicBlade = Mix_LoadWAV("audio/abilities/raider/toxicBlade.wav");
	gameState.audio.raiderBlock = Mix_LoadWAV("audio/abilities/raider/block.wav");
	gameState.audio.nailBomb = Mix_LoadWAV("audio/abilities/alchemist/nailBomb.wav");
	gameState.audio.bleed = Mix_LoadWAV("audio/effects/bleed.wav");
	gameState.audio.acidBomb[0] = Mix_LoadWAV("audio/abilities/alchemist/glassBreak.wav");
	gameState.audio.acidBomb[1] = Mix_LoadWAV("audio/abilities/alchemist/airRelease.wav");
	gameState.audio.acidBomb[2] = Mix_LoadWAV("audio/abilities/alchemist/acidFlask.wav");
	gameState.audio.slowBomb[0] = Mix_LoadWAV("audio/abilities/alchemist/slowGlass.wav");
	gameState.audio.slowBomb[1] = Mix_LoadWAV("audio/abilities/alchemist/splash.wav");
	gameState.audio.slowDebuff = Mix_LoadWAV("audio/abilities/alchemist/slowDebuff.wav");
	gameState.audio.flailStrike = Mix_LoadWAV("audio/abilities/knight/strike.wav");
	gameState.audio.shieldBash[0] = Mix_LoadWAV("audio/abilities/knight/shieldBash.wav");
	gameState.audio.shieldBash[1] = Mix_LoadWAV("audio/abilities/knight/shieldMove.wav");
	gameState.audio.rainAttack[0] = Mix_LoadWAV("audio/abilities/witch/rain.wav");
	gameState.audio.rainAttack[1] = Mix_LoadWAV("audio/abilities/witch/acid.wav");
	gameState.audio.teleport[0] = Mix_LoadWAV("audio/abilities/witch/realTele1.wav");
	gameState.audio.teleport[1] = Mix_LoadWAV("audio/abilities/witch/realTele2.wav");
	gameState.audio.heartBeat = Mix_LoadWAV("audio/abilities/witch/heartBeat.wav");
	gameState.audio.healPart = Mix_LoadWAV("audio/abilities/witch/helly.wav");
	gameState.audio.criticalHit = Mix_LoadWAV("audio/effects/criticalHit.wav");
	gameState.audio.skeleMelee = Mix_LoadWAV("audio/abilities/skele/skeleMelee.wav");
	gameState.audio.skeleLunge = Mix_LoadWAV("audio/abilities/skele/skeleLunge.wav");
	gameState.audio.thugStrike = Mix_LoadWAV("audio/abilities/thugs/thug.wav");
	gameState.audio.bigThugStrike = Mix_LoadWAV("audio/abilities/thugs/bigThug.wav");
}

void getFonts()
{
	gameState.fonts.googleFont = TTF_OpenFont("sprites/fonts/text.ttf", 64);
	gameState.fonts.googleFontSmall = TTF_OpenFont("sprites/fonts/text.ttf", 18);
	gameState.fonts.googleBold = TTF_OpenFont("sprites/fonts/textBold.ttf", 64);
	gameState.fonts.fire = TTF_OpenFont("sprites/fonts/fire.ttf", 64);
	gameState.fonts.neue = TTF_OpenFont("sprites/fonts/Neue.ttf", 64);
}

void getTextures(SDL_Renderer *rend)
{
	t_TextAndSur use;
	use = get_texture_and_surface(rend, "sprites/characters/thief/newThief.png");
	gameState.textures.thiefIdle1 = use.text;
	gameState.surfaces.thiefIdle1 = use.sur;
	use = get_texture_and_surface(rend, "sprites/characters/thief/newThief2.png");
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
	gameState.textures.thiefDaggerThrow = get_texture(rend, "sprites/characters/thief/newThiefDaggerThrow.png");
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
	gameState.textures.thiefSmokeThrow[0] = get_texture(rend, "sprites/characters/thief/newThiefSmoke.png");
	gameState.textures.thiefSmokeThrow[1] = get_texture(rend, "sprites/characters/thief/newThiefSmokeTrail.png");
	gameState.textures.smokes[0] = get_texture(rend, "sprites/env/smoke1-1.png");
	gameState.textures.smokes[1] = get_texture(rend, "sprites/env/smoke1-2.png");
	gameState.textures.smokes[2] = get_texture(rend, "sprites/env/smoke2-1.png");
	gameState.textures.smokes[3] = get_texture(rend, "sprites/env/smoke2-2.png");
	gameState.textures.stands.thiefIdle1Stand = get_texture(rend, "sprites/characters/thief/newThiefStand.png");
	gameState.textures.stands.thiefIdle2Stand = gameState.textures.stands.thiefIdle1Stand;
	gameState.textures.stands.skeleIdle1Stand = get_texture(rend, "sprites/characters/skele_stand.png");
	gameState.textures.stands.skeleIdle2Stand = get_texture(rend, "sprites/characters/skele2_stand.png");
	gameState.textures.smokeBomb = get_texture(rend, "sprites/weapon/smokeBomb.png");
	gameState.textures.thiefSlash[0] = get_texture(rend, "sprites/characters/thief/newThiefDaggerSlash.png");
	use = get_texture_and_surface(rend, "sprites/characters/thief/newThiefDaggerSlashTrail.png");
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
	use = get_texture_and_surface(rend, "sprites/env/control.png");
	gameState.textures.control = use.text;
	gameState.surfaces.control = use.sur;
	use = get_texture_and_surface(rend, "sprites/env/controlSmall.png");
	gameState.textures.controlSmall = use.text;
	gameState.surfaces.controlSmall = use.sur;
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
	use = get_texture_and_surface(rend, "sprites/characters/blacksmith/toolBox.png");
	gameState.textures.chars.toolBox = use.text;
	gameState.surfaces.toolBox = use.sur;
	gameState.textures.attacks.toolThrow[0] = get_texture(rend, "sprites/characters/blacksmith/blackSmithToolThrow.png");
	gameState.textures.attacks.toolThrow[1] = get_texture(rend, "sprites/characters/blacksmith/blackSmithToolTrail.png");
	gameState.textures.throwObj = get_texture(rend, "sprites/UI/abilities/throwObject.png");
	gameState.textures.reSupply = get_texture(rend, "sprites/UI/abilities/resuply.png");
	gameState.textures.supplyToolSymbol = get_texture(rend, "sprites/effects/suplyHoverSymbol.png");
	gameState.textures.smithAbilities[4] = get_texture(rend, "sprites/UI/abilities/smithBuff.png");
	gameState.textures.chars.handTools[3] = get_texture(rend, "sprites/characters/blacksmith/handBox3.png");
	gameState.textures.attacks.smithBuff = get_texture(rend, "sprites/characters/blacksmith/blacksmithbuff.png");
	gameState.textures.attacks.buffLight[0] = get_texture(rend, "sprites/attacks/LightEffect1.png");
	gameState.textures.attacks.buffLight[1] = get_texture(rend, "sprites/attacks/LightEffect2.png");
	use = get_texture_and_surface(rend, "sprites/UI/buffSymbol.png");
	gameState.textures.buffSymbol = use.text;
	gameState.surfaces.statuses.buff = use.sur;
	use = get_texture_and_surface(rend, "sprites/characters/mage/mage.png");
	gameState.textures.chars.mageIdle[0] = use.text;
	gameState.surfaces.mageIdle1 = use.sur;
	use = get_texture_and_surface(rend, "sprites/characters/mage/mage2.png");
	gameState.textures.chars.mageIdle[1] = use.text;
	gameState.surfaces.mageIdle2 = use.sur;
	gameState.textures.stands.mageStand = get_texture(rend, "sprites/characters/mage/mageStand.png");
	gameState.textures.chars.mageIndicator = get_texture(rend, "sprites/characters/mage/mageIndicator.png");
	gameState.textures.mageAbilities[0] = get_texture(rend, "sprites/UI/abilities/lightningBolt.png");
	gameState.textures.mageAbilities[1] = get_texture(rend, "sprites/UI/abilities/rockFall.png");
	gameState.textures.mageAbilities[2] = get_texture(rend, "sprites/UI/abilities/mindControl.png");
	gameState.textures.attacks.mageAttack = get_texture(rend, "sprites/characters/mage/mageAttack.png");
	gameState.textures.attacks.lightning = get_texture(rend, "sprites/attacks/bolt.png");
	gameState.textures.attacks.rockFall = get_texture(rend, "sprites/attacks/rock.png");
	gameState.textures.attacks.hostEyes = get_texture(rend, "sprites/characters/mage/mageAttackMind.png");
	use = get_texture_and_surface(rend, "sprites/attacks/hostEyesStatus.png");
	gameState.textures.hostSymbol = use.text;
	gameState.surfaces.hostSymbol = use.sur;
	use = get_texture_and_surface(rend, "sprites/attacks/mageHostEyesStatus.png");
	gameState.textures.hostingSymbol = use.text;
	gameState.surfaces.hostingSymbol = use.sur;
	gameState.textures.attacks.newExps[0] = get_texture(rend, "sprites/attacks/newExp1.png");
	gameState.textures.attacks.newExps[1] = get_texture(rend, "sprites/attacks/newExp2.png");
	gameState.textures.attacks.newExps[2] = get_texture(rend, "sprites/attacks/newExp3.png");
	use = get_texture_and_surface(rend, "sprites/characters/raider/raider1.png");
	gameState.textures.chars.raiderIdle[0] = use.text;
	gameState.surfaces.raiderIdle1 = use.sur;
	use = get_texture_and_surface(rend, "sprites/characters/raider/raider2.png");
	gameState.textures.chars.raiderIdle[1] = use.text;
	gameState.surfaces.raiderIdle2 = use.sur;
	gameState.textures.stands.raiderStand = get_texture(rend, "sprites/characters/raider/raiderStand.png");
	gameState.textures.raiderAbilities[0] = get_texture(rend, "sprites/UI/abilities/axeSlash.png");
	gameState.textures.raiderAbilities[1] = get_texture(rend, "sprites/UI/abilities/axeJump.png");
	gameState.textures.raiderAbilities[2] = get_texture(rend, "sprites/UI/abilities/toxinAxe.png");
	gameState.textures.raiderAbilities[3] = get_texture(rend, "sprites/UI/abilities/block.png");
	gameState.textures.attacks.axeSlash[0] = get_texture(rend, "sprites/characters/raider/raiderAttack.png");
	gameState.textures.attacks.axeSlash[1] = get_texture(rend, "sprites/characters/raider/raiderAttackTrail.png");
	gameState.textures.attacks.axeJump = get_texture(rend, "sprites/characters/raider/raiderJump.png");
	gameState.textures.attacks.jumpSlash[0] = get_texture(rend, "sprites/characters/raider/raiderAttack2.png");
	gameState.textures.attacks.jumpSlash[1] = get_texture(rend, "sprites/characters/raider/raiderAttack2Trail.png");
	use = get_texture_and_surface(rend, "sprites/effects/toxinsym2.png");
	gameState.surfaces.toxinSym = use.sur;
	gameState.textures.toxinSymbol = use.text;
	use = get_texture_and_surface(rend, "sprites/effects/poisonSym.png");
	gameState.surfaces.poisonSym = use.sur;
	gameState.textures.poisonSymbol = use.text;
	gameState.textures.attacks.raiderBlock = get_texture(rend, "sprites/characters/raider/raiderBlock.png");
	use = get_texture_and_surface(rend, "sprites/characters/alchemist/alchemist.png");
	gameState.textures.chars.AlchemistIdle[0] = use.text;
	gameState.surfaces.alchemistIdle1 = use.sur;
	use = get_texture_and_surface(rend, "sprites/characters/alchemist/alchemist2.png");
	gameState.textures.chars.AlchemistIdle[1] = use.text;
	gameState.surfaces.alchemistIdle2 = use.sur;
	gameState.textures.alchemistAbilities[0] = get_texture(rend, "sprites/UI/abilities/nailBomb.png");
	gameState.textures.alchemistAbilities[1] = get_texture(rend, "sprites/UI/abilities/acidExplosion.png");
	gameState.textures.alchemistAbilities[2] = get_texture(rend, "sprites/UI/abilities/slowDown.png");
	gameState.textures.attacks.alchemistThrow[0] = get_texture(rend, "sprites/characters/alchemist/alchemistThrow.png");
	gameState.textures.attacks.alchemistThrow[1] = get_texture(rend, "sprites/characters/alchemist/alchemistThrowTrail.png");
	gameState.textures.attacks.bombs[0] = get_texture(rend, "sprites/attacks/nailBomb.png");
	gameState.textures.attacks.bombs[1] = get_texture(rend, "sprites/attacks/acidBomb.png");
	gameState.textures.attacks.bombs[2] = get_texture(rend, "sprites/attacks/slowDownBomb.png");
	gameState.textures.attacks.nail = get_texture(rend, "sprites/attacks/nail.png");
	use = get_texture_and_surface(rend, "sprites/effects/bleedSym.png");
	gameState.textures.bleedSymbol = use.text;
	gameState.surfaces.bleedSymbol = use.sur;
	use = get_texture_and_surface(rend, "sprites/effects/slowSymbol.png");
	gameState.textures.slowSymbol = use.text;
	gameState.surfaces.slowSymbol = use.sur;
	gameState.textures.attacks.smithHeadSmack[0] = get_texture(rend, "sprites/characters/blacksmith/blacksmithHeadSmack.png");
	gameState.textures.attacks.smithHeadSmack[1] = get_texture(rend, "sprites/characters/blacksmith/blacksmithHeadSmackTrail.png");
	gameState.textures.smithAbilities[5] = get_texture(rend, "sprites/UI/abilities/goForTheHead.png");
	use = get_texture_and_surface(rend, "sprites/characters/knight/flail.png");
	gameState.textures.chars.knightIdle[0] = use.text;
	gameState.surfaces.knightIdle1 = use.sur;
	use = get_texture_and_surface(rend, "sprites/characters/knight/flail2.png");
	gameState.textures.chars.knightIdle[1] = use.text;
	gameState.surfaces.knightIdle2 = use.sur;
	gameState.textures.stands.knightStand = get_texture(rend, "sprites/characters/knight/flailStand.png");
	gameState.textures.knightAbilities[0] = get_texture(rend, "sprites/UI/abilities/flailStrike.png");
	gameState.textures.knightAbilities[1] = get_texture(rend, "sprites/UI/abilities/shieldStrike.png");
	gameState.textures.knightAbilities[2] = get_texture(rend, "sprites/UI/abilities/controlZone.png");
	gameState.textures.attacks.knightAttack[0] = get_texture(rend, "sprites/characters/knight/flailAttack.png");
	gameState.textures.attacks.knightAttack[1] = get_texture(rend, "sprites/characters/knight/flailAttackTrail.png");
	gameState.textures.attacks.shieldBash[0] = get_texture(rend, "sprites/characters/knight/flailShieldStrike.png");
	gameState.textures.attacks.shieldBash[1] = get_texture(rend, "sprites/characters/knight/flailShieldStrikeTrail.png");
	gameState.textures.filter = get_texture(rend, "sprites/env/filter.png");
	gameState.textures.backGround = get_texture(rend, "sprites/env/backGroundGround.png");
	use = get_texture_and_surface(rend, "sprites/characters/witch/witch.png");
	gameState.surfaces.witchIdle1 = use.sur;
	gameState.textures.chars.witchIdle[0] = use.text;
	use = get_texture_and_surface(rend, "sprites/characters/witch/witch2.png");
	gameState.surfaces.witchIdle2 = use.sur;
	gameState.textures.chars.witchIdle[1] = use.text;
	gameState.textures.stands.witchStand = get_texture(rend, "sprites/characters/witch/witchStand.png");
	gameState.textures.chars.witchSource = get_texture(rend, "sprites/characters/witch/witchTurnSprite.png");
	gameState.textures.witchAbilities[0] = get_texture(rend, "sprites/UI/abilities/acidRain.png");
	gameState.textures.witchAbilities[1] = get_texture(rend, "sprites/UI/abilities/teleport.png");
	gameState.textures.witchAbilities[2] = get_texture(rend, "sprites/UI/abilities/healthTransfer.png");
	gameState.textures.attacks.witchAttack = get_texture(rend, "sprites/characters/witch/witchAttack.png");
	gameState.textures.attacks.glows[0] = get_texture(rend, "sprites/characters/witch/witchAttackHand1.png");
	gameState.textures.attacks.glows[1] = get_texture(rend, "sprites/characters/witch/witchAttackHand2.png");
	gameState.textures.attacks.glows[2] = get_texture(rend, "sprites/characters/witch/witchAttackHand3.png");
	gameState.textures.attacks.rainDrop = get_texture(rend, "sprites/env/raindDrop.png");
	gameState.textures.attacks.heartBeat[0] = get_texture(rend, "sprites/env/heartBeat.png");
	gameState.textures.attacks.heartBeat[1] = get_texture(rend, "sprites/env/heartBeatOutline.png");
	gameState.textures.critFilter = get_texture(rend, "sprites/env/CritHit.png");
	gameState.textures.chars.phantLions[0] = get_texture(rend, "sprites/characters/lion/p1.png");
	gameState.textures.chars.phantLions[1] = get_texture(rend, "sprites/characters/lion/p2.png");
	gameState.textures.chars.phantLions[2] = get_texture(rend, "sprites/characters/lion/p3.png");
	gameState.textures.stands.toolsStand = get_texture(rend, "sprites/characters/blacksmith/toolBoxStand.png");
	gameState.textures.attacks.sekeleMelee = get_texture(rend, "sprites/characters/skelegrab.png");
	use = get_texture_and_surface(rend, "sprites/characters/skeleLunge.png");
	gameState.textures.attacks.skeleLunge = use.text;
	gameState.surfaces.skeleLunge = use.sur;
	gameState.textures.iconTexts.iconX = get_texture(rend, "sprites/UI/icons/DeadX.png");
	gameState.textures.iconTexts.iconBars[0] = get_texture(rend, "sprites/UI/icons/IconBar.png");
	gameState.textures.iconTexts.iconBars[1] = get_texture(rend, "sprites/UI/icons/IconFiller.png");
	gameState.textures.iconTexts.iconBars[2] = get_texture(rend, "sprites/UI/icons/IconBarBackGround.png");
	gameState.textures.iconTexts.icons[ALCHEMIST] = get_texture(rend, "sprites/UI/icons/AlchemistIcon.png");
	gameState.textures.iconTexts.icons[KNIGHT] = get_texture(rend, "sprites/UI/icons/KnightIcon.png");
	gameState.textures.iconTexts.icons[LION] = get_texture(rend, "sprites/UI/icons/LionIcon.png");
	gameState.textures.iconTexts.icons[MAGE] = get_texture(rend, "sprites/UI/icons/MageIcon.png");
	gameState.textures.iconTexts.icons[PHANTOM_LION] = get_texture(rend, "sprites/UI/icons/PhantomLionIcon.png");
	gameState.textures.iconTexts.icons[PYRO] = get_texture(rend, "sprites/UI/icons/PyroIcon.png");
	gameState.textures.iconTexts.icons[RAIDER] = get_texture(rend, "sprites/UI/icons/RaiderIcon.png");
	gameState.textures.iconTexts.icons[SKELE] = get_texture(rend, "sprites/UI/icons/SkeleIcon.png");
	gameState.textures.iconTexts.icons[SMITH] = get_texture(rend, "sprites/UI/icons/SmithIcon.png");
	gameState.textures.iconTexts.icons[THIEF] = get_texture(rend, "sprites/UI/icons/ThiefIcon.png");
	gameState.textures.iconTexts.icons[TOOLS] = get_texture(rend, "sprites/UI/icons/toolIcon.png");
	gameState.textures.iconTexts.icons[WITCH] = get_texture(rend, "sprites/UI/icons/WitchIcon.png");
	gameState.textures.iconTexts.icons[BIG_THUG] = get_texture(rend, "sprites/UI/icons/bigThugIcon.png");
	gameState.textures.iconTexts.icons[THUG] = get_texture(rend, "sprites/UI/icons/thugIcon.png");
	gameState.textures.rangedSymbol = get_texture(rend, "sprites/UI/RangedSymbol.png");
	gameState.textures.smallEnergy = get_texture(rend, "sprites/UI/smallEnergy.png");
	gameState.textures.hitSymbol = get_texture(rend, "sprites/UI/HitSymbol.png");
	gameState.textures.turnIndicator = get_texture(rend, "sprites/env/TurnIndicator.png");
	use = get_texture_and_surface(rend, "sprites/characters/bigThug/bigthugFlip.png");
	gameState.textures.chars.bigThugIdle[0] = use.text;
	gameState.surfaces.bigThugIdle1 = use.sur;
	use = get_texture_and_surface(rend, "sprites/characters/bigThug/bigthug2Flip.png");
	gameState.textures.chars.bigThugIdle[1] = use.text;
	gameState.surfaces.bigThugIdle2 = use.sur;
	gameState.textures.stands.bigThugStand = get_texture(rend, "sprites/characters/bigThug/bigthugStandFlip.png");
	gameState.textures.chars.bigThugIndicator = get_texture(rend, "sprites/characters/bigThug/bigThugIndicator.png");
	gameState.textures.attacks.bigThugAttack[0] = get_texture(rend, "sprites/characters/bigThug/btaFlip.png");
	gameState.textures.attacks.bigThugAttack[1] = get_texture(rend, "sprites/characters/bigThug/btaTrailFlip.png");
	use = get_texture_and_surface(rend, "sprites/characters/thug/thugStart.png");
	gameState.textures.chars.thugIdle[0] = use.text;
	gameState.surfaces.thugIdle1 = use.sur;
	use = get_texture_and_surface(rend, "sprites/characters/thug/thugStart2.png");
	gameState.textures.chars.thugIdle[1] = use.text;
	gameState.surfaces.thugIdle2 = use.sur;
	gameState.textures.stands.thugStand = get_texture(rend, "sprites/characters/thug/thugStartStand.png");
	gameState.textures.attacks.bigThugBuff = get_texture(rend, "sprites/characters/bigThug/bigthugInspireFlip.png");
	gameState.surfaces.thugSource = IMG_Load("sprites/characters/thug/thugSourceEffect.png");
	gameState.surfaces.thugSource2 = IMG_Load("sprites/characters/thug/thugSourceEffect2.png");
	use = get_texture_and_surface(rend, "sprites/effects/frenzySymbol.png");
	gameState.textures.frenzySymbol = use.text;
	gameState.surfaces.frenzySymbol = use.sur;
	use = get_texture_and_surface(rend, "sprites/effects/bigChar.png");
	gameState.surfaces.bigCharacterSymbol = use.sur;
	gameState.textures.bigCharacterSymbol = use.text;
	owState.textures.tileTexts.tileOutline = get_texture(rend, "sprites/ow/ground/tileOutline.png");
	owState.textures.tileTexts.grassTile = get_texture(rend, "sprites/ow/ground/grassTile.png");
	owState.textures.mule = get_texture(rend, "sprites/ow/chars/mule64.png");
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

void AiThread()
{
	static std::thread aiThread([]()
	{
		while (true)
		{
			AiManagerUpdate();
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
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
	SDL_GetWindowSize(wr->win, &gameCamera.screen.width, &gameCamera.screen.height);
	initScreen(gameCamera.screen.width, gameCamera.screen.height);
	initKeys(gameState.keys);
	initKeys(owKeys);
	getTextures(wr->rend);
	getFonts();
	getAudio();
	//SDL_SetWindowFullscreen(wr->win, 1);
	//SDL_ShowCursor(SDL_DISABLE);
	CraeteAudioThread();
	InitThugParts();
	static Renderer render(wr->rend);
	gameState.render = &render;
	owState.renderer = &render;
}

void InitBattle()
{
	InitHovers();
	gameState.render->CreateLayer(LAYER_NO_SORT); //backGround layer
	gameState.render->CreateLayer(LAYER_DEPTH_SORT); //battleground layer
	gameState.render->CreateLayer(LAYER_ORDER_SORT); //line layer
	gameState.render->CreateLayer(LAYER_NO_SORT); //dust layer
	gameState.render->CreateLayer(LAYER_NO_SORT); //tele layer
	gameState.render->CreateLayer(LAYER_NO_SORT); //flame port layer
	gameState.render->CreateLayer(LAYER_NO_SORT); //particle layer
	gameState.render->CreateLayer(LAYER_NO_SORT); //object layer
	gameState.render->CreateLayer(LAYER_ORDER_SORT); //filter layer
	gameState.render->CreateLayer(LAYER_DEPTH_SORT); //info layer
	gameState.render->CreateLayer(LAYER_ORDER_SORT); //turn order layer
	gameState.render->CreateLayer(LAYER_ORDER_SORT); //flying texts;
	gameState.render->CreateLayer(LAYER_ORDER_SORT); //counter layer
	gameState.render->CreateLayer(LAYER_ORDER_SORT); //text bubble layer
	gameState.render->CreateLayer(LAYER_ORDER_SORT); //menu layer
	static BattleGround battle(BATTLEGROUND_LAYER, gameState.wr.rend);
	gameState.battle.ground = &battle;
	gameState.battle.xDist = 6000;
	gameState.battle.yDist = 6000;
	gameState.battle.defaultYAdd = 1850;
	gameState.battle.yHeightAdd = 2300;
	gameState.updateObjs.turnOrder = NULL;
	gameState.updateObjs.fadeIter = 0.0f;
	gameState.updateObjs.characterAnimIter = 0;
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
	AiThread();
	InitThugParts();
}
