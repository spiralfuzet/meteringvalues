# Feladat

Adott a mellékelt payload (metervalues_payload.txt). A payloadon belül több OCPP 1.6 "MeterValues" üzenet payloadja található.

Készítsen Debian/Ubuntu distro alatt fordítható/futtatható projektet, amely feldolgozva a mellékelt payloadot, kilistázza az egyes "MeterValues" üzenet (UID) által leírt töltőteljesítményt (3 fázis szummája).

- Használja a Jsoncpp library-t (https://github.com/open-source-parsers/jsoncpp)
- A forráskódot és egyéb fájlokat töltse fel egy GIT repóba (GitHub/GitLab/BitBucket) ami link birtokában szabadon elérhető/letölthető (git clone)
- A projekt git clone / git checkout / cmake .. / make lépések után fordíthatónak kell lennie


# Build

## Setting up package manger

### 1. Get vcpkg

Both on Windows and Linux
```
git submodule update --init --recursive
```

### 2. Bootstrap vcpkg

On Windows:
```
vcpkg\bootstrap-vcpkg.bat -disableMetrics
```
On Linux:
```
./vcpkg/bootstrap-vcpkg.sh -disableMetrics
```

### 3. Compile

Both on Windows and Linux:
```
cmake -B build -S .
cmake --build build
```

## Run

On Windows:
```
build\Debug\meteringvalues.exe meteringvalues_payload.json
```
On Linux:
```
build/meteringvalues meteringvalues_payload.json
```
