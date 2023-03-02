#include "SelectionPolicy.h"
#include "Party.h"
#include "Graph.h"
#include <vector>
class Graph;
using std::vector;


int MandatesSelectionPolicy::select(vector<vector<int>> &A,Graph &G) //going through legal neighbors of the party and
{//ask the biggest ny mandates to join the coalition
    if(!A.empty()){
    Party currParty=G.getParty(A[0][0]);//first location int the inner vectors is the party's id
    int max=currParty.getMandates();//to compare the mandates
    int output=currParty.getId();//to keep the selected party's id
    for(vector<int> a:A)
    {
        currParty=G.getParty(a[0]);
        int currMandt=currParty.getMandates();
        if(currMandt>max)
           {
                max=currMandt;
                output=currParty.getId();
           } 

    }
    return output;
    } else {
        return -1;
    } 
}
int EdgeWeightSelectionPolicy::select(vector<vector<int>> &A,Graph &G) //going through legal neighbors of the party and
{//choose by the biggest weight of edge
    if(!A.empty()){
    Party currParty=G.getParty(A[0][0]);//first location int the inner vectors is the current party's id
    int output=currParty.getId();//keeps the best option's id
    int EdgeWeight=A[0][1];//first location int the inner vectors is the party's and current party's edge weight
    int max=EdgeWeight;//in order to compare betweeb the edges
    for(vector<int> a:A)
    {
        currParty=G.getParty(a[0]);
        EdgeWeight=a[1];
        if(EdgeWeight>max)
           {
                max=EdgeWeight;
                output=currParty.getId();
           } 

    }
    return output;
    } else {
        return -1;
    }
}

EdgeWeightSelectionPolicy* EdgeWeightSelectionPolicy::clone(){
    return new EdgeWeightSelectionPolicy(*this);
}

MandatesSelectionPolicy* MandatesSelectionPolicy::clone(){
    return new MandatesSelectionPolicy(*this);
}


