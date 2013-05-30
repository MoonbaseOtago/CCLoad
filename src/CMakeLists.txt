set(ccload_SRCS
   ccload.cpp
   main.cpp
   ccloadview.cpp
   mythread.cpp
   ttylock.cpp
 )

kde4_add_ui_files(ccload_SRCS ccloadview_base.ui prefs_base.ui)

kde4_add_kcfg_files(ccload_SRCS settings.kcfgc )

kde4_add_executable(ccload ${ccload_SRCS})

target_link_libraries(ccload ${KDE4_KDEUI_LIBS} )

install(TARGETS ccload ${INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( PROGRAMS ccload.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES ccload.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES ccloadui.rc  DESTINATION  ${DATA_INSTALL_DIR}/ccload )
