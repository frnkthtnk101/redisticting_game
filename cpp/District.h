/*
 * District.h
 *
 *      Author: scarbors
 */

#ifndef DISTRICT_H_
#define DISTRICT_H_

#include <map>
#include <vector>

#include "Tract.h"

namespace AIProj
{
  typedef size_t districtId;

  class District
  {
  public:

    District ();
    virtual
    ~District ();

    /**
     * @brief Retrieves the current district population
     * @return
     */
    size_t getCurrentPopulation() const { return population_; };

    /**
     * @brief Retrieves the Population total of the metric
     * @param
     * @return
     */
    size_t getMetricTotal(const tractMetric& ) const { return metricTotals_[tractMetric]; };

    /**
     * @brief Run the heuristics and see if we want this tract
     * @param
     * @return True if we want the tract
     */
    bool testTractForAdd(const Tract&);

    /**
     * @brief Add the tract to our list & update our totals
     * @param The id of the tract to be added
     * @return if the add was successful
     */
    bool addTract(const Tract* trct) { return ownedTracts_.insert(trct); };

    /**
     * @brief Retrieves the tracts already owned by this district
     */
    const std::set<const Tract*>& getTracts( void ) const { return ownedTracts_; };

    /**
     * @brief Get/Set for the static target population values
     * @return
     */
    static size_t getTargetPopulation() const { return targetPopulation_; };
    static void setTargetPopulation(size_t tgtPop) { targetPopulation_  = tgtPop; };

    size_t getId() const { return districtId_; };

  private:

    static size_t idCounter_;
    size_t districtId_;
    size_t population_;

    static size_t targetPopulation_;

    std::set<const Tract*> ownedTracts_;
    std::map<tractMetric, size_t> metricTotals_;
  };

} /* namespace AIProj */

#endif /* DISTRICT_H_ */
