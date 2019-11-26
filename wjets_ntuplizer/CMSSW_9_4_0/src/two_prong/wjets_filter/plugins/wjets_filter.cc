
// -*- C++ -*-
//
// Package:    two_prong/wjets_filter
// Class:      wjets_filter
// 
/**\class wjets_filter wjets_filter.cc two_prong/wjets_filter/plugins/wjets_filter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Stephen Greenberg
//         Created:  Wed, 28 Aug 2019 14:33:32 GMT
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDFilter.h"

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

using namespace std;

class wjets_filter : public edm::stream::EDFilter<> {
   public:
      explicit wjets_filter(const edm::ParameterSet&);
      ~wjets_filter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------

      int fTotal_events;
      int fPassed_events;
      edm::EDGetTokenT<std::vector<reco::Vertex>> vtxToken_;
      edm::EDGetTokenT<std::vector<pat::Muon>> muonToken_;
      edm::EDGetTokenT<std::vector<pat::Electron>> electronToken_;
      edm::EDGetTokenT<std::vector<pat::Tau>> tauToken_;
      edm::EDGetTokenT<std::vector<pat::Photon>> photonToken_;
      edm::EDGetTokenT<std::vector<pat::Jet>> jetToken_;
      edm::EDGetTokenT<std::vector<pat::Jet>> fatjetToken_;
      edm::EDGetTokenT<std::vector<pat::MET>> metToken_;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
  const std::string MUON_TRIGGER = "HLT_IsoMu24";
  const std::string MUON_TRIGGER_Tk = "HLT_IsoTkMu24";

  const double TRIGGEROBJ_MATCH_DR = 0.1;

  const double MUON_MIN_PT = 26;
  const double MUON_MAX_ETA = 2.1;
  const double MUON_MAX_DZ = 0.2;
  const double MUON_MAX_DXY = 0.045;

  const double MUON_VLOOSE_RELISO = 0.4;
  const double MUON_LOOSE_RELISO = 0.25;
  const double MUON_MEDIUM_RELISO = 0.20;
  const double MUON_TIGHT_RELISO = 0.15;
  const double MUON_VTIGHT_RELISO = 0.10;
  const double MUON_VVTIGHT_RELISO = 0.05;

  const double LOOSEMUON_MAX_ETA = 2.4;

  const double EXTRAMUON_MIN_PT = 10.0;
  const double EXTRAMUON_MAX_ETA = 2.4;
  const double EXTRAMUON_MAX_RELISO = 0.25;
  const double EXTRAMUON_MAX_DZ = 0.2;
  const double EXTRAMUON_MAX_DXY = 0.045;

  const double EXTRAELECTRON_MIN_PT = 10.0;
  const double EXTRAELECTRON_MAX_ETA = 2.5;
  const double EXTRAELECTRON_MAX_RELISO = 0.3;
  const double EXTRAELECTRON_MAX_DZ = 0.2;
  const double EXTRAELECTRON_MAX_DXY = 0.045;
  const int    EXTRAELECTRON_MAX_LOSTTRACKS = 1;


double computeMuonIsolation(const pat::Muon * mu)
{
  return (mu->pfIsolationR04().sumChargedHadronPt + max(0., mu->pfIsolationR04().sumNeutralHadronEt + mu->pfIsolationR04().sumPhotonEt - 0.5*mu->pfIsolationR04().sumPUPt))/mu->pt();
}

double computeElectronIsolation(const pat::Electron * el)
{
  return (el->pfIsolationVariables().sumChargedHadronPt + max(0., el->pfIsolationVariables().sumNeutralHadronEt + el->pfIsolationVariables().sumPhotonEt - 0.5*el->pfIsolationVariables().sumPUPt))/el->pt();
}

//
wjets_filter::wjets_filter(const edm::ParameterSet& iConfig):
    vtxToken_(consumes<std::vector<reco::Vertex>> (iConfig.getParameter<edm::InputTag>("vertices"))),
    muonToken_(consumes<std::vector<pat::Muon>> (iConfig.getParameter<edm::InputTag>("muons"))),
    electronToken_(consumes<std::vector<pat::Electron>> (iConfig.getParameter<edm::InputTag>("electrons"))),
    tauToken_(consumes<std::vector<pat::Tau>> (iConfig.getParameter<edm::InputTag>("taus"))),
    photonToken_(consumes<std::vector<pat::Photon>> (iConfig.getParameter<edm::InputTag>("photons"))),
    jetToken_(consumes<std::vector<pat::Jet>> (iConfig.getParameter<edm::InputTag>("jets"))),
    fatjetToken_(consumes<std::vector<pat::Jet>> (iConfig.getParameter<edm::InputTag>("fatjets"))),
    metToken_(consumes<std::vector<pat::MET>> (iConfig.getParameter<edm::InputTag>("mets")))

{
   //now do what ever initialization is needed

}


wjets_filter::~wjets_filter()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
wjets_filter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  fTotal_events++;


  /*

  edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
  edm::Handle<edm::TriggerResults>& triggerBits;

     // trigger 
    const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
    string trigger_name = MUON_TRIGGER;
    bool trigger_bit = false;
    string trigger_found = "";
    string trigger_name_tk = MUON_TRIGGER_Tk;
    bool trigger_bit_tk = false;
    string trigger_found_tk = "";
    for (unsigned int i = 0, n = triggerBits->size(); i < n; i++)
    {
       string triggerName = names.triggerName(i);
       std::size_t pos = triggerName.find(trigger_name);
       if ( pos != std::string::npos ) {
         trigger_bit = triggerBits->accept(i);
         trigger_found = triggerName;
       }
       pos = triggerName.find(trigger_name_tk);
       if ( pos != std::string::npos ) {
         trigger_bit_tk = triggerBits->accept(i);
         trigger_found_tk = triggerName;
       }
    }

      vector<TLorentzVector> trigger_objects;
    vector<TLorentzVector> trigger_objects_muon;
    vector<TLorentzVector> trigger_objects_muontk;
    for (pat::TriggerObjectStandAlone obj : *triggerObjects) {
       obj.unpackPathNames(names);
       TLorentzVector triggerobj;
       triggerobj.SetPtEtaPhiE(obj.pt(), obj.eta(), obj.phi(), obj.energy());
       std::vector<std::string> pathNamesAll = obj.pathNames(false);
       std::vector<std::string> pathNamesLast = obj.pathNames(true);
       for (unsigned h = 0, n = pathNamesAll.size(); h < n; ++h) {
           bool isBoth = obj.hasPathName( pathNamesAll[h], true, true );
           if (!isBoth) continue;
           string pathName = pathNamesAll[h];
           std::size_t pos = pathName.find(trigger_name);
           if ( pos != std::string::npos ) {
             trigger_objects.push_back(triggerobj);
             trigger_objects_muon.push_back(triggerobj);
           }
           pos = pathName.find(trigger_name_tk);
           if ( pos != std::string::npos ) {
             trigger_objects.push_back(triggerobj);
             trigger_objects_muontk.push_back(triggerobj);
           }
       }
    }
*/

  edm::Handle<vector<reco::Vertex>> vertices;
  iEvent.getByToken(vtxToken_, vertices);
  if (vertices->empty()) return false; 
  const reco::Vertex &PV = vertices->front();


  //START FILTERING BASED ON NUMBER OF GOOD MUONS
  ///////////////////////////////////////////////////////////////////////////////////////


  edm::Handle<vector<pat::Muon>> muons;
  iEvent.getByToken(muonToken_, muons);
  double fMuon_pt = -1.0;
