#include <Crypto.h>
#include <AES.h>
#include <Arduino.h>

#define BUFFER_SIZE 1024

AES256 aes256;
BlockCipher *cipher = &aes256;

void encryptMessage(char* message, char* encrypted, int blocks, uint8_t* key, int leftOver, int msgLen) {
    uint8_t blockBuffer[cipher->blockSize()];
    uint8_t messageBuffer[cipher->blockSize()];
    memset(encrypted, 0, BUFFER_SIZE);
    
    for (int i = 0; i < blocks; i++) {
        int startingPosition = i * cipher->blockSize();

        for (int k = 0; k < cipher->blockSize(); k++) {
            messageBuffer[k] = message[startingPosition + k];
        }

        cipher->setKey(key, cipher->keySize());
        cipher->encryptBlock(blockBuffer, messageBuffer);

        for (int m = 0; m < cipher->blockSize(); m++) {
            encrypted[startingPosition + m] = blockBuffer[m];
        }
    }

    // Handle padding for the last block
    if (leftOver != 0) {
        int startingPosition = blocks * cipher->blockSize();
        for (int k = 0; k < cipher->blockSize(); k++) {
            if (k < leftOver) {
                messageBuffer[k] = message[startingPosition + k];
            } else {
                messageBuffer[k] = 0x00; // Padding with null bytes
            }
        }

        cipher->setKey(key, cipher->keySize());
        cipher->encryptBlock(blockBuffer, messageBuffer);

        for (int m = 0; m < cipher->blockSize(); m++) {
            encrypted[startingPosition + m] = blockBuffer[m];
        }
    }
}

void decryptMessage(char* encrypted, char* decrypted, int blocks, uint8_t* key, int leftOver, int msgLen) {
    uint8_t blockBuffer[cipher->blockSize()];
    uint8_t messageBuffer[cipher->blockSize()];
    memset(decrypted, 0, BUFFER_SIZE);

    for (int i = 0; i < blocks; i++) {
        int startingPosition = i * cipher->blockSize();

        for (int m = 0; m < cipher->blockSize(); m++) {
            blockBuffer[m] = encrypted[startingPosition + m];
        }

        cipher->setKey(key, cipher->keySize());
        cipher->decryptBlock(messageBuffer, blockBuffer);

        for (int k = 0; k < cipher->blockSize(); k++) {
            decrypted[i * cipher->blockSize() + k] = (char)messageBuffer[k];
        }
    }

    // Handle padding for the last block
    if (leftOver != 0) {
        int startingPosition = blocks * cipher->blockSize();

        for (int m = 0; m < cipher->blockSize(); m++) {
            blockBuffer[m] = encrypted[startingPosition + m];
        }

        cipher->setKey(key, cipher->keySize());
        cipher->decryptBlock(messageBuffer, blockBuffer);

        for (int k = 0; k < leftOver; k++) {
            decrypted[blocks * cipher->blockSize() + k] = (char)messageBuffer[k];
        }
    }
}

void setup() {
    Serial.begin(9600);
    delay(500);
    Serial.println("Starting crypto");

    uint8_t key[33] = "P@ssw0rdP@ssw0rdP@ssw0rdP@ssw0rd";
    char message[BUFFER_SIZE] = "super secret message long with some padding to test the encryption and decryption of the message with the key if the message is long enough to require multiple blocks of encryption and decryption.";
    char message2[BUFFER_SIZE] = "super secret";
    char encrypted[BUFFER_SIZE];
    char decrypted[BUFFER_SIZE];

    Serial.println("Encrypting message: " + String((char*)message) + " with key: " + String((char*)key));
    
    // Here for now
    int msgLen = strlen((char*)message);
    int blocks = msgLen / 16;
    int leftOver = msgLen % 16;

    encryptMessage(message, encrypted, blocks, key, leftOver, msgLen);

    //for (int i = 0; i < (blocks + (leftOver != 0)) * cipher->blockSize(); i++) {
    //    Serial.print((char)encrypted[i]);
    //}

    Serial.println();
    Serial.println((String)encrypted);

    Serial.println("Done");

    decryptMessage(encrypted, decrypted, blocks, key, leftOver, msgLen);

    // Print the decrypted message
    //for (int i = 0; i < msgLen; i++) {
    //    Serial.print((char)decrypted[i]);
    //}

    Serial.println();
    Serial.println((String)decrypted);

 //   Serial.println("\n Message 2: ");
//
 //   // Encrypt and decrypt a shorter message
 //   msgLen = strlen((char*)message2);
 //   blocks = msgLen / 16;
 //   leftOver = msgLen % 16;
//
 //   encryptMessage(message2, encrypted, blocks, key, leftOver, msgLen);
//
 //   for (int i = 0; i < (blocks + (leftOver != 0)) * cipher->blockSize(); i++) {
 //       Serial.print((char)encrypted[i]);
 //   }
//
 //   Serial.println();
//
 //   decryptMessage(encrypted, decrypted, blocks, key, leftOver, msgLen);
//
 //   // Print the decrypted message
//
 //   for (int i = 0; i < msgLen; i++) {
 //       Serial.print((char)decrypted[i]);
 //   }
}

void loop() {}
