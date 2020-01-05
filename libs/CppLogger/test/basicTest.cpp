//
// Created by Emilien Lemaire on 08/12/2019.
//

#include "Log.h"

int main() {
    Log::createConsole("Main console", Log::LevelDebug);
    Log::Debug("Main console", "Debug");
    Log::Info("Main console", "Info");
    Log::Warn("Main console", "Warning"); //Print the file and line where the log is called
    Log::Error("Main console", "Error"); //Print the file and line where the log is called
    Log::Fatal("Main console", "Fatal"); //Will exit your application with EXIT_FAILURE

    return 0;
}