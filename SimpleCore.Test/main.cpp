#include <console.h>
#include <file.h>

void testFile()
{
    File file("C:\\Users\\Test\\Documents\\filename.ext");

    /* Read line by line */
    if (!file.open(ReadOnly)) {
        while (!file.atEnd()) {
            Console::print(file.readLine());
        }
    }

    /* Read all as string */
    const AVector<AString> contentString = file.readAllText().split("\n");

    AVector<AString> container;

    /* Example to deserialize */
    for (auto it = contentString.begin(); it != contentString.end(); ++it) {
        if ((*it).startsWith("Example") || (*it).isFloatNumber()) {
            container.append(AString(*it).removeAll("."));
        }
    }

    /* Call this to remove duplicate entries */
    container.removeDuplicates();

    /* Read all as byte array */
    const ByteArray contentArray = file.readAllBytes();
}

int main(int argc, char** argv)
{
    testFile();
    return 0;
}