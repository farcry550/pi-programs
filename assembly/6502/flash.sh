#!bin/bash
vasm6502_oldstyle -Fbin -dotdir program.s
minipro -p AT28C256 -w a.out
