
#include "../../hdr/global.h"

void ColorEffects::UpdateEffect(t_ColorEffect &unit)
{
	if (unit.time <= 0)
		return ;
	if (unit.delay > 0)
	{
		unit.delay -= 1;
		return ;
	}
	unit.sprite->ColorMod(unit.color.r, unit.color.g, unit.color.b);
	unit.time -= 1;
	if (unit.time <= 0)
		unit.sprite->ClearColorMod();
}

void ColorEffects::AddEffect(Sprite *sprite, int time, Color color, int delay)
{
	effects.push_back({sprite, color, time, delay});
}

void ColorEffects::Update()
{
	for (int i = 0; i < effects.size(); i++)
	{
		UpdateEffect(effects[i]);
		if (effects[i].time <= 0)
		{
			effects.erase(effects.begin() + i);
			i = (effects.size() == 0) ? 0 : i - 1;
		}
	}
}

void ColorEffects::Destroy()
{
	effects.clear();
}
