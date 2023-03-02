#include "Agent.h"
#include "Graph.h"
#include "Simulation.h"
#include "Party.h"
#include "SelectionPolicy.h"


Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    // You can change the implementation of the constructor, but not the signature!
}
Agent::Agent():mAgentId(-1),mPartyId(-1),mSelectionPolicy(nullptr){} // Default constructor

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim) //take the legal neighbors list and with the select method help, choose the right one
{
    Graph g=sim.getGraph();
    vector<vector<int>> LegalNeighbors=g.getParty(mPartyId).myLegalNeighbors(g);
    int a = mSelectionPolicy->select(LegalNeighbors,g);
    if (a!=-1) {
    sim.getGraphNoConst().getPartyNoConst(mSelectionPolicy->select(LegalNeighbors,g)).AddOffer(mPartyId);//send the offer
    sim.getGraphNoConst().getPartyNoConst(mSelectionPolicy->select(LegalNeighbors,g)).setState(CollectingOffers);//change state
    }
}

void Agent::setId(int id){
    mAgentId = id;
}

void Agent::setPartyId(int id){
    mPartyId=id;
}


//------rule of 5-------

//Copy Constructor - deep copy for resources (mSelectionPolicy)
Agent::Agent(const Agent& other):mAgentId(other.mAgentId),mPartyId(other.mPartyId),mSelectionPolicy(other.mSelectionPolicy->clone()){
    
}

//Destructor - cleaning resources
Agent::~Agent(){
    if(mSelectionPolicy)
        delete mSelectionPolicy;
}

//Copy Assignment Operator
Agent& Agent::operator=(const Agent& other){
    if(this!=&other){
        mAgentId=other.mAgentId;
        mPartyId=other.mPartyId;
        if(mSelectionPolicy)
            delete mSelectionPolicy;
        mSelectionPolicy=other.mSelectionPolicy->clone();
    }
    return *this;
}

//Move Constructor
Agent::Agent(Agent &&other):mAgentId(other.mAgentId),mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy){
    other.mSelectionPolicy=nullptr;
}

//Move Assignment Operator
Agent& Agent::operator=(Agent&& other) {
    if(this!=&other){
        mAgentId=other.mAgentId;
        mPartyId=other.mPartyId;
        if(mSelectionPolicy)
            delete mSelectionPolicy;
        mSelectionPolicy=other.mSelectionPolicy;
        other.mSelectionPolicy=nullptr;
    }
    return *this;
}
