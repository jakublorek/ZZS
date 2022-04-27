#include <iostream>
#include <time.h>
#include <stdio.h>
#include <chrono>


using namespace std;


////////////////////////////////////////////////////////////////////
/// PREDIFINED TABLES //////////////
///////////////////////////////////////////////////////////////////


/// INITIAL PERMUTATION TABLE /////

static int IP[64] =
{ 58, 50, 42, 34, 26, 18, 10, 2,
  60, 52, 44, 36, 28, 20, 12, 4,
  62, 54, 46, 38, 30, 22, 14, 6,
  64, 56, 48, 40, 32, 24, 16, 8,
  57, 49, 41, 33, 25, 17, 9, 1,
  59, 51, 43, 35, 27, 19, 11, 3,
  61, 53, 45, 37, 29, 21, 13, 5,
  63, 55, 47, 39, 31, 23, 15, 7 };


/// FINAL PERMUTATION TABLE /////

static int FIP[64] =
{ 40, 8, 48, 16, 56, 24, 64, 32,
  39, 7, 47, 15, 55, 23, 63, 31,
  38, 6, 46, 14, 54, 22, 62, 30,
  37, 5, 45, 13, 53, 21, 61, 29,
  36, 4, 44, 12, 52, 20, 60, 28,
  35, 3, 43, 11, 51, 19, 59, 27,
  34, 2, 42, 10, 50, 18, 58, 26,
  33, 1, 41, 9, 49, 17, 57, 25 };


/// EXPANSION TABLE /////

static int E[48] =
{ 32, 1, 2, 3, 4, 5,
  4, 5, 6, 7, 8, 9,
  8, 9, 10, 11, 12, 13,
  12, 13, 14, 15, 16, 17,
  16, 17, 18, 19, 20, 21,
  20, 21, 22, 23, 24, 25,
  24, 25, 26, 27, 28, 29,
  28, 29, 30, 31, 32, 1 };



/////////////////////////     S - BOXES      ////////////////////////////////

/////// S1 /////////

static int s1[4][16] =
{ 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
  0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
  4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
  15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 };


/////// S2 /////////

static int s2[4][16] =
{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
  3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
  0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
  13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 };


/////// S3 /////////

static int s3[4][16] =
{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
  13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1, 
  13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
  1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 };



/////// S4 /////////

static int s4[4][16] =
{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
  13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
  10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
  3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 };



/////// S5 /////////

static int s5[4][16] =
{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
  14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
  4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
  11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 };



/////// S6 /////////

static int s6[4][16] =
{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
  10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
  9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
  4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 };



/////// S7 /////////

static int s7[4][16] =
{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
  13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
  1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
  6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 };



/////// S8 /////////

static int s8[4][16] =
{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
  1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
  7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
  2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 };





////////////   PERMUTATION TABLE   /////////////

static int P[32] =
{ 16, 7, 20, 21, 29, 12, 28, 17,
  1, 15, 23, 26, 5, 18, 31, 10,
  2, 8, 24, 14, 32, 27, 3, 9,
  19, 13, 30, 6, 22, 11, 4, 25 };




/////////////////////////////    PERMUTATION CHOICE TABLES    //////////////////////////

//////// ONE ///////////

static int PC1[56] =
{ 57, 49, 41, 33, 25, 17, 9,
  1, 58, 50, 42, 34, 26, 18,
  10, 2, 59, 51, 43, 35, 27,
  19, 11, 3, 60, 52, 44, 36,
  63, 55, 47, 39, 31, 23, 15,
  7, 62, 54, 46, 38, 30, 22,
  14, 6, 61, 53, 45, 37, 29,
  21, 13, 5, 28, 20, 12, 4 };


//////// TWO ///////////

static int PC2[48] =
{ 14, 17, 11, 24, 1, 5, 3, 28,
  15, 6, 21, 10, 23, 19, 12, 4,
  26, 8, 16, 7, 27, 20, 13, 2,
  41, 52, 31, 37, 47, 55, 30, 40,
  51, 45, 33, 48, 44, 49, 39, 56,
  34, 53, 46, 42, 50, 36, 29, 32 };



void buffer_to_64binary(char buffer[8], bool output[64]) {

    for (int i = 0; i < 8; i++) {
        unsigned int mask = 128;
        for (int j = 0; j < 8; j++) {
            if (buffer[i] bitand mask) output[i * 8 + j] = true;
            else output[i * 8 + j] = false;
            mask >>= 1;
        }
    }

}

