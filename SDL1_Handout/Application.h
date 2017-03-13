#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include "Module.h"
#include "Dummy.h"
#include "DummyESC.h"

#define NUM_MODULES 2

class Application
{
public:

	Module* modules[NUM_MODULES];

public:

	Application()
	{
		modules[0] = new ModuleDummy();
		modules[1] = new ModuleDummyESC();
		// TODO 7: Create your new module "DummyESC"
		// it should check if player hit ESC key use kbhit()
		// http://www.cprogramming.com/fod/kbhit.html
	}

	// INIT all modules
	bool Init() 
	{
		bool ret_value = true;
		for (int i = 0; i < NUM_MODULES; ++i)
			if (modules[i]->Init() == false)
				ret_value = false;
		
		// TODO 5: Make sure that if Init() / PreUpdate/Update/PostUpdate/CleanUP return
		// an exit code App exits correctly.
		return ret_value;
	}

	// TODO 4: Add PreUpdate and PostUpdate calls

	// UPDATE all modules
	// TODO 2: Make sure all modules receive its update
	update_status Update() {
		for (int i = 0; i < NUM_MODULES; ++i) {
			update_status pre_update_status = modules[i]->PreUpdate();
			if (pre_update_status == update_status::UPDATE_ERROR || pre_update_status == update_status::UPDATE_STOP)
				return pre_update_status;
		}

		for (int i = 0; i < NUM_MODULES; ++i) {
			update_status update_stat = modules[i]->Update();
			if (update_stat == update_status::UPDATE_ERROR || update_stat == update_status::UPDATE_STOP)
				return update_stat;
		}

		for (int i = 0; i < NUM_MODULES; ++i) {
			update_status post_update_status = modules[i]->PostUpdate();
			if (post_update_status == update_status::UPDATE_ERROR || post_update_status == update_status::UPDATE_STOP)
				return post_update_status;
		}
		return update_status::UPDATE_CONTINUE;
	}

	// EXIT Update 
	// TODO 3: Make sure all modules have a chance to cleanup
	bool CleanUp()
	{
		bool ret_value = true;
		for (int i = NUM_MODULES - 1; i >= 0; --i)
			if (modules[i]->CleanUp() == false)
				ret_value = false;

		delete modules;
		return ret_value;
	}

};

#endif // __APPLICATION_H__