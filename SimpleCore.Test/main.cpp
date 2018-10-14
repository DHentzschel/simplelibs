#include <console.h>
#include <datetime.h>
#include <logger.h>
#include <file.h>

void testFile()
{
    Logger::info("Executing testFile():");

    File file("testfile.txt");
    const AString exampleFileContent = "This is an example for a text file";

    /* Read line by line */
    if (file.open(ReadOnly)) {
        AString fileContent;
        while (!file.atEnd()) {
            fileContent += file.readLine();
        }

        if (fileContent != exampleFileContent) {
            AString message = "Did not read file correctly. Expected: " + fileContent + " Actually: " + exampleFileContent;
            Logger::error(message.replaceAll("\n", "\\n").replaceAll("\r", "\\r"));
        }
        else {
            Logger::info("test open(), atEnd() and readLine() successful!");
        }
    }
    else {
        Logger::error("Could not open file " + file.getFilename());
    }

    /* Read all as string */
    const AString contentString = file.readAllText();
    


    /* Read all as byte array */
    const ByteArray contentArray = file.readAllBytes();
}

int main(int argc, char** argv)
{
    Logger::prepareLogFile("SimpleCore.Test-" + DateTime::getCurrentTimestamp());
    testFile();
    return 0;
}