// Node.h

#ifndef L1Trigger_L1TMuonEndCap_emtf_Node
#define L1Trigger_L1TMuonEndCap_emtf_Node

#include <string>
#include <vector>
#include "Event.h"

namespace emtf {

class Node
{
    public:
        Node();
        Node(std::string cName);
        ~Node();

        Node(Node &&) = default;

        std::string getName();
        void setName(std::string sName);

        Double_t getErrorReduction();
        void setErrorReduction(Double_t sErrorReduction);

        Node * getLeftDaughter();
        void setLeftDaughter(Node *sLeftDaughter);

        Node * getRightDaughter();
        void setRightDaughter(Node *sLeftDaughter);

        Node * getParent();
        void setParent(Node *sParent);

        Double_t getSplitValue();
        void setSplitValue(Double_t sSplitValue);

        Int_t getSplitVariable();
        void setSplitVariable(Int_t sSplitVar);

        Double_t getFitValue();
        void setFitValue(Double_t sFitValue);

        Double_t getTotalError();
        void setTotalError(Double_t sTotalError);

        Double_t getAvgError();
        void setAvgError(Double_t sAvgError);

        Int_t getNumEvents();
        void setNumEvents(Int_t sNumEvents);

        std::vector< std::vector<Event*> >& getEvents();
        void setEvents(std::vector< std::vector<Event*> >& sEvents);

        void calcOptimumSplit();
        void filterEventsToDaughters();
        Node* filterEventToDaughter(Event* e);
        void listEvents();
        void theMiracleOfChildBirth();
 
    private:
        Node(const Node &);
        Node& operator=(const Node &);

	std::string name;

        Node *leftDaughter;
        Node *rightDaughter;
        Node *parent;

        Double_t splitValue;
        Int_t splitVariable;

        Double_t errorReduction;
        Double_t totalError;
        Double_t avgError;

        Double_t fitValue;
        Int_t numEvents;

        std::vector< std::vector<Event*> > events;
};

} // end of emtf namespace

#endif
