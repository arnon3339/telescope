# Telescope

---

Geant4 - an Object-Oriented Toolkit for Simulation in HEP

## 1. Requrements

- Gean4 version 9.0
- CLEP
- ROOT
- CMAKE version in minimum (2.6)

## 2. Execute program

### 2.1 Go to app directory

```text
cd yourpath/telescope
```

### 2.2 Create build directory inside the app and move to it

```text
mkdir build && cd build
```

### 2.3 CMAKE and make it with number of threads

```text
cmake .. && make -j<number of threads>
```

### 2.4 Run the simulation

```text
./telescope
```
