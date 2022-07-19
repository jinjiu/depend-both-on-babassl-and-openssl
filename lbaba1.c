#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/asn1.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

void print_x509_valid_time(X509 *x509)
{
    BIO *bio = NULL, *out = NULL;

    out = BIO_new(BIO_s_file());
    if (out == NULL) {
        return;
    }

    BIO_set_fp(out, stderr, BIO_NOCLOSE);

    if (x509 == NULL) {
        BIO_printf(out, "\n%s:%d, x509 is NULL:\n", __FILE__, __LINE__);
        goto err;
    }

    BIO_printf(out, "\n%s:%d, x509 notBefore: ", __FILE__, __LINE__);
    ASN1_TIME_print(out, X509_get_notBefore(x509));
    BIO_printf(out, "\n%s:%d, x509 notAfter: ", __FILE__, __LINE__);
    ASN1_TIME_print(out, X509_get_notAfter(x509));

err:
    BIO_free(bio);
    return;
}
