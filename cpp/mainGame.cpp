/*
 * mainGm.cpp
 *
 *  Created on: Nov 28, 2018
 *      Author: ShadRS
 */

#include <Python.h>

#include "District.h"
#include "GameState.h"

int main(int argc, char *argv[])
{
  //----------------------
  //Python Test

  Py_Initialize();
  PyRun_SimpleString("import sys; sys.path.append('.')");
  PyRun_SimpleString("import mytest;");
  PyRun_SimpleString("print mytest.myabs(2.0)");
  Py_Finalize();

  return 0;
  //----------------------

  //Create GameState object
  AIProj::GameState gState;

  //Load Data (tracts)
  gState.initializeGameStateFromDB("DB Info");

  //Create Districts
  //TODO: How do we know how many and where they start?
  size_t tgtPop; //TODO
  AIProj::District::setTargetPopulation(tgtPop);
  std::vector<std::shared_ptr<AIProj::District>> districts;

  //Play the game
  while( gState.getAvailableTracts()->size() )
    {
      //Cycle through the districts
      for(auto dist : districts)
	{
	  //Make Decision
	  AIProj::tractId tctId = dist->makeTractDecision(gState);

	  //Commit to Tract
	  gState.setUsedTract(tctId,dist->getId());
	}
    }




}


