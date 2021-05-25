void data_processing(uint32_t instruction);
uint32_t checkImmediate(uint32_t instruction);
uint32_t checkSet(uint32_t instruction);
uint32_t getOpcode(uint32_t instruction);
uint32_t getRn(uint32_t instruction);
uint32_t getRd(uint32_t instruction);
uint32_t getBits(uint32_t instruction, uint32_t mask, int shiftNo);
uint32_t operandRotate(uint32_t instruction);
uint32_t operandImmediate(uint32_t insruction);
uint32_t oprandShift(uint32_t instruction);
uint32_t operandRm(uint32_t instruction);
void rotateRight(uint32_t* operand, int amount);

void printBits(uint32_t instruction);
