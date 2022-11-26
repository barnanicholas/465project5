#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>

int messagedigest(const unsigned char *message, unsigned char **digest)
{
   unsigned int len_digest;
   EVP_MD_CTX *mdctx;
	mdctx = EVP_MD_CTX_new();
	EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);
	EVP_DigestUpdate(mdctx, message, strlen(message));
	*digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_md5()));
   EVP_DigestFinal_ex(mdctx, *digest, &len_digest);
	EVP_MD_CTX_free(mdctx);

   return len_digest;
}






int main()
{
   char message[] = "hello, this is a really cool file with some really cool contents\n";
   char ** digest;
   messagedigest(message, digest);
   printf("the digest of \'%s\' is \'%s\'", message, *digest);

   return 0; 
}

