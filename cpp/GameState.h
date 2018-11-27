/*
 * GameState.h
 *
 *      Author: scarbors
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

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
    std::vector<const Tract*>* getAvailableTracts() const;

    /**
     * @brief Retrieves all tracts adjacent to the given District
     * @param dId [in] The District to get adjacent to
     * @return
     */
    const std::vector<const Tract*>* getAvailableTracts(const districtId& dId);

    /**
     * @brief A list of all unused tracts
     * @return
     */
    std::vector<const Tract*>* getUnavailableTracts() const;

    /**
     * @brief Designate a tract as being used by a district
     * @param trId [in] Tract to be used
     * @param dId [in] District using the tract
     * @return  true if the set was successful
     */
    bool setUsedTract(const tractId& trId, const districtId& dId );


  private:

    std::vector<const Tract*>* getTractsFromVector(const std::vector<tractId> &tractVec) const;

    size_t targetDistrictSize_;

    std::map<districtId, std::vector<tractId> > usedTractMap_;
    std::map<tractId, const Tract*> tractMap_;
    std::vector<tractId> unusedTractList_;
    std::vector<tractId> usedTractList_;

  };

} /* namespace AIProj */

inline void AIProj::GameState::initializeGameStateFromDB(std::string dbRef)
{
	//Create Tract Objects
}

inline std::vector<const Tract*>* AIProj::GameState::getAvailableTracts() const
{
	return getTractsFromVector(unusedTractList_);
}

inline std::vector<const Tract*>* AIProj::GameState::getUnavailableTracts() const
{
	return getTractsFromVector(usedTractList_);
}

inline std::vector<const Tract*>* AIProj::GameState::getTractsFromVector(const std::vector<tractId> &tractVec) const
{
	auto rValue = new std::vector<const Tract*>();

	//Retrieve the actual tracts off of the tract map and add them to the vector
	for( auto trct : tractVec )
	{
		rValue->push_back(tractMap_[trct]);
	}

	return rValue;
}

inline const std::vector<const Tract*>* AIProj::GameState::getAvailableTracts(
		const districtId& dId)
{
	auto rValue = getAvailableTracts();

	//----------------------------------------
	//Remove the non-adjacent Tracts
	//----------------------------------------
	//Build tractId adjacency set
	//TODO

	//Remove from the available list any tract that isn't in the adjacency set
	//TODO

	return rValue;
}

inline bool AIProj::GameState::setUsedTract(const tractId& trId,
		const districtId& dId)
{
	//Add the tract to the used lists
	usedTractMap_[dId].push_back(trId);
	usedTractList_.push_back(trId);

	//Remove it from the unused list
	unusedTractList_.erase(std::remove(unusedTractList_.begin(),
			                           unusedTractList_.end(),
									   trId),
			                unusedTractList_.end());
}


#endif /* GAMESTATE_H_ */
