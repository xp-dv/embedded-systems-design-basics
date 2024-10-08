# Button Debouncing
## Problem
[Lab 1 Part 3](/lab1/part3) toggles an LED based off of a flag triggered by a button press. It seemed like a straightforward task where I simply put `led_flag = 1` in the interrupt handler, then put the LED toggle, LED flag reset, and debouncing delay in an `if (led_flag == 1)` condition in the while loop. However, when I actually tested this implementation, the LED was toggling twice with a single button press. No matter how long I set the debouncing delay for, it did not solve the issue because the button was bouncing on _release_. Even though the interrupt was not set to detect the falling edge of the button signal, it could still trigger the interrupt for a second time if the bouncing caused it to rise again as the signal fell.
## Solution
The solution I decided on was **Button Press and Release Detection** using an external interrupt with rising/falling edge trigger detection.
> By setting a flag for both the press and release events, like this:
```
if (press_flag == 1) {
  /* Toggle LED */
  uint32_t odr = LED_GPIO_Port->ODR;
  LED_GPIO_Port->BSRR = PIN_RESET_MASK(odr & LED_Pin) | (~odr & LED_Pin);

  /* Debounce and Reset Flags */
  HAL_Delay(DEBOUNCE_TIME);
  press_flag = 0;

} else if (release_flag == 1) {
  /* Debounce and Reset Flags */
  HAL_Delay(DEBOUNCE_TIME);
  release_flag = 0;
}
```
> The main loop can process an action for both events, like this:
```
/* Press and release flags debounce both pos and neg edge of button press */
/* Ensure interrupt is set with rising/falling edge trigger detection */
if (BUTTON_GPIO_Port->IDR & BUTTON_Pin) {
  press_flag = 1;
} else {
  release_flag = 1;
}
```
This not only allows a debounce delay to be applied to both events, thus fixing the double toggle problem, it also allows any other action to be applied to either or both events.
