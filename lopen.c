#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/asn1.h>
#include "lopen.h"

void print_x509_period(X509 *x509)
{
    BIO *bio = NULL, *out = NULL;

    out = BIO_new(BIO_s_file());
    if (out == NULL) {
        return;
    }

    BIO_set_fp(out, stderr, BIO_NOCLOSE);

    if (x509 == NULL) {
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

void print_cert_info(const char *path)
{
    X509 *x509 = NULL;
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

    x509 = PEM_read_bio_X509(bio, NULL, NULL, NULL);
    if (x509 == NULL) {
        goto err;
    }

    X509_NAME_print_ex(out, X509_get_subject_name(x509), 0, XN_FLAG_ONELINE);
    BIO_printf(out, "\n");

    print_x509_period(x509);

err:
    X509_free(x509);
    BIO_free(bio);
    BIO_free(out);
    return;
}
