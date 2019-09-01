// -*- C++ -*-
//
// Package:    two_prong/wjets_analyzer
// Class:      wjets_analyzer
// 
/**\class wjets_analyzer wjets_analyzer.cc two_prong/wjets_analyzer/plugins/wjets_analyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Stephen Greenberg
//         Created:  Wed, 28 Aug 2019 14:33:06 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TTree.h"
#include "TLorentzVector.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class wjets_analyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit wjets_analyzer(const edm::ParameterSet&);
      ~wjets_analyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------

      edm::EDGetTokenT<std::vector<reco::Vertex>> vtxToken_;
      edm::EDGetTokenT<std::vector<pat::Muon>> muonToken_;
      edm::EDGetTokenT<std::vector<pat::Electron>> electronToken_;
      edm::EDGetTokenT<std::vector<pat::Tau>> tauToken_;
      edm::EDGetTokenT<std::vector<pat::Photon>> photonToken_;
      edm::EDGetTokenT<std::vector<pat::Jet>> jetToken_;
      edm::EDGetTokenT<std::vector<pat::Jet>> fatjetToken_;
      edm::EDGetTokenT<std::vector<pat::MET>> metToken_;
      edm::EDGetTokenT<pat::PackedCandidateCollection> pfcandsToken_;
      TTree *fTree;

      // ---------tree variables ---------------------------
      Double_t 			fmcXS;
      Double_t 			fmcN;
      std::vector<Double_t>     fMuon_pt;
      std::vector<Double_t>     fMuon_eta;
      std::vector<Double_t>     fMuon_phi;
      std::vector<Double_t>     fMuon_mass;
      int                       fMuon_veto;
      int                       fNum_Muons;
      int                       fbtag_veto;
      int                       fnPV;
      Double_t                  fmT;
      Double_t                  fHT; //bare style

      std::vector<Double_t>     fW_pt;
      std::vector<Double_t>     fW_eta;
      std::vector<Double_t>     fW_phi;
      std::vector<Double_t>     fW_mass;

      std::vector<Double_t>     fJet_pt;
      std::vector<Double_t>     fJet_eta;
      std::vector<Double_t>     fJet_phi;
      std::vector<Double_t>     fJet_mass;

  //TWO PRONG VARIABLES
  /////////////////////////////////////////////////////////////////

  int fnTwoProngCands;
  std::vector<Double_t> fTwoProngCand_pt;
  std::vector<Double_t> fTwoProngCand_eta;
  std::vector<Double_t> fTwoProngCand_phi;
  std::vector<Double_t> fTwoProngCand_MassPi0;
  std::vector<Double_t> fTwoProngCand_MassEta;
  std::vector<Double_t> fTwoProngCand_CHpos_pt;
  std::vector<Double_t> fTwoProngCand_CHpos_eta;
  std::vector<Double_t> fTwoProngCand_CHpos_phi;
  std::vector<Double_t> fTwoProngCand_CHpos_mass;
  std::vector<Double_t> fTwoProngCand_CHpos_dz;
  std::vector<Double_t> fTwoProngCand_CHpos_dxy;
  std::vector<Double_t> fTwoProngCand_CHneg_pt;
  std::vector<Double_t> fTwoProngCand_CHneg_eta;
  std::vector<Double_t> fTwoProngCand_CHneg_phi;
  std::vector<Double_t> fTwoProngCand_CHneg_mass;
  std::vector<Double_t> fTwoProngCand_CHneg_dz;
  std::vector<Double_t> fTwoProngCand_CHneg_dxy;
  std::vector<Double_t> fTwoProngCand_photon_pt;
  std::vector<Double_t> fTwoProngCand_photon_eta;
  std::vector<Double_t> fTwoProngCand_photon_phi;
  std::vector<Double_t> fTwoProngCand_photon_mass;
  std::vector<Double_t> fTwoProngCand_photon_nGamma;
  std::vector<Double_t> fTwoProngCand_photon_nElectron;
  std::vector<Double_t> fTwoProngCand_chargedIso;
  std::vector<Double_t> fTwoProngCand_neutralIso;
  std::vector<Double_t> fTwoProngCand_egammaIso;
  std::vector<Double_t> fTwoProngCand_trackAsym;
  std::vector<Double_t> fTwoProngCand_photonAsym;
  std::vector<Bool_t> fTwoProngCand_tight;
  std::vector<Bool_t> fTwoProngCand_loose;

  int fnTwoProngs;
  std::vector<Double_t> fTwoProng_pt;
  std::vector<Double_t> fTwoProng_eta;
  std::vector<Double_t> fTwoProng_phi;
  std::vector<Double_t> fTwoProng_MassPi0;
  std::vector<Double_t> fTwoProng_MassEta;
  std::vector<Double_t> fTwoProng_CHpos_pt;
  std::vector<Double_t> fTwoProng_CHpos_eta;
  std::vector<Double_t> fTwoProng_CHpos_phi;
  std::vector<Double_t> fTwoProng_CHpos_mass;
  std::vector<Double_t> fTwoProng_CHpos_dz;
  std::vector<Double_t> fTwoProng_CHpos_dxy;
  std::vector<Double_t> fTwoProng_CHneg_pt;
  std::vector<Double_t> fTwoProng_CHneg_eta;
  std::vector<Double_t> fTwoProng_CHneg_phi;
  std::vector<Double_t> fTwoProng_CHneg_mass;
  std::vector<Double_t> fTwoProng_CHneg_dz;
  std::vector<Double_t> fTwoProng_CHneg_dxy;
  std::vector<Double_t> fTwoProng_photon_pt;
  std::vector<Double_t> fTwoProng_photon_eta;
  std::vector<Double_t> fTwoProng_photon_phi;
  std::vector<Double_t> fTwoProng_photon_mass;
  std::vector<Double_t> fTwoProng_photon_nGamma;
  std::vector<Double_t> fTwoProng_photon_nElectron;
  std::vector<Double_t> fTwoProng_chargedIso;
  std::vector<Double_t> fTwoProng_neutralIso;
  std::vector<Double_t> fTwoProng_egammaIso;
  std::vector<Double_t> fTwoProng_trackAsym;
  std::vector<Double_t> fTwoProng_photonAsym;


   int fnTwoProngsLoose;
  std::vector<Double_t> fTwoProngLoose_pt;
  std::vector<Double_t> fTwoProngLoose_eta;
  std::vector<Double_t> fTwoProngLoose_phi;
  std::vector<Double_t> fTwoProngLoose_MassPi0;
  std::vector<Double_t> fTwoProngLoose_MassEta;
  std::vector<Double_t> fTwoProngLoose_CHpos_pt;
  std::vector<Double_t> fTwoProngLoose_CHpos_eta;
  std::vector<Double_t> fTwoProngLoose_CHpos_phi;
  std::vector<Double_t> fTwoProngLoose_CHpos_mass;
  std::vector<Double_t> fTwoProngLoose_CHpos_dz;
  std::vector<Double_t> fTwoProngLoose_CHpos_dxy;
  std::vector<Double_t> fTwoProngLoose_CHneg_pt;
  std::vector<Double_t> fTwoProngLoose_CHneg_eta;
  std::vector<Double_t> fTwoProngLoose_CHneg_phi;
  std::vector<Double_t> fTwoProngLoose_CHneg_mass;
  std::vector<Double_t> fTwoProngLoose_CHneg_dz;
  std::vector<Double_t> fTwoProngLoose_CHneg_dxy;
  std::vector<Double_t> fTwoProngLoose_photon_pt;
  std::vector<Double_t> fTwoProngLoose_photon_eta;
  std::vector<Double_t> fTwoProngLoose_photon_phi;
  std::vector<Double_t> fTwoProngLoose_photon_mass;
  std::vector<Double_t> fTwoProngLoose_photon_nGamma;
  std::vector<Double_t> fTwoProngLoose_photon_nElectron;
  std::vector<Double_t> fTwoProngLoose_chargedIso;
  std::vector<Double_t> fTwoProngLoose_neutralIso;
  std::vector<Double_t> fTwoProngLoose_egammaIso;
  std::vector<Double_t> fTwoProngLoose_trackAsym;
  std::vector<Double_t> fTwoProngLoose_photonAsym;


};

double ftwoprong_tracksMinPt(0.01);
double ftwoprong_DR(0.3);
double ftwoprong_PhiBox(0.2);
double ftwoprong_EtaBox(0.05);
double ftwoprong_AbsMaxEta(2.5);
double ftwoprong_MinPt(20);
double ETA_MASS(0.547862);
double PI0_MASS(0.13497);

double ftwoprong_ChargedIsoCut(0.10);
double ftwoprong_NeutralIsoCut(0.10);
double ftwoprong_EGammaIsoCut(0.10);
double ftwoprong_PhotonPtCut(20.0);

double ftwoprong_TrackAsymmetryCut(0.2);
double ftwoprong_PhotonAsymmetryCut(0.15);        
double ftwoprong_ChargedIsoFakeCut(1.0);
double ftwoprong_NeutralIsoFakeCut(0.10);
double ftwoprong_EGammaIsoFakeCut(1.0);
double ftwoprong_IsolationDR(0.3);
      



//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
wjets_analyzer::wjets_analyzer(const edm::ParameterSet& iConfig):
    vtxToken_(consumes<std::vector<reco::Vertex>> (iConfig.getParameter<edm::InputTag>("vertices"))),
    muonToken_(consumes<std::vector<pat::Muon>> (iConfig.getParameter<edm::InputTag>("muons"))),
    electronToken_(consumes<std::vector<pat::Electron>> (iConfig.getParameter<edm::InputTag>("electrons"))),
    tauToken_(consumes<std::vector<pat::Tau>> (iConfig.getParameter<edm::InputTag>("taus"))),
    photonToken_(consumes<std::vector<pat::Photon>> (iConfig.getParameter<edm::InputTag>("photons"))),
    jetToken_(consumes<std::vector<pat::Jet>> (iConfig.getParameter<edm::InputTag>("jets"))),
    fatjetToken_(consumes<std::vector<pat::Jet>> (iConfig.getParameter<edm::InputTag>("fatjets"))),
    metToken_(consumes<std::vector<pat::MET>> (iConfig.getParameter<edm::InputTag>("mets"))),
    pfcandsToken_(consumes<pat::PackedCandidateCollection>(edm::InputTag("packedPFCandidates"))),
    fmcXS(iConfig.getUntrackedParameter<double>("mcXS")),
    fmcN(iConfig.getUntrackedParameter<double>("mcN"))


{
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> fs;
   fTree = fs->make<TTree>("fTree","fTree");
	
   fTree->Branch("mcXS", &fmcXS, "mcXS/D");
   fTree->Branch("mcN", &fmcN, "mcN/D");
   fTree->Branch("Muon_pt",&fMuon_pt);
   fTree->Branch("Muon_eta",&fMuon_eta);
   fTree->Branch("Muon_phi",&fMuon_phi);
   fTree->Branch("Muon_mass",&fMuon_mass);
   fTree->Branch("Num_Muons",&fNum_Muons,"Num_Muons/I");

   fTree->Branch("Muon_veto", &fMuon_veto, "Muon_veto/I");
   fTree->Branch("btag_veto",&fbtag_veto,"btag_veto/I");
   fTree->Branch("nPV",&fnPV,"nPV/I");
   fTree->Branch("mT",&fmT,"mT/D");
   fTree->Branch("HT",&fHT,"HT/D");

   fTree->Branch("W_pt",&fW_pt);
   fTree->Branch("W_eta",&fW_eta);
   fTree->Branch("W_phi",&fW_phi);
   fTree->Branch("W_mass",&fW_mass);

   fTree->Branch("Jet_pt",&fJet_pt);
   fTree->Branch("Jet_eta",&fJet_eta);
   fTree->Branch("Jet_phi",&fJet_phi);
   fTree->Branch("Jet_mass",&fJet_mass);

  //TIGHT TWO PRONGS
  /////////////////////////////////////////////////////////////////////////

  fTree->Branch("nTwoProngs",&fnTwoProngs,"nTwoProngs/I");
  // kinematics
  fTree->Branch("TwoProng_pt",&fTwoProng_pt);
  fTree->Branch("TwoProng_eta",&fTwoProng_eta);
  fTree->Branch("TwoProng_phi",&fTwoProng_phi);
  // mass
  fTree->Branch("TwoProng_MassPi0",&fTwoProng_MassPi0);
  fTree->Branch("TwoProng_MassEta",&fTwoProng_MassEta);
  // CHpos constituent
  fTree->Branch("TwoProng_CHpos_pt",&fTwoProng_CHpos_pt);
  fTree->Branch("TwoProng_CHpos_eta",&fTwoProng_CHpos_eta);
  fTree->Branch("TwoProng_CHpos_phi",&fTwoProng_CHpos_phi);
  fTree->Branch("TwoProng_CHpos_mass",&fTwoProng_CHpos_mass);
  fTree->Branch("TwoProng_CHpos_dz",&fTwoProng_CHpos_dz);
  fTree->Branch("TwoProng_CHpos_dxy",&fTwoProng_CHpos_dxy);
  // CHneg constituent
  fTree->Branch("TwoProng_CHneg_pt",&fTwoProng_CHneg_pt);
  fTree->Branch("TwoProng_CHneg_eta",&fTwoProng_CHneg_eta);
  fTree->Branch("TwoProng_CHneg_phi",&fTwoProng_CHneg_phi);
  fTree->Branch("TwoProng_CHneg_mass",&fTwoProng_CHneg_mass);
  fTree->Branch("TwoProng_CHneg_dz",&fTwoProng_CHneg_dz);
  fTree->Branch("TwoProng_CHneg_dxy",&fTwoProng_CHneg_dxy);
  // photon constituent
  fTree->Branch("TwoProng_photon_pt",&fTwoProng_photon_pt);
  fTree->Branch("TwoProng_photon_eta",&fTwoProng_photon_eta);
  fTree->Branch("TwoProng_photon_phi",&fTwoProng_photon_phi);
  fTree->Branch("TwoProng_photon_mass",&fTwoProng_photon_mass);
  fTree->Branch("TwoProng_photon_nGamma",&fTwoProng_photon_nGamma);
  fTree->Branch("TwoProng_photon_nElectron",&fTwoProng_photon_nElectron);
  // cut variables
  fTree->Branch("TwoProng_chargedIso",&fTwoProng_chargedIso);
  fTree->Branch("TwoProng_neutralIso",&fTwoProng_neutralIso);
  fTree->Branch("TwoProng_egammaIso",&fTwoProng_egammaIso);
  fTree->Branch("TwoProng_trackAsym",&fTwoProng_trackAsym);
  fTree->Branch("TwoProng_photonAsym",&fTwoProng_photonAsym);



  //LOOSE TWO PRONGS
  ////////////////////////////////////////////////////////////////////////////////////
  fTree->Branch("nTwoProngsLoose",&fnTwoProngsLoose,"nTwoProngsLoose/I");
  // kinematics
  fTree->Branch("TwoProngLoose_pt",&fTwoProngLoose_pt);
  fTree->Branch("TwoProngLoose_eta",&fTwoProngLoose_eta);
  fTree->Branch("TwoProngLoose_phi",&fTwoProngLoose_phi);
  // mass
  fTree->Branch("TwoProngLoose_MassPi0",&fTwoProngLoose_MassPi0);
  fTree->Branch("TwoProngLoose_MassEta",&fTwoProngLoose_MassEta);
  // CHpos constituent
  fTree->Branch("TwoProngLoose_CHpos_pt",&fTwoProngLoose_CHpos_pt);
  fTree->Branch("TwoProngLoose_CHpos_eta",&fTwoProngLoose_CHpos_eta);
  fTree->Branch("TwoProngLoose_CHpos_phi",&fTwoProngLoose_CHpos_phi);
  fTree->Branch("TwoProngLoose_CHpos_mass",&fTwoProngLoose_CHpos_mass);
  fTree->Branch("TwoProngLoose_CHpos_dz",&fTwoProngLoose_CHpos_dz);
  fTree->Branch("TwoProngLoose_CHpos_dxy",&fTwoProngLoose_CHpos_dxy);
  // CHneg constituent
  fTree->Branch("TwoProngLoose_CHneg_pt",&fTwoProngLoose_CHneg_pt);
  fTree->Branch("TwoProngLoose_CHneg_eta",&fTwoProngLoose_CHneg_eta);
  fTree->Branch("TwoProngLoose_CHneg_phi",&fTwoProngLoose_CHneg_phi);
  fTree->Branch("TwoProngLoose_CHneg_mass",&fTwoProngLoose_CHneg_mass);
  fTree->Branch("TwoProngLoose_CHneg_dz",&fTwoProngLoose_CHneg_dz);
  fTree->Branch("TwoProngLoose_CHneg_dxy",&fTwoProngLoose_CHneg_dxy);
  // photon constituent
  fTree->Branch("TwoProngLoose_photon_pt",&fTwoProngLoose_photon_pt);
  fTree->Branch("TwoProngLoose_photon_eta",&fTwoProngLoose_photon_eta);
  fTree->Branch("TwoProngLoose_photon_phi",&fTwoProngLoose_photon_phi);
  fTree->Branch("TwoProngLoose_photon_mass",&fTwoProngLoose_photon_mass);
  fTree->Branch("TwoProngLoose_photon_nGamma",&fTwoProngLoose_photon_nGamma);
  fTree->Branch("TwoProngLoose_photon_nElectron",&fTwoProngLoose_photon_nElectron);
  // cut variables
  fTree->Branch("TwoProngLoose_chargedIso",&fTwoProngLoose_chargedIso);
  fTree->Branch("TwoProngLoose_neutralIso",&fTwoProngLoose_neutralIso);
  fTree->Branch("TwoProngLoose_egammaIso",&fTwoProngLoose_egammaIso);
  fTree->Branch("TwoProngLoose_trackAsym",&fTwoProngLoose_trackAsym);
  fTree->Branch("TwoProngLoose_photonAsym",&fTwoProngLoose_photonAsym);
  
  // matching
  ////////////////////////////////////////////////////////////////////////////////////



}


wjets_analyzer::~wjets_analyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
wjets_analyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;

   //CLEARING ALL THE BRANCH VARIABLES

  fMuon_pt.clear();
  fMuon_eta.clear();
  fMuon_phi.clear();
  fMuon_mass.clear();

  fMuon_veto = -1;
  fNum_Muons = -1;
  fbtag_veto = -1;
  fnPV = -1;
  fmT = -100;
  fHT = -100; //bare style

  fW_pt.clear();
  fW_eta.clear();
  fW_phi.clear();
  fW_mass.clear();

  fJet_pt.clear();
  fJet_eta.clear();
  fJet_phi.clear();
  fJet_mass.clear();

  //TWO PRONG VARIABLES
  /////////////////////////////////////////////////////////////////

  fnTwoProngCands = -1;
  fTwoProngCand_pt.clear();
  fTwoProngCand_eta.clear();
  fTwoProngCand_phi.clear();
  fTwoProngCand_MassPi0.clear();
  fTwoProngCand_MassEta.clear();
  fTwoProngCand_CHpos_pt.clear();
  fTwoProngCand_CHpos_eta.clear();
  fTwoProngCand_CHpos_phi.clear();
  fTwoProngCand_CHpos_mass.clear();
  fTwoProngCand_CHpos_dz.clear();
  fTwoProngCand_CHpos_dxy.clear();
  fTwoProngCand_CHneg_pt.clear();
  fTwoProngCand_CHneg_eta.clear();
  fTwoProngCand_CHneg_phi.clear();
  fTwoProngCand_CHneg_mass.clear();
  fTwoProngCand_CHneg_dz.clear();
  fTwoProngCand_CHneg_dxy.clear();
  fTwoProngCand_photon_pt.clear();
  fTwoProngCand_photon_eta.clear();
  fTwoProngCand_photon_phi.clear();
  fTwoProngCand_photon_mass.clear();
  fTwoProngCand_photon_nGamma.clear();
  fTwoProngCand_photon_nElectron.clear();
  fTwoProngCand_chargedIso.clear();
  fTwoProngCand_neutralIso.clear();
  fTwoProngCand_egammaIso.clear();
  fTwoProngCand_trackAsym.clear();
  fTwoProngCand_photonAsym.clear();
  fTwoProngCand_tight.clear();
  fTwoProngCand_loose.clear();


  fnTwoProngs = -1;
  fTwoProng_pt.clear();
  fTwoProng_eta.clear();
  fTwoProng_phi.clear();
  fTwoProng_MassPi0.clear();
  fTwoProng_MassEta.clear();
  fTwoProng_CHpos_pt.clear();
  fTwoProng_CHpos_eta.clear();
  fTwoProng_CHpos_phi.clear();
  fTwoProng_CHpos_mass.clear();
  fTwoProng_CHpos_dz.clear();
  fTwoProng_CHpos_dxy.clear();
  fTwoProng_CHneg_pt.clear();
  fTwoProng_CHneg_eta.clear();
  fTwoProng_CHneg_phi.clear();
  fTwoProng_CHneg_mass.clear();
  fTwoProng_CHneg_dz.clear();
  fTwoProng_CHneg_dxy.clear();
  fTwoProng_photon_pt.clear();
  fTwoProng_photon_eta.clear();
  fTwoProng_photon_phi.clear();
  fTwoProng_photon_mass.clear();
  fTwoProng_photon_nGamma.clear();
  fTwoProng_photon_nElectron.clear();
  fTwoProng_chargedIso.clear();
  fTwoProng_neutralIso.clear();
  fTwoProng_egammaIso.clear();
  fTwoProng_trackAsym.clear();
  fTwoProng_photonAsym.clear();

  fnTwoProngsLoose = -1;
  fTwoProngLoose_pt.clear();
  fTwoProngLoose_eta.clear();
  fTwoProngLoose_phi.clear();
  fTwoProngLoose_MassPi0.clear();
  fTwoProngLoose_MassEta.clear();
  fTwoProngLoose_CHpos_pt.clear();
  fTwoProngLoose_CHpos_eta.clear();
  fTwoProngLoose_CHpos_phi.clear();
  fTwoProngLoose_CHpos_mass.clear();
  fTwoProngLoose_CHpos_dz.clear();
  fTwoProngLoose_CHpos_dxy.clear();
  fTwoProngLoose_CHneg_pt.clear();
  fTwoProngLoose_CHneg_eta.clear();
  fTwoProngLoose_CHneg_phi.clear();
  fTwoProngLoose_CHneg_mass.clear();
  fTwoProngLoose_CHneg_dz.clear();
  fTwoProngLoose_CHneg_dxy.clear();
  fTwoProngLoose_photon_pt.clear();
  fTwoProngLoose_photon_eta.clear();
  fTwoProngLoose_photon_phi.clear();
  fTwoProngLoose_photon_mass.clear();
  fTwoProngLoose_photon_nGamma.clear();
  fTwoProngLoose_photon_nElectron.clear();
  fTwoProngLoose_chargedIso.clear();
  fTwoProngLoose_neutralIso.clear();
  fTwoProngLoose_egammaIso.clear();
  fTwoProngLoose_trackAsym.clear();
  fTwoProngLoose_photonAsym.clear();




  //STARTING ANALYSIS

    edm::Handle<vector<reco::Vertex>> vertices;
    iEvent.getByToken(vtxToken_, vertices);
    if (vertices->empty()) return; // skip the event if no PV found, these should be filtered out already, though
    const reco::Vertex &PV = vertices->front();
    fnPV = vertices->size();

    fMuon_veto = 0;
    edm::Handle<vector<pat::Muon>> muons;
    iEvent.getByToken(muonToken_, muons);
    int good_muon_count = 0;
    for (const pat::Muon &mu : *muons) {

      fMuon_pt.push_back(mu.pt());
      fMuon_eta.push_back(mu.eta());
      fMuon_phi.push_back(mu.phi());
      fMuon_mass.push_back(mu.mass());
      fNum_Muons++;
      if (mu.pt() > 25 &&  mu.eta() < 2.5 && mu.eta() > -2.5){
         if (mu.isTightMuon(PV)) good_muon_count++;  ////////////// MUON ID FOR 2016 ? 
       }
    }
    
    if (good_muon_count > 1) fMuon_veto = 1;
    if (good_muon_count == 0) fMuon_veto = 1;
    fNum_Muons = good_muon_count;


    std::vector<double> btag_vals;
    edm::Handle<vector<pat::Jet>> jets;
    iEvent.getByToken(jetToken_, jets);

    for (const pat::Jet &j : *jets) {
        if (j.pt() < 20) continue;
        if (fabs(j.eta()) > 2.5) continue;

        fJet_pt.push_back(j.pt());
        fJet_mass.push_back(j.mass());
        fJet_eta.push_back(j.eta());
        fJet_phi.push_back(j.phi());

        fHT += j.pt();

        btag_vals.push_back((std::max(0.f,j.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"))));

    }

    fbtag_veto = 0;
    for (double btag_val : btag_vals){
      if (btag_val > 0.890) fbtag_veto = 1;
    }


    edm::Handle<vector<pat::MET>>  mets;
    iEvent.getByToken(metToken_, mets);
    const pat::MET &met = mets->front();
    
    if (fMuon_pt.size() > 0 ) {
      fmT =TMath::Sqrt(2 * fMuon_pt[0] * met.pt() * (1 - TMath::Cos(met.phi())));
    } else {
      fmT = 0;
    }

    //CONSTRUCTING W

    TLorentzVector w_vector, u_vector, v_vector;
    double w_mass = 80.3790;
    if (good_muon_count > 0){

    //CREATING NUETRINO VECTOR

      double v_pt, v_eta, v_phi, v_pz;
      double v_mass = 0.0;
      v_pt = met.pt();
      v_phi = met.phi();

      double u_pt, u_eta, u_phi, u_pz, u_mass;
      u_pt = fMuon_pt[0];
      u_eta = fMuon_eta[0];
      u_phi = fMuon_phi[0];
      u_mass = fMuon_mass[0];
      u_pz = u_pt * TMath::SinH(u_eta);

      double k = w_mass * w_mass / 2 + u_pt * v_pt;
      double u_p2 = u_pt * u_pt + u_pz * u_pz;

      //FROM TOP PAIR PRODUCTION ARTICLE

      v_pz = (2 * k * u_pz - TMath::Sqrt(4 * k * k * u_pz * u_pz - 4 * u_pt * u_pt * (v_pt * v_pt * u_p2 - k * k))) / (2 * u_pt * u_pt);
      double v_p2 = v_pz * v_pz + v_pt * v_pt;
      v_eta = TMath::ATanH( v_pz / TMath::Sqrt(v_p2));

      u_vector.SetPtEtaPhiM(u_pt, u_eta, u_phi, u_mass);
      v_vector.SetPtEtaPhiM(v_pt, v_eta, v_phi, v_mass);

      w_vector = u_vector + v_vector;

      } else {

        w_vector.SetPxPyPzE(0, 0, 0, 0);
      }

      fW_pt.push_back(w_vector.Pt());
      fW_eta.push_back(w_vector.Eta());
      fW_phi.push_back(w_vector.Phi());
      fW_mass.push_back(w_vector.M());



      //TWO PRONG CODE

      //START BY FINDING ONE POSITIVE CHARGED TRACK, AND ONE NEGATIVE AS 'CENTER'

      edm::Handle<pat::PackedCandidateCollection> pfcands;
      iEvent.getByToken(pfcandsToken_, pfcands);

      for (unsigned int i = 0; i < pfcands->size(); i++){
        const pat::PackedCandidate &pf1 = (*pfcands)[i];
        if (pf1.pt() < ftwoprong_tracksMinPt){
          	continue;
          }
        if (pf1.fromPV()<=1) {
          	continue;
          }

        for (unsigned int j = i + 1; j < pfcands->size() - i; j++ ){
          const pat::PackedCandidate &pf2 = (*pfcands)[j];
          if (pf2.pt() < ftwoprong_tracksMinPt){
          	continue;
          }
          if (pf2.fromPV()<=1){
          	continue;
          }
          if (!( ((pf1.pdgId() == 211) && (pf2.pdgId() == -211)) || ((pf1.pdgId() == -211) && (pf2.pdgId() == 211)) )){
        	 continue;
          }
          TLorentzVector pfcand1;
          pfcand1.SetPtEtaPhiE(pf1.pt(), pf1.eta(), pf1.phiAtVtx(), pf1.energy());
          TLorentzVector pfcand2;
          pfcand2.SetPtEtaPhiE(pf2.pt(), pf2.eta(), pf2.phiAtVtx(), pf2.energy());

          double dr = pfcand1.DeltaR(pfcand2);

          if (dr > 0.3) continue;

          TLorentzVector center = pfcand1 + pfcand2;

          TLorentzVector photon;
          TLorentzVector leading_pf_photon;
          int numgamma = 0;
          int nume = 0;
          int index_of_leading_pf_photon = -1;
          double pt_of_leading_pf_photon = -1;

          for (unsigned int k = 0; k < pfcands->size(); k++) {
            const pat::PackedCandidate &pf3 = (*pfcands)[k];
            if ((pf3.pdgId() != 22) && (abs(pf3.pdgId()) != 11)) continue; // only pf electron or pf photon contribute to definition of photon
            TLorentzVector pfcand3;
            pfcand3.SetPtEtaPhiE(pf3.pt(), pf3.eta(), pf3.phiAtVtx(), pf3.energy());
            if (fabs(pf3.phiAtVtx() - center.Phi()) < ftwoprong_PhiBox/2.0 &&
                fabs(pf3.eta() - center.Eta()) < ftwoprong_EtaBox/2.0) {
              photon = photon + pfcand3;
              if (pf3.pdgId() == 22) {
                numgamma += 1;
              // find leading photon pf
                if (pf3.pt() > pt_of_leading_pf_photon) {
                  pt_of_leading_pf_photon = pf3.pt();
                  index_of_leading_pf_photon = k;
                }
              }
              else if (abs(pf3.pdgId()) == 11) {
                nume += 1;
              }
            }
          } // end pf cand loop

          
          
          if (index_of_leading_pf_photon == -1) continue;
          TLorentzVector TwoProngObject;
          TwoProngObject = center + photon;

          TLorentzVector neutral_as_pi0mass;
          neutral_as_pi0mass.SetPtEtaPhiM(photon.Pt(), photon.Eta(), photon.Phi(), PI0_MASS);
          TLorentzVector neutral_as_etamass; 
          neutral_as_etamass.SetPtEtaPhiM(photon.Pt(), photon.Eta(), photon.Phi(), ETA_MASS);

          if (fabs(TwoProngObject.Eta()) > ftwoprong_AbsMaxEta) continue;
          if (TwoProngObject.Pt() < ftwoprong_MinPt) continue;


          TLorentzVector poscand;
          TLorentzVector negcand;
          if (pf1.pdgId() > 0) {
            poscand = pfcand1;
            negcand = pfcand2;
            fTwoProngCand_CHpos_pt.push_back(pfcand1.Pt());
            fTwoProngCand_CHpos_eta.push_back(pfcand1.Eta());
            fTwoProngCand_CHpos_phi.push_back(pfcand1.Phi());
            fTwoProngCand_CHpos_mass.push_back(pfcand1.M());
            fTwoProngCand_CHneg_pt.push_back(pfcand2.Pt());
            fTwoProngCand_CHneg_eta.push_back(pfcand2.Eta());
            fTwoProngCand_CHneg_phi.push_back(pfcand2.Phi());
            fTwoProngCand_CHneg_mass.push_back(pfcand2.M());
            // impact parameters 
            fTwoProngCand_CHpos_dz.push_back( pf1.dz(PV.position()) );
            fTwoProngCand_CHpos_dxy.push_back( pf1.dxy(PV.position()));
            fTwoProngCand_CHneg_dz.push_back( pf2.dz( PV.position()) );
            fTwoProngCand_CHneg_dxy.push_back( pf2.dxy( PV.position()) );
          } else {
            poscand = pfcand2;
            negcand = pfcand1;
            fTwoProngCand_CHpos_pt.push_back(pfcand2.Pt());
            fTwoProngCand_CHpos_eta.push_back(pfcand2.Eta());
            fTwoProngCand_CHpos_phi.push_back(pfcand2.Phi());
            fTwoProngCand_CHpos_mass.push_back(pfcand2.M());
            fTwoProngCand_CHneg_pt.push_back(pfcand1.Pt());
            fTwoProngCand_CHneg_eta.push_back(pfcand1.Eta());
            fTwoProngCand_CHneg_phi.push_back(pfcand1.Phi());
            fTwoProngCand_CHneg_mass.push_back(pfcand1.M());
            // impact parameters
            fTwoProngCand_CHneg_dz.push_back( pf1.dz( PV.position()) );
            fTwoProngCand_CHneg_dxy.push_back( pf1.dxy( PV.position()) );
            fTwoProngCand_CHpos_dz.push_back( pf2.dz( PV.position()) );
            fTwoProngCand_CHpos_dxy.push_back( pf2.dxy( PV.position()) );
          }
          fTwoProngCand_photon_pt.push_back(photon.Pt());
          fTwoProngCand_photon_eta.push_back(photon.Eta());
          fTwoProngCand_photon_phi.push_back(photon.Phi());
          fTwoProngCand_photon_mass.push_back(photon.M());
          fTwoProngCand_photon_nGamma.push_back(numgamma);
          fTwoProngCand_photon_nElectron.push_back(nume);
          fTwoProngCand_pt.push_back(TwoProngObject.Pt());
          fTwoProngCand_eta.push_back(TwoProngObject.Eta());
          fTwoProngCand_phi.push_back(TwoProngObject.Phi());

          fTwoProngCand_MassPi0.push_back( (center + neutral_as_pi0mass).M() );
          fTwoProngCand_MassEta.push_back( (center + neutral_as_etamass).M() );

          // Now define isolations
          double chargedIso = 0;
          double neutralIso = 0;
          double egammaIso = 0;
          int chargedIsoCount = 0;
          int neutralIsoCount = 0;
          int egammaIsoCount = 0;
          for (unsigned int m = 0; m < pfcands->size(); m++) {
            const pat::PackedCandidate &pf4 = (*pfcands)[m];
            TLorentzVector pfcand4;
            pfcand4.SetPtEtaPhiE(pf4.pt(), pf4.eta(), pf4.phiAtVtx(), pf4.energy());
            if (pf4.fromPV() <= 1) continue;
            // charged (incl. muons)
            if (abs(pf4.pdgId()) == 13 || abs(pf4.pdgId()) == 211) {
              if ( center.DeltaR(pfcand4) < ftwoprong_IsolationDR && !(m == i || m == j) ) { // don't include one of CH from CH pair 
                  chargedIso += pfcand4.Pt();
                  chargedIsoCount++;
              }
            // neutral
            } else if (pf4.pdgId() == 130) {
              if (center.DeltaR(pfcand4) < ftwoprong_IsolationDR) {
                neutralIso += pfcand4.Pt();
                  neutralIsoCount++;
              }
            // e gamma
            } else if (abs(pf4.pdgId()) == 11 || pf4.pdgId() == 22) {
              if ( (center.DeltaR(pfcand4) < ftwoprong_IsolationDR) &&
                   !(fabs(pf4.phiAtVtx() - center.Phi()) < ftwoprong_PhiBox/2.0 && fabs(pf4.eta() - center.Eta()) < ftwoprong_EtaBox/2.0)) {
                egammaIso += pfcand4.Pt();
                  egammaIsoCount++;
              }
            }
          } // end pf cand loop
          double relchargedIso = chargedIso / TwoProngObject.Pt();
          double relneutralIso = neutralIso / TwoProngObject.Pt();
          double relegammaIso = egammaIso / TwoProngObject.Pt();
          fTwoProngCand_chargedIso.push_back(relchargedIso);
          fTwoProngCand_neutralIso.push_back(relneutralIso);
          fTwoProngCand_egammaIso.push_back(relegammaIso);


          // Asymmetry variables
          double track_asymmetry = 1.0;
          double photon_asymmetry = 1.0;
          track_asymmetry = min(pfcand1.Pt(),pfcand2.Pt()) / max(pfcand1.Pt(),pfcand2.Pt());
          photon_asymmetry = min(pfcand1.Pt()+pfcand2.Pt(),photon.Pt()) / max(pfcand1.Pt()+pfcand2.Pt(),photon.Pt());
          
   
          bool passTrackAsymmetry = (track_asymmetry > ftwoprong_TrackAsymmetryCut);
          bool passPhotonAsymmetry = (photon_asymmetry > ftwoprong_PhotonAsymmetryCut);
          fTwoProngCand_trackAsym.push_back(track_asymmetry);
          fTwoProngCand_photonAsym.push_back(photon_asymmetry);

          // Selection on Candidates
          bool passCharged = relchargedIso < ftwoprong_ChargedIsoCut;
          bool passNeutral = relneutralIso < ftwoprong_NeutralIsoCut;
          bool passEGamma = relegammaIso < ftwoprong_EGammaIsoCut;
          bool passPhotonPt = photon.Pt() > ftwoprong_PhotonPtCut;
          bool tight = passCharged && passNeutral && passEGamma && passPhotonPt && passTrackAsymmetry && passPhotonAsymmetry;
          bool loose = !tight && passPhotonPt && passTrackAsymmetry && passPhotonAsymmetry &&
                       relchargedIso < ftwoprong_ChargedIsoFakeCut &&
                       relneutralIso < ftwoprong_NeutralIsoFakeCut &&
                       relegammaIso < ftwoprong_EGammaIsoFakeCut;
          fTwoProngCand_tight.push_back(tight);
          fTwoProngCand_loose.push_back(loose);


        }

      }


    vector<unsigned int> sorted_indecies;
    for (unsigned int i = 0; i < fTwoProngCand_pt.size(); i++) {
    double largestPtSoFar = -1.0;
    unsigned int largestPtSoFarIndex = 999;
    for (unsigned int j = 0; j < fTwoProngCand_pt.size(); j++) {
      bool skip = false;
      for (unsigned int n = 0; n < sorted_indecies.size(); n++) {
        if (sorted_indecies[n] == j) {
          skip = true;
          break; } }
      if (skip) continue;
      else if (fTwoProngCand_pt[j] > largestPtSoFar) {
        largestPtSoFar = fTwoProngCand_pt[j];
        largestPtSoFarIndex = j; } }
    sorted_indecies.push_back(largestPtSoFarIndex);
  }
  for (unsigned int i = 0; i < sorted_indecies.size(); i++) {
    unsigned int index = sorted_indecies[i];
    if (fTwoProngCand_loose[index])
    {
      // Candidate is loose and is next leading, fill all loose candidate collections
      fTwoProngLoose_pt.push_back(fTwoProngCand_pt[index]);
      fTwoProngLoose_eta.push_back(fTwoProngCand_eta[index]);
      fTwoProngLoose_phi.push_back(fTwoProngCand_phi[index]);
      fTwoProngLoose_MassPi0.push_back(fTwoProngCand_MassPi0[index]);
      fTwoProngLoose_MassEta.push_back(fTwoProngCand_MassEta[index]);
      fTwoProngLoose_CHpos_pt.push_back(fTwoProngCand_CHpos_pt[index]);
      fTwoProngLoose_CHpos_eta.push_back(fTwoProngCand_CHpos_eta[index]);
      fTwoProngLoose_CHpos_phi.push_back(fTwoProngCand_CHpos_phi[index]);
      fTwoProngLoose_CHpos_mass.push_back(fTwoProngCand_CHpos_mass[index]);
      fTwoProngLoose_CHpos_dz.push_back(fTwoProngCand_CHpos_dz[index]);
      fTwoProngLoose_CHpos_dxy.push_back(fTwoProngCand_CHpos_dxy[index]);
      fTwoProngLoose_CHneg_pt.push_back(fTwoProngCand_CHneg_pt[index]);
      fTwoProngLoose_CHneg_eta.push_back(fTwoProngCand_CHneg_eta[index]);
      fTwoProngLoose_CHneg_phi.push_back(fTwoProngCand_CHneg_phi[index]);
      fTwoProngLoose_CHneg_mass.push_back(fTwoProngCand_CHneg_mass[index]);
      fTwoProngLoose_CHneg_dz.push_back(fTwoProngCand_CHneg_dz[index]);
      fTwoProngLoose_CHneg_dxy.push_back(fTwoProngCand_CHneg_dxy[index]);
      fTwoProngLoose_photon_pt.push_back(fTwoProngCand_photon_pt[index]);
      fTwoProngLoose_photon_eta.push_back(fTwoProngCand_photon_eta[index]);
      fTwoProngLoose_photon_phi.push_back(fTwoProngCand_photon_phi[index]);
      fTwoProngLoose_photon_mass.push_back(fTwoProngCand_photon_mass[index]);
      fTwoProngLoose_photon_nGamma.push_back(fTwoProngCand_photon_nGamma[index]);
      fTwoProngLoose_photon_nElectron.push_back(fTwoProngCand_photon_nElectron[index]);
      fTwoProngLoose_chargedIso.push_back(fTwoProngCand_chargedIso[index]);
      fTwoProngLoose_neutralIso.push_back(fTwoProngCand_neutralIso[index]);
      fTwoProngLoose_egammaIso.push_back(fTwoProngCand_egammaIso[index]);
      fTwoProngLoose_trackAsym.push_back(fTwoProngCand_trackAsym[index]);
      fTwoProngLoose_photonAsym.push_back(fTwoProngCand_photonAsym[index]);
    }
    if (fTwoProngCand_tight[index])
    {
      // Candidate is tight and is next leading, fill all tight candidate collections
      fTwoProng_pt.push_back(fTwoProngCand_pt[index]);
      fTwoProng_eta.push_back(fTwoProngCand_eta[index]);
      fTwoProng_phi.push_back(fTwoProngCand_phi[index]);
      fTwoProng_MassPi0.push_back(fTwoProngCand_MassPi0[index]);
      fTwoProng_MassEta.push_back(fTwoProngCand_MassEta[index]);
      fTwoProng_CHpos_pt.push_back(fTwoProngCand_CHpos_pt[index]);
      fTwoProng_CHpos_eta.push_back(fTwoProngCand_CHpos_eta[index]);
      fTwoProng_CHpos_phi.push_back(fTwoProngCand_CHpos_phi[index]);
      fTwoProng_CHpos_mass.push_back(fTwoProngCand_CHpos_mass[index]);
      fTwoProng_CHpos_dz.push_back(fTwoProngCand_CHpos_dz[index]);
      fTwoProng_CHpos_dxy.push_back(fTwoProngCand_CHpos_dxy[index]);
      fTwoProng_CHneg_pt.push_back(fTwoProngCand_CHneg_pt[index]);
      fTwoProng_CHneg_eta.push_back(fTwoProngCand_CHneg_eta[index]);
      fTwoProng_CHneg_phi.push_back(fTwoProngCand_CHneg_phi[index]);
      fTwoProng_CHneg_mass.push_back(fTwoProngCand_CHneg_mass[index]);
      fTwoProng_CHneg_dz.push_back(fTwoProngCand_CHneg_dz[index]);
      fTwoProng_CHneg_dxy.push_back(fTwoProngCand_CHneg_dxy[index]);
      fTwoProng_photon_pt.push_back(fTwoProngCand_photon_pt[index]);
      fTwoProng_photon_eta.push_back(fTwoProngCand_photon_eta[index]);
      fTwoProng_photon_phi.push_back(fTwoProngCand_photon_phi[index]);
      fTwoProng_photon_mass.push_back(fTwoProngCand_photon_mass[index]);
      fTwoProng_photon_nGamma.push_back(fTwoProngCand_photon_nGamma[index]);
      fTwoProng_photon_nElectron.push_back(fTwoProngCand_photon_nElectron[index]);
      fTwoProng_chargedIso.push_back(fTwoProngCand_chargedIso[index]);
      fTwoProng_neutralIso.push_back(fTwoProngCand_neutralIso[index]);
      fTwoProng_egammaIso.push_back(fTwoProngCand_egammaIso[index]);
      fTwoProng_trackAsym.push_back(fTwoProngCand_trackAsym[index]);
      fTwoProng_photonAsym.push_back(fTwoProngCand_photonAsym[index]);
    }
  }



      fTree->Fill();


}


// ------------ method called once each job just before starting event loop  ------------
void 
wjets_analyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
wjets_analyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
wjets_analyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(wjets_analyzer);
