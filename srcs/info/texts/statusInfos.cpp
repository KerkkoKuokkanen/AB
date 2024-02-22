
#include "../../../hdr/global.h"

void StatusInfo::SetUpBubble(int hoverIcon)
{
	if (bubble != NULL)
		delete bubble;
	bubble = new TextBubble({0, 0});
	bubble->SetMouseFollow({600, 600});
	bubble->id = hoverIcon;
	CreateBubbles(hoverIcon);
}

void StatusInfo::Update(int hoverIcon)
{
	if (hoverIcon == (-1))
	{
		if (bubble != NULL)
			delete bubble;
		bubble = NULL;
		return ;
	}
	if (bubble == NULL || bubble->id != hoverIcon)
		SetUpBubble(hoverIcon);
	bubble->Update();
}

void StatusInfo::Destroy()
{
	if (bubble != NULL)
		delete bubble;
}
