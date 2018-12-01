/*
 * Tract.h
 *
 *      Author: scarbors, frnkthtnk100
 */

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#ifndef TRACT_H_
#define TRACT_H_
using namespace std;

namespace AIProj
{
  typedef size_t tractId; //fid
  typedef std::string tractMetric;


  class Tract
  {
  public:

    Tract (tractId, size_t,size_t, int, std::map<tractMetric,size_t>);
    virtual ~Tract ();

    const tractId& getId() const { return tractId_; } ;

    int getPopulation(void) const { return population_; };

    //void addNeighbors(const std::set<tractId> &nghbor) { neighboringTracts_ = nghbor; } ;
    void addNeighbor(std::shared_ptr<Tract> nghbor) { if(nghbor->getId() != tractId_ ) neighboringTracts_.insert(nghbor); } ;
    std::set<std::shared_ptr<Tract> > getNeighbors(void) const { return neighboringTracts_; }; //Return by copy
    const std::set<std::shared_ptr<Tract> > & getNeighborsByRef(void) const { return neighboringTracts_; }; //Return by copy

    //void addAttributes(std::vector<std::pair<tractMetric,size_t> >);
    //void addAttribute( const tractMetric&,size_t);
    bool hasAttribute(const tractMetric&) const;
    size_t getAttributeValue(const tractMetric&) const;
    double getAttributeFraction(const tractMetric&) const;

    const std::map<tractMetric,size_t>& getAttributeMap(void) const { return attributeMap_; };
    const std::map<tractMetric,double>& getAttributeFractionMap(void) const { return attributeFraction_; };

    void setDistrictId(const size_t &did) { districtId_ = did; };
    size_t getDistrictId( void ) const { return districtId_; };

    double getCohesionValue( const size_t &did) const;

    size_t getCountyId(void) const { return countyId_; };

    size_t getFullTract(void) const { return fullTract_; };

  private:

    tractId tractId_;
    size_t districtId_;
    size_t countyId_;
    size_t fullTract_;
    int population_;
    std::map<tractMetric,size_t> attributeMap_;
    std::map<tractMetric,double> attributeFraction_;
    std::set<std::shared_ptr<Tract> > neighboringTracts_;
  };

} /* namespace AIProj */

#endif /* TRACT_H_ */
