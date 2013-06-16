# The final program is called "myapp"
SUBDIRS = src 

AM_CXXFLAGS = ${QT4_CFLAGS}
AM_LDFLAGS = ${QT4_LIBS}

ACLOCAL_AMFLAGS = -I /usr/share/aclocal

# This line ensures that generated moc_*.cpp and resources.cpp files are
# deleted when we make clean.
CLEANFILES = $(filter moc_%.cpp,$(ccload_SOURCES)) 
