#include "DQM/L1TMonitor/interface/L1TdeStage2CaloLayer2.h"

L1TdeStage2CaloLayer2::L1TdeStage2CaloLayer2 (const edm::ParameterSet& ps)
  : monitorDir(ps.getUntrackedParameter<std::string>("monitorDir", "")),
    calol2JetCollectionData(consumes <l1t::JetBxCollection>(
			      ps.getParameter<edm::InputTag>(
				"calol2JetCollectionData"))),
    calol2JetCollectionEmul(consumes <l1t::JetBxCollection>(
			      ps.getParameter<edm::InputTag>(
				"calol2JetCollectionEmul"))),
    calol2EGammaCollectionData(consumes <l1t::EGammaBxCollection>(
				 ps.getParameter<edm::InputTag>(
				   "calol2EGammaCollectionData"))),
    calol2EGammaCollectionEmul(consumes <l1t::EGammaBxCollection>(
				 ps.getParameter<edm::InputTag>(
				   "calol2EGammaCollectionEmul"))),
    calol2TauCollectionData(consumes <l1t::TauBxCollection>(
			      ps.getParameter<edm::InputTag>(
				"calol2TauCollectionData"))),
    calol2TauCollectionEmul(consumes <l1t::TauBxCollection>(
			      ps.getParameter<edm::InputTag>(
				"calol2TauCollectionEmul"))),
    calol2EtSumCollectionData(consumes <l1t::EtSumBxCollection>(
				ps.getParameter<edm::InputTag>(
				  "calol2EtSumCollectionData"))),
    calol2EtSumCollectionEmul(consumes <l1t::EtSumBxCollection>(
				ps.getParameter<edm::InputTag>(
				  "calol2EtSumCollectionEmul"))),
    verbose(ps.getUntrackedParameter<bool> ("verbose", false))
{}

L1TdeStage2CaloLayer2::~L1TdeStage2CaloLayer2()
{

}

void L1TdeStage2CaloLayer2::dqmBeginRun (
  edm::Run const &,
  edm::EventSetup const & evSetup) {}

void L1TdeStage2CaloLayer2::beginLuminosityBlock (
  const edm::LuminosityBlock& iLumi,
  const edm::EventSetup & evSetup) {}

void L1TdeStage2CaloLayer2::endLuminosityBlock(
  const edm::LuminosityBlock& lumi,
  const edm::EventSetup& evSetup)
{
  // divide the bin contents of high-level summary histogram by the totals
  // this might require too much memory (called every LS)
  TH1F * agreementHist = agreementSummary->getTH1F();
  agreementHist->SetBinContent(agreementHist->FindBin(EVENTGOOD),
			       goodEvents / (totalEvents * 1.0));
  agreementHist->SetBinContent(agreementHist->FindBin(JETGOOD_S),
			       goodJets / (totalJets * 1.0));
  agreementHist->SetBinContent(agreementHist->FindBin(EGGOOD_S),
			       goodEGs / (totalEGs * 1.0));
  agreementHist->SetBinContent(agreementHist->FindBin(TAUGOOD_S),
			       goodTaus / (totalTaus * 1.0));
  agreementHist->SetBinContent(agreementHist->FindBin(SUMGOOD_S),
			       goodSums / (totalSums * 1.0));

  // this might require too much memory (called every LS)
  TH1F * jetHist = jetSummary->getTH1F();
  jetHist->SetBinContent(jetHist->FindBin(JETGOOD),
			 goodJets / (totalJets * 1.0));
  jetHist->SetBinContent(jetHist->FindBin(JETPOSOFF),
			 posOffJets / (totalJets * 1.0));
  jetHist->SetBinContent(jetHist->FindBin(JETETOFF),
			 etOffJets / (totalJets * 1.0));

  TH1F * egHist = egSummary->getTH1F();
  egHist->SetBinContent(egHist->FindBin(EGGOOD), goodEGs / (totalEGs * 1.0));
  egHist->SetBinContent(egHist->FindBin(EGPOSOFF),
			posOffEGs / (totalEGs * 1.0));
  egHist->SetBinContent(egHist->FindBin(EGETOFF),
			etOffEGs / (totalEGs * 1.0));
  egHist->SetBinContent(egHist->FindBin(ISOEGGOOD),
			goodIsoEGs / (totalIsoEGs * 1.0));
  egHist->SetBinContent(egHist->FindBin(ISOEGPOSOFF),
			posOffIsoEGs / (totalIsoEGs * 1.0));
  egHist->SetBinContent(egHist->FindBin(ISOEGETOFF),
			etOffIsoEGs / (totalIsoEGs * 1.0));

  TH1F * tauHist = tauSummary->getTH1F();
  tauHist->SetBinContent(tauHist->FindBin(TAUGOOD),
			 goodTaus / (totalTaus * 1.0));
  tauHist->SetBinContent(tauHist->FindBin(TAUPOSOFF),
			 posOffTaus / (totalTaus * 1.0));
  tauHist->SetBinContent(tauHist->FindBin(TAUETOFF),
			 etOffTaus / (totalTaus * 1.0));
  tauHist->SetBinContent(tauHist->FindBin(ISOTAUGOOD),
			 goodIsoTaus / (totalIsoTaus * 1.0));
  tauHist->SetBinContent(tauHist->FindBin(ISOTAUPOSOFF),
			 posOffIsoTaus / (totalIsoTaus * 1.0));
  tauHist->SetBinContent(tauHist->FindBin(ISOTAUETOFF),
			 etOffIsoTaus / (totalIsoTaus * 1.0));

  TH1F * sumHist = sumSummary->getTH1F();
  sumHist->SetBinContent(sumHist->FindBin(SUMGOOD),
			 goodSums / (totalSums * 1.0));
  sumHist->SetBinContent(sumHist->FindBin(ETTSUMGOOD),
			 goodETTSums / (totalETTSums * 1.0 ));
  sumHist->SetBinContent(sumHist->FindBin(HTTSUMGOOD),
			 goodHTTSums / (totalHTTSums * 1.0 ));
  sumHist->SetBinContent(sumHist->FindBin(METSUMGOOD),
			 goodMETSums / (totalMETSums * 1.0));
  sumHist->SetBinContent(sumHist->FindBin(MHTSUMGOOD),
			 goodMHTSums / (totalMHTSums * 1.0));
  sumHist->SetBinContent(sumHist->FindBin(MBHFSUMGOOD),
			 goodMBHFSums / (totalMBHFSums * 1.0));
  sumHist->SetBinContent(sumHist->FindBin(TOWCOUNTGOOD),
			 goodTowCountSums / (totalTowCountSums * 1.0));
}

