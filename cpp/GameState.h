/*
 * GameState.h
 *
 *      Author: scarbors
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <set>
#include <memory>
#include <vector>

#include "District.h"
#include "Tract.h"

namespace AIProj
{

  class GameState
  {
  public:
    GameState ();
    virtual
    ~GameState ();

    /**
     * @brief retrieves the population record and calculates the target district size
     * @param dbRef
     */
    void initializeGameStateFromDB(std::string dbRef);

    /**
     * @brief Retrieves all unused tracts
     * @return
     */
    std::shared_ptr< std::set<const std::shared_ptr<Tract> > > getAvailableTracts() const;

    /**
     * @brief Retrieves all tracts adjacent to the given District
     * @param dId [in] The District to get adjacent to
     * @return
     */
    std::shared_ptr< std::set<const std::shared_ptr<Tract> > > getAvailableTracts(const districtId& dId) const;


    /**
     * @brief A list of all unused tracts
     * @return
     */
    std::shared_ptr< std::set<const std::shared_ptr<Tract> > > getUnavailableTracts() const;

    /**
     * @brief Designate a tract as being used by a district
     * @param trId [in] Tract to be used
     * @param dId [in] District using the tract
     * @return  true if the set was successful
     */
    bool setUsedTract(const tractId& trId, const districtId& dId );

    void addDistrict(std::shared_ptr<District> dst) { districtMap_[dst->getId()] = dst; };


  private:

    std::shared_ptr< std::vector<const std::shared_ptr<Tract> > > getTractsFromSet(const std::vector<tractId> &tractVec) const;

    size_t targetDistrictSize_;

    std::map<districtId, std::shared_ptr<District> > districtMap_;
    std::map<districtId, std::set<tractId> > usedTractMap_;
    std::map<tractId, std::shared_ptr<Tract> > tractMap_;
    std::set<tractId> unusedTractList_;
    std::set<tractId> usedTractList_;

  };

} /* namespace AIProj */

inline void AIProj::GameState::initializeGameStateFromDB(std::string dbRef)
{
	//Create Tract Objects
}

inline std::shared_ptr< std::set<const std::shared_ptr<Tract> > > AIProj::GameState::getAvailableTracts() const
{
	return getTractsFromSet(unusedTractList_);
}

inline std::shared_ptr< std::set<const std::shared_ptr<Tract> > > AIProj::GameState::getUnavailableTracts() const
{
	return getTractsFromSet(usedTractList_);
}

inline std::shared_ptr< std::set<const std::shared_ptr<Tract> > > AIProj::GameState::getTractsFromSet(const std::vector<tractId> &tractVec) const
{
	auto rValue = std::make_shared< std::set<const std::shared_ptr<Tract> > >();

	//Retrieve the actual tracts off of the tract map and add them to the vector
	for( auto trct : tractVec )
	{
		rValue->insert(tractMap_[trct]);
	}

	return rValue;
}

inline std::shared_ptr< std::set<const std::shared_ptr<Tract> > > AIProj::GameState::getAvailableTracts(
		const districtId& dId) const
{
	//Get all available tracts
	auto rValue = getAvailableTracts();

	//----------------------------------------
	//Remove the non-adjacent Tracts
	//----------------------------------------
	//Build tractId adjacency set
	std::set<const std::shared_ptr<Tract> > adjacencySet;
	for(auto trctSetItr : (districtMap_[dId])->getTracts())
	{
		const std::set<tractId> &neighbors = (tractMap_[*trctSetItr])->getNeighbors();
		adjacencySet.insert(neighbors.begin(), neighbors.end() );
	}

	//Remove from the available list any tract that isn't in the adjacency set
	for( auto trctItr = rValue->begin(); trctItr != rValue->end(); )
	{
		if(adjacencySet.find(*trctItr) )
			trctItr++;
		else
			trctItr = rValue->erase(trctItr);
	}

	return rValue;
}

inline bool AIProj::GameState::setUsedTract(const tractId& trId,
		const districtId& dId)
{
	//Add the tract to the used lists
	usedTractMap_[dId].insert(trId);
	usedTractList_.insert(trId);

	//Remove it from the unused list
	unusedTractList_.erase(std::remove(unusedTractList_.begin(),
			                           unusedTractList_.end(),
									   trId),
			                unusedTractList_.end());
}


#endif /* GAMESTATE_H_ */
