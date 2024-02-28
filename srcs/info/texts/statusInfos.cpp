
#include "../../../hdr/global.h"

void StatusInfo::SetUpBubble(int hoverIcon)
{
	if (hoverIcon != hovering)
	{
		hovering = hoverIcon;
		counter = 0;
	}
	else
	{
		if (counter < 30)
			counter++;
	}
	if (counter < 14)
		return ;
	if (bubble != NULL)
		delete bubble;
	bubble = new TextBubble({0, 0});
	bubble->SetMouseFollow({xAdd, yAdd});
	bubble->SetFollowCorner(followCorner);
	bubble->id = hoverIcon;
	CreateBubbles(hoverIcon);
}

void StatusInfo::Update(int hoverIcon)
{
	if (hoverIcon == (-1))
	{
		if (bubble != NULL)
			delete bubble;
		counter = 0;
		hovering = -1;
		bubble = NULL;
		return ;
	}
	if (bubble == NULL || bubble->id != hoverIcon)
		SetUpBubble(hoverIcon);
	if (bubble != NULL)
		bubble->Update();
}

void StatusInfo::Destroy()
{
	if (bubble != NULL)
		delete bubble;
}
