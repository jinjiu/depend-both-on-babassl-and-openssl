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

#ifdef RSA_SIZE
void print_rsa_size(const char *path)
{
    RSA *rsa = NULL;
    BIO *bio = NULL, *out = NULL;

    out = BIO_new(BIO_s_file());
    if (out == NULL) {
        goto err;
    }

    BIO_set_fp(out, stderr, BIO_NOCLOSE);

    bio = BIO_new_file(path, "r");
    if (bio == NULL) {
        goto err;
    }

    rsa = PEM_read_bio_RSAPrivateKey(bio, &rsa, NULL, NULL);
    if (rsa == NULL) {
        goto err;
    }

    BIO_printf(out, "%s:%d, RSA_size: %d\n", __FILE__, __LINE__, RSA_size(rsa));

err:
    RSA_free(rsa);
    BIO_free(bio);
    BIO_free(out);
    return;
}
#endif
