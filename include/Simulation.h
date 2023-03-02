#pragma once
#include <vector>
#include "Graph.h"
#include "Agent.h"

using std::string;
using std::vector;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;
    void addAgent(Agent &a);

    const Graph &getGraph() const;
    Graph &getGraphNoConst();
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    Party &getPartyNoConst(int partyId);
    vector<Coalition> &getCoalitions();
    const vector<vector<int>> getPartiesByCoalitions() const;
 
private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<Coalition> mCoalitions; 
};
