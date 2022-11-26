#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>

int messagedigest(const unsigned char *message, unsigned char **digest)
{
   printf("entering into md \n\n");
   unsigned int len_digest;
   EVP_MD_CTX *mdctx;
   printf("create \n\n");
	mdctx = EVP_MD_CTX_create();
   printf("INIT \n\n");
	EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);
	printf("update \n\n");
   EVP_DigestUpdate(mdctx, message, strlen(message));
	printf("malloc \n\n");
   *digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_md5()));
   printf("final \n\n");
   EVP_DigestFinal_ex(mdctx, *digest, &len_digest);
	printf(" destroy \n\n");

   return len_digest;
}






int main()
{
   printf("entering into main \n\n");

   unsigned char message[] = "hello, this is a really cool file with some really cool contents\n";
   unsigned char ** digest;
   messagedigest(message, digest);
   printf("exiting digest\n\n");
   printf("the digest of \'%s\' is \'%s\'\n", message, *digest);

   return 0; 
}

