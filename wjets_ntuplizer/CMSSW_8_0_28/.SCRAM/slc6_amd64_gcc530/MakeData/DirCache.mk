ifeq ($(strip $(two_prongwjets_filterAuto)),)
two_prongwjets_filterAuto := self/src/two_prong/wjets_filter/plugins
PLUGINS:=yes
two_prongwjets_filterAuto_files := $(patsubst src/two_prong/wjets_filter/plugins/%,%,$(wildcard $(foreach dir,src/two_prong/wjets_filter/plugins ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
two_prongwjets_filterAuto_BuildFile    := $(WORKINGDIR)/cache/bf/src/two_prong/wjets_filter/plugins/BuildFile
two_prongwjets_filterAuto_LOC_USE := self  FWCore/PluginManager FWCore/ParameterSet DataFormats/EgammaCandidates DataFormats/Math CommonTools/UtilAlgos DataFormats/VertexReco DataFormats/BeamSpot L1Trigger/GlobalTriggerAnalyzer RecoEcal/EgammaCoreTools RecoEgamma/EgammaTools CondFormats/EcalObjects CondFormats/DataRecord Geometry/CaloGeometry Geometry/EcalAlgo SimDataFormats/PileupSummaryInfo PhysicsTools/Utilities DataFormats/PatCandidates
two_prongwjets_filterAuto_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,two_prongwjets_filterAuto,two_prongwjets_filterAuto,$(SCRAMSTORENAME_LIB),src/two_prong/wjets_filter/plugins))
two_prongwjets_filterAuto_PACKAGE := self/src/two_prong/wjets_filter/plugins
ALL_PRODS += two_prongwjets_filterAuto
two_prong/wjets_filter_forbigobj+=two_prongwjets_filterAuto
two_prongwjets_filterAuto_INIT_FUNC        += $$(eval $$(call Library,two_prongwjets_filterAuto,src/two_prong/wjets_filter/plugins,src_two_prong_wjets_filter_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
two_prongwjets_filterAuto_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,two_prongwjets_filterAuto,src/two_prong/wjets_filter/plugins))
endif
ALL_COMMONRULES += src_two_prong_wjets_filter_plugins
src_two_prong_wjets_filter_plugins_parent := two_prong/wjets_filter
src_two_prong_wjets_filter_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_two_prong_wjets_filter_plugins,src/two_prong/wjets_filter/plugins,PLUGINS))
ifeq ($(strip $(two_prongwjets_analyzerAuto)),)
two_prongwjets_analyzerAuto := self/src/two_prong/wjets_analyzer/plugins
PLUGINS:=yes
two_prongwjets_analyzerAuto_files := $(patsubst src/two_prong/wjets_analyzer/plugins/%,%,$(wildcard $(foreach dir,src/two_prong/wjets_analyzer/plugins ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
two_prongwjets_analyzerAuto_BuildFile    := $(WORKINGDIR)/cache/bf/src/two_prong/wjets_analyzer/plugins/BuildFile
two_prongwjets_analyzerAuto_LOC_USE := self  FWCore/PluginManager FWCore/ParameterSet DataFormats/EgammaCandidates DataFormats/Math CommonTools/UtilAlgos DataFormats/VertexReco DataFormats/BeamSpot L1Trigger/GlobalTriggerAnalyzer RecoEcal/EgammaCoreTools RecoEgamma/EgammaTools CondFormats/EcalObjects CondFormats/DataRecord Geometry/CaloGeometry Geometry/EcalAlgo SimDataFormats/PileupSummaryInfo PhysicsTools/Utilities DataFormats/PatCandidates
two_prongwjets_analyzerAuto_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,two_prongwjets_analyzerAuto,two_prongwjets_analyzerAuto,$(SCRAMSTORENAME_LIB),src/two_prong/wjets_analyzer/plugins))
two_prongwjets_analyzerAuto_PACKAGE := self/src/two_prong/wjets_analyzer/plugins
ALL_PRODS += two_prongwjets_analyzerAuto
two_prong/wjets_analyzer_forbigobj+=two_prongwjets_analyzerAuto
two_prongwjets_analyzerAuto_INIT_FUNC        += $$(eval $$(call Library,two_prongwjets_analyzerAuto,src/two_prong/wjets_analyzer/plugins,src_two_prong_wjets_analyzer_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
two_prongwjets_analyzerAuto_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,two_prongwjets_analyzerAuto,src/two_prong/wjets_analyzer/plugins))
endif
ALL_COMMONRULES += src_two_prong_wjets_analyzer_plugins
src_two_prong_wjets_analyzer_plugins_parent := two_prong/wjets_analyzer
src_two_prong_wjets_analyzer_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_two_prong_wjets_analyzer_plugins,src/two_prong/wjets_analyzer/plugins,PLUGINS))
