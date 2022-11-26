#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>

// number of trials with a given message

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
   unsigned char message[256];
   unsigned char * digest = malloc(EVP_MAX_MD_SIZE);

   while (!(digest[0] == digestmain[0] && digest[1] == digestmain[1]  && digest[2] == digestmain[2]) || message[255] == 127)
   {
      for (int i = 0; i < 255; i++)
      {
         if (message[i] < 127)
         {
            message[i] = message[i] + 1;
         }
      }
      trials += 1;
   }
   
   if (message[255] == 127)
   {
      printf("better luck next time");
   }
   else
   {
   printf("digest main : ");
   for (int i = 0; i < 32; i++)
        printf("%02x", digestmain[i]);
    printf("\n");


   printf("digest alt : ");
   for (int i = 0; i < 32; i++)
        printf("%02x", digest[i]);
    printf("\n");
   
   printf("message main : %s \n message alt : \n", messagemain, message);
   

   }

   return 0; 
}
