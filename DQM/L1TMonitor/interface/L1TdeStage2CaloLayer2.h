#ifndef DQM_L1TMonitor_L1TdeStage2CaloLayer2
#define DQM_L1TMonitor_L1TdeStage2CaloLayer2

#include "FWCore/Framework/interface/MakerMacros.h"

#include "DQMServices/Core/interface/DQMEDAnalyzer.h"
#include "DQMServices/Core/interface/MonitorElement.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/L1Trigger/interface/EGamma.h"
#include "DataFormats/L1Trigger/interface/Jet.h"
#include "DataFormats/L1Trigger/interface/EtSum.h"
#include "DataFormats/L1Trigger/interface/Tau.h"

class L1TdeStage2CaloLayer2 : public DQMEDAnalyzer {

 public:
  L1TdeStage2CaloLayer2 (const edm::ParameterSet & ps);
  virtual ~L1TdeStage2CaloLayer2();

 protected:
  virtual void dqmBeginRun (const edm::Run&, const edm::EventSetup &) override;
  virtual void beginLuminosityBlock (const edm::LuminosityBlock&, const edm::EventSetup&);
  virtual void bookHistograms (DQMStore::IBooker&, const edm::Run&, const edm::EventSetup&) override;
  virtual void analyze (const edm::Event&, const edm::EventSetup&) override;

 private:
  // Holds the name of directory in DQM where module hostograms will be shown.
  // Value is taken from python configuration file (passed in class constructor)
  std::string monitorDir;

  // collections to hold entities reconstructed from data and emulation
  edm::EDGetTokenT<l1t::JetBxCollection> calol2JetCollectionData;
  edm::EDGetTokenT<l1t::JetBxCollection> calol2JetCollectionEmul;
  edm::EDGetTokenT<l1t::EGammaBxCollection> calol2EGammaCollectionData;
  edm::EDGetTokenT<l1t::EGammaBxCollection> calol2EGammaCollectionEmul;
  edm::EDGetTokenT<l1t::TauBxCollection> calol2TauCollectionData;
  edm::EDGetTokenT<l1t::TauBxCollection> calol2TauCollectionEmul;
  edm::EDGetTokenT<l1t::EtSumBxCollection> calol2EtSumCollectionData;
  edm::EDGetTokenT<l1t::EtSumBxCollection> calol2EtSumCollectionEmul;

  // objects to represent individual plots shown in DQM
  MonitorElement * jetPt2DCorr;
  MonitorElement * sampleHist;

  bool verbose;
};

#endif
