# SuperMarioBros

----Description

Yet another Super Mario Bros. (NES) clone.
This is a side project I created to improve my C++.


----Libraries

SFML, spdlog.


----Compatibilities

x86, x64.


----How to make it run on your local repo :

Clone the repo on your the remote machine. Then download the followings :
- SFML x64 : https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-64-bit.zip
- SFML x86 : https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-32-bit.zip
- spdlog : https://github.com/gabime/spdlog

You can only install SFML x64 or x86 if you want, but choose at least one to be able to compile.
-SFML includes should be put in the folder External/SFML-x64/include and External/SFML-x86/include. (example : External/SFML-x86/include/SFML/...)
-SFML libs should be put in the folder External/SFML-x64/lib and External/SFML-x86/lib. (example : External/SFML-x86/lib/SFML/...)
-spdlog includes should be put in the folder External/SPDLOG/include. (example : External/SPDLOG/include/spdlog/)

You should be able to compile by opening the solution with Visual Studio 19 (only tested IDE).
