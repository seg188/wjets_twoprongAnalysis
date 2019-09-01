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
