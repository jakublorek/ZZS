#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    using namespace CryptoPP;

    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(std::cout));

    SecByteBlock key(AES::DEFAULT_KEYLENGTH);

    prng.GenerateBlock(key, key.size());

    string original_file("input.bin");
    string encrypted_file("wynik.bin");
    string decrypted_file("deszyfrowanie.bin");


    try
    {
        auto begin = std::chrono::high_resolution_clock::now();
        ECB_Mode< AES >::Encryption e;
        e.SetKey(key, key.size());

        FileSource file_source(original_file.c_str(), true,
            new StreamTransformationFilter(e,
                new FileSink(encrypted_file.c_str())
            )
        );
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        printf("Encryption time: %.3f seconds.\n", elapsed.count() * 1e-9);
    }
    catch (const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }


    cout << "Key: ";
    encoder.Put(key, key.size());
    encoder.MessageEnd();
    std::cout << std::endl;



    try
    {
        auto begin = std::chrono::high_resolution_clock::now();
        ECB_Mode< AES >::Decryption d;
        d.SetKey(key, key.size());

        FileSource s(encrypted_file.c_str(), true,
            new StreamTransformationFilter(d,
                new FileSink(decrypted_file.c_str())
            ) 
        ); 
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        printf("Decryption time: %.3f seconds.\n", elapsed.count() * 1e-9);
    }
    catch (const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }


    cout << "key length: " << AES::DEFAULT_KEYLENGTH << endl;
    cout << "block size: " << AES::BLOCKSIZE << endl;

    return 0;
}
