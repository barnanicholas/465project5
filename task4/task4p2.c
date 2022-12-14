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
   unsigned char messagemain[] = "hello, this is a really cool file with some really cool contents\n";
   int average = 0;
   for (int k = 0; k < 5; k++)
   {

      //printf("entering into main \n\n");
      unsigned int trials = 0;
      unsigned char * digestmain = malloc(EVP_MAX_MD_SIZE);
      int len = messagedigest(messagemain, digestmain);
      //printf("exiting\n\n");
      unsigned char message[1001];
      for (int i = 0; i < 1001; i++)
      {
         message[i] = 34;
      }
      
      unsigned char * digest = malloc(EVP_MAX_MD_SIZE);

      //while (!(digest[0] == digestmain[0] && digest[1] == digestmain[1]  && digest[2] == digestmain[2]) || message[255] == 127)
      while (1)
      {
         for (int i = 0; i < 1001; i++)
         {
            message[i] = (rand() % (126 - 33 + 1)) + 33;
         }
         trials += 1;

         messagedigest(message, digest);

         if (digest[0] == digestmain[0] && digest[1] == digestmain[1]  && digest[2] == digestmain[2])
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
      
      average += trials;
   }

   
   average = average/5;
   printf("average overall: %u \n", average);
   return 0;
}

