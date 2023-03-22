/*
* RSA Algorithm - a very fast algorithm for encryption and decryption
* If we know a key pair, we can encrypt and decrypt messages
* Using two large prime numbers, p and q and computes n = pq. 
* Compute the totient function  λ(n) = (p – 1)(q – 1)
* Choosing e as a relatively prime number to λ(n) and 1 < e < λ(n) 
* And release e as the public key
* Private key : d * e = 1 mod λ(n)
* Encryption: c = me mod n
* Decryption: cd mod n
*/


/* 
*    int isPrime(int) – This function checks if the number is prime or not.
*    int gcd(int, int) – This function returns the greatest common divisor of two numbers.
*    int totient(int, int) – This function returns the totient of a number.
*    int randome(int) – This function returns a random number less than the given number.
*    int private_key(int, int) – This function returns the private key.
*    long pomod(long, long, long) – This function returns the modular exponentiation of a number.
*    char *encrypt(char *, long, long) – This function encrypts the message.
*    char *decrypt(char *, long, long) – This function decrypts the message.
*/

// compile with : gcc -o RSA.c -lm 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

 

unsigned long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
long int cd(long int);
int prime(long int);
char msg[100];
void ce();
void encrypt();
void decrypt();

int main(int argc, char ** argv[])
{
    printf("\nEnter first prime number\n");
    scanf("%ld", &p);
    flag = prime(p);
    if (flag == 0)
    {
        printf("\nWrong input\n");
        getchar();
        exit(1);
    }

    printf("\nEnter second prime number\n");
    scanf("%ld", &q);
    flag = prime(q);
    if (flag == 0 || p == q)
    {
        printf("\nWRONG INPUT\n");
        getchar();
        exit(1);
    }

    printf("\nEnter message to encrypt\n");
    fflush(stdin);
    scanf("%s", msg);
    for (i = 0; msg[i] != '\0'; i++)
    {
        m[i] = msg[i];
    }

    n = p * q;
    t = (p - 1) * (q - 1);
    ce();
    encrypt();
    decrypt();
    return 0;
}

int prime(long int pr)
{
    int i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
        {
            return 0;
        }

    }
    return 1;

}

void ce()
{
    int k;
    k = 0;

    for (i = 2; i < t; i++)
    {
        if (t % i == 0)
        {
            continue;
        }

        flag = prime(i);
        if (flag == 1 && i != p && i != q)
        {
            e[k] = i;
            flag = cd(e[k]);
            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if (k == 99)
            {
                break;
            }
        }
    }
}

long int cd(long int x)
{
    long int k = 1;
    while (1)
    {
        k = k + t;
        if (k % x == 0)
        {
            return (k / x);
        }

    }

}

void encrypt()

{

    long int pt, ct, key = e[0], k, len;
    i = 0;
    len = strlen(msg);
    while (i != len)
    {
        pt = m[i];
        pt = pt - 96;
        k = 1;

        for (j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }

        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }

    en[i] = -1;
    printf("\nEncrypted message is: ");

    for (i = 0; en[i] != -1; i++)
    {
        printf("%c", en[i]);
    }

}

void decrypt()
{

    long int pt, ct, key = d[0], k;
    i = 0;
    while (en[i] != -1)
    {
        ct = temp[i];
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }

        pt = k + 96;
        m[i] = pt;
        i++;
    }

    m[i] = -1;
    printf("\nDecrypted message is: ");
    for (i = 0; m[i] != -1; i++)
    {
        printf("%c", m[i]);
    }
    printf("\n");
}
