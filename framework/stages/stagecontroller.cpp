
#include "stagecontroller.h"

Stage* StageController::Current()
{
	if( stages.Count() == 0 )
	{
		return nullptr;
	} else {
		return stages.At( stages.Count() - 1 );
	}
}

void StageController::Start(Stage* NextStage)
{
	Stage* s = Current();
	if( s != nullptr )
	{
    s->Pause();
	}
	stages.Add( NextStage );
	NextStage->LoadResources();
	NextStage->Start();
}

Stage* StageController::Finish()
{
	Stage* s = Current();
	if( s != nullptr )
	{
		s->Finish();
		stages.DeleteAt( stages.Count() - 1 );
	}
	Stage* p = Current();
	if( p != nullptr )
	{
		p->Resume();
	}
	return s;
}


Stage* StageController::Previous()
{
	if( stages.Count() <= 1 )
	{
		return nullptr;
	}
	return stages.At( stages.Count() - 2 );
}

Stage* StageController::Previous(Stage* Of)
{
	int i = stages.Find( Of );
	if( i <= 0 )
	{
		return nullptr;
	}
	return stages.At( i - 1 );
}

