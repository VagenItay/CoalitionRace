#include "Party.h"
#include "Graph.h"
#include "Simulation.h"
#include "JoinPolicy.h"
#include "Coalition.h"


class Graph;


Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp),
 mState(Waiting),mTimer(0),mCoalitionId(-1),mAgentId(-1),mOffers() 
{
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

int Party::getId() const
{
    return mId;
}


const string & Party::getName() const
{
    return mName;
}

void Party::setCoalition(int a){
    mCoalitionId = a;
}

void Party::step(Simulation &s)
{
    Graph g = s.getGraph();
    /* Check if the state is CollectingOffers and update the timer if so*/
    if(mState==CollectingOffers){
        mTimer++;
        if(mTimer==3){ // Time to join one of the offers
          int joining = mJoinPolicy->Join(mOffers, s);  // joining holds the partyId that this party is going to join
          mCoalitionId = (g.getParty(joining).getCoalition()); // Setting this coalitionId after joinning 
          s.getCoalitions()[mCoalitionId].addParty(mId,g); // Updating Coalition
          setState(Joined);
          Agent brandNew (s.getAgents()[g.getParty(joining).getAgent()]); // Clonning agent
          // setting mAgent details
          mAgentId=(s.getAgents().size()); 
          brandNew.setId(mAgentId);
          brandNew.setPartyId(mId);
          s.addAgent(brandNew); // Updating agents
        }
    }
}

int Party::getTimer() const{
    return mTimer;
}

void Party::setAgent(int a){
   mAgentId = a;
}
int Party::getAgent() const{
    return mAgentId;
}

int Party::getCoalition() const{
    return mCoalitionId;
}

vector<int> Party::getMyOffers() const {
    return mOffers;
}

vector<vector<int>> Party::myLegalNeighbors(Graph &g) const //this method's purpose is to give the agent option for offers
{
    vector<vector<int>> A;
    int k=0;
    int length=g.getNumVertices();
    for(int i=0;i<length;i++)
    {
        bool LastTerm=true;//check if no other agent of the curr agent party already offered this party
        int EdgeWeight=g.getEdgeWeight(mId,i);
        if(EdgeWeight!=0&&g.getParty(i).getState()!=Joined)//if the party can get offers and can cooperate with us
        {
            for(int offer:g.getParty(i).getMyOffers()) 
            {
                if(mCoalitionId!=-1){
                if((g.getParty(offer).getCoalition())==mCoalitionId)//the last term check
                    LastTerm=false;
                }
            }
            if(LastTerm)//if the party is good for us, add to the output
               {
                vector<int> a{i,EdgeWeight};
                A.push_back(a);
                k++;
               } 
        }
    }
    return A;
}

void Party::AddOffer(int Offer)
{
    mOffers.push_back(Offer);
}

void Party::clear(){
    delete mJoinPolicy;
}

//------rule of 5-------
//Copy constructor - deep copy for resources (mJoinPolicy)
Party::Party(const Party& other):mId(other.mId),mName(other.mName),mMandates(other.mMandates),mJoinPolicy(other.mJoinPolicy->clone()),mState(other.mState),
mTimer(other.mTimer),mCoalitionId(other.mCoalitionId),mAgentId(other.mAgentId),mOffers(other.mOffers){
}

//Destructor - cleaning resources
Party::~Party(){
    if(mJoinPolicy)
        delete mJoinPolicy;
}

//Copy Assignment Operator
Party& Party::operator=(const Party& other){
    if(this!=&other){
        clear();
        mId = other.mId;
        mMandates = other.mMandates;
        mJoinPolicy = other.mJoinPolicy->clone();
        mState = other.mState;
        mTimer = other.mTimer;
        mCoalitionId = other.mCoalitionId;
        mAgentId = other.mAgentId;
        mOffers = other.mOffers;
    }
    return *this;
}

//Move Constructor
Party::Party(Party &&other):mId(other.mId),mName(other.mName),mMandates(other.mMandates),mJoinPolicy(other.mJoinPolicy),mState(other.mState),
mTimer(other.mTimer),mCoalitionId(other.mCoalitionId),mAgentId(other.mAgentId),mOffers(other.mOffers){
        other.mJoinPolicy=nullptr;
}

//Move Assignment Operator
Party& Party::operator=(Party&& other) {
    if(this!=&other){
        clear();
        mId = other.mId;
        mMandates = other.mMandates;
        mJoinPolicy = other.mJoinPolicy;
        mState = other.mState;
        mTimer = other.mTimer;
        mCoalitionId = other.mCoalitionId;
        mAgentId = other.mAgentId;
        mOffers = other.mOffers;
        other.mJoinPolicy=nullptr;
    }
    return *this;
}
