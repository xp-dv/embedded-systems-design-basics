# UART Interrupts vs Polling

## HAL UART Receive Interrupt
The `HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)` function sets up an interrupt to receive data on the specified UART channel `*huart`, writing it to the buffer/array/char passed in `*pData`. The interrupt is not complete until the number of bytes of data specified by `Size` is received.

> `HAL_UART_Receive_IT()` is *non-blocking*. While the interrupt waits for data, the CPU is free to perform other tasks.

### Implementation
`HAL_UART_Receive_IT()` includes many built-in callbacks such as `HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)` which is automatically called when the specified number of bytes in `Size` has been received. Most implementations of UART interrupts receive 1 byte at a time. Each byte is written to or read from the circular buffer to prevent buffer overflow. Two pointers, read and write, are used to track the read and write progress of the processor. The buffer stores the data not yet read or written, allowing the slower of the two processes to catch up.

> Generally, interrupts are much more complicated to usably set up than polling, but have many benefits.
> The *non-blocking* nature of interrupts means that the LED continues blinking, uninterrupted by the UART communication process.

> [Lab 2 Part 2](/lab2/part2_uart_interrupt) uses a pseudo-circular-buffer which prevents overflow into unallocated memory, but doesn't queue multiple commands sent in quick succession as there is only one index pointer. The message is copied and the circular buffer is cleared when a specific character, line feed (LF) or `'\n'` in this case, is detected.

## HAL UART Receive Polling
The `HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)` function polls data on the specified UART channel `*huart`, writing it to the buffer/array/char passed in `*pData`. The operation is not complete until the number of bytes of data specified by `Size` is received.

> `HAL_UART_Receive()` is *blocking*. While polling, the CPU is delayed until all bytes are received or until the number of milliseconds in `Timeout` have passed.

### Implementation
Simply use `HAL_UART_Receive()` when data is expected, or constantly poll for it at all times if the delivery time is unknown, setting the exact number of bytes that must be received to `Size`, and setting the `Timeout` according to the serial baud rate of the slower of the two devices and how many bytes of data are being sent.

> Generally, polling is very easy to usably set up, but has many disadvantages as opposed to interrupts and DMA.
> Polling may be viable in simple projects for ease of setup or in situations where the data transfer is infrequent, doesn't need to be robust, and/or available DMA and interrupt channels are limited.
> The *blocking* nature of polling means that the UART communication process adds delay, equivalent to `Timeout`, to the LED blinking.
