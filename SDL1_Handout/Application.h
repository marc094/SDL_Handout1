#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include "Module.h"
#include "Dummy.h"

#define NUM_MODULES 1

class Application
{
public:

	Module* modules[NUM_MODULES];

public:

	Application()
	{
		modules[0] = new ModuleDummy();
		// TODO 7: Create your new module "DummyESC"
		// it should check if player it ESC key use kbhit()
		// http://www.cprogramming.com/fod/kbhit.html
	}

	// INIT all modules
	bool Init() 
	{
		bool ret_value = false;
		for (int i = 0; i < NUM_MODULES; ++i)
			if (modules[i]->Init())
				ret_value = true;
		
		// TODO 5: Make sure that if Init() / PreUpdate/Update/PostUpdate/CleanUP return
		// an exit code App exits correctly.
		return ret_value;
	}

	// TODO 4: Add PreUpdate and PostUpdate calls

	// UPDATE all modules
	// TODO 2: Make sure all modules receive its update
	update_status Update() {
		update_status ret_value = update_status::UPDATE_CONTINUE;
		bool update_stop = false, update_error = false;

		for (int i = 0; i < NUM_MODULES; ++i) {
			update_status pre_update_status = modules[i]->PreUpdate();
			if (pre_update_status == update_status::UPDATE_ERROR)
				update_error = true;
			else if (pre_update_status == update_status::UPDATE_STOP)
				update_stop = true;
		}

		for (int i = 0; i < NUM_MODULES; ++i) {
			update_status update_stat = modules[i]->Update();
			if (update_stat == update_status::UPDATE_ERROR)
				update_error = true;
			else if (update_stat == update_status::UPDATE_STOP)
				update_stop = true;
		}

		for (int i = 0; i < NUM_MODULES; ++i) {
			update_status post_update_status = modules[i]->PostUpdate();
			if (post_update_status == update_status::UPDATE_ERROR)
				update_error = true;
			else if (post_update_status == update_status::UPDATE_STOP)
				update_stop = true;
		}

		if (update_error)
			ret_value = update_status::UPDATE_ERROR;
		else if (update_stop)
			ret_value = update_status::UPDATE_STOP;
		else
			ret_value = update_status::UPDATE_CONTINUE;

		return ret_value;
	}

	// EXIT Update 
	// TODO 3: Make sure all modules have a chance to cleanup
	bool CleanUp()
	{
		bool ret_value = true;
		for (int i = NUM_MODULES - 1; i >= 0; --i)
			if (!modules[i]->CleanUp())
				ret_value = false;
		return ret_value;
	}

};

#endif // __APPLICATION_H__