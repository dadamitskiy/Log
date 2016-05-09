# Log – Version 1.6

Trello Feature Board: https://trello.com/b/pO2yKzYp/log 

Log is a lightweight logging system that only has a single .h and .cpp. Using the system is extremely easy. Simply start by including Log.h into whatever file you need to log and call DA_LOG().

This project was built and includes project files for Visual Studio 2015. Build to run on a Windows, 64 bit platform. Windows 32-bit and 64-bit executables of the project are included in zip files.

Calling DA_LOG() will ask for the following parameters:
  1. Category: Any category you want to label this message under.
  2. VerbosityLevel: Either Default, Debug, Warning, Error, or Fatal to specify the type of message.
  3. OutputType: Either All, ConsoleWindow, OutputWindow, or TextFile. ConsoleWindow will log to a console window, OutputWindow is designed to log to Visual Studio output window, TextFile will log to a text file titled whatever your category name is under a folder called OutputLogs where the vcproj exists, and All will log to all three.
  4. DetailLevel: Either Low, Medium, or High. Low just logs the message, while medium and high provide the file, function, and line the log statement is called. Also, high will add a timestamp.
  5. Format: The message to log.
  6.  __VA_ARGS__ : Optional parameter that works very similar to printf in C++. Use the Format parameter and this parameter to fill out the message.

Example:
DA_LOG(MyCategory, Error, TextFile, Low, "This is my %s message.", "error");

This will log "This is my error message." to a text file called 'MyCategory.txt'.

See ExampleUsage.cpp for more examples of using the log system.
