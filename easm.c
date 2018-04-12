#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Current version
#define VERSION "v0.1"

//Output buffer initial size and increment when running out
#define BUFFER_INCREMENT 1048576

//Number of EVM instructions
#define INSTRUCTIONS_COUNT 130

//Stores information about an EVM instruction
typedef struct instruction_struct {
 char *mnemonic;
 unsigned char bytecode;
 unsigned int parameter_length;
} instruction;

//Array of all EVM instructions
instruction instructions[] = {{"STOP",         0x00,  0},
                              {"ADD",          0x01,  0},
                              {"MUL",          0x02,  0},
                              {"SUB",          0x03,  0},
                              {"DIV",          0x04,  0},
                              {"SDIV",         0x05,  0},
                              {"MOD",          0x06,  0},
                              {"SMOD",         0x07,  0},
                              {"ADDMOD",       0x08,  0},
                              {"MULMOD",       0x09,  0},
                              {"EXP",          0x0a,  0},
                              {"SIGNEXTEND",   0x0b,  0},
                              {"LT",           0x10,  0},
                              {"GT",           0x11,  0},
                              {"SLT",          0x12,  0},
                              {"SGT",          0x13,  0},
                              {"EQ",           0x14,  0},
                              {"ISZERO",       0x15,  0},
                              {"AND",          0x16,  0},
                              {"OR",           0x17,  0},
                              {"XOR",          0x18,  0},
                              {"NOT",          0x19,  0},
                              {"BYTE",         0x1a,  0},
                              {"SHA3",         0x20,  0},
                              {"ADDRESS",      0x30,  0},
                              {"BALANCE",      0x31,  0},
                              {"ORIGIN",       0x32,  0},
                              {"CALLER",       0x33,  0},
                              {"CALLVALUE",    0x34,  0},
                              {"CALLDATALOAD", 0x35,  0},
                              {"CALLDATASIZE", 0x36,  0},
                              {"CALLDATACOPY", 0x37,  0},
                              {"CODESIZE",     0x38,  0},
                              {"CODECOPY",     0x39,  0},
                              {"GASPRICE",     0x3a,  0},
                              {"EXTCODESIZE",  0x3b,  0},
                              {"EXTCODECOPY",  0x3c,  0},
                              {"BLOCKHASH",    0x40,  0},
                              {"COINBASE",     0x41,  0},
                              {"TIMESTAMP",    0x42,  0},
                              {"NUMBER",       0x43,  0},
                              {"DIFFICULTY",   0x44,  0},
                              {"GASLIMIT",     0x45,  0},
                              {"POP",          0x50,  0},
                              {"MLOAD",        0x51,  0},
                              {"MSTORE",       0x52,  0},
                              {"MSTORE8",      0x53,  0},
                              {"SLOAD",        0x54,  0},
                              {"SSTORE",       0x55,  0},
                              {"JUMP",         0x56,  0},
                              {"JUMPI",        0x57,  0},
                              {"PC",           0x58,  0},
                              {"MSIZE",        0x59,  0},
                              {"GAS",          0x5a,  0},
                              {"JUMPDEST",     0x5b,  0},
                              {"PUSH1",        0x60,  1},
                              {"PUSH2",        0x61,  2},
                              {"PUSH3",        0x62,  3},
                              {"PUSH4",        0x63,  4},
                              {"PUSH5",        0x64,  5},
                              {"PUSH6",        0x65,  6},
                              {"PUSH7",        0x66,  7},
                              {"PUSH8",        0x67,  8},
                              {"PUSH9",        0x68,  9},
                              {"PUSH10",       0x69, 10},
                              {"PUSH11",       0x6a, 11},
                              {"PUSH12",       0x6b, 12},
                              {"PUSH13",       0x6c, 13},
                              {"PUSH14",       0x6d, 14},
                              {"PUSH15",       0x6e, 15},
                              {"PUSH16",       0x6f, 16},
                              {"PUSH17",       0x70, 17},
                              {"PUSH18",       0x71, 18},
                              {"PUSH19",       0x72, 19},
                              {"PUSH20",       0x73, 20},
                              {"PUSH21",       0x74, 21},
                              {"PUSH22",       0x75, 22},
                              {"PUSH23",       0x76, 23},
                              {"PUSH24",       0x77, 24},
                              {"PUSH25",       0x78, 25},
                              {"PUSH26",       0x79, 26},
                              {"PUSH27",       0x7a, 27},
                              {"PUSH28",       0x7b, 28},
                              {"PUSH29",       0x7c, 29},
                              {"PUSH30",       0x7d, 30},
                              {"PUSH31",       0x7e, 31},
                              {"PUSH32",       0x7f, 32},
                              {"DUP1",         0x80,  0},
                              {"DUP2",         0x81,  0},
                              {"DUP3",         0x82,  0},
                              {"DUP4",         0x83,  0},
                              {"DUP5",         0x84,  0},
                              {"DUP6",         0x85,  0},
                              {"DUP7",         0x86,  0},
                              {"DUP8",         0x87,  0},
                              {"DUP9",         0x88,  0},
                              {"DUP10",        0x89,  0},
                              {"DUP11",        0x8a,  0},
                              {"DUP12",        0x8b,  0},
                              {"DUP13",        0x8c,  0},
                              {"DUP14",        0x8d,  0},
                              {"DUP15",        0x8e,  0},
                              {"DUP16",        0x8f,  0},
                              {"SWAP1",        0x90,  0},
                              {"SWAP2",        0x91,  0},
                              {"SWAP3",        0x92,  0},
                              {"SWAP4",        0x93,  0},
                              {"SWAP5",        0x94,  0},
                              {"SWAP6",        0x95,  0},
                              {"SWAP7",        0x96,  0},
                              {"SWAP8",        0x97,  0},
                              {"SWAP9",        0x98,  0},
                              {"SWAP10",       0x99,  0},
                              {"SWAP11",       0x9a,  0},
                              {"SWAP12",       0x9b,  0},
                              {"SWAP13",       0x9c,  0},
                              {"SWAP14",       0x9d,  0},
                              {"SWAP15",       0x9e,  0},
                              {"SWAP16",       0x9f,  0},
                              {"LOG0",         0xa0,  0},
                              {"LOG1",         0xa1,  0},
                              {"LOG2",         0xa2,  0},
                              {"LOG3",         0xa3,  0},
                              {"LOG4",         0xa4,  0},
                              {"CREATE",       0xf0,  0},
                              {"CALL",         0xf1,  0},
                              {"CALLCODE",     0xf2,  0},
                              {"RETURN",       0xf3,  0},
                              {"DELEGATECALL", 0xf4,  0},
                              {"INVALID",      0xfe,  0},
                              {"SELFESTRUCT",  0xff,  0},
                             };

