cmake_minimum_required(VERSION 3.14)
project(PacmanGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# Szuka QT6, jezeli nie ma to próbuje QT5
find_package(Qt6 COMPONENTS Core Gui Widgets Multimedia REQUIRED)
if (NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Core Gui Widgets Multimedia REQUIRED)
endif()
# Pliki z logiką
set(SOURCES
        src/main.cpp
        src/Game.cpp
        src/GameBoard.cpp
        src/GameWindow.cpp
        src/Pacman.cpp
        src/Ghost.cpp
        src/Entity.cpp
        src/Blinky.cpp
        src/Clyde.cpp
        src/Inky.cpp
        src/Pinky.cpp
        src/PowerUp.cpp
        src/PowerPellet.cpp
        src/MainMenu.cpp
        src/GameOverScreen.cpp
        src/WinScreen.cpp
        src/AudioManager.cpp
        src/ScoreboardWidget.cpp
        src/ScoreManager.cpp
)
# Pliki z klasami/metodami
set(HEADERS
        src/Game.h
        src/GameBoard.h
        src/GameWindow.h
        src/Pacman.h
        src/Ghost.h
        src/Entity.h
        src/Blinky.h
        src/Clyde.h
        src/Inky.h
        src/Pinky.h
        src/PowerUp.h
        src/PowerPellet.h
        src/MainMenu.h
        src/GameOverScreen.h
        src/WinScreen.h
        src/AudioManager.h
        src/ScoreboardWidget.h
        src/ScoreManager.h
)

# Zasoby gry
set(RESOURCES
        resources/resources.qrc
)

add_executable(PacmanGame ${SOURCES} ${HEADERS} ${RESOURCES})

if (Qt6_FOUND)
    target_link_libraries(PacmanGame PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia)
else()
    target_link_libraries(PacmanGame PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia)
endif()

# Problemy z odnalezieniem QT przez Debuger Konrada na Win 10...

##Kopiowanie wymaganych bibliotek dll
#add_custom_command(TARGET PacmanGame POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "C:/Qt/6.4.2/mingw_64/bin/Qt6Core.dll"
#        "C:/Qt/6.4.2/mingw_64/bin/Qt6Gui.dll"
#        "C:/Qt/6.4.2/mingw_64/bin/Qt6Widgets.dll"
#        $<TARGET_FILE_DIR:PacmanGame>)
## Kopiowanie folderu platforms
#add_custom_command(TARGET PacmanGame POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        "C:/Qt/6.4.2/mingw_64/plugins/platforms"
#        "$<TARGET_FILE_DIR:PacmanGame>/platforms")