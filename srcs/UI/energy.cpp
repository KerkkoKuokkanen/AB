
#include "../../hdr/global.h"

Energy::Energy()
{
	SDL_Rect dest = {0, 0, 2600, 3900};
	stand = new Sprite(gameState.textures.energy[0], dest, NULL, NULL, 0, FLIP_NONE, true);
	energy = new Sprite(gameState.textures.energy[1], dest, NULL, NULL, 0, FLIP_NONE, true);
	stand->Deactivate();
	energy->Deactivate();
	gameState.render->AddSprite(stand, TURN_ORDER_LAYER);
	gameState.render->AddSprite(energy, TURN_ORDER_LAYER);
}

void Energy::Used()
{
	energy->Deactivate();
}

void Energy::TakeBack()
{
	energy->Activate();
}

void Energy::Position(Vector place)
{
	stand->Position(place);
	energy->Position(place);
}

void Energy::Activate()
{
	stand->Activate();
	energy->Activate();
}

void Energy::Deactivate()
{
	stand->Deactivate();
	energy->Deactivate();
}

void Energy::Destroy()
{
	delete stand;
	delete energy;
}
