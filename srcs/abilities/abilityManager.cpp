
#include "../../hdr/global.h"

void AbilityManager::SetAbility(void *ability, int type)
{
	switch (type)
	{
		case DAGGER_THROW:
			daggerThrow = (DaggerThrow*)ability;
			break ;
	}
}

void AbilityManager::Update()
{
	abilityActive = false;
	if (gameState.updateObjs.turnOrder->stuffHappening || gameState.keys.rightClick != 0)
	{
		ClearAbilities();
		return ;
	}
	if (daggerThrow != NULL)
	{
		abilityActive = true;
		daggerThrow->Update();
	}
}

void AbilityManager::ClearAbilities()
{
	if (daggerThrow != NULL)
	{
		daggerThrow->Destroy();
		delete daggerThrow;
		daggerThrow = NULL;
	}
}