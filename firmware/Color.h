uint16_t BLUE = display->color565(0, 160, 255);
uint16_t RED = display->color565(255, 0, 0);
uint16_t GREEN = display->color565(0, 255, 0);
uint16_t CYAN = display->color565(0, 255, 255);
uint16_t ROSE = display->color565(255, 119, 255);
uint16_t YELLOW = display->color565(255, 255, 0);
uint16_t WHITE = display->color565(255, 255, 255);
uint16_t BLACK = display->color565(0, 0, 0);
uint16_t GRAY = display->color565(157, 161, 170);

uint16_t NightBLUE = display->color565(33, 59, 99);
uint16_t NightFiolet = display->color565(117, 93, 154);

const uint16_t ColorTable[]{ BLUE, RED, GREEN, CYAN, ROSE, YELLOW, WHITE, GRAY };
const uint16_t ColorTableNight[]{ NightBLUE, NightFiolet };
