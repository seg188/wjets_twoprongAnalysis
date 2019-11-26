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
