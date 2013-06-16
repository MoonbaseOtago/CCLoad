# The final program is called "myapp"
bin_PROGRAMS = ccload

AM_CXXFLAGS = ${QT4_CFLAGS}
ccload_LDADD =  ${QT4_LIBS}

# You have two .cpp files you wrote, myapp.cpp and another.cpp
# Remember to include the name of the resource file with the .cpp extension.
ccload_SOURCES = \
	ccload.cpp \
	ccloadview.cpp \
	main.cpp \
	mythread.cpp \
	ttylock.cpp

# You have one .h file, it's called myapp.h. Therefore, here I list
# its mocced name, moc_myapp.cpp.
nodist_ccload_SOURCES = \
	moc_ccload.cpp \
	moc_ccloadview.cpp \
	ui_prefs_base.h \
	ui_ccloadview_base.h

# This is to ensure the myapp.h file is distributed in your myapp-0.1.tar.gz
# I also have a resources.qrc I need to include. The png is used in myapp.
EXTRA_DIST = \
	$(nodist_ccload_SOURCES:moc_%.cpp=%.h) 
	ccloadview_base.ui \
	prefs_base.ui

# This rule lets GNU make create any moc_*.cpp from the equivalent *.h
moc_%.cpp: %.h
	moc $< -o $@

ui_%.h: %.ui
	uic $< -o $@

# This line ensures that generated moc_*.cpp and resources.cpp files are
# deleted when we make clean.
CLEANFILES = $(filter moc_%.cpp,$(ccload_SOURCES)) 
