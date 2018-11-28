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
    char _STATE;

    int _TRACT,_AREALAND,_POP100,_H001001,_H002001,_H002005,_H003001,_H003002;
    int _H003003,_P001001,_P002001,_P002002,_P002005,_P003001,_P003002,_P003003;
    int _P003004,_P003005,_P003006,_P003007,_P003008,_P003009,_P003010,_P003026;
    int _P003047,_P003063,_P003070,_P004001,_P004002,_P004003,_P012001,_P012002;
    int _P012026,_P012A001,_P012A002,_P012A026,_P012B001,_P012B002,_P012B026;
    int _P012C001,_P012C002,_P012C026,_P012D001,_P012D002,_P012D026,_P012E001;
    int _P012E002,_P012E026,_P012F001,_P012F002,_P012F026,_P012G001,_P012G002;
    int _P012G026,_P012H001,_P012H002,_P012H026,_P012I001,_P012I002,_P012I026;
    int _P013001,_P013A001,_P013B001,_P013C001,_P013D001,_P013E001,_P013F001;
    int _P013G001,_P013H001,_P013I001;

  public:

    Tract (tractId, std::map<tractMetric,size_t>);
    virtual ~Tract ();

    Tract (char C_STATE, int C_TRACT, int C_AREALAND, int C_POP100, int C_H001001, int C_H002001, int C_H002005, 
    int C_H003001, int C_H003002, int C_H003003, int C_P001001, int C_P002001, int C_P002002, int C_P002005, 
    int C_P003001, int C_P003002, int C_P003003, int C_P003004, int C_P003005, int C_P003006, int C_P003007, 
    int C_P003008, int C_P003009, int C_P003010, int C_P003026, int C_P003047, int C_P003063, int C_P003070, 
    int C_P004001, int C_P004002, int C_P004003, int C_P012001, int C_P012002, int C_P012026, int C_P012A001, 
    int C_P012A002, int C_P012A026, int C_P012B001, int C_P012B002, int C_P012B026, int C_P012C001, int C_P012C002, 
    int C_P012C026, int C_P012D001, int C_P012D002, int C_P012D026, int C_P012E001, int C_P012E002, int C_P012E026, 
    int C_P012F001, int C_P012F002, int C_P012F026, int C_P012G001, int C_P012G002, int C_P012G026, int C_P012H001, 
    int C_P012H002, int C_P012H026, int C_P012I001, int C_P012I002, int C_P012I026, int C_P013001, int C_P013A001, 
    int C_P013B001, int C_P013C001, int C_P013D001, int C_P013E001, int C_P013F001, int C_P013G001, int C_P013H001, 
    int C_P013I001);


    char get_STATE();
    int get_TRACT();
    int get_AREALAND();
    int get_POP100();
    int get_H001001();
    int get_H002001();
    int get_H002005();
    int get_H003001();
    int get_H003002();
    int get_H003003();
    int get_P001001();
    int get_P002001();
    int get_P002002();
    int get_P002005();
    int get_P003001();
    int get_P003002();
    int get_P003003();
    int get_P003004();
    int get_P003005();
    int get_P003006();
    int get_P003007();
    int get_P003008();
    int get_P003009();
    int get_P003010();
    int get_P003026();
    int get_P003047();
    int get_P003063();
    int get_P003070();
    int get_P004001();
    int get_P004002();
    int get_P004003();
    int get_P012001();
    int get_P012002();
    int get_P012026();
    int get_P012A001();
    int get_P012A002();
    int get_P012A026();
    int get_P012B001();
    int get_P012B002();
    int get_P012B026();
    int get_P012C001();
    int get_P012C002();
    int get_P012C026();
    int get_P012D001();
    int get_P012D002();
    int get_P012D026();
    int get_P012E001();
    int get_P012E002();
    int get_P012E026();
    int get_P012F001();
    int get_P012F002();
    int get_P012F026();
    int get_P012G001();
    int get_P012G002();
    int get_P012G026();
    int get_P012H001();
    int get_P012H002();
    int get_P012H026();
    int get_P012I001();
    int get_P012I002();
    int get_P012I026();
    int get_P013001();
    int get_P013A001();
    int get_P013B001();
    int get_P013C001();
    int get_P013D001();
    int get_P013E001();
    int get_P013F001();
    int get_P013G001();
    int get_P013H001();
    int get_P013I001();
//---------------------------------------------------

    const tractId& getId() const { return tractId_; } ;

    void addNeighbors(const std::set<tractId> &nghbor) { neighboringTracts_ = nghbor; } ;
    const std::set<tractId>& getNeighbors(void) const { return neighboringTracts_; };

    void addAttributes(std::vector<std::pair<tractMetric,size_t> >);
    void addAttribute( const tractMetric&,size_t);
    bool hasAttribute(const tractMetric&) const;
    size_t getAttributeValue(const tractMetric&) const;

  private:

    tractId tractId_;
    size_t population_;
    std::map<tractMetric,size_t> attributeMap_;
    std::set<tractId> neighboringTracts_;
  };

} /* namespace AIProj */

#endif /* TRACT_H_ */
