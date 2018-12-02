/*
 * District.h
 *
 *      Author: scarbors
 */

#ifndef DISTRICT_H_
#define DISTRICT_H_

#include <map>
#include <memory>
#include <vector>

//#include "GameState.h"
#include "Tract.h"

namespace AIProj
{
  class GameState;

  typedef size_t districtId;

  class District
  {
  public:

    District (districtId dId);
    virtual
    ~District ();

    /**
     * @brief Factory method to create districts from a file.
     * @param starterFile
     * @return
     */
    static std::map<districtId, tractId> createDistricts(std::string starterFile,
							 std::vector<std::shared_ptr<AIProj::District>> &districts);
    /**
     * @brief Retrieves the current district population
     * @return
     */
    int getCurrentPopulation() const { return population_; };

    /**
     * @brief Retrieves the Population total of the metric
     * @param
     * @return
     */
    size_t getMetricTotal(const tractMetric& tM) const { return metricTotals_.at(tM); };

    /**
     * @brief given the tract list decides on one and adds it to its list
     * @param The tract set
     * @return The ID of the added tract
     */
    tractId makeTractDecision(AIProj::GameState &gState);

    /**
     * @brief Run the heuristics and see how much we want this tract
     * @param voice
     * @param tct The tract being examined
     * @param depthToGo How deep to go recursively
     * @return
     */
    void calculateChoice (int &voice,
			  std::shared_ptr<AIProj::Tract> tct,
			  int depthToGo,
			  AIProj::GameState &gState,
			  std::set<tractId> &ignoreList);

    /**
     * @brief Add the tract to our list & update our totals
     * @param The id of the tract to be added
     * @return if the add was successful
     */
    void addTract(std::shared_ptr<AIProj::Tract> trct) ;
    //void addFirstTract(std::shared_ptr<AIProj::Tract> trct) ;

    /**
     * @brief Retrieves the tracts already owned by this district
     */
    const std::set<std::shared_ptr<AIProj::Tract> >& getTracts( void ) const { return ownedTracts_; };

    /**
     * @brief Get/Set for the static target population values
     * @return
     */
    static int getTargetPopulation() { return targetPopulation_; };
    static void setTargetPopulation(size_t tgtPop) { targetPopulation_  = tgtPop; };

    size_t getId() const { return districtId_; };

    void dump(std::ofstream &fout);
    void dumpMetrics(std::ofstream &fout);
    void dumpMetricHeader(std::ofstream &fout);
  private:

    bool similar(std::shared_ptr<AIProj::Tract>  tract);
    bool noRacialBias(std::shared_ptr<AIProj::Tract> tract);

    std::shared_ptr<Tract> decideOnBestTract (std::shared_ptr<Tract> &bestVoiceT,
    			    int &bestVoice,
    			    double &bestCohesion,
    			    double &bestWeight,
    			    std::shared_ptr<Tract> &cBestCohesionT,
    			    int &cBestVoice,
    			    double &cBestCohesion,
    			    //double &cBestWeight,
    			    std::shared_ptr<Tract> &wBestCohesionT,
    			    int &wBestVoice,
    			    double &wBestCohesion,
    			    double &wBestWeight);

    static size_t similarityLimit_;
    static int targetPopulation_;
    static size_t tractChoiceDepth_;
    static int countyFactor_;

    size_t districtId_;
    int population_;
    int lastCounty_;

    std::set<std::shared_ptr<AIProj::Tract>> ownedTracts_;
    std::map<tractMetric, size_t> metricTotals_;
    std::map<tractMetric, double> metricFractions_;
    std::vector<tractMetric> metricNames_;
  };

  /**
   * @brief Add the tract to our list & update our totals
   * @param The id of the tract to be added
   * @return if the add was successful
   */
  inline void District::addTract(std::shared_ptr<AIProj::Tract> trct)
  {
    ownedTracts_.insert(trct);
    auto tctMetrics = trct->getAttributeMap();

    //Set the district id on the tract
    trct->setDistrictId(districtId_);
    lastCounty_ = trct->getCountyId();

    //If this is the first time we're running this we need to initialize the totals
    if(metricTotals_.size() == 0)
      {
	population_ = trct->getPopulation();

	for(auto metric : tctMetrics)
	  {
	    metricTotals_[metric.first] = metric.second;
	    metricNames_.push_back(metric.first);

	    if(population_ == 0)
	      {
		metricFractions_[metric.first] = double(metricTotals_[metric.first]);
	      }
	    else
	      {
		metricFractions_[metric.first] = double(metricTotals_[metric.first]) / double(population_);
	      }
	  }
      }
    else
      {
	population_ += trct->getPopulation();
	for(auto metric : tctMetrics)
	  {
	    metricTotals_[metric.first] += metric.second;
	    metricFractions_[metric.first] = double(metricTotals_[metric.first]) / double(population_);
	  }
      }
  };


} /* namespace AIProj */



#endif /* DISTRICT_H_ */
