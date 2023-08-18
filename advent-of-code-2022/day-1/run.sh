#!/bin/bash
as program.s -o program.o
ld program.o -o program
./program
