# EVM-Assembler

An assembler that translates Ethereum Virtual Machine mnemonics to bytecode. Developed for Linux, might work on other platforms.

This is a rudimentary implementation we needed for some experiments, it was not tested very thoroughly.


## Usage

Compiling EVM-Assembler: gcc -o easm easm.c

Running EVM-Assembler: easm [source.asm]

Source syntax:
* Opcodes must be written exactly as in the Ethereum yellow paper (all caps)
* Each opcode must be on a new line
* Parameters for PUSH1 to PUSH32 must be provided in hex with leading '0x'
* Comments can be written by prefixing the line with '#'

Created by (https://www.itseclabs.com "IT Security Labs")
