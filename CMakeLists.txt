cmake_minimum_required(VERSION 3.16)

project(assign7 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        gameprocess.h gameprocess.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(assign7
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        startmenu.h startmenu.cpp startmenu.ui
        resizeablepicture.h resizeablepicture.cpp
        resources.qrc
        
        flappybird.h flappybird.cpp
        scoredisplay.h scoredisplay.cpp scoredisplay.ui
        getreadymenu.h getreadymenu.cpp getreadymenu.ui
        endmenu.h endmenu.cpp endmenu.ui
        scoredisplay2.h scoredisplay2.cpp scoredisplay2.ui
        release/generic/qtuiotouchplugin.dll release/iconengines/qsvgicon.dll release/imageformats/qgif.dll release/imageformats/qico.dll release/imageformats/qjpeg.dll release/imageformats/qsvg.dll release/multimedia/ffmpegmediaplugin.dll release/multimedia/windowsmediaplugin.dll release/networkinformation/qnetworklistmanager.dll release/platforms/qwindows.dll release/styles/qmodernwindowsstyle.dll release/tls/qcertonlybackend.dll release/tls/qschannelbackend.dll release/assign7.exe release/avcodec-61.dll release/avformat-61.dll release/avutil-59.dll release/D3Dcompiler_47.dll release/libgcc_s_seh-1.dll release/libstdc++-6.dll release/libwinpthread-1.dll release/opengl32sw.dll release/Qt6Core.dll release/Qt6Gui.dll release/Qt6Multimedia.dll release/Qt6Network.dll release/Qt6Svg.dll release/Qt6Widgets.dll release/swresample-5.dll release/swscale-8.dll
        release/generic/qtuiotouchplugin.dll release/iconengines/qsvgicon.dll release/imageformats/qgif.dll release/imageformats/qico.dll release/imageformats/qjpeg.dll release/imageformats/qsvg.dll release/multimedia/ffmpegmediaplugin.dll release/multimedia/windowsmediaplugin.dll release/networkinformation/qnetworklistmanager.dll release/platforms/qwindows.dll release/styles/qmodernwindowsstyle.dll release/tls/qcertonlybackend.dll release/tls/qschannelbackend.dll release/assign7.exe release/avcodec-61.dll release/avformat-61.dll release/avutil-59.dll release/D3Dcompiler_47.dll release/libgcc_s_seh-1.dll release/libstdc++-6.dll release/libwinpthread-1.dll release/opengl32sw.dll release/Qt6Core.dll release/Qt6Gui.dll release/Qt6Multimedia.dll release/Qt6Network.dll release/Qt6Svg.dll release/Qt6Widgets.dll release/swresample-5.dll release/swscale-8.dll
        flow chart.drawio flow chart.png uml class diagram.drawio uml class diagram.png

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET assign7 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(assign7 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(assign7
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(assign7 PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Multimedia
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.assign7)
endif()
set_target_properties(assign7 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS assign7
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(assign7)
endif()
