#!/bin/bash

cluster=$1
process=$2

# CMSSW setup etc
export SCRAM_ARCH="slc7_amd64_gcc700"
export VO_CMS_SW_DIR="/cms/base/cmssoft"
export COIN_FULL_INDIRECT_RENDERING=1
source $VO_CMS_SW_DIR/cmsset_default.sh

cd ~/wjets_twoprongAnalysis/wjets_ntuplizer/CMSSW_9_4_0/src/two_prong/wjets_analyzer/test 
eval `scramv1 runtime -sh`

#./RUNGUN.sh /cms/xaastorage/MINIAOD/2016/GJets_DR/GJets_DR0p4_HT-200to400/ PAT ../outputs/GJets/

cmsRun cmssw_wjetstest_cfg.py file=/store/mc/RunIISummer16MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/FE6128F4-23BD-E611-A913-0090FAA57F14.root globalTag=mc2016
