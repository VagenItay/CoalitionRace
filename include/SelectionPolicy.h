
#pragma once
#include <vector>
using std::vector;


class Party;
class Graph;


class SelectionPolicy {
    public: 
        virtual int select(vector<vector<int>> &A,Graph &G)=0;
        virtual ~SelectionPolicy(){};
        virtual SelectionPolicy* clone() = 0;
 };

class MandatesSelectionPolicy: public SelectionPolicy{   
    public: 
        virtual int select(vector<vector<int>> &A,Graph &G);
        virtual MandatesSelectionPolicy* clone();
        virtual ~MandatesSelectionPolicy(){};
 };


class EdgeWeightSelectionPolicy: public SelectionPolicy{        
    public: 
        virtual int select(vector<vector<int>> &A,Graph &G);
        virtual EdgeWeightSelectionPolicy* clone();
        virtual ~EdgeWeightSelectionPolicy(){};
};