ALL_SUBSYSTEMS+=two_prong
subdirs_src_two_prong = src_two_prong_wjets_filter src_two_prong_wjets_analyzer
ALL_COMMONRULES += src_two_prong_wjets_analyzer_test
src_two_prong_wjets_analyzer_test_parent := two_prong/wjets_analyzer
src_two_prong_wjets_analyzer_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_two_prong_wjets_analyzer_test,src/two_prong/wjets_analyzer/test,TEST))
ALL_PACKAGES += two_prong/wjets_analyzer
subdirs_src_two_prong_wjets_analyzer := src_two_prong_wjets_analyzer_plugins src_two_prong_wjets_analyzer_python src_two_prong_wjets_analyzer_test src_two_prong_wjets_analyzer_doc
ifeq ($(strip $(Pytwo_prongwjets_filter)),)
Pytwo_prongwjets_filter := self/src/two_prong/wjets_filter/python
src_two_prong_wjets_filter_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/two_prong/wjets_filter/python)
Pytwo_prongwjets_filter_files := $(patsubst src/two_prong/wjets_filter/python/%,%,$(wildcard $(foreach dir,src/two_prong/wjets_filter/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
Pytwo_prongwjets_filter_LOC_USE := self  
Pytwo_prongwjets_filter_PACKAGE := self/src/two_prong/wjets_filter/python
ALL_PRODS += Pytwo_prongwjets_filter
Pytwo_prongwjets_filter_INIT_FUNC        += $$(eval $$(call PythonProduct,Pytwo_prongwjets_filter,src/two_prong/wjets_filter/python,src_two_prong_wjets_filter_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,Pytwo_prongwjets_filter,src/two_prong/wjets_filter/python))
endif
ALL_COMMONRULES += src_two_prong_wjets_filter_python
src_two_prong_wjets_filter_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_two_prong_wjets_filter_python,src/two_prong/wjets_filter/python,PYTHON))
ALL_PACKAGES += two_prong/wjets_filter
subdirs_src_two_prong_wjets_filter := src_two_prong_wjets_filter_plugins src_two_prong_wjets_filter_python src_two_prong_wjets_filter_test src_two_prong_wjets_filter_doc
ALL_COMMONRULES += src_two_prong_wjets_filter_test
src_two_prong_wjets_filter_test_parent := two_prong/wjets_filter
src_two_prong_wjets_filter_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_two_prong_wjets_filter_test,src/two_prong/wjets_filter/test,TEST))
ifeq ($(strip $(Pytwo_prongwjets_analyzer)),)
Pytwo_prongwjets_analyzer := self/src/two_prong/wjets_analyzer/python
src_two_prong_wjets_analyzer_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/two_prong/wjets_analyzer/python)
Pytwo_prongwjets_analyzer_files := $(patsubst src/two_prong/wjets_analyzer/python/%,%,$(wildcard $(foreach dir,src/two_prong/wjets_analyzer/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
Pytwo_prongwjets_analyzer_LOC_USE := self  
Pytwo_prongwjets_analyzer_PACKAGE := self/src/two_prong/wjets_analyzer/python
ALL_PRODS += Pytwo_prongwjets_analyzer
Pytwo_prongwjets_analyzer_INIT_FUNC        += $$(eval $$(call PythonProduct,Pytwo_prongwjets_analyzer,src/two_prong/wjets_analyzer/python,src_two_prong_wjets_analyzer_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,Pytwo_prongwjets_analyzer,src/two_prong/wjets_analyzer/python))
endif
ALL_COMMONRULES += src_two_prong_wjets_analyzer_python
src_two_prong_wjets_analyzer_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_two_prong_wjets_analyzer_python,src/two_prong/wjets_analyzer/python,PYTHON))
