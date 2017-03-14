#ifndef __DUMMYESC_H__
#define __DUMMYESC_H__

#include "Module.h"
#include "Globals.h"
#include <conio.h>

class ModuleDummyESC : public Module
{
	bool Init()
	{
		LOG("\nDummyESC Init!");
		return true;
	}

	update_status PreUpdate()
	{
		LOG("\nDummyESC PreUpdate!");
		if (_kbhit()) {
			LOG("\nKeyboard Pressed!");
			return update_status::UPDATE_STOP;
		}
		return update_status::UPDATE_CONTINUE;
	}

	update_status Update()
	{
		LOG("\nDummyESC Update!");
		return update_status::UPDATE_CONTINUE;
	}

	update_status PostUpdate()
	{
		LOG("\nDummyESC PostUpdate!");
		return update_status::UPDATE_CONTINUE;
	}

	bool CleanUp()
	{
		LOG("\nDummyESC CleanUp!");
		return true;
	}
};

#endif // __DUMMYESC_H__