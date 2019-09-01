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
