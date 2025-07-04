## Instalación OpenGL

Open GL sólo se encarga del renderizado, por lo que se requiere de algunas bibliotecas manejar el entorno gráfico de la computadora. 

### GLFW 

Es una biblioteca multiplataforma diseñada para facilitar el desarrollo de aplicaciones gráficas como `Open GL`, `Open GL ES` y `Vulkan`. Se encarga de: 

#### 🪟 Gestión de ventanas y contextos gráficos 
- Crear y administrar ventanas con un contexto gráfico asociado. 
- Soporte para multiples monitores y pantallas de alta resolución. 
- Control de modos de video y configuración de ventanas. 


#### 🎮 Entrada de usuario 

- Captura de eventos de teclado, ratón y joysticks/gamepads.
- Soporte para entradas por callbacks o por sondeo. 

#### 🧩 Compatibilidad Multiplataforma

- Proporciona una API uniforme para que tu código sea portable entre sistemas operativos. 


#### Instalción 

Descargar el repositorio de GLFW e instalar GLFW (en este caso se muestra como biblioteca compartida).
```bash
git clone https://github.com/glfw/glfw.git
cd glfw
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=ON ..
cmake --build . --config Release
sudo make install
```
El pasod de `cmake -DBUILD_SHARED_LIBS=ON ..` puede mandar errores pidiendo la instalación de bibliotecas faltantes, es importante que cada vez que se instalen bibliotecas faltantes se borre el directorio de `build` con `rm -rf build` y se vuelva a crear `mkdir build && cd build` para ejecutar de nuevo `cmake -DBUILD_SHARED_LIBS=ON ..`

Puede mandar un error de falta de biblioteca `wayland`, la cual se instala con
```bash
sudo apt install wayland-protocols libwayland-dev
```

Puede mandar un error de falta de biblioteca `xbkcommon`, la cual se instala con
```bash
sudo apt install libxkbcommon-dev
```

Puede mandar un error de falta de biblioteca `xbkcommon`, la cual se instala con
```bash
sudo apt install libxrandr-dev
```

### GLEW (OpenGL Extension Wrangler)

1. Se recomienda descargar el .zip o el .tgz de la página de [GLEW](https://glew.sourceforge.net/). 
2. Descomprimir el archivo. 
3. Estando dentro de la carpeta, en este caso `glew-2.2.0` se requiere compilar:
```
make extensions
make GLEW_DEST=/usr/local
```

