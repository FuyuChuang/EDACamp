# Checker for NTU EDA Camp 2017 Mini Contest
Intersection Manager

## Compilation
Just type `make`.

## Usage

```sh
Usage: ./checker <input file> <result file>
```

For convenience, type `./check.sh <input dir> <output dir>` to check all outputs
at once.

However, there are some requirements for `check.sh` to work correctly:
 * Every output file must have the same name as its corresponding input
 * All output files of a contestant must be placed in a directory under `<output
   dir>`

For example, if `<input dir>` is `input` and `<output dir>` is `output`,
```txt
input
├── case1.in
├── case2.in
└── case3.in
```

then `output` must have the following structure:
```txt
output
├── contestant-01
│   ├── case1.out
│   ├── case2.out
│   └── case3.out
├── contestant-02
│   ├── case1.out
│   ├── case2.out
│   └── case3.out
└── contestant-03
    ├── case1.out
    ├── case2.out
    └── case3.out
```
