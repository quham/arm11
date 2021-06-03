#include "em_general.h"

bool checkBit(instr instruction, int bit_no) {
  return 1 & (instruction >> bit_no);
}

void setFlag(State* state, int index, bool bit) {
  word32 cpsr = state->regs[CPSR_INDEX];
  state->regs[CPSR_INDEX] = bit ? (cpsr | (1 << index)) : (cpsr & ~(1 << index));
}

bool checkImmediate(instr instruction) {
  return checkBit(instruction, 25);
}

bool checkSet(instr instruction) {
  return checkBit(instruction, 20);
}

// inclusive start_index, exclusive end_index
word32 getBits(word32 word, int start_index, int end_index) {
  word32 mask = UINT32_MAX >> (WORD_SIZE - (end_index - start_index));
  return (word >> start_index) & mask;
}

word32 condCode(instr instruction) {
  return getBits(instruction, 28, 32);
}

word32 getRs(instr instruction) {
  return getBits(instruction, 8, 12);
}

word32 getRm(instr instruction) {
  return getBits(instruction, 0, 4);
}

word32 getRd(instr instruction) {
  return getBits(instruction, 12, 16);
}

word32 getRn(instr instruction) {
  return getBits(instruction, 16, 20);
}

void rotateRight(word32* operand, int amount) {
  word32 msb = 0;
  word32 mask = 1;
  for (int i = 0; i < amount; i++) {
    msb = mask & *operand;
    *operand = (msb << (WORD_SIZE - 1)) | (*operand >> 1);
  }
}

word32 signExtend(word32 number, int no_of_bits) {
  word32 mask = ((1 << (WORD_SIZE - no_of_bits)) - 1) << no_of_bits;
  return number | (number & (1 << (no_of_bits - 1)) ? mask : 0);
}

bool addressValid(word32 addr) {
  if (addr > MEMORY_SIZE) {
    fprintf(stdout, "Error: Out of bounds memory access at address 0x%08x\n", addr);
    return false;
  }
  return true;
}

// Calculates the value of the operand2.
word32 getOperand(word32 instruction, bool immediate_cond, State* state) {
  word32 operand;

  if (immediate_cond) {
    operand = getBits(instruction, 0, 8);
    rotateRight(&operand, ROTATION_MULTIPLIER * getBits(instruction, 8, 12));
  } else {
    operand = state->regs[getRm(instruction)];
    word32 shift = getBits(instruction, 4, 12);
    word32 bit4 = checkBit(shift, 0);
    word32 shift_value = bit4 ? state->regs[getRs(instruction)] : getBits(instruction, 7, 12);
    word32 shift_type = getBits(shift, 1, 3);
    bool carry_out = checkBit(operand, (shift_value % WORD_SIZE) - 1);

    switch (shift_type) {
      case 0:  // logic shift left
        operand <<= shift_value;
        break;
      case 1:  // logic shift right
        operand >>= shift_value;
        break;
      case 2:  // arithmetic shift right
        operand = signExtend(operand, shift_value);
        break;
      case 3:  // rotate right
        rotateRight(&operand, shift_value);
    }

    if (immediate_cond) {
      setFlag(state, 29, carry_out);
    }
  }
  return operand;
}

/* ---------- Debugging ---------- */

// test functions
void decomp_tests() {
  instr test_instruction = 0xaf0c324e;

  instr bits_12_to_20 = 0xc3;  // inclusive
  if (getBits(test_instruction, 12, 20) == bits_12_to_20) {
    printf("getBits - pass\n");
  } else {
    printf("getBits - fail\n");
  }

  instr rd_bits = 0x3;
  if (getRd(test_instruction) == rd_bits) {
    printf("getRd - pass\n");
  } else {
    printf("getRd - fail\n");
  }

  instr cond_bits = 0xa;
  if (condCode(test_instruction) == cond_bits) {
    printf("condCode - pass\n");
  } else {
    printf("condCode - fail\n");
  }

  if (checkImmediate(test_instruction)) {
    printf("checkImmediate - pass\n");
  } else {
    printf("checkImmediate - fail\n");
  }
}
