# My FreeRTOS Project

A FreeRTOS project for POSIX/Linux systems.

## Requirements

- Linux/POSIX environment
- GCC compiler
- Make build tool
- pthread library

## Building

```bash
make
```

## Running

```bash
./build/posix_demo
```

Press `Ctrl+C` to stop.

## Project Structure

```
my-freertos-project/
├── main.c              # Your main application code
├── Src/                # Additional source files
├── Inc/                # Header files
├── core/               # FreeRTOS kernel and libraries
├── Makefile            # Build configuration
└── README.md           # This file
```

## Getting Started

1. **Edit main.c** - Add your tasks and application logic
2. **Build** - Run `make` to compile
3. **Run** - Execute `./build/posix_demo`

## Adding New Tasks

```c
void MyNewTask(void *pvParameters) {
    while(1) {
        // Your task code here
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// In main():
xTaskCreate(MyNewTask, "MyTask", TASK_STACK_SIZE, NULL, 1, NULL);
```

## Important Notes

- Stack size is set to `configMINIMAL_STACK_SIZE` - adjust if needed
- The trace recorder stack monitor is disabled (fixes 64-bit bug)
- Use mutexes/semaphores for inter-task communication

## License

See core/FreeRTOS-License/ for FreeRTOS licensing.
