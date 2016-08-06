# Some pratice with SFML.
![Gameplay](https://raw.githubusercontent.com/timadevelop/SFMLPractice/master/build/src/gameplay.png)

DOCS: http://www.sfml-dev.org/documentation/2.3.2-fr
SFML downloads: http://www.sfml-dev.org/download.php

### Download
Windows version: [Download](https://raw.githubusercontent.com/timadevelop/SFMLPractice/master/build/Release/win32_game.rar)

Linux version: build it.  [Download](https://raw.githubusercontent.com/timadevelop/SFMLPractice/master/build/Release/linux_game.zip)

### Build with cmake
```bash
install sfml from http://www.sfml-dev.org/download.php
$ cd build/linux_version
$ cmake ../..
$ make
$ ./Game
```
### Build in Visual Studio
Change SFML path in CMakeLists for windows

Open vs project in ./build/visualStudio/Game

Change project properties following oficial tutorial: http://www.sfml-dev.org/tutorials/2.3/start-vc.php
