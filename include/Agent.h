#pragma once
#include <vector>

class SelectionPolicy;
class Simulation;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent();

    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    void clear();
    void setId(int id);
    void setPartyId(int id);
    //rule of 5
    virtual ~Agent(); //destructor
    Agent ( const Agent& other); //copy constructor
    Agent& operator=(const Agent& other);//copy assignment operator
    Agent(Agent &&other);//move constructor
    Agent& operator=(Agent &&other);//move assignment operator
    

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
};
