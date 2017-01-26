#include "DQM/L1TMonitorClient/interface/L1TStage2CaloLayer2DEClient.h"

L1TStage2CaloLayer2DEClient::L1TStage2CaloLayer2DEClient(const edm::ParameterSet& ps):
  monitor_dir_(ps.getUntrackedParameter<std::string>("monitorDir","")),
  input_dir_data_(ps.getUntrackedParameter<std::string>("inputDataDir","")),
  input_dir_emul_(ps.getUntrackedParameter<std::string>("inputEmulDir",""))
{}

L1TStage2CaloLayer2DEClient::~L1TStage2CaloLayer2DEClient(){}

void L1TStage2CaloLayer2DEClient::dqmEndLuminosityBlock(DQMStore::IBooker &ibooker,DQMStore::IGetter &igetter,const edm::LuminosityBlock& lumiSeg, const edm::EventSetup& c) {
  book(ibooker);
  processHistograms(igetter);
}

void L1TStage2CaloLayer2DEClient::book(DQMStore::IBooker &ibooker){
  
  ibooker.setCurrentFolder(monitor_dir_);
  
  CenJetRankComp_=ibooker.book1D("CenJetsRankDERatio","Data/Emul of Central Jet E_{T}; Jet iE_{T}; Counts", 2048, -0.5, 2047.5);
  CenJetEtaComp_=ibooker.book1D("CenJetsEtaDERatio","Data/Emul of Central Jet #eta; Jet i#eta; Counts", 229, -114.5, 114.5);
  CenJetPhiComp_=ibooker.book1D("CenJetsPhiDERatio","Data/Emul of Central Jet #phi; Jet i#phi; Counts", 144, -0.5, 143.5);
  ForJetRankComp_=ibooker.book1D("ForJetsRankDERatio","Data/Emul of Forward Jet E_{T}; Jet iE_{T}; Counts", 2048, -0.5, 2047.5);
  ForJetEtaComp_=ibooker.book1D("ForJetsEtaDERatio","Data/Emul of Forward Jet #eta; Jet i#eta; Counts", 229, -114.5, 114.5);
  ForJetPhiComp_=ibooker.book1D("ForJetsPhiDERatio","Data/Emul of Forward Jet #phi; Jet i#phi; Counts", 144, -0.5, 143.5);
  IsoEGRankComp_=ibooker.book1D("IsoEGRankDERatio","Data/Emul of isolated eg E_{T}; EG iE_{T}; Counts", 512, -0.5, 511.5);
  IsoEGEtaComp_=ibooker.book1D("IsoEGEtaDERatio","Data/Emul of isolated eg #eta; EG i#eta; Counts", 229, -114.5, 114.5);
  IsoEGPhiComp_=ibooker.book1D("IsoEGPhiDERatio","Data/Emul of isolated eg #phi; EG i#eta; Counts", 144, -0.5, 143.5);
  NonIsoEGRankComp_=ibooker.book1D("NonIsoEGRankDERatio","Data/Emul of non-isolated eg E_{T}; EG iE_{T}; Counts", 512, -0.5, 511.5);
  NonIsoEGEtaComp_=ibooker.book1D("NonIsoEGEtaDERatio","Data/Emul of non-isolated eg #eta; EG i#eta; Counts", 229, -114.5, 114.5);
  NonIsoEGPhiComp_=ibooker.book1D("NonIsoEGPhiDERatio","Data/Emul of non-isolated eg #phi; EG i#phi; Counts", 144, -0.5, 143.5);
  TauRankComp_=ibooker.book1D("TauRankDERatio","Data/Emul of relax tau E_{T}; Tau iE_{T}; Counts", 512, -0.5, 511.5);
  TauEtaComp_=ibooker.book1D("TauEtaDERatio","Data/Emul of relax tau #eta; Tau i#eta; Counts", 229, -114.5, 114.5);
  TauPhiComp_=ibooker.book1D("TauPhiDERatio","Data/Emul of relax tau eg #phi; Tau i#phi; Counts", 144, -0.5, 143.5);
  IsoTauRankComp_=ibooker.book1D("IsoTauRankDERatio","Data/Emul of iso tau E_{T}; ISO Tau iE_{T}; Counts", 512, -0.5, 511.5);
  IsoTauEtaComp_=ibooker.book1D("IsoTauEtaDERatio","Data/Emul of iso tau #eta; ISO Tau i#eta; Counts", 229, -114.5, 114.5);
  IsoTauPhiComp_=ibooker.book1D("IsoTauPhiDERatio","Data/Emul of iso tau #phi; ISO Tau i#phi; Counts", 144, -0.5, 143.5);
  METComp_=ibooker.book1D("METRatio","Data/Emul of MET; iE_{T}; Events", 4096, -0.5, 4095.5);
  METPhiComp_=ibooker.book1D("METPhiRatio","Data/Emul of MET #phi; MET i#Phi; Events", 1008, -0.5, 1007.5);
  METHFComp_=ibooker.book1D("METHFRatio","Data/Emul of METHF; METHF iE_{T}; Events", 4096, -0.5, 4095.5);
  METHFPhiComp_=ibooker.book1D("METHFPhiRatio","Data/Emul of METHF #phi; METHF i#phi; Events", 1008, -0.5, 1007.5);
  MHTComp_=ibooker.book1D("MHTRatio","Data/Emul of MHT; MHT iE_{T}; Events", 4096, -0.5, 4095.5);
  METPhiComp_=ibooker.book1D("MHTPhiRatio","Data/Emul of MHT #phi; MHTHF i#phi; Events", 1008, -0.5, 1007.5);
  MHTHFComp_=ibooker.book1D("MHTHFRatio","Data/Emul of MHTHF; MHTHF iE_{T}; Events", 4096, -0.5, 4095.5);
  MHTPhiComp_=ibooker.book1D("MHTHFPhiRatio","Data/Emul of MHTHF #phi; MHTHF i#phi; Events", 1008, -0.5, 1007.5);
  ETTComp_=ibooker.book1D("ETTRatio","Data/Emul of ET Total; ETT iE_{T}; Events", 4096, -0.5, 4095.5);
  ETTEMComp_=ibooker.book1D("ETTEMRatio","Data/Emul of ET Total EM; ETTEM iE_{T}; Events", 4096, -0.5, 4095.5);
  HTTComp_=ibooker.book1D("HTTRatio","Data/Emul of HT Total; HT iE_{T}; Events", 4096, -0.5, 4095.5);

  MinBiasHFP0Comp_ = ibooker.book1D("MinBiasHFP0Ratio", "Data/Emul MinBiasHFP0; N_{towers}; Events", 16, -0.5, 15.5);
  MinBiasHFM0Comp_ = ibooker.book1D("MinBiasHFM0Ratio", "Data/Emul MinBiasHFM0; N_{towers}; Events", 16, -0.5, 15.5);
  MinBiasHFP1Comp_ = ibooker.book1D("MinBiasHFP1Ratio", "Data/Emul MinBiasHFP1; N_{towers}; Events", 16, -0.5, 15.5);
  MinBiasHFM1Comp_ = ibooker.book1D("MinBiasHFM1Ratio", "Data/Emul MinBiasHFM1; N_{towers}; Events", 16, -0.5, 15.5);

  TowerCountComp_ = ibooker.book1D("TowCountRatio", "Data/Emul Tower Count; N_{towers}; Events", 5904, -0.5, 5903.5);

  SummaryPlot_ = ibooker.book1D("CaloLayer2Summary", "CaloLayer2 Data-Emulator agreement summary", 35, 0, 35);
}

