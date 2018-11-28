/*
 * mainGm.cpp
 *
 *  Created on: Nov 28, 2018
 *      Author: ShadRS
 */

#include "District.h"
#include "GameState.h"

int main(int argc, char *argv[])
{
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
	  //Get Available Tracts
	  const std::shared_ptr< std::set< std::shared_ptr<AIProj::Tract> > > tracts
	           = gState.getAvailableTracts(dist->getId());

	  //Make Decision
	  AIProj::tractId tctId = dist->makeTractDecision(tracts);

	  //Commit to Tract
	  gState.setUsedTract(tctId,dist->getId());
	}
    }




}


