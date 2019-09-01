# Command line options
from FWCore.ParameterSet.VarParsing import VarParsing
import FWCore.ParameterSet.Config as cms

options = VarParsing ("python")
options.register("file", "", VarParsing.multiplicity.singleton, VarParsing.varType.string, "which file to run over")
options.register("sample", "", VarParsing.multiplicity.singleton, VarParsing.varType.string, "which sample we want to run over")
options.register("globalTag", "", VarParsing.multiplicity.singleton, VarParsing.varType.string, "global tag to use when running")
options.register("out", "output.root", VarParsing.multiplicity.singleton, VarParsing.varType.string, "name of output rootfile")
options.setDefault("maxEvents", -1)
options.register("mcXS", 1.0, VarParsing.multiplicity.singleton, VarParsing.varType.float, "mc cross section, if desired to be filled in trees")
options.register("mcN", 1.0, VarParsing.multiplicity.singleton, VarParsing.varType.float, "mc number generated, if desired to be filled in trees")

options.parseArguments()

# process start
process = cms.Process("wjetsTwoprongAnalysis")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

# Source
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring( options.file ))

# Global Tag
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = options.globalTag

# output analyzer ROOT file
process.TFileService = cms.Service( "TFileService", fileName = cms.string( options.out ) )

process.Analyzer = cms.EDAnalyzer("wjets_analyzer",
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    muons = cms.InputTag("slimmedMuons"),
    electrons = cms.InputTag("slimmedElectrons"),
    taus = cms.InputTag("slimmedTaus"),
    photons = cms.InputTag("slimmedPhotons"),
    jets = cms.InputTag("slimmedJets"),
    fatjets = cms.InputTag("slimmedJetsAK8"),
    mets = cms.InputTag("slimmedMETs"),
    mcXS = cms.untracked.double(1.0),
    mcN = cms.untracked.double(1.0),

)

process.Filter = cms.EDFilter("wjets_filter",
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    muons = cms.InputTag("slimmedMuons"),
    electrons = cms.InputTag("slimmedElectrons"),
    taus = cms.InputTag("slimmedTaus"),
    photons = cms.InputTag("slimmedPhotons"),
    jets = cms.InputTag("slimmedJets"),
    fatjets = cms.InputTag("slimmedJetsAK8"),
    mets = cms.InputTag("slimmedMETs"),
)

process.Analyzer.mcXS = options.mcXS
process.Analyzer.mcN = options.mcN

# Global Tag
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
if options.globalTag == 'mc2016':
  process.GlobalTag.globaltag = '80X_mcRun2_asymptotic_2016_TrancheIV_v6'
elif options.globalTag == 'mc2015':
  process.GlobalTag.globaltag = '76X_mcRun2_asymptotic_v12'
elif options.globalTag == 'data2015':
  process.GlobalTag.globaltag = '74X_dataRun2_HLT_v3'
elif options.globalTag == 'data2016':
  process.GlobalTag.globaltag = '80X_dataRun2_2016SeptRepro_v7'
else:
  process.GlobalTag.globaltag = options.globalTag
if process.GlobalTag.globaltag == "":
  print "Must choose a GlobalTag, GlobalTag left blank... exiting"
  sys.exit()
print "Using GlobalTag: ", process.GlobalTag.globaltag



# the Path
process.p = cms.Path(process.Filter * process.Analyzer)
