#include "Coalition.h"
#include "Party.h"
#include "Graph.h"

Coalition::Coalition(int CoalitionId, int mandates, vector <int> parties): mCoalitionId(CoalitionId),
 mMandates(mandates),mParties(parties) {
}

Coalition::Coalition():mCoalitionId(-1),mMandates(-1),mParties(){} //Deafult Constructor


int Coalition::getCoalitionId() const {
    return mCoalitionId;
}

int Coalition::getMandates() const {
    return mMandates;
}

vector<int> Coalition::getParties() const {
    return mParties;
}

void Coalition::addParty(int p,Graph& g) {
    mParties.push_back(p);
    mMandates=mMandates+g.getParty(p).getMandates();
}

