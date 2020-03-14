# CppLogger Library

This is just a simple logger library.

This library was only tested on macOS Catalina to make it work on your system you might have to modify the **CMakeLists.txt** file.
## Install
To install the library just execute the following commands:
``` shell script
cmake .
make
make install
```

## Usage

In your CMakeList.txt:
```cmake
include_directories(/usr/local/include)

#Other stuff

find_package(CppLogger REQUIRED)

#Other stuff

include_directories(${CPPLOGGER_INCLUDE_DIR})
target_link_libraries(yourProjectTarget ${CPPLOGGER_LIBRARY})
```

In your source files:
``` c++
#include <Log.h>
```

In your **main** function:
``` c++
// To create a debug level console prompt as [Main console]
Log::createConsole("Main console", Log::LevelDebug);
```

Available log levels:

| Level|
|---|
| **Log**::LevelDebug  |
| **Log**::LevelInfo  |
| **Log**::LevelWarn  |
| **Log**::LevelError  |
| **Log**::LevelFatal  |

Anywhere you want to log to the console:
``` c++
Log::Debug("Main console", "Debug");
Log::Info("Main console", "Info");
Log::Warn("Main console", "Warning"); //Print the file and line where the log is called
Log::Error("Main console", "Error"); //Print the file and line where the log is called
Log::Fatal("Main console", "Fatal"); //Will exit your application with EXIT_FAILURE
```
These are macro definitions, **Log::** is not mandatory but it is advised to use it for better
readability. The second argument can accept any type that can be logged via **_cout <<_** .

The code above will prompt:
``` shell script

[Main console] Debug: Debug
[Main console] Info: Info
[Main console] Warning: $file:$line: Warning
[Main console] Error: $file:$line: Error
[Main console] Fatal error: $file:$line: Fatal

Process finished with exit code 1
 ```
 ## To Do
 * Add a formatting function for the consoles prompt.
