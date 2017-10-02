
#pragma once

#include "stage.h"
#include "../core/list.h"

class StageController
{

	private:
		List<Stage*> stages;

	public:
		Stage* Current();
		void Start(Stage* NextStage);
		Stage* Finish();

		Stage* Previous();
		Stage* Previous(Stage* Of);

};
