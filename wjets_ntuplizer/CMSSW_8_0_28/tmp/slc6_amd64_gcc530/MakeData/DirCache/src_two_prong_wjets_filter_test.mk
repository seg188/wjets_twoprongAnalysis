ALL_COMMONRULES += src_two_prong_wjets_filter_test
src_two_prong_wjets_filter_test_parent := two_prong/wjets_filter
src_two_prong_wjets_filter_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_two_prong_wjets_filter_test,src/two_prong/wjets_filter/test,TEST))
