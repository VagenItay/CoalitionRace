#pragma once
#include <vector>
#include "Graph.h"
using std::vector;

class Party;

class JoinPolicy {
    public:
        virtual int Join( vector<int> &offers , Simulation& s) = 0;
        virtual ~JoinPolicy(){};
        virtual JoinPolicy* clone() = 0;
        
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        virtual int Join( vector<int> &offers , Simulation& s); 
        virtual MandatesJoinPolicy* clone();  
        virtual ~MandatesJoinPolicy(){};  

};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        virtual int Join( vector<int> &offers , Simulation& s); 
        virtual LastOfferJoinPolicy* clone();
        virtual ~LastOfferJoinPolicy(){};    
        
};