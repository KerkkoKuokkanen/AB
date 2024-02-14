
#include "../../../hdr/global.h"

bool IconBarHandler::AlreadyInPool(Character *character)
{
	for (int i = 0; i < characters.size(); i++)
	{
		if (characters[i].character == character)
			return (true);
	}
	return (false);
}

void IconBarHandler::CreateNewBar(Character *character, int aStart, int a, int hStart, int h)
{
	int size = iconBars.size();
	for (int i = 0; i < iconBars.size(); i++)
	{
		Character *check = iconBars[i]->CheckCharacter();
		if (check == character)
		{
			size = iconBars[i]->GetSlot();
			delete iconBars[i];
			iconBars.erase(iconBars.begin() + i);
			break ;
		}
	}
	iconBars.push_back(new IconBar(character, size, aStart, a, hStart, h));
}

void IconBarHandler::CheckCharacterInPool(Character *character)
{
	for (int i = 0; i < characters.size(); i++)
	{
		if (characters[i].character == character)
		{
			if (characters[i].currArmor != character->stats.armor ||
				characters[i].currHealth != character->stats.health)
			{
				CreateNewBar(character, characters[i].currArmor, character->stats.armor,
								characters[i].currHealth, character->stats.health);
				characters[i].currArmor = character->stats.armor;
				characters[i].currHealth = character->stats.health;
				if (characters[i].currHealth <= 0)
					characters.erase(characters.begin() + i);
			}
			return ;
		}
	}
}

void IconBarHandler::PollMap()
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			t_GMU *gmu = &gameState.battle.ground->map[i][j];
			if (gmu->character == NULL)
				continue ;
			if (AlreadyInPool(gmu->character))
				CheckCharacterInPool(gmu->character);
			else
				characters.push_back({gmu->character, gmu->character->stats.health, gmu->character->stats.armor});
		}
	}
}

void IconBarHandler::RePositionBars(int removedSlot)
{
	for (int i = 0; i < iconBars.size(); i++)
	{
		int currSlot = iconBars[i]->GetSlot();
		if (currSlot > removedSlot)
			iconBars[i]->RePosition(currSlot - 1);
	}
}

void IconBarHandler::UpdateBars()
{
	for (int i = 0; i < iconBars.size(); i++)
	{
		iconBars[i]->Update();
		if (iconBars[i]->done)
		{
			RePositionBars(iconBars[i]->GetSlot());
			delete iconBars[i];
			iconBars.erase(iconBars.begin() + i);
			i = (iconBars.size() == 0) ? 0 : i - 1;
		}
	}
}

void IconBarHandler::Update()
{
	UpdateBars();
	PollMap();
}

void IconBarHandler::Destroy()
{
	for (int i = 0; i < iconBars.size(); i++)
	{
		delete iconBars[i];
	}
}
