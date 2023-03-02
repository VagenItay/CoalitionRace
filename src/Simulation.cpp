#include "Simulation.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents),mCoalitions() 
{
    //Going to build mCoalitions vector out of simulation data
    vector <Party> parties = mGraph.getVertices();
    for(Agent a:agents){
        vector <int> party;
        party.push_back(a.getPartyId()); // Setting up vector of partyIds that belong to the agent's coalition
        Coalition brandNew = Coalition(a.getId(),getPartyNoConst(a.getPartyId()).getMandates(),
         party); // Creating Coalition
        mCoalitions.push_back(brandNew); //Adding to simulation
        getPartyNoConst(a.getPartyId()).setCoalition(a.getId()); // Updating party's coalition
        getPartyNoConst(a.getPartyId()).setAgent(a.getId()); //Updating party's agent
    }
}

void Simulation::step()
{
  if(shouldTerminate())
        return;   
    vector<Party> partysId = mGraph.getVertices();
    for(Party a:partysId) //Step each party
    {
        getPartyNoConst(a.getId()).step(*this);
    }
    for(Agent b: mAgents) //Step each agent
    {
        b.step(*this);
    }
}


bool Simulation::shouldTerminate() const // this method returns true if we should stop the simulation
{
    for(Coalition c:mCoalitions) //check if there is a big enough coalition (61 mandates)
    {
        if(c.getMandates()>60)
            return true;
    }
    for(Party p:mGraph.getVertices())//check if there are more party to offer them COoperating 
    {
        if(p.getState()!=Joined)
            return false;
    }
    return true;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

Graph &Simulation::getGraphNoConst()
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

void Simulation::addAgent(Agent &a){
    mAgents.push_back(a);
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

 Party &Simulation::getPartyNoConst(int partyId)
{
    return mGraph.getPartyNoConst(partyId);
}
vector<Coalition> &Simulation::getCoalitions()
{
    return mCoalitions;
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const // Itay add notes
{
    vector<vector<int>> output;
    for(Coalition a:mCoalitions)
    {
     output.push_back(a.getParties());
    }
    return output;
}