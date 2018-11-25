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
    const std::vector<const Tract*>* getAvailableTracts() const;

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
    const std::vector<const Tract*>* getUnavailableTracts() const;

    /**
     * @brief Designate a tract as being used by a district
     * @param trId [in] Tract to be used
     * @param dId [in] District using the tract
     * @return  true if the set was successful
     */
    bool setUsedTract(const tractId& trId, const districtId& dId );


  private:
    size_t targetDistrictSize_;

    std::map<districtId, std::vector<tractId> > usedTractMap_;
    std::vector<tractId> usedTractList_;

  };

} /* namespace AIProj */

#endif /* GAMESTATE_H_ */
