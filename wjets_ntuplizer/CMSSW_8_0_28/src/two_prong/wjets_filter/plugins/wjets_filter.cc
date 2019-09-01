
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


  edm::Handle<vector<reco::Vertex>> vertices;
  iEvent.getByToken(vtxToken_, vertices);
  if (vertices->empty()) return false; 
  const reco::Vertex &PV = vertices->front();

  //START FILTERING BASED ON NUMBER OF GOOD MUONS
  ///////////////////////////////////////////////////////////////////////////////////////

  bool fMuon_veto = true;
  edm::Handle<vector<pat::Muon>> muons;
  iEvent.getByToken(muonToken_, muons);
  int g_muon_count = 0;
  double fMuon_pt = -1.0;

  for (const pat::Muon &mu : *muons) {

    if (mu.pt() > 25 &&  mu.eta() < 2.5 && mu.eta() > -2.5){
      if (mu.isTightMuon(PV)){
        g_muon_count++;
        fMuon_pt = mu.pt();
      }
    }
  }

  if (g_muon_count == 1) fMuon_veto = false;
  if (fMuon_veto) return false;

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
    fmT =TMath::Sqrt(2 * fMuon_pt * met.pt() * (1 - TMath::Cos(met.phi())));
  } else {
    fmT = 0;
  }

  if (fmT < 50.0) return false;

  ////////////////////////////////////////////////////////////////////////////////////////

  return true;


}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
wjets_filter::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
wjets_filter::endStream() {
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