void L1TStage2CaloLayer2DEClient::processHistograms(DQMStore::IGetter &igetter){
  
  MonitorElement* dataHist_;
  MonitorElement* emulHist_;

  // central jets
  dataHist_ = igetter.get(input_dir_data_+"/Central-Jets/"+"CenJetsRank");
  emulHist_ = igetter.get(input_dir_emul_+"/Central-Jets/"+"CenJetsRank");

  if (dataHist_ && emulHist_){
    TH1F *cjrNum = dataHist_->getTH1F();
    TH1F *cjrDen = emulHist_->getTH1F();
  
    TH1F *CenJetRankRatio = CenJetRankComp_->getTH1F();

    CenJetRankRatio->Divide(cjrNum, cjrDen);
  }
  
  
  dataHist_ = igetter.get(input_dir_data_+"/Central-Jets/"+"CenJetsEta");
  emulHist_ = igetter.get(input_dir_emul_+"/Central-Jets/"+"CenJetsEta");

  if (dataHist_ && emulHist_){  
    TH1F *cjeNum = dataHist_->getTH1F();
    TH1F *cjeDen = emulHist_->getTH1F();

    TH1F *CenJetEtaRatio = CenJetEtaComp_->getTH1F();
    
    CenJetEtaRatio->Divide(cjeNum, cjeDen);
  }

  dataHist_ = igetter.get(input_dir_data_+"/Central-Jets/"+"CenJetsPhi");
  emulHist_ = igetter.get(input_dir_emul_+"/Central-Jets/"+"CenJetsPhi");

  if (dataHist_ && emulHist_){  
    TH1F *cjpNum = dataHist_->getTH1F();
    TH1F *cjpDen = emulHist_->getTH1F();
    
    TH1F *CenJetPhiRatio = CenJetPhiComp_->getTH1F();
    
    CenJetPhiRatio->Divide(cjpNum, cjpDen);
  }

  // forward jets
  dataHist_ = igetter.get(input_dir_data_+"/Forward-Jets/"+"ForJetsRank");
  emulHist_ = igetter.get(input_dir_emul_+"/Forward-Jets/"+"ForJetsRank");
  
  if (dataHist_ && emulHist_){  
    
    TH1F *fjrNum = dataHist_->getTH1F();
    TH1F *fjrDen = emulHist_->getTH1F();
    
    TH1F *ForJetRankRatio = ForJetRankComp_->getTH1F();
    
    ForJetRankRatio->Divide(fjrNum, fjrDen);
  }
  
  dataHist_ = igetter.get(input_dir_data_+"/Forward-Jets/"+"ForJetsEta");
  emulHist_ = igetter.get(input_dir_emul_+"/Forward-Jets/"+"ForJetsEta");

  if (dataHist_ && emulHist_){
    TH1F *fjeNum = dataHist_->getTH1F();
    TH1F *fjeDen = emulHist_->getTH1F();
    
    TH1F *ForJetEtaRatio = ForJetEtaComp_->getTH1F();
    
    ForJetEtaRatio->Divide(fjeNum, fjeDen);
  }
    
  dataHist_ = igetter.get(input_dir_data_+"/Forward-Jets/"+"ForJetsPhi");
  emulHist_ = igetter.get(input_dir_emul_+"/Forward-Jets/"+"ForJetsPhi");

  if (dataHist_ && emulHist_){
    TH1F *fjpNum = dataHist_->getTH1F();
    TH1F *fjpDen = emulHist_->getTH1F();
    
    TH1F *ForJetPhiRatio = ForJetPhiComp_->getTH1F();
    
    ForJetPhiRatio->Divide(fjpNum, fjpDen);
  }

  // isolated eg
  dataHist_ = igetter.get(input_dir_data_+"/Isolated-EG/"+"IsoEGsRank");
  emulHist_ = igetter.get(input_dir_emul_+"/Isolated-EG/"+"IsoEGsRank");

  if (dataHist_ && emulHist_){  
    TH1F *ierNum = dataHist_->getTH1F();
    TH1F *ierDen = emulHist_->getTH1F();
    
    TH1F *IsoEGRankRatio = IsoEGRankComp_->getTH1F();
    
    IsoEGRankRatio->Divide(ierNum, ierDen);
  }
  
  dataHist_ = igetter.get(input_dir_data_+"/Isolated-EG/"+"IsoEGsEta");
  emulHist_ = igetter.get(input_dir_emul_+"/Isolated-EG/"+"IsoEGsEta");

  if (dataHist_ && emulHist_){
    TH1F *ieeNum = dataHist_->getTH1F();
    TH1F *ieeDen = emulHist_->getTH1F();
    
    TH1F *IsoEGEtaRatio = IsoEGEtaComp_->getTH1F();
    
    IsoEGEtaRatio->Divide(ieeNum, ieeDen);
  }
    
  dataHist_ = igetter.get(input_dir_data_+"/Isolated-EG/"+"IsoEGsPhi");
  emulHist_ = igetter.get(input_dir_emul_+"/Isolated-EG/"+"IsoEGsPhi");

  if (dataHist_ && emulHist_){
    TH1F *iepNum = dataHist_->getTH1F();
    TH1F *iepDen = emulHist_->getTH1F();
    
    TH1F *IsoEGPhiRatio = IsoEGPhiComp_->getTH1F();
    
    IsoEGPhiRatio->Divide(iepNum, iepDen);
  }

  // non-isolated eg
  dataHist_ = igetter.get(input_dir_data_+"/NonIsolated-EG/"+"NonIsoEGsRank");
  emulHist_ = igetter.get(input_dir_emul_+"/NonIsolated-EG/"+"NonIsoEGsRank");

  if (dataHist_ && emulHist_){  
    TH1F *nerNum = dataHist_->getTH1F();
    TH1F *nerDen = emulHist_->getTH1F();
    
    TH1F *NonIsoEGRankRatio = NonIsoEGRankComp_->getTH1F();
    
    NonIsoEGRankRatio->Divide(nerNum, nerDen);
  }
    
  dataHist_ = igetter.get(input_dir_data_+"/NonIsolated-EG/"+"NonIsoEGsEta");
  emulHist_ = igetter.get(input_dir_emul_+"/NonIsolated-EG/"+"NonIsoEGsEta");

  if (dataHist_ && emulHist_){
    TH1F *neeNum = dataHist_->getTH1F();
    TH1F *neeDen = emulHist_->getTH1F();
    
    TH1F *NonIsoEGEtaRatio = NonIsoEGEtaComp_->getTH1F();
    
    NonIsoEGEtaRatio->Divide(neeNum, neeDen);
  }
  
  dataHist_ = igetter.get(input_dir_data_+"/NonIsolated-EG/"+"NonIsoEGsPhi");
  emulHist_ = igetter.get(input_dir_emul_+"/NonIsolated-EG/"+"NonIsoEGsPhi");

  if (dataHist_ && emulHist_){
    TH1F *nepNum = dataHist_->getTH1F();
    TH1F *nepDen = emulHist_->getTH1F();
    
    TH1F *NonIsoEGPhiRatio = NonIsoEGPhiComp_->getTH1F();
    
    NonIsoEGPhiRatio->Divide(nepNum, nepDen);
  }

  // rlx tau
  dataHist_ = igetter.get(input_dir_data_+"/NonIsolated-Tau/"+"TausRank");
  emulHist_ = igetter.get(input_dir_emul_+"/NonIsolated-Tau/"+"TausRank");
  
  if (dataHist_ && emulHist_){  
    TH1F *trNum = dataHist_->getTH1F();
    TH1F *trDen = emulHist_->getTH1F();
    
    TH1F *TauRankRatio = TauRankComp_->getTH1F();
    
    TauRankRatio->Divide(trNum, trDen);
  }
    
  dataHist_ = igetter.get(input_dir_data_+"/NonIsolated-Tau/"+"TausEta");
  emulHist_ = igetter.get(input_dir_emul_+"/NonIsolated-Tau/"+"TausEta");

  if (dataHist_ && emulHist_){
    TH1F *teNum = dataHist_->getTH1F();
    TH1F *teDen = emulHist_->getTH1F();
    
    TH1F *TauEtaRatio = TauEtaComp_->getTH1F();
    
    TauEtaRatio->Divide(teNum, teDen);
  }
    
  dataHist_ = igetter.get(input_dir_data_+"/NonIsolated-Tau/"+"TausPhi");
  emulHist_ = igetter.get(input_dir_emul_+"/NonIsolated-Tau/"+"TausPhi");

  if (dataHist_ && emulHist_){
    TH1F *tpNum = dataHist_->getTH1F();
    TH1F *tpDen = emulHist_->getTH1F();
    
    TH1F *TauPhiRatio = TauPhiComp_->getTH1F();
    
    TauPhiRatio->Divide(tpNum, tpDen);  
  }
  
  // iso tau
  dataHist_ = igetter.get(input_dir_data_+"/Isolated-Tau/"+"IsoTausRank");
  emulHist_ = igetter.get(input_dir_emul_+"/Isolated-Tau/"+"IsoTausRank");

  if (dataHist_ && emulHist_){ 
    TH1F *itrNum = dataHist_->getTH1F();
    TH1F *itrDen = emulHist_->getTH1F();
    
    TH1F *IsoTauRankRatio = IsoTauRankComp_->getTH1F();
    
    IsoTauRankRatio->Divide(itrNum, itrDen);
  }
  
  dataHist_ = igetter.get(input_dir_data_+"/Isolated-Tau/"+"IsoTausEta");
  emulHist_ = igetter.get(input_dir_emul_+"/Isolated-Tau/"+"IsoTausEta");
  
  if (dataHist_ && emulHist_){  
    TH1F *iteNum = dataHist_->getTH1F();
    TH1F *iteDen = emulHist_->getTH1F();
    
    TH1F *IsoTauEtaRatio = IsoTauEtaComp_->getTH1F();
    
    IsoTauEtaRatio->Divide(iteNum, iteDen);
  }
    
  dataHist_ = igetter.get(input_dir_data_+"/Isolated-Tau/"+"IsoTausPhi");
  emulHist_ = igetter.get(input_dir_emul_+"/Isolated-Tau/"+"IsoTausPhi");

  if (dataHist_ && emulHist_){
    TH1F *itpNum = dataHist_->getTH1F();
    TH1F *itpDen = emulHist_->getTH1F();
    
    TH1F *IsoTauPhiRatio = IsoTauPhiComp_->getTH1F();
    
    IsoTauPhiRatio->Divide(itpNum, itpDen);
  }
  
  // MET
  dataHist_ = igetter.get(input_dir_data_+"/Energy-Sums/"+"METRank");
  emulHist_ = igetter.get(input_dir_emul_+"/Energy-Sums/"+"METRank");

  if (dataHist_ && emulHist_){
    TH1F *metNum = dataHist_->getTH1F();
    TH1F *metDen = emulHist_->getTH1F();
    
    TH1F *METRatio = METComp_->getTH1F();
    
    METRatio->Divide(metNum, metDen);
  }

  /*
  // MET Phi
  dataHist_ = igetter.get(input_dir_data_+"/Energy-Sums/"+"METPhi");
  emulHist_ = igetter.get(input_dir_emul_+"/Energy-Sums/"+"METPhi");

  if (dataHist_ && emulHist_){
    TH1F *metphiNum = dataHist_->getTH1F();
    TH1F *metphiDen = emulHist_->getTH1F();

    TH1F *METPhiRatio = METPhiComp_->getTH1F();
    
    METPhiRatio->Divide(metphiNum, metphiDen);
  } 
  */ 

  // METHF
  dataHist_ = igetter.get(input_dir_data_+"/Energy-Sums/"+"METHFRank");
  emulHist_ = igetter.get(input_dir_emul_+"/Energy-Sums/"+"METHFRank");

  if (dataHist_ && emulHist_){
    TH1F *methfNum = dataHist_->getTH1F();
    TH1F *methfDen = emulHist_->getTH1F();

    TH1F *METHFRatio = METHFComp_->getTH1F();

    METHFRatio->Divide(methfNum, methfDen);
  }

  /*
  // METHF Phi
  dataHist_ = igetter.get(input_dir_data_+"/Energy-Sums/"+"METHFPhi");
  emulHist_ = igetter.get(input_dir_emul_+"/Energy-Sums/"+"METHFPhi");

  if (dataHist_ && emulHist_){
    TH1F *methfphiNum = dataHist_->getTH1F();
    TH1F *methfphiDen = emulHist_->getTH1F();

    TH1F *METHFPhiRatio = METHFPhiComp_->getTH1F();

    METHFPhiRatio->Divide(methfphiNum, methfphiDen);
  }
  */

  // MHT
  dataHist_ = igetter.get(input_dir_data_+"/Energy-Sums/"+"MHTRank");
  emulHist_ = igetter.get(input_dir_emul_+"/Energy-Sums/"+"MHTRank");

  if (dataHist_ && emulHist_){
    TH1F *mhtNum = dataHist_->getTH1F();
    TH1F *mhtDen = emulHist_->getTH1F();

    TH1F *MHTRatio = MHTComp_->getTH1F();
    
    MHTRatio->Divide(mhtNum, mhtDen);
  }

  // MHTHF
  dataHist_ = igetter.get(input_dir_data_+"/Energy-Sums/"+"MHTHFRank");
  emulHist_ = igetter.get(input_dir_emul_+"/Energy-Sums/"+"MHTHFRank");

  if (dataHist_ && emulHist_){
    TH1F *mhthfNum = dataHist_->getTH1F();
    TH1F *mhthfDen = emulHist_->getTH1F();

    TH1F *MHTHFRatio = MHTHFComp_->getTH1F();

    MHTHFRatio->Divide(mhthfNum, mhthfDen);
  }

  /*
  // MHTHF Phi
  dataHist_ = igetter.get(input_dir_data_+"/Energy-Sums/"+"MHTHFPhi");
  emulHist_ = igetter.get(input_dir_emul_+"/Energy-Sums/"+"MHTHFPhi");

  if (dataHist_ && emulHist_){
    TH1F *mhthfphiNum = dataHist_->getTH1F();
    TH1F *mhthfphiDen = emulHist_->getTH1F();

    TH1F *MHTHFPhiRatio = MHTHFPhiComp_->getTH1F();

    MHTHFPhiRatio->Divide(mhthfphiNum, mhthfphiDen);
    }*/

  // ETT
  dataHist_ = igetter.get(input_dir_data_+"/Energy-Sums/"+"ETTRank");
  emulHist_ = igetter.get(input_dir_emul_+"/Energy-Sums/"+"ETTRank");

  if (dataHist_ && emulHist_){
    TH1F *ettNum = dataHist_->getTH1F();
    TH1F *ettDen = emulHist_->getTH1F();
    
    TH1F *ETTRatio = ETTComp_->getTH1F();
    
    ETTRatio->Divide(ettNum, ettDen);
  }

  // ETTEM
  dataHist_ = igetter.get(input_dir_data_+"/Energy-Sums/"+"ETTEMRank");
  emulHist_ = igetter.get(input_dir_emul_+"/Energy-Sums/"+"ETTEMRank");

  if (dataHist_ && emulHist_){
    TH1F *ettemNum = dataHist_->getTH1F();
    TH1F *ettemDen = emulHist_->getTH1F();

    TH1F *ETTEMRatio = ETTEMComp_->getTH1F();

    ETTEMRatio->Divide(ettemNum, ettemDen);
  }

  // HTT
  dataHist_ = igetter.get(input_dir_data_+"/Energy-Sums/"+"HTTRank");
  emulHist_ = igetter.get(input_dir_emul_+"/Energy-Sums/"+"HTTRank");

  if (dataHist_ && emulHist_){
    TH1F *httNum = dataHist_->getTH1F();
    TH1F *httDen = emulHist_->getTH1F();
    
    TH1F *HTTRatio = HTTComp_->getTH1F();
    
    HTTRatio->Divide(httNum, httDen);
  }

  // MBHFP0
  dataHist_ = igetter.get(input_dir_data_+"/Energy-Sums/"+"MinBiasHFP0");
  emulHist_ = igetter.get(input_dir_emul_+"/Energy-Sums/"+"MinBiasHFP0");

  if (dataHist_ && emulHist_){
    TH1F *mbhfp0Num = dataHist_->getTH1F();
    TH1F *mbhfp0Den = emulHist_->getTH1F();

    TH1F *MBHFP0Ratio = MinBiasHFP0Comp_->getTH1F();

    MBHFP0Ratio->Divide(mbhfp0Num, mbhfp0Den);
  }

  // MBHFM0
  dataHist_ = igetter.get(input_dir_data_+"/Energy-Sums/"+"MinBiasHFM0");
  emulHist_ = igetter.get(input_dir_emul_+"/Energy-Sums/"+"MinBiasHFM0");

  if (dataHist_ && emulHist_){
    TH1F *mbhfm0Num = dataHist_->getTH1F();
    TH1F *mbhfm0Den = emulHist_->getTH1F();

    TH1F *MBHFM0Ratio = MinBiasHFM0Comp_->getTH1F();

    MBHFM0Ratio->Divide(mbhfm0Num, mbhfm0Den);
  }

  // MBHFP1
  dataHist_ = igetter.get(input_dir_data_+"/Energy-Sums/"+"MinBiasHFP1");
  emulHist_ = igetter.get(input_dir_emul_+"/Energy-Sums/"+"MinBiasHFP1");

  if (dataHist_ && emulHist_){
    TH1F *mbhfp1Num = dataHist_->getTH1F();
    TH1F *mbhfp1Den = emulHist_->getTH1F();

    TH1F *MBHFP1Ratio = MinBiasHFP1Comp_->getTH1F();

    MBHFP1Ratio->Divide(mbhfp1Num, mbhfp1Den);
  }

  // MBHFM1
  dataHist_ = igetter.get(input_dir_data_+"/Energy-Sums/"+"MinBiasHFM1");
  emulHist_ = igetter.get(input_dir_emul_+"/Energy-Sums/"+"MinBiasHFM1");

  if (dataHist_ && emulHist_){
    TH1F *mbhfm1Num = dataHist_->getTH1F();
    TH1F *mbhfm1Den = emulHist_->getTH1F();

    TH1F *MBHFM1Ratio = MinBiasHFM1Comp_->getTH1F();

    MBHFM1Ratio->Divide(mbhfm1Num, mbhfm1Den);
  }

  // TowerCount
  dataHist_ = igetter.get(input_dir_data_+"/Energy-Sums/"+"TowCount");
  emulHist_ = igetter.get(input_dir_emul_+"/Energy-Sums/"+"TowCount");

  if (dataHist_ && emulHist_){
    TH1F *towCountNum = dataHist_->getTH1F();
    TH1F *towCountDen = emulHist_->getTH1F();

    TH1F *TowCountRatio = TowerCountComp_->getTH1F();

    TowCountRatio->Divide(towCountNum, towCountDen);
  }

  // Summary plot
  TH1F * SummaryHist = SummaryPlot_->getTH1F();

  // add informtion from ratio plots to summary histogram:
  addObjToSummary(igetter, SummaryHist, std::string("/Central-Jets/CenJetsRank"), "Central Jet iEt");
  addObjToSummary(igetter, SummaryHist, std::string("/Central-Jets/CenJetsEta"), "Central Jet iEta");
  addObjToSummary(igetter, SummaryHist, std::string("/Central-Jets/CenJetsPhi"), "Central Jet iPhi");
  addObjToSummary(igetter, SummaryHist, std::string("/Forward-Jets/ForJetsRank"), "Forward Jet iEt");
  addObjToSummary(igetter, SummaryHist, std::string("/Forward-Jets/ForJetsEta"), "Forward Jet iEta");
  addObjToSummary(igetter, SummaryHist, std::string("/Forward-Jets/ForJetsPhi"), "Forward Jet iPhi");
  addObjToSummary(igetter, SummaryHist, std::string("/Isolated-EG/IsoEGsRank"), "Isolated EG iEt");
  addObjToSummary(igetter, SummaryHist, std::string("/Isolated-EG/IsoEGsEta"), "Isolated EG iEta");
  addObjToSummary(igetter, SummaryHist, std::string("/Isolated-EG/IsoEGsPhi"), "Isolated EG iPhi");
  addObjToSummary(igetter, SummaryHist, std::string("/NonIsolated-EG/NonIsoEGsRank"), "Non-isolated EG iEt");
  addObjToSummary(igetter, SummaryHist, std::string("/NonIsolated-EG/NonIsoEGsEta"), "Non-isolated EG iEta");
  addObjToSummary(igetter, SummaryHist, std::string("/NonIsolated-EG/NonIsoEGsPhi"), "Non-isolated EG iPhi");
  addObjToSummary(igetter, SummaryHist, std::string("/Isolated-Tau/IsoTausRank"), "Isolated Tau iEt");
  addObjToSummary(igetter, SummaryHist, std::string("/Isolated-Tau/IsoTausEta"), "Isolated Tau iEta");
  addObjToSummary(igetter, SummaryHist, std::string("/Isolated-Tau/IsoTausPhi"), "Isolated Tau iPhi");
  addObjToSummary(igetter, SummaryHist, std::string("/NonIsolated-Tau/TausRank"), "Non-isolated Tau iEt");
  addObjToSummary(igetter, SummaryHist, std::string("/NonIsolated-Tau/TausPhi"), "Non-isolated Tau iPhi");
  addObjToSummary(igetter, SummaryHist, std::string("/NonIsolated-Tau/TausEta"), "Non-isolated Tau iEta");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/METRank"), "MET Rank");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/METPhi"), "MET iPhi");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/METHFRank"), "METHF Rank");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/METHFPhi"), "METHF iPhi");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/MHTRank"), "MHT Rank");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/MHTPhi"), "MHT iPhi");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/MHTHFRank"), "MHTHF Rank");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/MHTHFPhi"), "MHTHF iPhi");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/ETTRank"), "ETT Rank");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/HTTRank"), "HTT Rank");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/MBHFP0"), "MinBiasHFP0");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/MBHFM0"), "MinBiasHFM0");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/MBHFP1"), "MinBiasHFP1");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/MBHFM1"), "MinBiasHFM1");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/ETTEMRank"), "ETTEM Rank");
  addObjToSummary(igetter, SummaryHist, std::string("/Energy-Sums/TowCount"), "Tower Count");

  //SummaryHist->LabelsOption("v", "x");
  SummaryHist->LabelsDeflate();
}

