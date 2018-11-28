/*
 * GameState.cpp
 *
 *      Author: scarbors
 */

#include "GameState.h"
#include "Tract.h"

namespace AIProj
{

  GameState::GameState ()
  :  targetDistrictSize_ (0)
  {

  }

  GameState::~GameState ()
  {
	  //Using shared_ptrs so no need to manually delete
  }

  void
  GameState::initializeGameStateFromDB(std::string dbRef)
  {
    //Create Tract Objects
    //TODO

    //Determine total Pop and set targetDistrictSize_
  }

} /* namespace AIProj */
