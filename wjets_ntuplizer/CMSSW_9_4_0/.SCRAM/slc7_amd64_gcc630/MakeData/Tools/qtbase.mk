ALL_TOOLS      += qtbase
qtbase_EX_INCLUDE := /cvmfs/cms.cern.ch/slc7_amd64_gcc630/external/qt/4.8.7/include /cvmfs/cms.cern.ch/slc7_amd64_gcc630/external/qt/4.8.7/include/Qt /cvmfs/cms.cern.ch/slc7_amd64_gcc630/external/qt/4.8.7/include/QtCore /cvmfs/cms.cern.ch/slc7_amd64_gcc630/external/qt/4.8.7/include/QtXml
qtbase_EX_LIB := QtCore QtXml
qtbase_EX_USE := root_cxxdefaults zlib
qtbase_EX_FLAGS_CPPDEFINES  := -DQT_ALTERNATE_QTSMANIP -DQT_CLEAN_NAMESPACE -DQT_THREAD_SUPPORT