void L1TStage2CaloLayer2DEClient::addObjToSummary(DQMStore::IGetter & getter, TH1F * hist, std::string objPath, const char * binLabel) {

  MonitorElement* dataHist_;
  MonitorElement* emulHist_;

  dataHist_ = getter.get(input_dir_data_ + objPath);
  emulHist_ = getter.get(input_dir_emul_ + objPath);

  if (dataHist_ && emulHist_){

    // double dataInt = dataHist_->getTH1F()->Integral();
    // double emuInt = emulHist_->getTH1F()->Integral();

		double binVal = 0;
		double binDiff = 0;
		double dataBin = 0;
		double emulBin = 0;

		unsigned int nBins = dataHist_->getTH1F()->GetNbinsX();

		for (unsigned int i = 0; i < nBins; ++i) {

			dataBin = dataHist_->getTH1F()->GetBinContent(i);
			emulBin = emulHist_->getTH1F()->GetBinContent(i);

		binDiff = dataBin - emulBin;
			binVal += binDiff * binDiff;
		}
    
    hist->Fill(binLabel, sqrt(binVal)/nBins);
  }
}  

void L1TStage2CaloLayer2DEClient::dqmEndJob(DQMStore::IBooker &ibooker, DQMStore::IGetter &igetter) {
  book(ibooker);
  processHistograms(igetter);
}
