/*
 * GameState.h
 *
 *      Author: scarbors
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <iostream>
#include <set>
#include <memory>

#include "District.h"
#include "Tract.h"

namespace AIProj
{

  class GameState
  {
  public:
    GameState ();
    virtual ~GameState ();

    /**
     * @brief retrieves the population record and calculates the target district size
     * @param tractFile
     * @param adjacencyFile
     */
    void initializeGameStateFromFile(std::string tractFile, std::string adjacencyFile, size_t dCount);

    /**
     * @brief Retrieves all unused tracts
     * @return
     */
    const std::shared_ptr< std::set<std::shared_ptr<Tract> > > & getAvailableTracts() const;

    /**
     * @brief Retrieves all tracts adjacent to the given District
     * @param dId [in] The District to get adjacent to
     * @return
     */
    const std::shared_ptr< std::set< std::shared_ptr<Tract> > > getAvailableTracts(const districtId& dId) const;

    /**
     * @brief Retrives all untaken tracts adjacent to the given tract
     * @param dId
     * @return
     */
    const std::shared_ptr< std::set< std::shared_ptr<Tract> > > getAvailableTractsForATract(const tractId& dId,std::set<tractId> &ignoreList) const;

    /**
     * @brief A list of all unused tracts
     * @return
     */
    const std::shared_ptr< std::set< std::shared_ptr<Tract> > > getUnavailableTracts() const;

    /**
     * @brief Designate a tract as being used by a district
     * @param trId [in] Tract to be used
     * @param dId [in] District using the tract
     * @return  true if the set was successful
     */
    void setUsedTract(const tractId& trId, const districtId& dId );

    /**
     * @brief Adds a district to the control of this GameState object
     * @param dst
     */
    void addDistrict(std::shared_ptr<District> dst) { districtMap_[dst->getId()] = dst; };

    size_t getTargetDistrictSize( void ) const { return targetDistrictSize_; };

    std::shared_ptr<Tract> getTract(tractId tId) { return tractMap_[tId]; };

  private:

    /**
     * @brief Turns the set of tractIds into a set of Tract pointers
     * @param tractVec
     * @return
     */
    const std::shared_ptr< std::set< std::shared_ptr<Tract> > > getTractsFromSet(const std::set<tractId> &tractVec) const;

    /**
     * @brief Creates a list of available Tracts from the list of adjacent tracts
     * @param adjacencySet
     * @return
     */
    inline void trimAdjacencySet( std::shared_ptr< std::set<std::shared_ptr<Tract> > > &adjacencySet, std::set<tractId> &sharedList) const;

    size_t targetDistrictSize_;

    std::map<districtId, std::shared_ptr<District> > districtMap_;
    //std::map<districtId, std::set<tractId> > usedTractMap_;
    std::map<tractId, std::shared_ptr<Tract> > tractMap_;
    std::shared_ptr< std::set<std::shared_ptr<AIProj::Tract> > > unusedTractList_;
    std::shared_ptr< std::set<std::shared_ptr<AIProj::Tract> > > usedTractList_;

  };

} /* namespace AIProj */


inline const std::shared_ptr< std::set< std::shared_ptr<AIProj::Tract> > > & AIProj::GameState::getAvailableTracts() const
{
	return unusedTractList_;
}

inline const std::shared_ptr< std::set< std::shared_ptr<AIProj::Tract> > >  AIProj::GameState::getUnavailableTracts() const
{
	return usedTractList_;
}

inline const std::shared_ptr< std::set< std::shared_ptr<AIProj::Tract> > > AIProj::GameState::getTractsFromSet(const std::set<tractId> &tractVec) const
{
	auto rValue = std::make_shared< std::set< std::shared_ptr<Tract> > >();

	//Retrieve the actual tracts off of the tract map and add them to the vector
	for( auto trct : tractVec )
	{
		rValue->insert(tractMap_.at(trct));
	}

	return rValue;
}

inline const std::shared_ptr< std::set< std::shared_ptr<AIProj::Tract> > > AIProj::GameState::getAvailableTracts(
		const districtId& dId) const
{
  //----------------------------------------
  //Remove the non-adjacent Tracts
  //----------------------------------------
  //Build tractId adjacency set
  std::shared_ptr< std::set<std::shared_ptr<Tract> > > adjacencySet(new std::set<std::shared_ptr<Tract> > () );
  std::shared_ptr<District> district = districtMap_.at(dId);

  for(auto trctSetItr : district->getTracts())
    {
      //const std::set<tractId> &neighbors = trctSetItr->getNeighbors();

      const std::set<std::shared_ptr<Tract> > & neighbors
               = trctSetItr->getNeighborsByRef();

      for( auto nItr : neighbors)
	{
	  adjacencySet->insert(nItr);
	}
    }

  std::set<tractId> ignoreList;
  trimAdjacencySet(adjacencySet,ignoreList);
  return adjacencySet;
}

inline const std::shared_ptr< std::set< std::shared_ptr<AIProj::Tract> > >
AIProj::GameState::getAvailableTractsForATract(const tractId& tctId, std::set<tractId> &ignoreList) const
{
  //----------------------------------------
  //Remove the non-adjacent Tracts
  //----------------------------------------
  //Build tractId adjacency set
  std::shared_ptr< std::set<std::shared_ptr<Tract> > > adjacencySet(new std::set<std::shared_ptr<Tract> >(tractMap_.at(tctId)->getNeighbors()));

//  if(tractMap_.find(tctId) == tractMap_.end())
//    {
//      std::cout << "Failed to find!!\n" << std::flush;
//	exit(EXIT_FAILURE);
//    }

  //const std::set<tractId> &neighbors = tractMap_.at(tctId)->getNeighbors();

//  for( auto nItr : neighbors)
//    {
//      adjacencySet->insert(tractMap_.at(nItr));
//    }

  trimAdjacencySet(adjacencySet, ignoreList);
  return adjacencySet;
}

inline void
AIProj::GameState::trimAdjacencySet( std::shared_ptr< std::set<std::shared_ptr<Tract> > > &adjacencySet, std::set<tractId> &ignoreList) const
{
  //Remove from the adjacency set anything that isn't available
  for(auto trctItr = adjacencySet->begin(); trctItr != adjacencySet->end(); )
    {
      if( (unusedTractList_->find(*trctItr) != unusedTractList_->end() )
	  && ignoreList.find((*trctItr)->getId()) == ignoreList.end() )
	{
	  trctItr++;
	}
      else
	{
	  trctItr = adjacencySet->erase(trctItr);
	}
    }

}

inline void AIProj::GameState::setUsedTract(const tractId& trId,
		const districtId& dId)
{
	//Add the tract to the used lists
	//usedTractMap_[dId].insert(trId);
	usedTractList_->insert(tractMap_.at(trId));

	//Remove it from the unused list
	unusedTractList_->erase(tractMap_.at(trId));
}


#endif /* GAMESTATE_H_ */