/**
   Method to declare or "book" all histograms that will be part of module

   Histograms that are to be visualised as part of the DQM module should be
   registered with the IBooker object any additional configuration such as title
   or axis labels and ranges. A good rule of thumb for the amount of
   configuration is that it should be possible to understnand the contents of
   the histogram using the configuration received from this method since the
   plots generated by this module would later be stored into ROOT files for
   transfer to the DQM system and it should be possible to ...

   @param DQMStore::IBooker&      ibooker
   @param edm::Run const &
   @param edm::EventSetup const &

   @return void
 */
void L1TdeStage2CaloLayer2::bookHistograms(
  DQMStore::IBooker &ibooker,
  edm::Run const &,
  edm::EventSetup const&) {

  ibooker.setCurrentFolder(monitorDir + "/Problematic Jets candidates");
  jetEt = ibooker.book1D("Problematic Jet iEt", "Jet iE_{T}", 1400, 0, 1399);
  jetEta = ibooker.book1D("Problematic Jet iEta", "Jet i#eta",
			  227, -113.5, 113.5);
  jetPhi = ibooker.book1D("Problematic Jet iPhi", "Jet i#phi",
			  288, -0.5, 143.5);

  ibooker.setCurrentFolder(monitorDir + "/Problematic EG candidtes");

  egEt = ibooker.book1D("Problematic Eg iEt", "Eg iE_{T}", 1400, 0, 1399);
  egEta = ibooker.book1D("Problematic Eg iEta", "Eg i#eta", 227, -113.5, 113.5);
  egPhi = ibooker.book1D("Problematic Eg iPhi", "Eg i#phi", 288, -0.5, 143.5);

  isoEgEt = ibooker.book1D("Problematic Isolated Eg iEt", "Iso Eg iE_{T}",
			   1400, 0, 1399);
  isoEgEta = ibooker.book1D("Problematic Isolated Eg iEta", "Iso Eg i#eta",
			    227, -113.5, 113.5);
  isoEgPhi = ibooker.book1D("Problematic Isolated Eg iPhi", "Iso Eg i#phi",
			    288, -0.5, 143.5);

  ibooker.setCurrentFolder(monitorDir + "/Problematic Tau candidtes");

  tauEt = ibooker.book1D("Problematic Tau iEt", "Tau iE_{T}", 1400, 0, 1399);
  tauEta = ibooker.book1D("Problematic Tau iEta", "Tau i#eta",
			  227, -113.5, 113.5);
  tauPhi = ibooker.book1D("Problematic Tau iPhi", "Tau i#phi",
			  288, -0.5, 143.5);
  isoTauEt = ibooker.book1D("Problematic Isolated Tau iEt", "Iso Tau iE_{T}",
			    1400, 0, 1399);
  isoTauEta = ibooker.book1D("Problematic Isolated Tau iEta", "Iso Tau i#eta",
			     227, -113.5, 113.5);
  isoTauPhi = ibooker.book1D("Problematic Isolated Tau iPhi", "Iso Tau i#phi",
			     288, -0.5, 143.5);

  ibooker.setCurrentFolder(monitorDir + "/Problematic Sums");
  // for reference on arguments of book2D, see
  // https://cmssdt.cern.ch/SDT/doxygen/CMSSW_8_0_24/doc/html/df/d26/DQMStore_8cc_source.html#l01070


  // setup the directory where the histograms are to be visualised, value is set
  // in constructor and taken from python configuration file for module
  ibooker.setCurrentFolder(monitorDir);

  // Jet energy in MP firmware is stored in 16 bits which sets the range of
  // jet energy to 2^16 * 0.5 GeV = 32768 GeV (65536 hardware units)
  // --- this is only for MP jets, the demux jets have much decreased precision
  // --- and this should be replaced

  // the index of the first bin in histogram should match value of first enum
  agreementSummary = ibooker.book1D(
    "CaloL2 Object Agreement Summary",
    "CaloL2 event-by-event object agreement fractions", 5, 1, 6);

  agreementSummary->getTH1F()->GetXaxis()->SetBinLabel(EVENTGOOD,
						       "good events");
  agreementSummary->getTH1F()->GetXaxis()->SetBinLabel(JETGOOD_S, "good jets");
  agreementSummary->getTH1F()->GetXaxis()->SetBinLabel(EGGOOD_S, "good e/gs");
  agreementSummary->getTH1F()->GetXaxis()->SetBinLabel(TAUGOOD_S, "good taus");
  agreementSummary->getTH1F()->GetXaxis()->SetBinLabel(SUMGOOD_S, "good sums");

  jetSummary = ibooker.book1D(
    "Jet Agreement Summary", "Jet Agreement Summary", 4, 1, 5);
  // jetSummary->getTH1F()->GetXaxis()->SetBinLabel(NJETS, "total jets");
  jetSummary->getTH1F()->GetXaxis()->SetBinLabel(JETGOOD, "good jets");
  jetSummary->getTH1F()->GetXaxis()->SetBinLabel(JETPOSOFF, "jets pos off");
  jetSummary->getTH1F()->GetXaxis()->SetBinLabel(JETETOFF, "jets Et off");

  egSummary = ibooker.book1D(
    "EG Agreement Summary", "EG Agreement Summary", 6, 1, 7);
  // egSummary->getTH1F()->GetXaxis()->SetBinLabel(NEGS, "total e/gs");
  egSummary->getTH1F()->GetXaxis()->SetBinLabel(EGGOOD, "good e/gs");
  egSummary->getTH1F()->GetXaxis()->SetBinLabel(EGPOSOFF, "e/gs pos off");
  egSummary->getTH1F()->GetXaxis()->SetBinLabel(EGETOFF, "e/gs Et off");
  egSummary->getTH1F()->GetXaxis()->SetBinLabel(ISOEGGOOD, "good iso e/gs");
  egSummary->getTH1F()->GetXaxis()->SetBinLabel(ISOEGPOSOFF,
						"iso e/gs pos off");
  egSummary->getTH1F()->GetXaxis()->SetBinLabel(ISOEGETOFF, "iso e/gs Et off");

  tauSummary = ibooker.book1D(
    "Tau Agreement Summary", "Tau Agreement Summary", 6, 1, 7);
  // tauSummary->getTH1F()->GetXaxis()->SetBinLabel(NTAUS, "total taus");
  tauSummary->getTH1F()->GetXaxis()->SetBinLabel(TAUGOOD, "good taus");
  tauSummary->getTH1F()->GetXaxis()->SetBinLabel(TAUPOSOFF, "taus pos off");
  tauSummary->getTH1F()->GetXaxis()->SetBinLabel(TAUETOFF, "taus Et off");
  tauSummary->getTH1F()->GetXaxis()->SetBinLabel(ISOTAUGOOD, "good iso taus");
  tauSummary->getTH1F()->GetXaxis()->SetBinLabel(ISOTAUPOSOFF,
						 "iso taus pos off");
  tauSummary->getTH1F()->GetXaxis()->SetBinLabel(ISOTAUETOFF,
						 "iso taus Et off");

  sumSummary = ibooker.book1D(
    "Emergy Sum Agreement Summary", "Sum Agreement Summary", 7, 1, 8);

  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(SUMGOOD, "good sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(ETTSUMGOOD, "good ETT sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(HTTSUMGOOD, "good HTT sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(METSUMGOOD, "good MET sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(MHTSUMGOOD, "good MHT sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(MBHFSUMGOOD, "good MBHF sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(TOWCOUNTGOOD,
						 "good TowCount sums");

  mpSummary = ibooker.book1D("MP Specific Bad Events Summary", "MP Summary",
			     8, 1, 9);
}
void L1TdeStage2CaloLayer2::analyze (
  const edm::Event& e,
  const edm::EventSetup & c) {

  ++totalEvents;

  if (verbose)
    edm::LogInfo("L1TdeStage2CaloLayer2") << "L1TdeStage2CaloLayer2: analyse "
					  << std::endl;

  // define collections to hold lists of objects in event
  edm::Handle<l1t::JetBxCollection> jetDataCol;
  edm::Handle<l1t::JetBxCollection> jetEmulCol;
  edm::Handle<l1t::EGammaBxCollection> egDataCol;
  edm::Handle<l1t::EGammaBxCollection> egEmulCol;
  edm::Handle<l1t::TauBxCollection> tauDataCol;
  edm::Handle<l1t::TauBxCollection> tauEmulCol;
  edm::Handle<l1t::EtSumBxCollection> sumDataCol;
  edm::Handle<l1t::EtSumBxCollection> sumEmulCol;

  // map event contents to above collections
  e.getByToken(calol2JetCollectionData, jetDataCol);
  e.getByToken(calol2JetCollectionEmul, jetEmulCol);
  e.getByToken(calol2EGammaCollectionData, egDataCol);
  e.getByToken(calol2EGammaCollectionEmul, egEmulCol);
  e.getByToken(calol2TauCollectionData, tauDataCol);
  e.getByToken(calol2TauCollectionEmul, tauEmulCol);
  e.getByToken(calol2EtSumCollectionData, sumDataCol);
  e.getByToken(calol2EtSumCollectionEmul, sumEmulCol);

  bool eventGood = true;

  // std::cout << "Jet event by event comparisons. " << std::endl;

  // unsigned int currBx = 0;
  // we assume that the first and last bx of the emulator data is 0 since it is
  // very unlikely to have received RAW data from more than just the triggered
  // bx

  /**
     Notes:
     - The hardware can send up to 12 jets due to bandwidth limitation so it
       will sort the jets it has found in order of decreasing pT and will send
       only the top 12. The emulator does not have similar constraint but can be
       configured to truncate the list of jets it has found. In the case that a
       small number of jets is found (less than 12), the full list will be sent.
     - Currently, the edge case where the number of jets/objects in data and
       emulator are different is being skipped but would need to be addressed
       before the module can be declared complete.

     Edge cases to consider:
     - there are more emulator jets than data jets
     - there are more data jets than emulator jets
     - missing jet is at beginning/end
     - missing jet is in the middle
  */


  l1t::EGammaBxCollection::const_iterator dataEGIt = egDataCol->begin(currBx);
  l1t::EGammaBxCollection::const_iterator emulEGIt = egEmulCol->begin(currBx);

  l1t::TauBxCollection::const_iterator dataTauIt = tauDataCol->begin(currBx);
  l1t::TauBxCollection::const_iterator emulTauIt = tauEmulCol->begin(currBx);

  l1t::EtSumBxCollection::const_iterator dataSumIt = sumDataCol->begin(currBx);
  l1t::EtSumBxCollection::const_iterator emulSumIt = sumEmulCol->begin(currBx);

  TH1F * hist = agreementSummary->getTH1F();

  TH1F * jetHist = jetSummary->getTH1F();
  TH1F * jetEtHist = jetEt->getTH1F();
  TH1F * jetEtaHist = jetEta->getTH1F();
  TH1F * jetPhiHist = jetPhi->getTH1F();

  TH1F * egHist = egSummary->getTH1F();
  TH1F * egEtHist = egEt->getTH1F();
  TH1F * egEtaHist = egEta->getTH1F();
  TH1F * egPhiHist = egPhi->getTH1F();
  TH1F * isoEgEtHist = isoEgEt->getTH1F();
  TH1F * isoEgEtaHist = isoEgEta->getTH1F();
  TH1F * isoEgPhiHist = isoEgPhi->getTH1F();

  TH1F * tauHist = tauSummary->getTH1F();
  TH1F * tauEtHist = tauEt->getTH1F();
  TH1F * tauEtaHist = tauEta->getTH1F();
  TH1F * tauPhiHist = tauPhi->getTH1F();
  TH1F * isoTauEtHist = isoTauEt->getTH1F();
  TH1F * isoTauEtaHist = isoTauEta->getTH1F();
  TH1F * isoTauPhiHist = isoTauPhi->getTH1F();

  TH1F * sumHist = sumSummary->getTH1F();

  // hist->Fill(NEVENTS);

  if (!compareJets(jetDataCol,
		   jetEmulCol,
		   hist,
		   jetHist,
		   jetEtHist,
		   jetEtaHist,
		   jetPhiHist))
    eventGood = false;

  if (!compareEGs(egDataCol,
		  egEmulCol,
		  hist,
		  egHist,
		  egEtHist,
		  egEtaHist,
		  egPhiHist,
		  isoEgEtHist,
		  isoEgEtaHist,
		  isoEgPhiHist))
    eventGood = false;

  if (!compareTaus(tauDataCol,
		   tauEmulCol,
		   hist,
		   tauHist,
		   tauEtHist,
		   tauEtaHist,
		   tauPhiHist,
		   isoTauEtHist,
		   isoTauEtaHist,
		   isoTauPhiHist))
    eventGood = false;

  if (!compareSums(sumDataCol, sumEmulCol, hist, sumHist))
    eventGood = false;

  // loop over the different bx associated with the collections (choose one)

  // at each iteration:

  // skip BXs which do not exist in the "other" collection (the one not being
  // looped over)

  // extract the data and emul jet collections for each BX
  // this loop can be used to populate all histograms associated with a given
  // object, i.e. pT, eta, phi, etc

  // while looping over the two collections one can assume that both collections
  // have the objects sorted in the same order which would only require to
  // compare the objects available at the current iteration.

  /**
     Questions:
     - what could make the data and emul bx ranges to be different?
     - how can I confirm that the emulator data is being filled?
  */

  if (eventGood) {
    hist->Fill(EVENTGOOD);
    ++goodEvents;
  }
}



// comparison method for jets
bool L1TdeStage2CaloLayer2::compareJets(
  const edm::Handle<l1t::JetBxCollection> & dataCol,
  const edm::Handle<l1t::JetBxCollection> & emulCol,
  TH1F * & summaryHist,
  TH1F * & objSummaryHist,
  TH1F * & objEtHist,
  TH1F * & objEtaHist,
  TH1F * & objPhiHist)
{
  bool eventGood = true;

  l1t::JetBxCollection::const_iterator dataIt = dataCol->begin(currBx);
  l1t::JetBxCollection::const_iterator emulIt = emulCol->begin(currBx);

  // process jets
  if (dataCol->size() != emulCol->size()) {


    if (dataCol->size() < emulCol->size()) {
      if (dataCol->size() < 1)
	return false;

      while (true) {
	objEtHist->Fill(dataIt->hwPt());
	objEtaHist->Fill(dataIt->hwEta());
	objPhiHist->Fill(dataIt->hwPhi());

	++dataIt;

	if (dataIt == dataCol->end(currBx))
	  break;
      }
    } else{

      if (emulCol->size() < 1)
	return false;

      while (true) {

	objEtHist->Fill(emulIt->hwPt());
	objEtaHist->Fill(emulIt->hwEta());
	objPhiHist->Fill(emulIt->hwPhi());

	++emulIt;

	if (emulIt == emulCol->end(currBx))
	  break;
      }
    }

    return false;
  }

  if (dataIt != dataCol->end(currBx) ||
      emulIt != emulCol->end(currBx)) {
    while(true) {

      bool posGood = true;
      bool etGood = true;

      // jet Et mismatch
      if (dataIt->hwPt() != emulIt->hwPt()) {
        etGood = false;
	eventGood = false;
      }

      // jet position mismatch
      if (dataIt->hwPhi() != emulIt->hwPhi()){
	posGood = false;
	eventGood = false;
      }
      if (dataIt->hwEta() != emulIt->hwEta()) {
	posGood = false;
	eventGood = false;
      }

      // if both position and energy agree, jet is good
      if (eventGood) {
	summaryHist->Fill(JETGOOD_S);
	objSummaryHist->Fill(JETGOOD);
	++goodJets;
      } else {
	objEtHist->Fill(dataIt->hwPt());
	objEtaHist->Fill(dataIt->hwEta());
	objPhiHist->Fill(dataIt->hwPhi());
      }

      // if only position agrees
      if (posGood && !etGood) {
	objSummaryHist->Fill(JETETOFF);

	++etOffJets;
      }

      // if only energy agrees
      if (!posGood && etGood) {
	objSummaryHist->Fill(JETPOSOFF);
	++posOffJets;
      }

      // keep track of jets
      // summaryHist->Fill(NJETS_S);
      // objSummaryHist->Fill(NJETS);

      ++totalJets;

      ++dataIt;
      ++emulIt;

      if (dataIt == dataCol->end(currBx) ||
	  emulIt == emulCol->end(currBx))
	break;
    }
  } else {
    return false;
  }

  // return a boolean that states whether the jet data in the event is in
  // agreement
  return eventGood;
}

// comparison method for e/gammas
bool L1TdeStage2CaloLayer2::compareEGs(
  const edm::Handle<l1t::EGammaBxCollection> & dataCol,
  const edm::Handle<l1t::EGammaBxCollection> & emulCol,
  TH1F * & summaryHist,
  TH1F * & objSummaryHist,
  TH1F * & objEtHist,
  TH1F * & objEtaHist,
  TH1F * & objPhiHist,
  TH1F * & isoObjEtHist,
  TH1F * & isoObjEtaHist,
  TH1F * & isoObjPhiHist)
{
  bool eventGood = true;

  l1t::EGammaBxCollection::const_iterator dataIt = dataCol->begin(currBx);
  l1t::EGammaBxCollection::const_iterator emulIt = emulCol->begin(currBx);

  // check length of collections
  if (dataCol->size() != emulCol->size()) {

    if (dataCol->size() < emulCol->size()) {
      if (dataCol->size() < 1)
	return false;

      // if there are more events in data loop over the data collection
      while (true) {

	// TODO: Populate different set of histograms if object is solated

	if (dataIt->hwIso()) {
	  isoObjEtHist->Fill(dataIt->hwPt());
	  isoObjEtaHist->Fill(dataIt->hwEta());
	  isoObjPhiHist->Fill(dataIt->hwPhi());
	} else {
	  objEtHist->Fill(dataIt->hwPt());
	  objEtaHist->Fill(dataIt->hwEta());
	  objPhiHist->Fill(dataIt->hwPhi());
	}

	++dataIt;

	if (dataIt == dataCol->end(currBx))
	  break;
      }
    } else {

      if (emulCol->size() < 1)
	return false;

      while (true) {

	// TODO: Populate different set of histograms if object is solated

	if(emulIt->hwIso()) {
	  isoObjEtHist->Fill(emulIt->hwPt());
	  isoObjEtaHist->Fill(emulIt->hwEta());
	  isoObjPhiHist->Fill(emulIt->hwPhi());
	} else {
	  objEtHist->Fill(emulIt->hwPt());
	  objEtaHist->Fill(emulIt->hwEta());
	  objPhiHist->Fill(emulIt->hwPhi());
	}

	++emulIt;

	if (emulIt == emulCol->end(currBx))
	  break;
      }
    }

    return false;
  }

  // processing continues only of length of data collections is the same
  if (dataIt != dataCol->end(currBx) ||
      emulIt != emulCol->end(currBx)) {

    while(true) {

      bool posGood = true;
      bool etGood = true;
      bool iso = dataIt->hwIso();

      // object Et mismatch
      if (dataIt->hwPt() != emulIt->hwPt()) {
	etGood = false;
	eventGood = false;
      }

      // object position mismatch
      if (dataIt->hwPhi() != emulIt->hwPhi()) {
	posGood = false;
	eventGood = false;
      }
      if (dataIt->hwEta() != emulIt->hwEta()) {
	posGood = false;
	eventGood = false;
      }

      // if both position and energy agree, object is good
      if (eventGood) {
	summaryHist->Fill(EGGOOD_S);

	if (iso) {
	  ++goodIsoEGs;
	  objSummaryHist->Fill(ISOEGGOOD);
	} else {
	  ++goodEGs;
	  objSummaryHist->Fill(EGGOOD);
	}

	// ++goodEGs;
      } else {

	if (iso) {
	  isoObjEtHist->Fill(dataIt->hwPt());
	  isoObjEtaHist->Fill(dataIt->hwEta());
	  isoObjPhiHist->Fill(dataIt->hwPhi());
	} else {
	  objEtHist->Fill(dataIt->hwPt());
	  objEtaHist->Fill(dataIt->hwEta());
	  objPhiHist->Fill(dataIt->hwPhi());
	}
      }

      // if only position agrees
      if (posGood && !etGood) {
	if (iso) {
	  ++etOffIsoEGs;
	  objSummaryHist->Fill(ISOEGETOFF);
	} else {
	  ++etOffEGs;
	  objSummaryHist->Fill(EGETOFF);
	}
      }

      // if only energy agrees
      if (!posGood && etGood) {
	if (iso) {
	  ++posOffIsoEGs;
	  objSummaryHist->Fill(ISOEGPOSOFF);
	} else {
	  ++posOffEGs;
	  objSummaryHist->Fill(EGPOSOFF);
	}
      }

      // keep track of number of objects
      // summaryHist->Fill(NEGS_S);
      // objSummaryHist->Fill(NEGS);

      if (iso) {
	++totalIsoEGs;
      } else {
	++totalEGs;
      }

      ++dataIt;
      ++emulIt;

      if (dataIt == dataCol->end(currBx) ||
	  emulIt == emulCol->end(currBx))
	break;
    }
  } else {
    return false;
  }

  // return a boolean that states whether the jet data in the event is in
  // agreement
  return eventGood;
}

// comparison method for taus
bool L1TdeStage2CaloLayer2::compareTaus(
  const edm::Handle<l1t::TauBxCollection> & dataCol,
  const edm::Handle<l1t::TauBxCollection> & emulCol,
  TH1F * & summaryHist,
  TH1F * & objSummaryHist,
  TH1F * & objEtHist,
  TH1F * & objEtaHist,
  TH1F * & objPhiHist,
  TH1F * & isoObjEtHist,
  TH1F * & isoObjEtaHist,
  TH1F * & isoObjPhiHist)
{
  bool eventGood = true;

  l1t::TauBxCollection::const_iterator dataIt = dataCol->begin(currBx);
  l1t::TauBxCollection::const_iterator emulIt = emulCol->begin(currBx);

  // check length of collections
  if (dataCol->size() != emulCol->size()) {

    if (dataCol->size() < emulCol->size()) {
      if (dataCol->size() < 1)
	return false;

      // if there are more events in data loop over the data collection
      while (true) {

	// TODO: Populate different set of histograms if object is solated

	if (dataIt->hwIso()) {
	  isoObjEtHist->Fill(dataIt->hwPt());
	  isoObjEtaHist->Fill(dataIt->hwEta());
	  isoObjPhiHist->Fill(dataIt->hwPhi());
	} else {
	  objEtHist->Fill(dataIt->hwPt());
	  objEtaHist->Fill(dataIt->hwEta());
	  objPhiHist->Fill(dataIt->hwPhi());
	}

	++dataIt;

	if (dataIt == dataCol->end(currBx))
	  break;
      }
    } else {

      if (emulCol->size() < 1)
	return false;

      while (true) {

	// TODO: Populate different set of histograms if object is solated

	if(emulIt->hwIso()) {
	  isoObjEtHist->Fill(emulIt->hwPt());
	  isoObjEtaHist->Fill(emulIt->hwEta());
	  isoObjPhiHist->Fill(emulIt->hwPhi());
	} else {
	  objEtHist->Fill(emulIt->hwPt());
	  objEtaHist->Fill(emulIt->hwEta());
	  objPhiHist->Fill(emulIt->hwPhi());
	}

	++emulIt;

	if (emulIt == emulCol->end(currBx))
	  break;
      }
    }

    return false;
  }

  // processing continues only of length of data collections is the same
  if (dataIt != dataCol->end(currBx) ||
      emulIt != emulCol->end(currBx)) {

    while(true) {

      bool posGood = true;
      bool etGood = true;
      bool iso = dataIt->hwIso();

      // object Et mismatch
      if (dataIt->hwPt() != emulIt->hwPt()) {
	etGood = false;
	eventGood = false;
      }

      // object position mismatch
      if (dataIt->hwPhi() != emulIt->hwPhi()) {
	posGood = false;
	eventGood = false;
      }
      if (dataIt->hwEta() != emulIt->hwEta()) {
	posGood = false;
	eventGood = false;
      }

      // if both position and energy agree, object is good
      if (eventGood) {
	summaryHist->Fill(TAUGOOD_S);

	// ++goodTaus;

	if (iso) {
	  ++goodIsoTaus;
	  objSummaryHist->Fill(ISOTAUGOOD);
	} else {
	  ++goodTaus;
	  objSummaryHist->Fill(TAUGOOD);
	}
      } else {

	if (iso) {
	  isoObjEtHist->Fill(dataIt->hwPt());
	  isoObjEtaHist->Fill(dataIt->hwEta());
	  isoObjPhiHist->Fill(dataIt->hwPhi());
	} else {
	  objEtHist->Fill(dataIt->hwPt());
	  objEtaHist->Fill(dataIt->hwEta());
	  objPhiHist->Fill(dataIt->hwPhi());
	}
      }

      // if only position agrees
      if (posGood && !etGood) {
	if (iso) {
	  ++etOffIsoTaus;
	  objSummaryHist->Fill(ISOTAUETOFF);
	} else {
	  ++etOffTaus;
	  objSummaryHist->Fill(TAUETOFF);
	}
      }

      // if only energy agrees
      if (!posGood && etGood) {
	if (iso) {
	  ++posOffIsoTaus;
	  objSummaryHist->Fill(ISOTAUPOSOFF);
	} else {
	  ++posOffTaus;
	  objSummaryHist->Fill(TAUPOSOFF);
	}
      }

      // keep track of number of objects
      // objSummaryHist->Fill(NTAUS);

      if (iso) {
	++totalIsoTaus;
      } else {
	++totalTaus;
      }

      ++dataIt;
      ++emulIt;

      if (dataIt == dataCol->end(currBx) ||
	  emulIt == emulCol->end(currBx))
	break;
    }
  } else {
    return false;
  }

  // return a boolean that states whether the jet data in the event is in
  // agreement
  return eventGood;
}

// comparison method for sums
bool L1TdeStage2CaloLayer2::compareSums(
  const edm::Handle<l1t::EtSumBxCollection> & dataCol,
  const edm::Handle<l1t::EtSumBxCollection> & emulCol,
  TH1F * & hist,
  TH1F * & objSummaryHist)
{
  bool eventGood = true;

  bool etGood = true;
  bool phiGood = true;

  l1t::EtSumBxCollection::const_iterator dataIt = dataCol->begin(currBx);
  l1t::EtSumBxCollection::const_iterator emulIt = emulCol->begin(currBx);

  while(true) {

    // It should be possible to implement this with a switch statement
    etGood = true;
    phiGood = true;

    // ETT
    if (l1t::EtSum::EtSumType::kTotalEt == dataIt->getType()) {

      // objSummaryHist->Fill(NSUMS);
      // objSummaryHist->Fill(NSCALARSUMS);
      ++totalETTSums;
      if (dataIt->hwPt() != emulIt->hwPt()) {
	eventGood = false;
      } else {
	++goodSums;
	++goodETTSums;
	hist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(ETTSUMGOOD);
      }
    }

    // ETTHF
    if (l1t::EtSum::EtSumType::kTotalEtHF == dataIt->getType()) {

      // objSummaryHist->Fill(NSUMS);
      // objSummaryHist->Fill(NSCALARSUMS);
      ++totalETTSums;
      if (dataIt->hwPt() != emulIt->hwPt()) {
	eventGood = false;
      } else {
	++goodSums;
	++goodETTSums;
	hist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(ETTSUMGOOD);
      }
    }

    // ETTEM
    if (l1t::EtSum::EtSumType::kTotalEtEm == dataIt->getType()) {

      // objSummaryHist->Fill(NSUMS);
      // objSummaryHist->Fill(NSCALARSUMS);
      ++totalETTSums;
      if (dataIt->hwPt() != emulIt->hwPt()) {
	eventGood = false;
      } else {
	++goodSums;
	++goodETTSums;
	hist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(ETTSUMGOOD);
      }
    }

    // HTT
    if (l1t::EtSum::EtSumType::kTotalHt == dataIt->getType()) {

      // objSummaryHist->Fill(NSUMS);
      // objSummaryHist->Fill(NSCALARSUMS);
      ++totalHTTSums;
      if (dataIt->hwPt() != emulIt->hwPt()) {
	eventGood = false;
      } else {
	++goodSums;
	++goodHTTSums;
	hist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(HTTSUMGOOD);
      }
    }

    // HTTHF
    if (l1t::EtSum::EtSumType::kTotalHtHF == dataIt->getType()) {

      // objSummaryHist->Fill(NSUMS);
      // objSummaryHist->Fill(NSCALARSUMS);
      ++totalHTTSums;
      if (dataIt->hwPt() != emulIt->hwPt()) {
	eventGood = false;
      } else {
	++goodSums;
	++goodHTTSums;
	hist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(HTTSUMGOOD);
      }
    }

    // MET
    if (l1t::EtSum::EtSumType::kMissingEt == dataIt->getType()) {

      // objSummaryHist->Fill(NSUMS);
      // objSummaryHist->Fill(NVECTORSUMS);
      ++totalMETSums;
      if (dataIt->hwPt() != emulIt->hwPt()) {
	etGood = false;
	eventGood = false;
      }

      if (dataIt->hwPhi() != emulIt->hwPhi()) {
	phiGood = false;
	eventGood = false;
      }

      if (etGood && phiGood) {
	++goodSums;
	++goodMETSums;
	hist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(METSUMGOOD);
      }
    }

    // METHF
    if (l1t::EtSum::EtSumType::kMissingEtHF == dataIt->getType()) {

      // objSummaryHist->Fill(NSUMS);
      // objSummaryHist->Fill(NVECTORSUMS);
      ++totalMETSums;
      if (dataIt->hwPt() != emulIt->hwPt()) {
	etGood = false;
	eventGood = false;
      }

      if (dataIt->hwPhi() != emulIt->hwPhi()) {
	phiGood = false;
	eventGood = false;
      }

      if (etGood && phiGood) {
	++goodSums;
	++goodMETSums;
	hist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(METSUMGOOD);
      }
    }

    // MHT
    if (l1t::EtSum::EtSumType::kMissingHtHF == dataIt->getType()) {

      // objSummaryHist->Fill(NSUMS);
      // objSummaryHist->Fill(NVECTORSUMS);
      ++totalMHTSums;
      if (dataIt->hwPt() != emulIt->hwPt()) {
	etGood = false;
	eventGood = false;
      }

      if (dataIt->hwPhi() != emulIt->hwPhi()) {
	phiGood = false;
	eventGood = false;
      }

      if (etGood && phiGood) {
	++goodSums;
	++goodMHTSums;
	hist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(MHTSUMGOOD);
      }
    }

    // MHTHF
    if (l1t::EtSum::EtSumType::kMissingEt == dataIt->getType()) {

      // objSummaryHist->Fill(NSUMS);
      // objSummaryHist->Fill(NVECTORSUMS;)
      ++totalMHTSums;
      if (dataIt->hwPt() != emulIt->hwPt()) {
	phiGood = false;
	eventGood = false;
      }

      if (dataIt->hwPhi() != emulIt->hwPhi()) {
	phiGood = false;
	eventGood = false;
      }

      if (etGood && phiGood) {
	++goodSums;
	++goodMHTSums;
	hist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(MHTSUMGOOD);
      }
    }

    // MBHFP0
    if (l1t::EtSum::EtSumType::kMinBiasHFP0 == dataIt->getType()) {

      // objSummaryHist->Fill(NSUMS);
      // objSummaryHist->Fill(NFEATURESUMS);
      ++totalMBHFSums;
      if (dataIt->hwPt() != emulIt->hwPt()) {
	eventGood = false;
      } else {
	++goodSums;
	++goodMBHFSums;
	hist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(MBHFSUMGOOD);
      }
    }

    // MBHFM0
    if (l1t::EtSum::EtSumType::kMinBiasHFM0 == dataIt->getType()) {

      // objSummaryHist->Fill(NSUMS);
      // objSummaryHist->Fill(NFEATURESUMS);
      ++totalMBHFSums;
      if (dataIt->hwPt() != emulIt->hwPt()) {
	eventGood = false;
      } else {
	++goodSums;
	++goodMBHFSums;
	hist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(MBHFSUMGOOD);
      }
    }

    // MBHFP1
    if (l1t::EtSum::EtSumType::kMinBiasHFP1 == dataIt->getType()) {

      // objSummaryHist->Fill(NSUMS);
      // objSummaryHist->Fill(NFEATURESUMS);
      ++totalMBHFSums;
      if (dataIt->hwPt() != emulIt->hwPt()) {
	eventGood = false;
      } else {
	++goodSums;
	++goodMBHFSums;
	hist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(MBHFSUMGOOD);
      }
    }

    // MBHFM1
    if (l1t::EtSum::EtSumType::kMinBiasHFM1 == dataIt->getType()) {

      // objSummaryHist->Fill(NSUMS);
      // objSummaryHist->Fill(NFEATURESUMS);
      ++totalMBHFSums;
	++goodMBHFSums;
      if (dataIt->hwPt() != emulIt->hwPt()) {
	eventGood = false;
      } else {
	++goodSums;
	++goodMBHFSums;
	hist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(MBHFSUMGOOD);
      }
    }

    // TowerCount
    if (l1t::EtSum::EtSumType::kTowerCount == dataIt->getType()) {

      // objSummaryHist->Fill(NSUMS);
      // objSummaryHist->Fill(NFEATURESUMS);
      ++totalTowCountSums;
      if (dataIt->hwPt() != emulIt->hwPt()) {
	eventGood = false;
      } else {
	++goodSums;
	++goodTowCountSums;
	hist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(TOWCOUNTGOOD);
      }
    }

    ++totalSums;

    ++dataIt;
    ++emulIt;

    if (dataIt == dataCol->end(currBx) || emulIt == emulCol->end(currBx))
      break;
  }

  if (eventGood)
    hist->Fill(SUMGOOD_S);

  // return a boolean that states whether the jet data in the event is in
  // agreement
  return eventGood;
}

DEFINE_FWK_MODULE (L1TdeStage2CaloLayer2);
