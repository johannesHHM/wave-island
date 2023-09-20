# About

Final project for IDATT2505 Extended Reality.
A program that uses wave function collapse algorithm to generate an island.

# Compile and Run

## Linux Compile

Make sure GLU and GLUT is installed, and OpenGL is available.

```sh
git clone https://gitlab.stud.idi.ntnu.no/jhmorkem/IDATT2505-Project
mkdir IDATT2505-Project/build
cd IDATT2505-Project/build
cmake ..
make
```

## Run

The program can be run by giving it zero arguments, and going thorugh configuration at runtime.

```sh
./island
```

Or you can supply the 5 needed arguments, in order,

- size: integer from 0 to 50 (recommend 6 - 15)
- height: integer from 0 to 50 (recommend 4 - 8)
- houses: integer from 0 and up (recommend 0 - 4)
- trees: any integer for trees -1 for no trees (recommend 1)
- seed: any integer for seed, -1 for random seed (recommend -1)

```sh
./island 12 5 2 1 -1
```



