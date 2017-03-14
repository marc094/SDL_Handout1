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
	
	~Application() {
		delete modules[0];
		delete modules[1];
	}

	// INIT all modules
	bool Init() 
	{
		bool ret_value = true;
		for (int i = 0; i < NUM_MODULES && ret_value; ++i)
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

		update_status status = update_status::UPDATE_CONTINUE;

		for (int i = 0; i < NUM_MODULES && status == update_status::UPDATE_CONTINUE; ++i) {
			status = modules[i]->PreUpdate();
		}

		for (int i = 0; i < NUM_MODULES && status == update_status::UPDATE_CONTINUE; ++i) {
			status = modules[i]->Update();
		}

		for (int i = 0; i < NUM_MODULES && status == update_status::UPDATE_CONTINUE; ++i) {
			status = modules[i]->PostUpdate();
		}

		return status;
	}

	// EXIT Update 
	// TODO 3: Make sure all modules have a chance to cleanup
	bool CleanUp()
	{
		bool ret_value = true;
		for (int i = NUM_MODULES - 1; i >= 0; --i)
			if (modules[i]->CleanUp() == false)
				ret_value = false;

		return ret_value;
	}

};

#endif // __APPLICATION_H__