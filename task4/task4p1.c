#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




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

for (int k = 0; k < 5; k++)
   {
      unsigned int trials = 0;
      unsigned char messagemain[1001];
      unsigned char * digestmain = malloc(EVP_MAX_MD_SIZE);
      int len = messagedigest(messagemain, digestmain);
      unsigned char * digest = malloc(EVP_MAX_MD_SIZE);  
      //printf("entering into main \n\n");
      //printf("exiting\n\n");
      unsigned char message[1001];
      //while (!(digest[0] == digestmain[0] && digest[1] == digestmain[1]  && digest[2] == digestmain[2]) || message[255] == 127)
      while (1)
      {
         for (int i = 0; i < 1001; i++)
         {
            messagemain[i] = (rand() % (126 - 33 + 1)) + 33;
            message[i] = (rand() % (126 - 33 + 1)) + 33;
         }
         trials += 1;
         
         messagedigest(messagemain, digestmain);
         messagedigest(message, digest);
         if (digest[0] == digestmain[0])
         {
            printf("sucess");
            break;
         }

      }

      printf("digest main : ");
      for (int i = 0; i < 32; i++)
         printf("%02x", digestmain[i]);
      printf("\n");

      printf("digest alt : ");
      for (int i = 0; i < 32; i++)
         printf("%02x", digest[i]);
      printf("\n");

      printf("message main : %s \n message alt : %s \n number of trials req: %u \n", messagemain, message, trials);
   }
   return 0;
}

