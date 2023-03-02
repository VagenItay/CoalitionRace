#include "JoinPolicy.h"
#include "Graph.h"
#include "Party.h"
#include "Simulation.h"




int MandatesJoinPolicy::Join( vector<int> &offers , Simulation& s){
    int maxMandates = 0;
    int partyID;
    for(int a: offers){
         // Going through offers to check what offer is from the party with the most mandadtes.
         // offers is an vector that holds integers, each integer represents the partyId that made the offer.
        if(s.getCoalitions()[(s.getParty(a).getCoalition())].getMandates() > maxMandates){
                    maxMandates = s.getCoalitions()[(s.getParty(a).getCoalition())].getMandates();
                    partyID = a;
        }
    }
    return partyID;
}

MandatesJoinPolicy* MandatesJoinPolicy::clone(){
    return new MandatesJoinPolicy(*this);
}

int LastOfferJoinPolicy::Join( vector<int> &offers , Simulation& s){
    return(int)(offers.back()); // Last offer is always at the end of vector of offers.
}

LastOfferJoinPolicy* LastOfferJoinPolicy::clone(){
    return new LastOfferJoinPolicy(*this);
}