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

void L1TdeStage2CaloLayer2::bookHistograms(
  DQMStore::IBooker &ibooker,
  edm::Run const &,
  edm::EventSetup const&) {

  // DQM directory to store histograms with problematic jets
  ibooker.setCurrentFolder(monitorDir + "/Problematic Jets candidates");

  jetEtData = ibooker.book1D("Problematic Data Jet iEt", "Jet iE_{T}",
			     1400, 0, 1399);
  jetEtaData = ibooker.book1D("Problematic Data Jet iEta", "Jet i#eta",
			  227, -113.5, 113.5);
  jetPhiData = ibooker.book1D("Problematic Data Jet iPhi", "Jet i#phi",
			  288, -0.5, 143.5);
  jetEtEmul = ibooker.book1D("Problematic Emul Jet iEt", "Jet iE_{T}",
			     1400, 0, 1399);
  jetEtaEmul = ibooker.book1D("Problematic Emul Jet iEta", "Jet i#eta",
			  227, -113.5, 113.5);
  jetPhiEmul = ibooker.book1D("Problematic Emul Jet iPhi", "Jet i#phi",
			  288, -0.5, 143.5);

  // DQM directory to store histograms with problematic e/gs
  ibooker.setCurrentFolder(monitorDir + "/Problematic EG candidtes");

  egEtData = ibooker.book1D("Problematic Data Eg iEt", "Eg iE_{T}",
			    1400, 0, 1399);
  egEtaData = ibooker.book1D("Problematic Data Eg iEta", "Eg i#eta",
			     227, -113.5, 113.5);
  egPhiData = ibooker.book1D("Problematic Data Eg iPhi", "Eg i#phi",
			     288, -0.5, 143.5);
  egEtEmul = ibooker.book1D("Problematic Emul Eg iEt", "Eg iE_{T}",
			    1400, 0, 1399);
  egEtaEmul = ibooker.book1D("Problematic Emul Eg iEta", "Eg i#eta",
			     227, -113.5, 113.5);
  egPhiEmul = ibooker.book1D("Problematic Emul Eg iPhi", "Eg i#phi",
			     288, -0.5, 143.5);

  isoEgEtData = ibooker.book1D("Problematic Isolated Data Eg iEt",
			       "Iso Eg iE_{T}", 1400, 0, 1399);
  isoEgEtaData = ibooker.book1D("Problematic Isolated Data Eg iEta",
				"Iso Eg i#eta", 227, -113.5, 113.5);
  isoEgPhiData = ibooker.book1D("Problematic Isolated Data Eg iPhi",
				"Iso Eg i#phi", 288, -0.5, 143.5);
  isoEgEtEmul = ibooker.book1D("Problematic Isolated Emul Eg iEt",
			       "Iso Eg iE_{T}", 1400, 0, 1399);
  isoEgEtaEmul = ibooker.book1D("Problematic Isolated Emul Eg iEta",
				"Iso Eg i#eta", 227, -113.5, 113.5);
  isoEgPhiEmul = ibooker.book1D("Problematic Isolated Emul Eg iPhi",
				"Iso Eg i#phi", 288, -0.5, 143.5);

  // DQM directory to store histograms with problematic taus
  ibooker.setCurrentFolder(monitorDir + "/Problematic Tau candidtes");

  tauEtData = ibooker.book1D("Problematic Data Tau iEt", "Tau iE_{T}",
			     1400, 0, 1399);
  tauEtaData = ibooker.book1D("Problematic Data Tau iEta", "Tau i#eta",
			  227, -113.5, 113.5);
  tauPhiData = ibooker.book1D("Problematic Data Tau iPhi", "Tau i#phi",
			  288, -0.5, 143.5);
  tauEtEmul = ibooker.book1D("Problematic Emul Tau iEt", "Tau iE_{T}",
			     1400, 0, 1399);
  tauEtaEmul = ibooker.book1D("Problematic Emul Tau iEta", "Tau i#eta",
			  227, -113.5, 113.5);
  tauPhiEmul = ibooker.book1D("Problematic Emul Tau iPhi", "Tau i#phi",
			  288, -0.5, 143.5);

  isoTauEtData = ibooker.book1D("Problematic Isolated Data Tau iEt",
				"Iso Tau iE_{T}", 1400, 0, 1399);
  isoTauEtaData = ibooker.book1D("Problematic Isolated Data Tau iEta",
				 "Iso Tau i#eta", 227, -113.5, 113.5);
  isoTauPhiData = ibooker.book1D("Problematic Isolated Data Tau iPhi",
				 "Iso Tau i#phi", 288, -0.5, 143.5);
  isoTauEtEmul = ibooker.book1D("Problematic Isolated Emul Tau iEt",
				"Iso Tau iE_{T}", 1400, 0, 1399);
  isoTauEtaEmul = ibooker.book1D("Problematic Isolated Emul Tau iEta",
				 "Iso Tau i#eta", 227, -113.5, 113.5);
  isoTauPhiEmul = ibooker.book1D("Problematic Isolated Emul Tau iPhi",
				 "Iso Tau i#phi", 288, -0.5, 143.5);

  // DQM directory to store histograms with problematic sums
  ibooker.setCurrentFolder(monitorDir + "/Problematic Sums");

  // book ETT type sums
  ettData = ibooker.book1D("Problematic ETT Sum - Data", "ETT iE_{T}",
			   7000, -0.5, 6999.5);
  ettEmul = ibooker.book1D("Problematic ETT Sum - Emulator", "ETT iE_{T}",
			   7000, -0.5, 6999.5);
  ettHFData = ibooker.book1D("Problematic ETTHF Sum - Data", "ETTHF iE_{T}",
			   7000, -0.5, 6999.5);
  ettHFEmul = ibooker.book1D("Problematic ETTHF Sum - Emulator", "ETTHF iE_{T}",
			   7000, -0.5, 6999.5);
  ettEmData = ibooker.book1D("Problematic ETTEM Sum - Data", "ETTEM iE_{T}",
			   7000, -0.5, 6999.5);
  ettEmEmul = ibooker.book1D("Problematic ETTEM Sum - Emulator", "ETTEM iE_{T}",
			   7000, -0.5, 6999.5);

  // book HTT type sums
  httData = ibooker.book1D("Problematic HTT Sum - Data", "HTT iE_{T}",
			   7000, -0.5, 6999.5);
  httEmul = ibooker.book1D("Problematic HTT Sum - Emulator", "HTT iE_{T}",
			   7000, -0.5, 6999.5);
  httHFData = ibooker.book1D("Problematic HTTHF Sum - Data", "HTTHF iE_{T}",
			   7000, -0.5, 6999.5);
  httHFEmul = ibooker.book1D("Problematic HTTHF Sum - Emulator", "HTTHF iE_{T}",
			   7000, -0.5, 6999.5);

  // book MET type sums
  metEtData = ibooker.book1D("Problematic MET Sum Et - Data", "MET iE_{T}",
			     7000, -0.5, 6999.5);
  metEtEmul = ibooker.book1D("Problematic MET Sum Et - Emulator", "MET iE_{T}",
			     7000, -0.5, 6999.5);
  metPhiData = ibooker.book1D("Problematic MET Sum phi - Data", "MET i#phi",
			      1008, -0.5, 1007.5);
  metPhiEmul = ibooker.book1D("Problematic MET Sum phi - Emulator", "MET i#phi",
			      1008, -0.5, 1007.5);

  metHFEtData = ibooker.book1D("Problematic METHF Sum Et - Data",
			       "METHF iE_{T}", 7000, -0.5, 6999.5);
  metHFEtEmul = ibooker.book1D("Problematic METHF Sum Et - Emulator",
			       "METHF iE_{T}", 7000, -0.5, 6999.5);
  metHFPhiData = ibooker.book1D("Problematic METHF Sum phi - Data",
				"METHF i#phi", 1008, -0.5, 1007.5);
  metHFPhiEmul = ibooker.book1D("Problematic METHF Sum phi - Emulator",
				"METHF i#phi", 1008, -0.5, 1007.5);

  // book MHT type sums
  mhtEtData = ibooker.book1D("Problematic MHT Sum Et - Data", "MHT iE_{T}",
			     7000, -0.5, 6999.5);
  mhtEtEmul = ibooker.book1D("Problematic MHT Sum Et - Emulator", "MHT iE_{T}",
			     7000, -0.5, 6999.5);
  mhtPhiData = ibooker.book1D("Problematic MHT Sum phi - Data", "MHT i#phi",
			      1008, -0.5, 1007.5);
  mhtPhiEmul = ibooker.book1D("Problematic MHT Sum phi - Emulator", "MHT i#phi",
			      1008, -0.5, 1007.5);

  mhtHFEtData = ibooker.book1D("Problematic MHTHF Sum Et - Data",
			       "MHTHF iE_{T}", 7000, -0.5, 6999.5);
  mhtHFEtEmul = ibooker.book1D("Problematic MHTHF Sum Et - Emulator",
			       "MHTHF iE_{T}", 7000, -0.5, 6999.5);
  mhtHFPhiData = ibooker.book1D("Problematic MHTHF Sum phi - Data",
				"MHTHF i#phi", 1008, -0.5, 1007.5);
  mhtHFPhiEmul = ibooker.book1D("Problematic MHTHF Sum phi - Emulator",
				"MHTHF i#phi", 1008, -0.5, 1007.5);

  // book minimum bias sums
  mbhfp0Data = ibooker.book1D("Problematic MBHFP0 Sum - Data",
			      "", 16, -0.5, 15.5);
  mbhfp0Emul = ibooker.book1D("Problematic MBHFP0 Sum - Emulator",
			      "", 16, -0.5, 15.5);
  mbhfm0Data = ibooker.book1D("Problematic MBHFM0 Sum - Data",
			      "", 16, -0.5, 15.5);
  mbhfm0Emul = ibooker.book1D("Problematic MBHFM0 Sum - Emulator",
			      "", 16, -0.5, 15.5);
  mbhfm1Data = ibooker.book1D("Problematic MBHFM1 Sum - Data",
			      "", 16, -0.5, 15.5);
  mbhfm1Emul = ibooker.book1D("Problematic MBHFM1 Sum - Emulator",
			      "", 16, -0.5, 15.5);
  mbhfp1Data = ibooker.book1D("Problematic MBHFP1 Sum - Data",
			      "", 16, -0.5, 15.5);
  mbhfp1Emul = ibooker.book1D("Problematic MBHFP1 Sum - Emulator",
			      "", 16, -0.5, 15.5);

  // book tower count sums
  towCountData = ibooker.book1D("Problematic Tower Count Sum - Data",
				"", 5904, -0.5, 5903.5);
  towCountEmul = ibooker.book1D("Problematic Tower Count Sum - Emulator",
				"", 5904, -0.5, 5903.5);
  // for reference on arguments of book2D, see
  // https://cmssdt.cern.ch/SDT/doxygen/CMSSW_8_0_24/doc/html/df/d26/DQMStore_8cc_source.html#l01070


  // setup the directory where the histograms are to be visualised, value is set
  // in constructor and taken from python configuration file for module
  ibooker.setCurrentFolder(monitorDir + "/expert");


  // Jet energy in MP firmware is stored in 16 bits which sets the range of
  // jet energy to 2^16 * 0.5 GeV = 32768 GeV (65536 hardware units)
  // --- this is only for MP jets, the demux jets have much decreased precision
  // --- and this should be replaced

  // the index of the first bin in histogram should match value of first enum
  agreementSummary = ibooker.book1D(
    "CaloL2 Object Agreement Summary",
    "CaloL2 event-by-event object agreement fractions", 10, 1, 11);

  agreementSummary->getTH1F()->GetXaxis()->SetBinLabel(EVENTGOOD,
						       "good events");
  agreementSummary->getTH1F()->GetXaxis()->SetBinLabel(NEVENTS,
						       "total events");
  agreementSummary->getTH1F()->GetXaxis()->SetBinLabel(NJETS_S, "total jets");
  agreementSummary->getTH1F()->GetXaxis()->SetBinLabel(JETGOOD_S, "good jets");
  agreementSummary->getTH1F()->GetXaxis()->SetBinLabel(NEGS_S, "total e/gs");
  agreementSummary->getTH1F()->GetXaxis()->SetBinLabel(EGGOOD_S, "good e/gs");
  agreementSummary->getTH1F()->GetXaxis()->SetBinLabel(NTAUS_S, "total taus");
  agreementSummary->getTH1F()->GetXaxis()->SetBinLabel(TAUGOOD_S, "good taus");
  agreementSummary->getTH1F()->GetXaxis()->SetBinLabel(NSUMS_S, "total sums");
  agreementSummary->getTH1F()->GetXaxis()->SetBinLabel(SUMGOOD_S, "good sums");

  jetSummary = ibooker.book1D(
    "Jet Agreement Summary", "Jet Agreement Summary", 4, 1, 5);
  jetSummary->getTH1F()->GetXaxis()->SetBinLabel(NJETS, "total jets");
  jetSummary->getTH1F()->GetXaxis()->SetBinLabel(JETGOOD, "good jets");
  jetSummary->getTH1F()->GetXaxis()->SetBinLabel(JETPOSOFF,
						 "jets pos off only");
  jetSummary->getTH1F()->GetXaxis()->SetBinLabel(JETETOFF, "jets Et off only ");

  egSummary = ibooker.book1D(
    "EG Agreement Summary", "EG Agreement Summary", 8, 1, 9);
  egSummary->getTH1F()->GetXaxis()->SetBinLabel(NEGS, "total non-iso e/gs");
  egSummary->getTH1F()->GetXaxis()->SetBinLabel(EGGOOD, "good non-iso e/gs");
  egSummary->getTH1F()->GetXaxis()->SetBinLabel(EGPOSOFF,
						"non-iso e/gs pos off");
  egSummary->getTH1F()->GetXaxis()->SetBinLabel(EGETOFF, "non-iso e/gs Et off");
  egSummary->getTH1F()->GetXaxis()->SetBinLabel(NISOEGS, "total iso e/gs");
  egSummary->getTH1F()->GetXaxis()->SetBinLabel(ISOEGGOOD, "good iso e/gs");
  egSummary->getTH1F()->GetXaxis()->SetBinLabel(ISOEGPOSOFF,
						"iso e/gs pos off");
  egSummary->getTH1F()->GetXaxis()->SetBinLabel(ISOEGETOFF, "iso e/gs Et off");

  tauSummary = ibooker.book1D(
    "Tau Agreement Summary", "Tau Agreement Summary", 8, 1, 9);
  tauSummary->getTH1F()->GetXaxis()->SetBinLabel(NTAUS, "total taus");
  tauSummary->getTH1F()->GetXaxis()->SetBinLabel(TAUGOOD, "good non-iso taus");
  tauSummary->getTH1F()->GetXaxis()->SetBinLabel(TAUPOSOFF,
						 "non-iso taus pos off");
  tauSummary->getTH1F()->GetXaxis()->SetBinLabel(TAUETOFF,
						 "non-iso taus Et off");
  tauSummary->getTH1F()->GetXaxis()->SetBinLabel(NISOTAUS, "total iso taus");
  tauSummary->getTH1F()->GetXaxis()->SetBinLabel(ISOTAUGOOD, "good iso taus");
  tauSummary->getTH1F()->GetXaxis()->SetBinLabel(ISOTAUPOSOFF,
						 "iso taus pos off");
  tauSummary->getTH1F()->GetXaxis()->SetBinLabel(ISOTAUETOFF,
						 "iso taus Et off");
  sumSummary = ibooker.book1D(
    "Energy Sum Agreement Summary", "Sum Agreement Summary", 14, 1, 15);
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(NSUMS, "total sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(SUMGOOD, "good sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(NETTSUMS, "total ETT sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(ETTSUMGOOD, "good ETT sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(NHTTSUMS, "total HTT sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(HTTSUMGOOD, "good HTT sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(NMETSUMS, "total MET sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(METSUMGOOD, "good MET sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(NMHTSUMS, "total MHT sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(MHTSUMGOOD, "good MHT sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(NMBHFSUMS, "total MBHF sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(MBHFSUMGOOD, "good MBHF sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(NTOWCOUNTS,
						 "total TowCount sums");
  sumSummary->getTH1F()->GetXaxis()->SetBinLabel(TOWCOUNTGOOD,
						 "good TowCount sums");

  // high level directory
  ibooker.setCurrentFolder(monitorDir);

  problemSummary = ibooker.book1D(
    "Problem Summary", "Problematic Event Summary", 8, 1, 9);
  problemSummary->getTH1F()->GetXaxis()->SetBinLabel(NEVENTS_P, "total events");
  problemSummary->getTH1F()->GetXaxis()->SetBinLabel(
    JETCOLLSIZE, "jet collection size");
  problemSummary->getTH1F()->GetXaxis()->SetBinLabel(
    EGCOLLSIZE, "eg collection size");
  problemSummary->getTH1F()->GetXaxis()->SetBinLabel(
    TAUCOLLSIZE, "tau collection size");
  problemSummary->getTH1F()->GetXaxis()->SetBinLabel(
    JETMISMATCH, "jet mismatch");
  problemSummary->getTH1F()->GetXaxis()->SetBinLabel(EGMISMATCH, "eg mismatch");
  problemSummary->getTH1F()->GetXaxis()->SetBinLabel(
    TAUMISMATCH, "tau mismatch");
  problemSummary->getTH1F()->GetXaxis()->SetBinLabel(
    SUMMISMATCH, "sum mismatch");
}
void L1TdeStage2CaloLayer2::analyze (
  const edm::Event& e,
  const edm::EventSetup & c) {

  if (count > countLimit)
    exit(1);

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

  // edm::Handle<l1t::CaloTowerBxCollection> towDataCol;
  // edm::Handle<l1t::CaloTowerBxCollection> towEmulCol;

  // e.getByToken(calol2TowCollectionData, towDataCol);
  // e.getByToken(calol2TowCollectionEmul, towEmulCol);

  // std::cout << "meh: data tow col size: " << towDataCol->size()
  // 	    << " \t emul tow col size: "  //<< towEmulCol->size() << std::endl;
  // 	    << std::endl;
  // exit(1);

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

  TH1F * agreementHist = agreementSummary->getTH1F();

  l1t::EGammaBxCollection::const_iterator dataEGIt = egDataCol->begin(currBx);
  l1t::EGammaBxCollection::const_iterator emulEGIt = egEmulCol->begin(currBx);

  l1t::TauBxCollection::const_iterator dataTauIt = tauDataCol->begin(currBx);
  l1t::TauBxCollection::const_iterator emulTauIt = tauEmulCol->begin(currBx);

  l1t::EtSumBxCollection::const_iterator dataSumIt = sumDataCol->begin(currBx);
  l1t::EtSumBxCollection::const_iterator emulSumIt = sumEmulCol->begin(currBx);

  std::cout << "meh: processing event " << e.id() << " (" << count << ")"
   	    << " -------------------- "
   	    << std::endl;

  if (!compareJets(jetDataCol, jetEmulCol)) {
    std::cout << "meh: jet problem" << std::endl;
    eventGood = false;
  }

  if (!compareEGs(egDataCol, egEmulCol)) {
    std::cout << "meh: eg problem" << std::endl;
    eventGood = false;
  }

  if (!compareTaus(tauDataCol, tauEmulCol)) {
    std::cout << "meh: tau problem" << std::endl;
    eventGood = false;
  }

  if (!compareSums(sumDataCol, sumEmulCol)) {
    std::cout << "meh: sum problem" << std::endl;
    eventGood = false;
  }

  /**
     Questions:
     - what could make the data and emul bx ranges to be different?
     - how can I confirm that the emulator data is being filled?
  */

  if (eventGood) {
    agreementHist->Fill(EVENTGOOD);
  }

  agreementHist->Fill(NEVENTS);
  problemSummary->getTH1F()->Fill(NEVENTS_P);

  ++count;
}

// comparison method for jets
bool L1TdeStage2CaloLayer2::compareJets(
  const edm::Handle<l1t::JetBxCollection> & dataCol,
  const edm::Handle<l1t::JetBxCollection> & emulCol)
{
  bool eventGood = true;
  bool debug = true;

  l1t::JetBxCollection::const_iterator dataIt = dataCol->begin(currBx);
  l1t::JetBxCollection::const_iterator emulIt = emulCol->begin(currBx);

  TH1F * objEtHistData = jetEtData->getTH1F();
  TH1F * objPhiHistData = jetPhiData->getTH1F();
  TH1F * objEtaHistData = jetEtaData->getTH1F();

  TH1F * objEtHistEmul = jetEtEmul->getTH1F();
  TH1F * objPhiHistEmul = jetPhiEmul->getTH1F();
  TH1F * objEtaHistEmul = jetEtaEmul->getTH1F();

  TH1F * objSummaryHist = jetSummary->getTH1F();
  TH1F * summaryHist = agreementSummary->getTH1F();

  // process jets
  if (dataCol->size(currBx) != emulCol->size(currBx)) {

    std::cout << "meh: jet size problem" << std::endl;

    if (dataCol->size(currBx) < emulCol->size(currBx)) {

      std::cout << "meh: more emul jets" << std::endl;

      if (dataCol->size(currBx) < 1) {
	return false;
      }

      while (true) {
	objEtHistData->Fill(dataIt->hwPt());
	objEtaHistData->Fill(dataIt->hwEta());
	objPhiHistData->Fill(dataIt->hwPhi());

	++dataIt;

	if (dataIt == dataCol->end(currBx))
	  break;
      }
    } else {

      std::cout << "meh: more data jets (" << dataCol->size(0)
		<< " vs " << emulCol->size(0) << ")" << std::endl;

      if (emulCol->size(currBx) < 1) {
	return false;
      }

      while (true) {

	objEtHistEmul->Fill(emulIt->hwPt());
	objEtaHistEmul->Fill(emulIt->hwEta());
	objPhiHistEmul->Fill(emulIt->hwPhi());

 	// std::cout << "meh: Jet Et  = " << emulIt->hwPt() << std::endl;
	// std::cout << "meh: Jet Eta = " << emulIt->hwEta() << std::endl;
	// std::cout << "meh: Jet phi = " << emulIt->hwPhi() << std::endl;

	++emulIt;

	if (emulIt == emulCol->end(currBx))
	  break;
      }

      while (true) {

	objEtHistEmul->Fill(dataIt->hwPt());
	objEtaHistEmul->Fill(dataIt->hwEta());
	objPhiHistEmul->Fill(dataIt->hwPhi());

 	// std::cout << "meh: Jet Et  = " << dataIt->hwPt() << std::endl;
	// std::cout << "meh: Jet Eta = " << dataIt->hwEta() << std::endl;
	// std::cout << "meh: Jet phi = " << dataIt->hwPhi() << std::endl;

	++dataIt;

	if (dataIt == dataCol->end(currBx))
	  break;
      }
    }

    problemSummary->getTH1F()->Fill(JETCOLLSIZE);
    return false;
  }

  int nJets = 0;
  if (dataIt != dataCol->end(currBx) ||
      emulIt != emulCol->end(currBx)) {
    while(true) {

      ++nJets;

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
      if (etGood && posGood) {
	summaryHist->Fill(JETGOOD_S);
	objSummaryHist->Fill(JETGOOD);
      } else {
	objEtHistData->Fill(dataIt->hwPt());
	objEtaHistData->Fill(dataIt->hwEta());
	objPhiHistData->Fill(dataIt->hwPhi());

	objEtHistEmul->Fill(emulIt->hwPt());
	objEtaHistEmul->Fill(emulIt->hwEta());
	objPhiHistEmul->Fill(emulIt->hwPhi());

	problemSummary->getTH1F()->Fill(JETMISMATCH);

	if (debug) {
	  std::cout << "meh: ---" << std::endl;
	  std::cout << "meh: data jet Et = " << dataIt->hwPt() << std::endl;
	  std::cout << "meh: emul jet Et = " << emulIt->hwPt() << std::endl;
	  std::cout << "meh: data jet phi = " << dataIt->hwPhi() << std::endl;
	  std::cout << "meh: emul jet phi = " << emulIt->hwPhi() << std::endl;
	  std::cout << "meh: data jet eta = " << dataIt->hwEta() << std::endl;
	  std::cout << "meh: emul jet eta = " << emulIt->hwEta() << std::endl;
	  std::cout << "meh: ---" << std::endl;
	}
      }

      // if only position agrees
      if (posGood && !etGood) {
	objSummaryHist->Fill(JETETOFF);

	if (debug) {
	  std::cout << "meh: jet energy pooped" << std::endl;
	  std::cout << "meh: ---" << std::endl;
	  std::cout << "meh: data jet Et = " << dataIt->hwPt() << std::endl;
	  std::cout << "meh: emul jet Et = " << emulIt->hwPt() << std::endl;
	  std::cout << "meh: data jet phi = " << dataIt->hwPhi() << std::endl;
	  std::cout << "meh: emul jet phi = " << emulIt->hwPhi() << std::endl;
	  std::cout << "meh: data jet eta = " << dataIt->hwEta() << std::endl;
	  std::cout << "meh: emul jet eta = " << emulIt->hwEta() << std::endl;
	  std::cout << "meh: ---" << std::endl;
	}
      }

      // if only energy agrees
      if (!posGood && etGood) {
	objSummaryHist->Fill(JETPOSOFF);

	if (debug) {
	  std::cout << "meh: jet position pooped" << std::endl;
	  std::cout << "meh: ---" << std::endl;
	  std::cout << "meh: data jet Et = " << dataIt->hwPt() << std::endl;
	  std::cout << "meh: emul jet Et = " << emulIt->hwPt() << std::endl;
	  std::cout << "meh: data jet phi = " << dataIt->hwPhi() << std::endl;
	  std::cout << "meh: emul jet phi = " << emulIt->hwPhi() << std::endl;
	  std::cout << "meh: data jet eta = " << dataIt->hwEta() << std::endl;
	  std::cout << "meh: emul jet eta = " << emulIt->hwEta() << std::endl;
	  std::cout << "meh: ---" << std::endl;
	}
      }

      // keep track of jets
      summaryHist->Fill(NJETS_S);
      objSummaryHist->Fill(NJETS);

      // increase position of pointers
      ++dataIt;
      ++emulIt;

      if (dataIt == dataCol->end(currBx) ||
	  emulIt == emulCol->end(currBx))
	break;
    }
  } else {
    if (dataCol->size(currBx) != 0 || emulCol->size(currBx) != 0)
      return false;
  }

  // return a boolean that states whether the jet data in the event is in
  // agreement
  return eventGood;
}

// comparison method for e/gammas
bool L1TdeStage2CaloLayer2::compareEGs(
  const edm::Handle<l1t::EGammaBxCollection> & dataCol,
  const edm::Handle<l1t::EGammaBxCollection> & emulCol)
{
  bool eventGood = true;
  bool debug = true;

  l1t::EGammaBxCollection::const_iterator dataIt = dataCol->begin(currBx);
  l1t::EGammaBxCollection::const_iterator emulIt = emulCol->begin(currBx);

  TH1F * isoObjEtHistData = isoEgEtData->getTH1F();
  TH1F * isoObjPhiHistData = isoEgPhiData->getTH1F();
  TH1F * isoObjEtaHistData = isoEgEtaData->getTH1F();
  TH1F * isoObjEtHistEmul = isoEgEtEmul->getTH1F();
  TH1F * isoObjPhiHistEmul = isoEgPhiEmul->getTH1F();
  TH1F * isoObjEtaHistEmul = isoEgEtaEmul->getTH1F();

  TH1F * objEtHistData = egEtData->getTH1F();
  TH1F * objPhiHistData = egPhiData->getTH1F();
  TH1F * objEtaHistData = egEtaData->getTH1F();
  TH1F * objEtHistEmul = egEtEmul->getTH1F();
  TH1F * objPhiHistEmul = egPhiEmul->getTH1F();
  TH1F * objEtaHistEmul = egEtaEmul->getTH1F();

  TH1F * objSummaryHist = egSummary->getTH1F();
  TH1F * summaryHist = agreementSummary->getTH1F();

  // check length of collections
  if (dataCol->size(currBx) != emulCol->size(currBx)) {

    if (dataCol->size(currBx) < emulCol->size(currBx)) {

      std::cout << "meh: more data egs" << std::endl;

      if (dataCol->size(currBx) < 1)
	return false;

      // if there are more events in data loop over the data collection
      while (true) {

	// Populate different set of histograms if object is solated
	if (dataIt->hwIso()) {
	  isoObjEtHistData->Fill(dataIt->hwPt());
	  isoObjEtaHistData->Fill(dataIt->hwEta());
	  isoObjPhiHistData->Fill(dataIt->hwPhi());
	} else {
	  objEtHistData->Fill(dataIt->hwPt());
	  objEtaHistData->Fill(dataIt->hwEta());
	  objPhiHistData->Fill(dataIt->hwPhi());
	}

	++dataIt;

	if (dataIt == dataCol->end(currBx))
	  break;
      }
    } else {

      std::cout << "meh: more emul egs" << std::endl;
      if (emulCol->size(currBx) < 1) {
	return false;
      }

      while (true) {

	// Populate different set of histograms if object is solated

	if(emulIt->hwIso()) {
	  isoObjEtHistEmul->Fill(emulIt->hwPt());
	  isoObjEtaHistEmul->Fill(emulIt->hwEta());
	  isoObjPhiHistEmul->Fill(emulIt->hwPhi());
	} else {
	  objEtHistEmul->Fill(emulIt->hwPt());
	  objEtaHistEmul->Fill(emulIt->hwEta());
	  objPhiHistEmul->Fill(emulIt->hwPhi());
	}

	++emulIt;

	if (emulIt == emulCol->end(currBx))
	  break;
      }
    }

    problemSummary->getTH1F()->Fill(EGCOLLSIZE);
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
	// std::cout << "meh: eg Et mismatch" << std::endl;
      }

      // object position mismatch
      if (dataIt->hwPhi() != emulIt->hwPhi()) {
	posGood = false;
	eventGood = false;
	// std::cout << "meh: eg phi mismatch" << std::endl;
      }
      if (dataIt->hwEta() != emulIt->hwEta()) {
	posGood = false;
	eventGood = false;
	// std::cout << "meh: eg Eta mismatch" << std::endl;
      }

      // if both position and energy agree, object is good
      if (posGood && etGood) {
	summaryHist->Fill(EGGOOD_S);

	if (iso) {
	  objSummaryHist->Fill(ISOEGGOOD);
	} else {
	  objSummaryHist->Fill(EGGOOD);
	}

      } else {

	if (iso) {
	  isoObjEtHistData->Fill(dataIt->hwPt());
	  isoObjEtaHistData->Fill(dataIt->hwEta());
	  isoObjPhiHistData->Fill(dataIt->hwPhi());

	  isoObjEtHistEmul->Fill(emulIt->hwPt());
	  isoObjEtaHistEmul->Fill(emulIt->hwEta());
	  isoObjPhiHistEmul->Fill(emulIt->hwPhi());
	} else {
	  objEtHistData->Fill(dataIt->hwPt());
	  objEtaHistData->Fill(dataIt->hwEta());
	  objPhiHistData->Fill(dataIt->hwPhi());

	  objEtHistEmul->Fill(emulIt->hwPt());
	  objEtaHistEmul->Fill(emulIt->hwEta());
	  objPhiHistEmul->Fill(emulIt->hwPhi());
	}

	if (debug) {
	  std::cout << "meh: eg is pooped" << std::endl;
	  std::cout << "meh: ------------" << std::endl;
	  std::cout << "meh: data eg Et = " << dataIt->hwPt() << std::endl;
	  std::cout << "meh: emul eg Et = " << emulIt->hwPt() << std::endl;
	  std::cout << "meh: data eg Phi = " << dataIt->hwPhi() << std::endl;
	  std::cout << "meh: emul eg Phi = " << emulIt->hwPhi() << std::endl;
	  std::cout << "meh: data eg Eta = " << dataIt->hwEta() << std::endl;
	  std::cout << "meh: emul eg Eta = " << emulIt->hwEta() << std::endl;
	  std::cout << "meh: ------------" << std::endl;
	}

	problemSummary->getTH1F()->Fill(EGMISMATCH);
      }

      // if only position agrees
      if (posGood && !etGood) {
	if (iso) {
	  objSummaryHist->Fill(ISOEGETOFF);
	} else {
	  objSummaryHist->Fill(EGETOFF);
	}
      }

      // if only energy agrees
      if (!posGood && etGood) {
	if (iso) {
	  objSummaryHist->Fill(ISOEGPOSOFF);
	} else {
	  objSummaryHist->Fill(EGPOSOFF);
	}
      }

      // keep track of number of objects
      if (iso) {
	objSummaryHist->Fill(NISOEGS);
      } else {
	objSummaryHist->Fill(NEGS);
      }
      summaryHist->Fill(NEGS_S);

      // increment position of pointers
      ++dataIt;
      ++emulIt;

      if (dataIt == dataCol->end(currBx) ||
	  emulIt == emulCol->end(currBx))
	break;
    }
  } else {
    if (dataCol->size(currBx) != 0 || emulCol->size(currBx) != 0)
      return false;
  }

  // return a boolean that states whether the jet data in the event is in
  // agreement
  return eventGood;
}

// comparison method for taus
bool L1TdeStage2CaloLayer2::compareTaus(
  const edm::Handle<l1t::TauBxCollection> & dataCol,
  const edm::Handle<l1t::TauBxCollection> & emulCol)
{
  bool eventGood = true;
  bool debug = true;

  l1t::TauBxCollection::const_iterator dataIt = dataCol->begin(currBx);
  l1t::TauBxCollection::const_iterator emulIt = emulCol->begin(currBx);

  TH1F * isoObjEtHistData = isoTauEtData->getTH1F();
  TH1F * isoObjPhiHistData = isoTauPhiData->getTH1F();
  TH1F * isoObjEtaHistData = isoTauEtaData->getTH1F();
  TH1F * isoObjEtHistEmul = isoTauEtEmul->getTH1F();
  TH1F * isoObjPhiHistEmul = isoTauPhiEmul->getTH1F();
  TH1F * isoObjEtaHistEmul = isoTauEtaEmul->getTH1F();

  TH1F * objEtHistData = tauEtData->getTH1F();
  TH1F * objPhiHistData = tauPhiData->getTH1F();
  TH1F * objEtaHistData = tauEtaData->getTH1F();
  TH1F * objEtHistEmul = tauEtEmul->getTH1F();
  TH1F * objPhiHistEmul = tauPhiEmul->getTH1F();
  TH1F * objEtaHistEmul = tauEtaEmul->getTH1F();

  TH1F * objSummaryHist = tauSummary->getTH1F();
  TH1F * summaryHist = agreementSummary->getTH1F();

  // check length of collections
  if (dataCol->size(currBx) != emulCol->size(currBx)) {

    if (dataCol->size(currBx) < emulCol->size(currBx)) {

      std::cout << "meh: more data taus" << std::endl;

      if (dataCol->size(currBx) < 1)
	return false;

      // if there are more events in data loop over the data collection
      while (true) {

	// Populate different set of histograms if object is solated

	if (dataIt->hwIso()) {
	  isoObjEtHistData->Fill(dataIt->hwPt());
	  isoObjEtaHistData->Fill(dataIt->hwEta());
	  isoObjPhiHistData->Fill(dataIt->hwPhi());
	} else {
	  objEtHistData->Fill(dataIt->hwPt());
	  objEtaHistData->Fill(dataIt->hwEta());
	  objPhiHistData->Fill(dataIt->hwPhi());
	}

	++dataIt;

	if (dataIt == dataCol->end(currBx))
	  break;
      }
    } else {

      std::cout << "meh: more emul taus" << std::endl;
      if (emulCol->size(currBx) < 1)
	return false;

      while (true) {

	// Populate different set of histograms if object is solated

	if(emulIt->hwIso()) {
	  isoObjEtHistEmul->Fill(emulIt->hwPt());
	  isoObjEtaHistEmul->Fill(emulIt->hwEta());
	  isoObjPhiHistEmul->Fill(emulIt->hwPhi());
	} else {
	  objEtHistEmul->Fill(emulIt->hwPt());
	  objEtaHistEmul->Fill(emulIt->hwEta());
	  objPhiHistEmul->Fill(emulIt->hwPhi());
	}

	++emulIt;

	if (emulIt == emulCol->end(currBx))
	  break;
      }
    }

    problemSummary->getTH1F()->Fill(TAUCOLLSIZE);
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
      if (posGood && etGood) {
	summaryHist->Fill(TAUGOOD_S);

	if (iso) {
	  objSummaryHist->Fill(ISOTAUGOOD);
	} else {
	  objSummaryHist->Fill(TAUGOOD);
	}
      } else {

	if (iso) {
	  isoObjEtHistData->Fill(dataIt->hwPt());
	  isoObjEtaHistData->Fill(dataIt->hwEta());
	  isoObjPhiHistData->Fill(dataIt->hwPhi());

	  isoObjEtHistEmul->Fill(emulIt->hwPt());
	  isoObjEtaHistEmul->Fill(emulIt->hwEta());
	  isoObjPhiHistEmul->Fill(emulIt->hwPhi());

	} else {
	  objEtHistData->Fill(dataIt->hwPt());
	  objEtaHistData->Fill(dataIt->hwEta());
	  objPhiHistData->Fill(dataIt->hwPhi());

	  objEtHistEmul->Fill(emulIt->hwPt());
	  objEtaHistEmul->Fill(emulIt->hwEta());
	  objPhiHistEmul->Fill(emulIt->hwPhi());
	}

	if (debug) {
	  std::cout << "meh: tau is pooped" << std::endl;
	  std::cout << "meh: ------------" << std::endl;
	  std::cout << "meh: data tau Et = " << dataIt->hwPt() << std::endl;
	  std::cout << "meh: emul tau Et = " << emulIt->hwPt() << std::endl;
	  std::cout << "meh: data tau Phi = " << dataIt->hwPhi() << std::endl;
	  std::cout << "meh: emul tau Phi = " << emulIt->hwPhi() << std::endl;
	  std::cout << "meh: data tau Eta = " << dataIt->hwEta() << std::endl;
	  std::cout << "meh: emul tau Eta = " << emulIt->hwEta() << std::endl;
	  std::cout << "meh: ------------" << std::endl;
	}

	problemSummary->getTH1F()->Fill(TAUMISMATCH);
      }

      // if only position agrees
      if (posGood && !etGood) {
	if (iso) {
	  objSummaryHist->Fill(ISOTAUETOFF);
	} else {
	  objSummaryHist->Fill(TAUETOFF);
	}
      }

      // if only energy agrees
      if (!posGood && etGood) {
	if (iso) {
	  objSummaryHist->Fill(ISOTAUPOSOFF);
	} else {
	  objSummaryHist->Fill(TAUPOSOFF);
	}
      }

      // keep track of number of objects
      if (iso) {
	objSummaryHist->Fill(NISOTAUS);
      } else {
	objSummaryHist->Fill(NTAUS);
      }

      summaryHist->Fill(NTAUS_S);

      // increment position of pointers
      ++dataIt;
      ++emulIt;

      if (dataIt == dataCol->end(currBx) ||
	  emulIt == emulCol->end(currBx))
	break;
    }
  } else {
    if (dataCol->size(currBx) != 0 || emulCol->size(currBx) != 0)
      return false;
  }

  // return a boolean that states whether the jet data in the event is in
  // agreement
  return eventGood;
}

// comparison method for sums
bool L1TdeStage2CaloLayer2::compareSums(
  const edm::Handle<l1t::EtSumBxCollection> & dataCol,
  const edm::Handle<l1t::EtSumBxCollection> & emulCol)
{
  bool eventGood = true;
  bool debug = true;

  bool etGood = true;
  bool phiGood = true;

  double dataEt = 0;
  double emulEt = 0;
  double dataPhi = 0;
  double emulPhi = 0;

  l1t::EtSumBxCollection::const_iterator dataIt = dataCol->begin(currBx);
  l1t::EtSumBxCollection::const_iterator emulIt = emulCol->begin(currBx);

  TH1F * objSummaryHist = sumSummary->getTH1F();
  TH1F * summaryHist = agreementSummary->getTH1F();
  TH1F * problemHist = problemSummary->getTH1F();

  while(true) {

    // It should be possible to implement this with a switch statement
    etGood = true;
    phiGood = true;

    // ETT
    if (l1t::EtSum::EtSumType::kTotalEt == dataIt->getType()) {

      dataEt = dataIt->hwPt();
      emulEt = emulIt->hwPt();

      objSummaryHist->Fill(NETTSUMS);

      if (dataEt != emulEt) {
	eventGood = false;

	ettData->getTH1F()->Fill(dataEt);
	ettEmul->getTH1F()->Fill(emulEt);

	// if (debug) {
	//   std::cout << "meh: ETT issue" << std::endl;
	//   std::cout << "meh: data ETT = " << dataEt << std::endl;
	//   std::cout << "meh: emul ETT = " << emulEt << std::endl;
	// }
      } else {
	summaryHist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(ETTSUMGOOD);
      }

      if (debug) {
	std::cout << "meh: ETT       | ";
	if (dataEt != emulEt)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout << dataEt << "\t" << emulEt;
	std::cout << std::endl;
      }
    }

    // // ETTHF
    // if (l1t::EtSum::EtSumType::kTotalEtHF == dataIt->getType()) {

    //   objSummaryHist->Fill(NETTSUMS);
    //   summaryHist->Fill(NSUMS_S);

    //   if (dataEt != emulEt) {
    // 	eventGood = false;

    // 	ettHFData->getTH1F()->Fill(dataEt);
    // 	ettHFEmul->getTH1F()->Fill(emulEt);

    // 	// if (debug) {
    // 	//   std::cout << "meh: ETTHF issue" << std::endl;
    // 	//   std::cout << "meh: data ETTHF = " << dataEt << std::endl;
    // 	//   std::cout << "meh: emul ETTHF = " << emulEt << std::endl;
    // 	// }

    //   } else {
    // 	summaryHist->Fill(SUMGOOD_S);
    // 	objSummaryHist->Fill(SUMGOOD);
    // 	objSummaryHist->Fill(ETTSUMGOOD);
    //   }

    //   if (debug) {
    // 	std::cout << "meh: ETTHF = " << dataEt << "\t" << emulEt
    // 		  << std::endl;
    //   }
    // }

    // ETTEM
    if (l1t::EtSum::EtSumType::kTotalEtEm == dataIt->getType()) {

      dataEt = dataIt->hwPt();
      emulEt = emulIt->hwPt();

      objSummaryHist->Fill(NETTSUMS);
      //summaryHist->Fill(NSUMS_S);

      if (dataEt != emulEt) {
	eventGood = false;
	ettEmData->getTH1F()->Fill(dataEt);
	ettEmEmul->getTH1F()->Fill(emulEt);

	// if (debug) {
	//   std::cout << "meh: ETTEM issue" << std::endl;
	//   std::cout << "meh: data ETTEM = " << dataEt << std::endl;
	//   std::cout << "meh: emul ETTEM = " << emulEt << std::endl;
	// }
      } else {
	summaryHist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(ETTSUMGOOD);
      }

      if (debug) {
	std::cout << "meh: ETTEM     | ";
	if (dataEt != emulEt)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout << dataEt << "\t" << emulEt;
	std::cout << std::endl;
      }
    }

    // HTT
    if (l1t::EtSum::EtSumType::kTotalHt == dataIt->getType()) {

      dataEt = dataIt->hwPt();
      emulEt = emulIt->hwPt();

      objSummaryHist->Fill(NHTTSUMS);
      // summaryHist->Fill(NSUMS_S);

      if (dataEt != emulEt) {
	eventGood = false;
	httData->getTH1F()->Fill(dataEt);
	httEmul->getTH1F()->Fill(emulEt);

	// if (debug) {
	//   std::cout << "meh: HTT issue" << std::endl;
	//   std::cout << "meh: data HTT = " << dataEt << std::endl;
	//   std::cout << "meh: emul HTT = " << emulEt << std::endl;
	// }
      } else {
	summaryHist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(HTTSUMGOOD);
      }

      if (debug) {
	std::cout << "meh: HTT       | ";
	if (dataEt != emulEt)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout << dataEt << "\t" << emulEt;
	std::cout << std::endl;
      }
    }

    // // HTTHF
    // if (l1t::EtSum::EtSumType::kTotalHtHF == dataIt->getType()) {

    //   dataEt = dataIt->hwPt();
    //   emulEt = emulIt->hwPt();

    //   objSummaryHist->Fill(NHTTSUMS);
    //   summaryHist->Fill(NSUMS_S);

    //   if (dataEt != emulEt) {
    // 	eventGood = false;
    // 	httHFData->getTH1F()->Fill(dataEt);
    // 	httHFEmul->getTH1F()->Fill(emulEt);

    // 	// if (debug) {
    // 	//   std::cout << "meh: HTTHF issue" << std::endl;
    // 	//   std::cout << "meh: data HTTHF = " << dataEt << std::endl;
    // 	//   std::cout << "meh: emul HTTHF = " << emulEt << std::endl;
    // 	// }

    //   } else {
    // 	summaryHist->Fill(SUMGOOD_S);
    // 	objSummaryHist->Fill(SUMGOOD);
    // 	objSummaryHist->Fill(HTTSUMGOOD);
    //   }

    //   if (debug) {
    // 	std::cout << "meh: HTTHF     | " << dataEt << "\t"
    // 		  << emulEt << " | ";
    // 	std::cout << std::endl;
    //   }
    // }

    // MET
    if (l1t::EtSum::EtSumType::kMissingEt == dataIt->getType()
	&& dataIt->hwPt() != 0) {

      dataEt = dataIt->hwPt();
      emulEt = emulIt->hwPt();

      dataPhi = dataIt->hwPhi();
      emulPhi = emulIt->hwPhi();

      objSummaryHist->Fill(NMETSUMS);
      // summaryHist->Fill(NSUMS_S);

      if (dataEt != emulEt) {
	etGood = false;
	eventGood = false;
      }

      if (dataPhi != emulPhi) {
	phiGood = false;
	eventGood = false;
      }

      if (etGood && phiGood) {
	summaryHist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(METSUMGOOD);
      } else {
	metEtData->getTH1F()->Fill(dataEt);
	metPhiData->getTH1F()->Fill(dataPhi);
	metEtEmul->getTH1F()->Fill(emulEt);
	metPhiEmul->getTH1F()->Fill(emulPhi);

	// if (debug) {
	//   std::cout << "meh: MET issue" << std::endl;
	//   std::cout << "meh: data MET = " << dataEt << std::endl;
	//   std::cout << "meh: emul MET = " << emulEt << std::endl;
	//   std::cout << "meh: data MET phi = " << dataPhi << std::endl;
	//   std::cout << "meh: emul MET phi = " << emulPhi << std::endl;
	// }
      }

      if (debug) {
	std::cout << "meh: MET       | ";
	if (dataEt != emulEt)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout << dataEt << "\t" << emulEt;
	std::cout << std::endl;
	std::cout << "meh: MET phi   | ";
	if (dataPhi != emulPhi)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout<< dataPhi << "\t" << emulPhi;
	std::cout << std::endl;
      }
    }

    // METHF
    if (l1t::EtSum::EtSumType::kMissingEtHF == dataIt->getType()
	&& dataIt->hwPt() != 0) {

      dataEt = dataIt->hwPt();
      emulEt = emulIt->hwPt();

      dataPhi = dataIt->hwPhi();
      emulPhi = emulIt->hwPhi();

      objSummaryHist->Fill(NMETSUMS);

      if (dataEt != emulEt) {
	etGood = false;
	eventGood = false;
      }

      if (dataPhi != emulPhi) {
	phiGood = false;
	eventGood = false;
      }

      if (etGood && phiGood) {
	summaryHist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(METSUMGOOD);
      } else {
	metHFEtData->getTH1F()->Fill(dataEt);
	metHFPhiData->getTH1F()->Fill(dataPhi);
	metHFEtEmul->getTH1F()->Fill(emulEt);
	metHFPhiEmul->getTH1F()->Fill(emulPhi);

	// if (debug) {
	//   std::cout << "meh: METHF issue" << std::endl;
	//   std::cout << "meh: data METHF = " << dataEt << std::endl;
	//   std::cout << "meh: emul METHF = " << emulEt << std::endl;
	//   std::cout << "meh: data METHF phi = " << dataPhi << std::endl;
	//   std::cout << "meh: emul METHF phi = " << emulPhi << std::endl;
	// }
      }

      if (debug) {
	std::cout << "meh: METHF     | ";
	if (dataEt != emulEt)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout << dataEt << "\t" << emulEt;
	std::cout << std::endl;
	std::cout << "meh: METHF phi | ";
	if (dataPhi != emulPhi)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout << dataPhi << "\t" << emulPhi;
	std::cout << std::endl;
      }
    }

    // MHT
    if (l1t::EtSum::EtSumType::kMissingHt == dataIt->getType()
	&& dataIt->hwPt() != 0) {

      dataEt = dataIt->hwPt();
      emulEt = emulIt->hwPt();

      dataPhi = dataPhi;
      emulPhi = emulIt->hwPhi();

      objSummaryHist->Fill(NMHTSUMS);
      // summaryHist->Fill(NSUMS_S);

      if (dataEt != emulEt) {
	etGood = false;
	eventGood = false;
      }

      if (!(etGood && dataEt == 0)) {
	if (dataPhi != emulPhi) {
	  phiGood = false;
	  eventGood = false;
	}
      }

      if (etGood && phiGood) {
	summaryHist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(MHTSUMGOOD);
      } else {
	mhtEtData->getTH1F()->Fill(dataEt);
	mhtPhiData->getTH1F()->Fill(dataPhi);
	mhtEtEmul->getTH1F()->Fill(emulEt);
	mhtPhiEmul->getTH1F()->Fill(emulPhi);

	// if (debug) {
	//   std::cout << "meh: MHT issue" << std::endl;
	//   std::cout << "meh: data MHT = " << dataEt << std::endl;
	//   std::cout << "meh: emul MHT = " << emulEt << std::endl;
	//   std::cout << "meh: data MHT phi = " << dataPhi << std::endl;
	//   std::cout << "meh: emul MHT phi = " << emulPhi << std::endl;
	// }

	std::cout << "meh: MHT issue" << std::endl;
      }

      if (debug) {
	std::cout << "meh: MHT       | ";
	if (dataEt != emulEt)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout << dataEt << "\t" << emulEt;
	std::cout << std::endl;
	std::cout << "meh: MHT phi   | ";
	if (dataPhi != emulPhi)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout << dataPhi << "\t" << emulPhi;
	std::cout << std::endl;
      }
    }

    // MHTHF
    if (l1t::EtSum::EtSumType::kMissingHtHF == dataIt->getType()
	&& dataIt->hwPt() != 0) {

      dataEt = dataIt->hwPt();
      emulEt = emulIt->hwPt();

      dataPhi = dataPhi;
      emulPhi = emulIt->hwPhi();

      objSummaryHist->Fill(NMHTSUMS);
      // summaryHist->Fill(NSUMS_S);

      if (dataEt != emulEt) {
	phiGood = false;
	eventGood = false;
      }

      if (!(etGood && dataEt == 0)) {
	if (dataPhi != emulPhi) {
	  phiGood = false;
	  eventGood = false;
	}
      }

      if (etGood && phiGood) {
	summaryHist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(MHTSUMGOOD);
      } else {
       	mhtHFEtData->getTH1F()->Fill(dataEt);
	mhtHFPhiData->getTH1F()->Fill(dataPhi);
	mhtHFEtEmul->getTH1F()->Fill(emulEt);
	mhtHFPhiEmul->getTH1F()->Fill(emulPhi);

	// if (debug) {
	//   std::cout << "meh: ----  MHTHF" << std::endl;
	//   std::cout << "meh: data MHTHF = " << dataEt << std::endl;
	//   std::cout << "meh: emul MHTHF = " << emulEt << std::endl;
	//   std::cout << "meh: data MHTHF phi = " << dataPhi << std::endl;
	//   std::cout << "meh: emul MHTHF phi = " << emulPhi << std::endl;
	// }
      }

      if (debug) {
	std::cout << "meh: MHTHF     | ";
	if (dataEt != emulEt)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout  << dataEt << "\t" << emulEt;
	std::cout << std::endl;
	std::cout << "meh: MHTHF phi | ";
	if (dataPhi != emulPhi)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout << dataPhi << "\t" << emulPhi;
	std::cout << std::endl;
      }
    }

    // MBHFP0
    if (l1t::EtSum::EtSumType::kMinBiasHFP0 == dataIt->getType()) {

      dataEt = dataIt->hwPt();
      emulEt = emulIt->hwPt();

      objSummaryHist->Fill(NMBHFSUMS);
      // summaryHist->Fill(NSUMS_S);

      if (dataEt != emulEt) {
	eventGood = false;
	mbhfp0Data->getTH1F()->Fill(dataEt);
	mbhfp0Emul->getTH1F()->Fill(emulEt);

	// if (debug) {
	//   std::cout << "meh: MBHFP0 issue" << std::endl;
	//   std::cout << "meh: data MBHFP0 = " << dataEt << std::endl;
	//   std::cout << "meh: emul MBHFP0 = " << emulEt << std::endl;
	// }

      } else {
	summaryHist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(MBHFSUMGOOD);
      }

      if (debug) {
	std::cout << "meh: MBHFP0    | ";
	if (dataEt != emulEt)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout  << dataEt << "\t" << emulEt;
	std::cout << std::endl;
      }
    }

    // MBHFM0
    if (l1t::EtSum::EtSumType::kMinBiasHFM0 == dataIt->getType()) {

      dataEt = dataIt->hwPt();
      emulEt = emulIt->hwPt();

      objSummaryHist->Fill(NMBHFSUMS);
      // summaryHist->Fill(NSUMS_S);

      if (dataEt != emulEt) {
	eventGood = false;
	mbhfm0Data->getTH1F()->Fill(dataEt);
	mbhfm0Emul->getTH1F()->Fill(emulEt);

	// if (debug) {
	//   std::cout << "meh: MBHFM0 issue" << std::endl;
	//   std::cout << "meh: data MBHFM0 = " << dataEt << std::endl;
	//   std::cout << "meh: emul MBHFM0 = " << emulEt << std::endl;
	// }
      } else {
	summaryHist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(MBHFSUMGOOD);
      }

      if (debug) {
	std::cout << "meh: MBHFM0    | ";
	if (dataEt != emulEt)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout << dataEt << "\t" << emulEt;
	std::cout << std::endl;
      }
    }

    // MBHFP1
    if (l1t::EtSum::EtSumType::kMinBiasHFP1 == dataIt->getType()) {

      dataEt = dataIt->hwPt();
      emulEt = emulIt->hwPt();

      objSummaryHist->Fill(NMBHFSUMS);
      // summaryHist->Fill(NSUMS_S);

      if (dataEt != emulEt) {
	eventGood = false;
	mbhfp1Data->getTH1F()->Fill(dataEt);
	mbhfp1Emul->getTH1F()->Fill(emulEt);

	// if (debug) {
	//   std::cout << "meh: MBHFP1 issue" << std::endl;
	//   std::cout << "meh: data MBHFP1 = " << dataEt << std::endl;
	//   std::cout << "meh: emul MBHFP1 = " << emulEt << std::endl;
	// }
      } else {
	summaryHist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(MBHFSUMGOOD);
      }

      if (debug) {
	std::cout << "meh: MBHFP1    | ";
	if (dataEt != emulEt)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout  << dataEt << "\t" << emulEt;
	std::cout << std::endl;
      }
    }

    // MBHFM1
    if (l1t::EtSum::EtSumType::kMinBiasHFM1 == dataIt->getType()) {

      dataEt = dataIt->hwPt();
      emulEt = emulIt->hwPt();

      objSummaryHist->Fill(NMBHFSUMS);
      // summaryHist->Fill(NSUMS_S);

      if (dataEt != emulEt) {
	eventGood = false;
	mbhfm1Data->getTH1F()->Fill(dataEt);
	mbhfm1Emul->getTH1F()->Fill(emulEt);

	// if (debug) {
	//   std::cout << "meh: MBHFM1 issue" << std::endl;
	//   std::cout << "meh: data MBHFM1 = " << dataEt << std::endl;
	//   std::cout << "meh: emul MBHFM1 = " << emulEt << std::endl;
	// }

      } else {
	summaryHist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(MBHFSUMGOOD);
      }

      if (debug) {
	std::cout << "meh: MBHFM1    | ";
	if (dataEt != emulEt)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout << dataEt << "\t" << emulEt;
	std::cout  << std::endl;
      }
    }

    // TowerCount
    if (l1t::EtSum::EtSumType::kTowerCount == dataIt->getType()) {

      dataEt = dataIt->hwPt();
      emulEt = emulIt->hwPt();

      objSummaryHist->Fill(NTOWCOUNTS);
      // summaryHist->Fill(NSUMS_S);

      if (dataEt != emulEt) {
	eventGood = false;
	towCountData->getTH1F()->Fill(dataEt);
	towCountEmul->getTH1F()->Fill(emulEt);

	// if (debug) {
	//   std::cout << "meh: TowCount issue" << std::endl;
	//   std::cout << "meh: data TowCount = " << dataEt << std::endl;
	//   std::cout << "meh: emul TowCount = " << emulEt << std::endl;
	// }
      } else {
	summaryHist->Fill(SUMGOOD_S);
	objSummaryHist->Fill(SUMGOOD);
	objSummaryHist->Fill(TOWCOUNTGOOD);
      }

      if (debug) {
	std::cout << "meh: TowCount  | ";
	if (dataEt != emulEt)
	  std::cout << "x ";
	else
	  std::cout << "  ";
	std::cout  << dataEt << "\t" << emulEt;
	std::cout << std::endl;
      }
    }

    summaryHist->Fill(NSUMS_S);
    objSummaryHist->Fill(NSUMS);

    ++dataIt;
    ++emulIt;

    if (dataIt == dataCol->end(currBx) || emulIt == emulCol->end(currBx))
      break;
  }

  if (eventGood) {
    objSummaryHist->Fill(SUMGOOD);
  } else {
    problemHist->Fill(SUMMISMATCH);
  }

  // return a boolean that states whether the jet data in the event is in
  // agreement
  return eventGood;
}

DEFINE_FWK_MODULE (L1TdeStage2CaloLayer2);
