/*
 * mainGm.cpp
 *
 *  Created on: Nov 28, 2018
 *      Author: ShadRS
 */

#include <chrono>
#include <iostream>

#include "District.h"
#include "GameState.h"

int main(int argc, char *argv[])
{
  //Create GameState object
  AIProj::GameState gState;

  //Load Data (districts)
  std::cout << "Creating Districts\n" << std::flush;
  std::vector<std::shared_ptr<AIProj::District>> districts;
  std::map<AIProj::districtId, AIProj::tractId> starterTracts
  = AIProj::District::createDistricts("./startingDistricts.csv", districts);

  std::cout << districts.size() << " Districts created\n" << std::flush;

  //Load Data (tracts)
  std::cout << "Creating Tracts\n" << std::flush;
  gState.initializeGameStateFromFile("./tractinfo/tract.txt", "./tractinfo/relationship.txt", districts.size());
  std::cout << gState.getAvailableTracts()->size() << " Tracts created\n" << std::flush;

  AIProj::District::setTargetPopulation(gState.getTargetDistrictSize());

  std::cout << "Pairing Districts with starter tracts\n" << std::flush;

  for(auto dis : districts)
    {
      //Add districts to game state
      AIProj::tractId tId = starterTracts[dis->getId()];
      gState.addDistrict(dis);

      //Pair tracts and Districts
      dis->addTract(gState.getTract(tId));
      gState.setUsedTract(tId,dis->getId());
    }

  std::cout << "Files loaded, preparing to start!\n"
      << gState.getAvailableTracts()->size()
      << " Tracts to be sorted.\n";

  //Play the game
  bool movesMade = true;
  size_t moves = 0;
  while( gState.getAvailableTracts()->size() && movesMade )
    {
      // Get starting timepoint
      auto start = std::chrono::high_resolution_clock::now();
      moves++;
      std::cout << "Playing round " << moves
	  << ", Remaining tracts: " << gState.getAvailableTracts()->size()
	  << std::endl << std::flush;

      //To prevent getting stuck due to size constraints
      movesMade = false;

      //Cycle through the districts
      for(auto dist : districts)
	{
	  std::cout << " District(" << dist->getId() << ") - "
	      << std::flush;

	  //Make Decision
	  AIProj::tractId tctId = dist->makeTractDecision(gState);

	  std::cout << "Tract(" << tctId << ")\n" << std::flush;

	  if(tctId != 0)
	    {
	      //Commit to Tract
	      gState.setUsedTract(tctId,dist->getId());
	      movesMade = true;
	    }
	}

      // Get ending timepoint
      auto stop = std::chrono::high_resolution_clock::now();

      // use duration cast method
      auto duration = std::chrono::duration_cast<std::chrono::minutes>(stop - start);
      std::cout << "Elapsed time: "
	  << duration.count() << std::endl << std::flush;
    }

  if( !movesMade )
    {
      std::cerr << "Stalled on improper moves!\n";
      exit(EXIT_FAILURE);
    }


  exit(EXIT_SUCCESS);
}


