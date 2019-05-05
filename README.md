# Tuxdriver

## Project description

libtuxdriver is a shared library to control Tuxdroid.

## How to build

- Windows

Download and install [MinGW-w64](https://mingw-w64.org/doku.php/download/mingw-builds) and add to path the `bin` folder to path.

Go in win32 folder and run

```powershell
mingw32-make.exe
```

You should find libtuxdriver.dll in win32 folder.

- Ubuntu and similar

Install required tools

```bash
sudo apt install build-essentials
```

Then go in unix folder and run

```bash
make
```

You should find libtuxdriver.so in unix folder.

## Prebuilt download

View GitHub's [releases](https://github.com/kowalski7cc/tuxdriver/releases) section

## License

GNU General Public License v2.0