void string_to_64binary(string key, bool output[64]) {

    for (int i = 0; i < 8; i++) {
        unsigned int mask = 128;
        for (int j = 0; j < 8; j++) {
            if (key[i] bitand mask) output[i * 8 + j] = 1;
            else output[i * 8 + j] = 0;
            mask >>= 1;
        }
    }

}

void bit64tochar(bool input[64], char output[8]) {
    

    for (int j = 0; j < 8; j++) {
        int counter = 128;
        unsigned int c = 0;

        for (int i = 0; i < 8; i++) {
            if (input[8*j + i] == true) c += counter;
            counter /= 2;
        }

        output[j] = static_cast<char>(c);
    }
}

void LS(bool input[28], int n) {
    for (int p = 0; p < n; p++) {
        bool temp = input[0];
        for (int i = 0; i < 27; i++) {
            input[i] = input[i + 1];
        }
        input[27] = temp;
    }
}

void Initial_Perm(bool mess[64], bool output[64]) {
    for (int i = 0; i < 64; i++) {
        output[i] = mess[IP[i]-1];
    }
}

int bin2int(bool input[4], int n) {
    int resault = 0;
    int c = 1;
    for (int i = n; i > 0; i--) {
        if (input[i - 1] == 1) resault += c;
        c *= 2;
    }

    return resault;
}

void DES(bool message_64b[64], bool subkeys[16][48]) {
  
    bool IPedMess[64];

    Initial_Perm(message_64b, IPedMess);





    bool R_in[32], L_in[32], R_out[32], L_out[32], R_temp[48];

    for (int i = 0; i < 32; i++) {
        R_in[i] = IPedMess[i + 32];
        L_in[i] = IPedMess[i];
    }

    for (int j = 0; j < 16; j++) {

        for (int i = 0; i < 32; i++) {
            L_out[i] = R_in[i];
        }

        for (int i = 0; i < 48; i++) {
            R_temp[i] = R_in[E[i] - 1];
            R_temp[i] = R_temp[i] ^ subkeys[j][i];
        }



        int counter = 0;

        while (counter < 8) {

            bool input1[2] = { R_temp[counter * 6 + 0],R_temp[counter * 6 + 5] };
            int raw = bin2int(input1, 2);

            bool input2[4] = { R_temp[counter * 6 + 1],R_temp[counter * 6 + 2],R_temp[counter * 6 + 3],R_temp[counter * 6 + 4] };
            int col = bin2int(input2, 4);

            int output;

            switch (counter) {
            case(0): {
                output = s1[raw][col];
                break;
            }
            case(1): {
                output = s2[raw][col];
                break;
            }
            case(2): {
                output = s3[raw][col];
                break;
            }
            case(3): {
                output = s4[raw][col];
                break;
            }
            case(4): {
                output = s5[raw][col];
                break;
            }
            case(5): {
                output = s6[raw][col];
                break;
            }
            case(6): {
                output = s7[raw][col];
                break;
            }
            case(7): {
                output = s8[raw][col];
                break;
            }

            }



            unsigned int mask2 = 8;

            for (int i = 0; i < 4; i++) {
                if (mask2 & output) R_temp[counter * 4 + i] = 1;
                else R_temp[counter * 4 + i] = 0;
                mask2 /= 2;
            }

            counter++;

        }

        for (int i = 0; i < 32; i++) {
            R_out[i] = R_temp[P[i] - 1];
            R_out[i] = R_out[i] ^ L_in[i];
        }


        if (j != 15) {
            for (int i = 0; i < 32; i++) {
                R_in[i] = R_out[i];
                L_in[i] = L_out[i];
            }
        }





    }


    bool resualt_prod[64];

    for (int i = 0; i < 32; i++) {
        resualt_prod[i] = R_out[i];
        resualt_prod[i + 32] = L_out[i];
    }

    for (int i = 0; i < 64; i++) {
        message_64b[i] = resualt_prod[FIP[i] - 1];
    }

}

