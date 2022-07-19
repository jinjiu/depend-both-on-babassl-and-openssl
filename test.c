#include <stdio.h>
#include "lopen.h"
#include "lbaba.h"

int main(int argc, char *argv[])
{
    const char *cert = "/root/github/BabaSSL/test/certs/test_rsa_crt.pem";
#ifdef RSA_SIZE
    const char *key = "/root/github/BabaSSL/test/certs/test_rsa_key.pem";
#endif

    print_cert_info(cert);
    print_x509_valid_time(NULL);

#ifdef RSA_SIZE
    print_rsa_size(key);
#endif

    return 0;
}
