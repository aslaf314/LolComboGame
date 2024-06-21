#include "Resources.h"


Assets* Assets::src = nullptr; 

Assets* Assets::getAssets()
{
	if (src == nullptr)
		src = new Assets();
	return src; 
}
