#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

std::vector<unsigned char> readFileToByteArray(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    return std::vector<unsigned char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void saveByteArrayToHeader(const std::vector<unsigned char>& byteArray, const std::string& outputFilename) {
    std::ofstream outputFile(outputFilename);

    //outputFile << "#ifndef UM_H\n#define UM_H\n\n";
    //outputFile << "#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n";

    outputFile << "static const unsigned char um_data[" << byteArray.size() << "] = {\n";

    for (size_t i = 0; i < byteArray.size(); ++i) {
        outputFile << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byteArray[i]);
        if (i < byteArray.size() - 1) {
            outputFile << ",";
        }
        if ((i + 1) % 12 == 0) {
            outputFile << "\n";
        }
        else {
            outputFile << " ";
        }
    }

    outputFile << "\n};\n\n";
    //outputFile << "#ifdef __cplusplus\n}\n#endif\n\n";
    //outputFile << "#endif // UM_H\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_dll>\n";
        return 1;
    }

    std::string dllPath = argv[1];
    std::vector<unsigned char> byteArray = readFileToByteArray(dllPath);
    saveByteArrayToHeader(byteArray, "um.h");

    std::cout << "DLL successfully converted to byte array and saved as um.h\n";
    return 0;
}