void key_perm( string key, bool subkeys[16][48] ) {

    bool key_64b[64];

    string_to_64binary(key, key_64b);




    ////////// KEY PERMUTATION ////////////

    bool key_56b_L[28];
    bool key_56b_R[28];

    for (int i = 0; i < 56; i++) {
        if (i < 28) key_56b_L[i] = key_64b[PC1[i] - 1];
        else key_56b_R[i - 28] = key_64b[PC1[i] - 1];
    }


    for (int j = 0; j < 16; j++) {

        LS(key_56b_L, 1);
        LS(key_56b_R, 1);

        if (j != 0 && j != 1 && j != 8 && j != 15) {
            LS(key_56b_L, 1);
            LS(key_56b_R, 1);
        }

        for (int i = 0; i < 48; i++) {
            if (PC2[i] < 29) subkeys[j][i] = key_56b_L[PC2[i] - 1];
            else subkeys[j][i] = key_56b_R[PC2[i] - 1 - 28];
        }


    }

}


int main()
{

    cout << "Choose type: 1 - encrypt, 2 - decrypt" << endl;

    int type;

    cin >> type;

    if (type == 1) {


        char keyEl[8];
        string key, key2, key3;

        srand(time(NULL));

        cout << "Processing key... " << endl;
        cout << "Key I is: ";

        for (int i = 0; i < 8; i++) {
            keyEl[i] = static_cast<char>(33 + rand() % 94);
            key += keyEl[i];
        }

        cout << key;
        cout << endl;

        cout << "Key II is: ";

        for (int i = 0; i < 8; i++) {
            keyEl[i] = static_cast<char>(33 + rand() % 94);
            key2 += keyEl[i];
        }

        cout << key2;
        cout << endl;

        cout << "Key III is: ";

        for (int i = 0; i < 8; i++) {
            keyEl[i] = static_cast<char>(33 + rand() % 94);
            key3 += keyEl[i];
        }

        cout << key3;
        cout << endl;

        auto begin = std::chrono::high_resolution_clock::now();

        bool subkeys[16][48], subkeys2[16][48], tempkeys2[16][48], subkeys3[16][48];

        key_perm(key, subkeys);

        key_perm(key2, tempkeys2);

        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 48; j++) {
                subkeys2[i][j] = tempkeys2[15 - i][j];
            }
        }

        key_perm(key3, subkeys3);




        char message[8];
        bool message_64b[64];

        FILE* plik;
        plik = fopen("input.bin", "rb");
        fpos_t position;

        FILE* plikzapis;
        plikzapis = fopen("wynik.bin", "wb");


        while (!feof(plik)) {


            

            size_t liczba = fread(message, sizeof(char), 8, plik);
            fgetpos(plik, &position);


            if (feof(plik)) break;

            buffer_to_64binary(message, message_64b);

            DES(message_64b, subkeys);

            DES(message_64b, subkeys2);

            DES(message_64b, subkeys3);

            bit64tochar(message_64b, message);

            size_t ilzapis = fwrite(message, sizeof(char), 8, plikzapis);

            

        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

        printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);


        fclose(plik);
        fclose(plikzapis);
        

        

    }

    else {

        string key, key2, key3;
        cout << "Insert key I: " << endl;
        cin >> key;
        cout << "Insert key II: " << endl;
        cin >> key2;
        cout << "Insert key III: " << endl;
        cin >> key3;

        auto begin = std::chrono::high_resolution_clock::now();

        bool subkeys[16][48], subkeys2[16][48], tempkeys[16][48], tempkeys3[16][48], subkeys3[16][48];

        key_perm(key2, subkeys2);

        key_perm(key, tempkeys);

        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 48; j++) {
                subkeys[i][j] = tempkeys[15 - i][j];
            }
        }

        key_perm(key3, tempkeys3);

        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 48; j++) {
                subkeys3[i][j] = tempkeys3[15 - i][j];
            }
        }




        char message[8];
        bool message_64b[64];


        FILE* plik;
        plik = fopen("wynik.bin", "rb");
        fpos_t position;

        FILE* plikzapis;
        plikzapis = fopen("deszyfrowanie.bin", "wb");

        while (!feof(plik)) {


            size_t liczba = fread(message, sizeof(char), 8, plik);
            fgetpos(plik, &position);


            if (feof(plik)) break;

            buffer_to_64binary(message, message_64b);

            DES(message_64b, subkeys3);

            DES(message_64b, subkeys2);

            DES(message_64b, subkeys);

            bit64tochar(message_64b, message);


            size_t ilzapisow = fwrite(message, sizeof(char), 8, plikzapis);

        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

        printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

        fclose(plik);
        fclose(plikzapis);
        
    

    }
 

    return 0;
 
}