/*
  for (const pat::Muon &mu : *muons) {

    if (mu.pt() > 25 &&  mu.eta() < 2.5 && mu.eta() > -2.5){
      if (mu.isTightMuon(PV)){
        if (mu.trackIso() < 3.0 && mu.normChi2() < 10){
          g_lepton_count++;
          fMuon_pt = mu.pt();
        }
      }
    }
  }
*/
  //ADD ELECTRON ISOLATION HERE............ IF THE ELECTRON HAS GOOD ID AND ISOLATION WE WANT TO VETO THE EVENT
/*
  edm::Handle<vector<pat::Electron>> electrons;
  iEvent.getByToken(electronToken_, electrons);
  for (const pat::Electron &el : *electrons) { 
      if (el.pt() < 5) continue;

      printf("elec with pt %4.1f, supercluster eta %+5.3f, sigmaIetaIeta %.3f (%.3f with full5x5 shower shapes), lost hits %d, pass conv veto %d\n",
         el.pt(), el.superCluster()->eta(), el.sigmaIetaIeta(), el.full5x5_sigmaIetaIeta(), 0, el.passConversionVeto());
    }

*/

    std::vector<const pat::Muon *> passedMuons;
    for (const pat::Muon &muon : *muons) {
      if (muon.pt() > MUON_MIN_PT &&
        fabs(muon.eta()) < MUON_MAX_ETA &&
        computeMuonIsolation(&muon) < MUON_TIGHT_RELISO &&
        fabs(muon.muonBestTrack()->dz(PV.position())) < MUON_MAX_DZ &&
        fabs(muon.muonBestTrack()->dxy(PV.position())) < MUON_MAX_DXY) {

          if (!muon.isTightMuon(PV)) continue;
          fMuon_pt = muon.pt();
          TLorentzVector mu; mu.SetPtEtaPhiM(muon.pt(), muon.eta(), muon.phi(), muon.mass());
          passedMuons.push_back(&muon);
        /*

        bool matched_to_trigger_obj = false;
        for (TLorentzVector trigobj : triggerobjects) {
          if (trigobj.DeltaR(mu) < TRIGGEROBJ_MATCH_DR) matched_to_trigger_obj = true; }
      / if (matched_to_trigger_obj) passedMuons.push_back(&muon);
      */
        }
    }

    // extra lepton veto
    bool skipped_one_passing_muon = false;
    bool extraMuon = false;
    for (const pat::Muon &muon : *muons) {
      if (muon.pt() > EXTRAMUON_MIN_PT &&
          fabs(muon.eta()) < EXTRAMUON_MAX_ETA &&
          computeMuonIsolation(&muon) < EXTRAMUON_MAX_RELISO &&
          fabs(muon.muonBestTrack()->dz(PV.position())) < EXTRAMUON_MAX_DZ &&
          fabs(muon.muonBestTrack()->dxy(PV.position())) < EXTRAMUON_MAX_DXY &&
          muon.isMediumMuon() ) {
        if (muon.pt() > MUON_MIN_PT &&
            fabs(muon.eta()) < MUON_MAX_ETA &&
            computeMuonIsolation(&muon) < MUON_TIGHT_RELISO &&
            fabs(muon.muonBestTrack()->dz(PV.position())) < MUON_MAX_DZ &&
            fabs(muon.muonBestTrack()->dxy(PV.position())) < MUON_MAX_DXY &&
            muon.isMediumMuon() ) {
          if (skipped_one_passing_muon) extraMuon = true;
          if (!skipped_one_passing_muon) skipped_one_passing_muon = true;
        } else {
          extraMuon = true;
        }
      }
    }

    bool extraElectron = false;

    
    edm::Handle<vector<pat::Electron>> electrons;
    iEvent.getByToken(electronToken_, electrons);
    for (const pat::Electron &electron : *electrons) {
      
      if (electron.pt() > EXTRAELECTRON_MIN_PT &&
          fabs(electron.eta()) < EXTRAELECTRON_MAX_ETA &&
          fabs(electron.gsfTrack()->dz(PV.position())) < EXTRAELECTRON_MAX_DZ &&
          fabs(electron.gsfTrack()->dxy(PV.position())) < EXTRAELECTRON_MAX_DXY &&
          electron.passConversionVeto() &&
          computeElectronIsolation(&electron) < EXTRAELECTRON_MAX_RELISO &&
          electron.gsfTrack()->lost() <= EXTRAELECTRON_MAX_LOSTTRACKS)

        extraElectron = true;
        
    }

