#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef unsigned char BYTE;

// A function to calculate (base^exponent)%modulus
int modulo(int base, int exponent, int modulus)
{
    long long x = 1;
    long long y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % modulus;
        y = (y * y) % modulus;
        exponent = exponent / 2;
    }
    return x % modulus;
}

// To calculate g^x mod p
int diffieHellmanKeyExchange(int g, int x, int p)
{
    return modulo(g, x, p);
}

// A function to generate a 64-bit key
BYTE* generateKey()
{
    BYTE* key = (BYTE*)malloc(sizeof(BYTE) * 64);
    int i;

    // Generate a 64-bit key
    for (i = 0; i < 64; i++)
    {
        key[i] = rand() % 256;
    }

    return key;
}

// A function to encrypt a message with a given key
BYTE* encryptMessage(BYTE* message, BYTE* key)
{
    int i;
    int messageLength = strlen(message);
    BYTE* encryptedMessage = (BYTE*)malloc(sizeof(BYTE) * (messageLength + 1));

    // Encrypt the message with the given key
    for (i = 0; i < messageLength; i++)
    {
        encryptedMessage[i] = message[i] ^ key[i % 64];
    }

    encryptedMessage[messageLength] = '\0';
    return encryptedMessage;
}

// A function to decrypt a message with a given key
BYTE* decryptMessage(BYTE* encryptedMessage, BYTE* key)
{
    int i;
    int messageLength = strlen(encryptedMessage);
    BYTE* decryptedMessage = (BYTE*)malloc(sizeof(BYTE) * (messageLength + 1));

    // Decrypt the message with the given key
    for (i = 0; i < messageLength; i++)
    {
        decryptedMessage[i] = encryptedMessage[i] ^ key[i % 64];
    }

    decryptedMessage[messageLength] = '\0';
    return decryptedMessage;
}

int main()
{
    // Generate a 64-bit key
    BYTE* key = generateKey();

    // Message to be encrypted
    BYTE* message = "This is a secret message!";

    // Generate Waifu's and Simp's private keys
    int waifuPrivateKey = 5;
    int simpPrivateKey = 7;

    // Generate Waifu's and Simp's public keys
    int waifuPublicKey = diffieHellmanKeyExchange(5, waifuPrivateKey, 23);
    int simpPublicKey = diffieHellmanKeyExchange(5, simpPrivateKey, 23);

    // Generate the shared secret key
    int waifuSharedSecretKey = diffieHellmanKeyExchange(simpPublicKey, waifuPrivateKey, 23);
    int simpSharedSecretKey = diffieHellmanKeyExchange(waifuPublicKey, simpPrivateKey, 23);

    // Check if the generated shared secret keys are equal
    if (waifuSharedSecretKey == simpSharedSecretKey)
    {
        printf("Waifu and Simp have successfully generated the shared secret key\n");
    }
    else
    {
        printf("Waifu and Simp have failed to generate the shared secret key\n");
        return 0;
    }

    // Encrypt the message with the shared secret key
    BYTE* encryptedMessage = encryptMessage(message, key);
    printf("Encrypted Message: %s\n", encryptedMessage);

    // Decrypt the encrypted message with the shared secret key
    BYTE* decryptedMessage = decryptMessage(encryptedMessage, key);
Waifu    printf("Decrypted Message: %s\n", decryptedMessage);

    return 0;
}
