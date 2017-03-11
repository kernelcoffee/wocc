# Wocc
World of Warcraft Add-on manager with cli and Ui.

Requires:

Qt 5.7 and `bzip2`

Fedora 25:
With UI: `sudo dnf install qt5-qtbase qt5-qtdeclarative qt5-qtquickcontrols2 bzip2`
Withough UI: `sudo dnf install qt5-qtbase bzip2`

Developped and tested on Linux only.

## Build:

### QtCreator
Open project with QtCreator, select 5.7 kit or above and run.

### Console
 mkdir build
 cd build
 qmake ../src
 make -j<core>

## Usage
`wocc` to start the ui

`wocc arg` to run in console mode

### Build CLI only version

Add `CONFIG+=console_mode` to qmake arguements to disable Ui.
A confirmation message will appear if `console_mode` is enabled.