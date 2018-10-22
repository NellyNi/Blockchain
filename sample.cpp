#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int main()
{
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char string[] = "hello world!";
    
    SHA256((unsigned char*)&string, strlen(string), (unsigned char*)&digest);    
    printf("SHA256 digest hexadecimal format: %s\n\n", digest);

    char mdString[SHA256_DIGEST_LENGTH*2+1];

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    	/* Convert the unsigned int in hexadecimal format to char and store it in variable 'mdString' */
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    }
    
    printf("SHA256 digest: %s\n", mdString);

    return 0;
}
