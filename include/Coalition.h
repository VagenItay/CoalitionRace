#pragma once
#include <vector>
using std::vector;

class Party;
class Simulation;
class Graph;

class Coalition
{
public:
    Coalition(int CoalitionId, int mandates, vector <int> parties);
    Coalition();

    vector <int> getParties() const;
    int getCoalitionId() const;
    int getMandates() const;
    void clear();
    void addParty( int b ,Graph &g);


private:
    int mCoalitionId;
    int mMandates; 
    vector <int> mParties; 
    
};
