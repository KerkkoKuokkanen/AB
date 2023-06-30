
#include "../../hdr/global.h"

Vector Damager::GetDirection(Character *character, Character *target)
{
	SDL_Rect cDest = character->sprite->dest;
	SDL_Rect eDest = target->sprite->dest;
	Vector toEnemy(cDest.x - eDest.x, cDest.y - eDest.y);
	float angle = vectorAngle(Vector(0.0f, 1.0f), toEnemy);
	float sign = (cDest.x <= eDest.x) ? 1.0f : -1.0f;
	if (angle < PI / 2)
		return(Vector(0.5 * sign, -0.5f));
	return (Vector(0.5f * sign, 0.5f));
}

void Damager::AddDamage(t_Ability *ability, Character *character, std::vector<SDL_Point> &targets)
{
	for (int i = 0; i < targets.size(); i++)
	{
		t_Sound add2 = {gameState.audio.daggerThrow[0], Channels::DAGGER_THROW0, 0};
		t_Sound add3 = {gameState.audio.daggerThrow[1], Channels::DAGGER_THROW1, 0};
		std::vector<t_Sound> sounds = {add2, add3};
		Character *targ = gameState.battle.ground->map[targets[i].y][targets[i].x].character;
		damageCreator.CreateDamage(targ, Color(255, 0, 0), 5, 5, GetDirection(character, targ), sounds);
	}
}

void Damager::Update()
{
	damageCreator.Update();
}
