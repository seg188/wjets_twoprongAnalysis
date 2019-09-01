ALL_COMMONRULES += src_two_prong_wjets_analyzer_test
src_two_prong_wjets_analyzer_test_parent := two_prong/wjets_analyzer
src_two_prong_wjets_analyzer_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_two_prong_wjets_analyzer_test,src/two_prong/wjets_analyzer/test,TEST))