if (extraElectron || extraMuon) return false;
if (passedMuons.size() == 0) return false;
//if (passedMuons.size() != 1) return false;

  //START FILTERING BASED ON GOOD BTAG
  ////////////////////////////////////////////////////////////////////////////////////////

  std::vector<double> btag_vals;
  edm::Handle<vector<pat::Jet>> jets;
  iEvent.getByToken(jetToken_, jets);

  for (const pat::Jet &j : *jets) {
    btag_vals.push_back((std::max(0.f,j.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"))));
  }

  bool fbtag_veto = false;
  for (double btag_val : btag_vals){

    if (btag_val > 0.890) fbtag_veto = true;

  }

  if (fbtag_veto) return false;

  //START FILTERING BASED ON MT
  ///////////////////////////////////////////////////////////////////////////////////////


  edm::Handle<vector<pat::MET>>  mets;
  iEvent.getByToken(metToken_, mets);
  const pat::MET &met = mets->front();
  double fmT = 0;
  if (fMuon_pt > 0 ) {
    fmT =TMath::Sqrt(2 * fMuon_pt * met.pt() * (1 - TMath::Cos((*passedMuons[0]).phi() -  met.phi())));
  } else {
    fmT = 0;
  }//

  if (fmT < 50.0) fPassed_events = fPassed_events - 1;

  ////////////////////////////////////////////////////////////////////////////////////////

  fPassed_events++;
 
  return true;


}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
wjets_filter::beginStream(edm::StreamID)
{
  fTotal_events = 0;
  fPassed_events = 0;
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
wjets_filter::endStream() {

  std::cout << "T=" << fTotal_events << std::endl;
  std::cout << "P=" << fPassed_events << std::endl;
  
}

// ------------ method called when starting to processes a run  ------------
/*
void
wjets_filter::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
wjets_filter::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
wjets_filter::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
wjets_filter::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
wjets_filter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(wjets_filter);

