# The Static and Const Keywords
## Static
* Static global variables can only be accessed by functions within the file in which they are defined. This guards against variable name conflicts and unintended value changes if the document is imported to another program.
* Programs, such as main.c and static_const.c, are separated so that all functions are implemented when compiled together, but not treated as one compilation unit. This is necessary for the static keyword to properly limit the scope of variables and functions defined in src.c.
## Const
* Variables that should not be changed (and there is the available space in memory for it) should be declared as `const` and should be named in SCREAMING_SNAKE_CASE to denote their constant nature. Otherwise, global constants and magic numbers can generally be defined by the preprocessor using `#define`.
* Const also better informs the compiler how it should treat the variable, allowing it to perform its own optimization on its implementation.