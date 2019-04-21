# Incorpore

Juego roguelike 2D desarrollado con C++ usando la librería [SMFL](https://www.sfml-dev.org/).

### Software usado:

* [Ubuntu 16.04](https://www.ubuntu.com/) (recommended)
* [Code::Blocks](http://www.codeblocks.org/)
* GNU GCC Compiler
* [SFML 2.X](https://www.sfml-dev.org/)

### Instalación de entorno:

1. instalación **OpenGL**:
 ```
 sudo apt-get install mesa-common-dev
 sudo apt-get install freeglut3-dev
 ```

2. instalación **C++ compilator** (en caso de no tenerlo):
 ```
 sudo apt-get install build-essential
 ```

3. instalación **SFML** para Linux:
 ```
 sudo apt-get install libsfml-dev
 sudo dpkg -L libsfm-dev
 ```

4. instalación **CodeBlocks (v.13)** [ si una **nueva versión** es deseada pasar al punto 5 ]
 ```
 sudo apt-get install codeblocks
 ```

5. instalación CodeBlocks (v. 16)
 ```
 sudo add-apt-repository ppa:damien-moore/codeblocks-stable
 sudo apt-get update
 sudo apt-get install codeblocks codeblocks-contrib
 ```

---

### Ejecución del proyecto:

1. Abrir codeblocks

2. "Open project"
 - File > Open > {folderPath}/Incorpore/Incorpore.cbp
 - Project mode: DEBUG (Build target)
 - Compile, execute and have fun ^^
