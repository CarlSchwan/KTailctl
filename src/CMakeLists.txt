# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023 Fabian Köhler <me@fkoehler.org>

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT ipo_output)

add_executable(ktailctl
    about.cpp
    app.cpp
    main.cpp
    peer.cpp
    peer_model.cpp
    preferences.cpp
    speed_statistics.cpp
    statistics.cpp
    status.cpp
    taildrop_receiver.cpp
    taildrop_sender.cpp
    tailscale.cpp
    tray_icon.cpp
    util.cpp
    resources.qrc
)

target_link_libraries(ktailctl
    KF5::ConfigCore
    KF5::ConfigGui
    KF5::CoreAddons
    KF5::I18n
    # KF5::Notifications
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::Svg
)

target_include_directories(
    ktailctl PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}/../tailctlpp
)
target_link_directories(
    ktailctl PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/../tailctlpp
)
target_link_libraries(ktailctl tailctlpp)
add_dependencies(ktailctl tailctlpp)

if(KTAILCTL_FLATPAK_BUILD)
    target_compile_definitions(ktailctl PRIVATE KTAILCTL_FLATPAK_BUILD)
endif()

kconfig_add_kcfg_files(ktailctl GENERATE_MOC ktailctlconfig.kcfgc)
install(TARGETS ktailctl ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

if(ipo_supported)
    set_property(TARGET ktailctl PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if(APPLE)
    kirigami_package_breeze_icons(ICONS
        application-exit
        applications-graphics
        computer
        document-send
        edit-copy
        help-about
        list-add
        media-playback-start
        proces-stop
        question
        smartphone
        vcs-pull
        vcs-push
        view-refresh
        window
    )
endif()
