#pragma once
#include <string>
#include <vector>
#include "Coalition.h"
#include "Agent.h"
using std::string;
using std::vector;

class JoinPolicy;
class Simulation;
class Graph;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    int getId() const;
    int getTimer() const;
    int getAgent() const;
    int getCoalition() const;
    void clear();
    vector<vector<int>> myLegalNeighbors(Graph &g) const;
    void AddOffer(int Offer);
    vector<int> getMyOffers() const;
    void setCoalition(int a);
    void setAgent(int a);


    //rule of 5
    virtual ~Party(); //destructor
    Party ( const Party& other); //copy constructor
    Party();//Default constructor
    Party& operator=(const Party& other);//copy assignment operator
    Party(Party &&other);//move constructor
    Party& operator=(Party &&other);//move assignment operator

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int mTimer;
    int mCoalitionId;
    int mAgentId;
    vector<int> mOffers;
};
