/*
 * Tract.h
 *
 *      Author: scarbors, frnkthtnk100
 */

#include <map>
#include <set>
#include <string>
#include <vector>

#ifndef TRACT_H_
#define TRACT_H_
using namespace std;

namespace AIProj
{
  typedef std::pair<size_t,size_t> tractId; //County Id, Tract Id
  typedef std::string tractMetric;


  class Tract
  {
  public:

    Tract (tractId, int, std::map<tractMetric,size_t>);
    virtual ~Tract ();

    const tractId& getId() const { return tractId_; } ;

    int getPopulation(void) const { return population_; };

    void addNeighbors(const std::set<tractId> &nghbor) { neighboringTracts_ = nghbor; } ;
    const std::set<tractId>& getNeighbors(void) const { return neighboringTracts_; };

    void addAttributes(std::vector<std::pair<tractMetric,size_t> >);
    void addAttribute( const tractMetric&,size_t);
    bool hasAttribute(const tractMetric&) const;
    size_t getAttributeValue(const tractMetric&) const;

    const std::map<tractMetric,size_t>& getAttributeMap(void) const { return attributeMap_; };

  private:

    tractId tractId_;
    int population_;
    std::map<tractMetric,size_t> attributeMap_;
    std::set<tractId> neighboringTracts_;
  };

} /* namespace AIProj */

#endif /* TRACT_H_ */
