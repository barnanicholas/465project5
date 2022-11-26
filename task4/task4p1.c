#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>



// number of trials to find two messages

int messagedigest(const unsigned char *message, unsigned char * digest)
{
   //printf("entering into md \n\n");

   unsigned int len_digest;
   EVP_MD_CTX *mdctx;
   //printf("create \n\n");
	mdctx = EVP_MD_CTX_create();
   //printf("INIT \n\n");
	EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
	//printf("update \n\n");
   EVP_DigestUpdate(mdctx, message, strlen(message));
	//printf("malloc \n\n");
   *digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha256()));
   //printf("final \n\n");
   EVP_DigestFinal_ex(mdctx, digest, &len_digest);
   //printf("the digest of \'%s\'\n", digest);
	//printf(" destroy \n\n");
   EVP_MD_CTX_destroy(mdctx);

   return len_digest;
}






int main()
{
   //printf("entering into main \n\n");
   unsigned int trials = 0;
   unsigned char messagemain[] = "hello, this is a really cool file with some really cool contents\n";
   unsigned char * digestmain = malloc(EVP_MAX_MD_SIZE);
   int len = messagedigest(messagemain, digestmain);
   //printf("exiting\n\n");
   unsigned char message[] = "";
   unsigned char * digest = malloc(EVP_MAX_MD_SIZE);



   int len = messagedigest(messagemain, digestmain);
   



   
   for (int i = 0; i < len; i++)
        printf("%02x", digest[i]);
    printf("\n");

   return 0; 
}

