

void data_processing(uint32_t instruction);
uint32_t checkImmediate(void);
uint32_t checkSet(void);
uint32_t getOpcode(void);
uint32_t getRn(void);
uint32_t getRd(void);
uint32_t getBits(uint32_t instruction, uint32_t mask, int shiftNo);
uint32_t operandRotate(void);
uint32_t operandImmediate(void);
uint32_t oprandShift(void);
uint32_t operandRm(void);
void rotateRight(uint32_t* operand, int amount);

void printBits(uint32_t instruction);
