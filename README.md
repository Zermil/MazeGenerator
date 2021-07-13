# MazeGenerator 

Maze generator for console and SDL written in C++ using [depth-first search](https://en.wikipedia.org/wiki/Maze_generation_algorithm)

![maze](./maze.jpg)

## Quick start

### CONSOLE_ASCII_Windows:

### `Build:`
```console
> g++ main.cpp
```
### `Run:`
```console
> a.exe
```

### SDL_x64_VC:

This 'build' is using SDL for 64bit machine, but AFAIK you can use x86 / 32bit SDL and it will
work just fine. This 'build' is also using Visual Studio Community IDE to compile everything.

### `Build and Run`:
- In Project->Properties->Configuration Properties->VC++ Directories | Add to: Include Directories -> `dependencies/include`, Library Directories -> `dependencies/lib`
- In Project->Properties->Linker->Input->Additional Dependencies | Add: `SDL2.lib` and `SDL2main.lib`
- After you build your solution / project, add `SDL2.dll` to the folder containing your `.exe` file