//Main function
int main(int argc, char *argv[]) {
 FILE *fin;
 char *line = NULL;
 size_t len = 0;
 ssize_t read;
 unsigned int lines = 0;
 unsigned char *output = NULL;
 unsigned int output_length = 0;

 //Output version
 printf("easm %s\n", VERSION);

 //Check for correct number of command line parameters
 if (argc != 2) {
  printf("Usage: easm [input]\n");
  exit(EXIT_FAILURE);
 }

 //Open input file
 fin = fopen(argv[1], "r");
 if (fin == NULL) {
  printf("Error: Unable to open %s as input\n", argv[1]);
  exit(EXIT_FAILURE);
 }

 //Process each line of the input file
 while ((read = getline(&line, &len, fin)) != -1) {
  char *mnemonic;
  int instruction_iterator;
  instruction instruction_current;
  char *parameter;
  unsigned char parameter_bytecode[32];
  unsigned int parameter_bytecode_length = 0;

  //Count lines
  lines++;

  //Skip line if it is commented out by #
  if (line[0] == '#') {
   continue;
  }

  //Get the mnemonic of this line
  mnemonic = strtok(line, " \n");
  if (mnemonic == NULL) continue;

  //Find instruction that fits the mnemonic
  for (instruction_iterator = 0; instruction_iterator < INSTRUCTIONS_COUNT; instruction_iterator++) {
   if (strcmp(mnemonic, instructions[instruction_iterator].mnemonic) == 0) {
    instruction_current = instructions[instruction_iterator];
    break;
   }
  }
  if (instruction_iterator == INSTRUCTIONS_COUNT) {
   printf("Warning on line %u: Unknown mnemonic \"%s\", line skipped\n", lines, mnemonic);
   continue;
  }

  //Retrieve the parameter
  parameter = strtok(NULL, " \n");

  //Should there be a parameter for this menmonic?
  if (instruction_current.parameter_length > 0) {
   //Yes

   bool error = false;
   char hex[3];
   hex[2] = 0;

   //Check if there is exactly one parameter
   if (parameter == NULL) {
    printf("Warning on line %u: Parameter missing, line skipped\n", lines);
    continue;
   } else if (strtok(NULL, " \n") != NULL) {
    printf("Warning on line %u: Unnecessary second parameter, line skipped\n", lines);
    continue;
   }

   //Check if the parameter is hex
   if (strlen(parameter) <= 2 || parameter[0] != '0' || parameter[1] != 'x') {
    printf("Warning on line %u: Parameter format not understood, only hex with preceding 0x is supported, line skipped\n", lines);
    continue;
   }

   //Is the parameter as long as it should be for this mnemonic?
   if (strlen(parameter) > instruction_current.parameter_length*2+2 || strlen(parameter) < instruction_current.parameter_length*2+1) {
    printf("Warning on line %u: Wrong parameter length for mnemonic \"%s\", line skipped\n", lines, mnemonic);
    continue;
   }

   //If there is an uneven number of hex characters convert the first character to bytecode
   if (strlen(parameter) % 2) {
    hex[1] = parameter[2];
    if (sscanf(&hex[1], "%1hhx", parameter_bytecode) == EOF) {
     printf("Warning on line %u: Parameter format not understood, only hex is supported, line skipped\n", lines);
     continue;
    }
    parameter_bytecode_length = 1;
   }

   //Convert remaining hex characters to bytecode
   for (int parameter_length = parameter_bytecode_length+2; parameter[parameter_length] != 0; parameter_length += 2) {
    hex[0] = parameter[parameter_length];
    hex[1] = parameter[parameter_length+1];
    if (sscanf(hex, "%2hhx", &parameter_bytecode[parameter_bytecode_length]) == EOF) {
     error = true;
     break;
    }
    parameter_bytecode_length++;
   }
   if (error) {
    printf("Warning on line %u: Parameter format not understood, only hex is supported, line skipped\n", lines);
    continue;
   }
  } else if (parameter != NULL) {
   //No (there should not be a parameter on this line)
   printf("Warning on line %u: Unnecessary parameter, line skipped\n", lines);
   continue;
  }

  //Allocate additional memory if necessary
  static unsigned int buffer_chunks = 0;
  if (output_length + 33 > buffer_chunks*BUFFER_INCREMENT) {
   buffer_chunks++;
   output = realloc(output, buffer_chunks*BUFFER_INCREMENT);
   if (output == NULL) {
    printf("Unable to reserve %i byte of memory\n", buffer_chunks*BUFFER_INCREMENT);
    exit(EXIT_FAILURE);
   }
  }

  memcpy(&output[output_length], &instruction_current.bytecode, 1);
  output_length++;

  memcpy(&output[output_length], &parameter_bytecode, parameter_bytecode_length);

  output_length += parameter_bytecode_length;
 }

 //Output the result
 printf("0x");
 for (int i = 0; i < output_length; i++) {
  printf("%02x", output[i]);
 }
 printf("\n");

 //Free memory and close files
 if (line) free(line);
 free(output);
 fclose(fin);

 exit(EXIT_SUCCESS);
} 
