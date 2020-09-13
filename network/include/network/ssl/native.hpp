#ifndef NETWORK_NATIVE_HPP
#define NETWORK_NATIVE_HPP

#include "context_base.hpp"

#include <openssl/err.h>
#include <openssl/ssl.h>

namespace network::ssl::native
{
	class openssl_init
	{
	  public:
		openssl_init()
		{
			::SSL_library_init();
			::OpenSSL_add_ssl_algorithms();
			::OpenSSL_add_all_algorithms();
			::SSL_load_error_strings();
			::ERR_load_crypto_strings();
		}

		~openssl_init()
		{
			::FIPS_mode_set(0);
			EVP_cleanup();
			CRYPTO_cleanup_all_ex_data();
			ERR_free_strings();
		}
	};

	const char* get_last_error() { return ERR_reason_error_string(ERR_peek_last_error()); }

	constexpr const SSL_METHOD* get_method(context_base::method m)
	{
		switch(m)
		{
			case context_base::tls:
				return TLS_method();
			case context_base::tls_client:
				return TLS_client_method();
			case context_base::tls_server:
				return TLS_server_method();
			case context_base::dtls:
				return DTLS_method();
			case context_base::dtls_client:
				return DTLS_client_method();
			case context_base::dtls_server:
				return DTLS_server_method();
			default:
				return nullptr;
		}
	}

	constexpr int get_verify_mode(context_base::verify_mode m)
	{
		switch(m)
		{
			case context_base::none:
				return SSL_VERIFY_NONE;
			case context_base::peer:
				return SSL_VERIFY_PEER;
			case context_base::verify_client_fail:
				return SSL_VERIFY_FAIL_IF_NO_PEER_CERT;
			case context_base::verify_client_once:
				return SSL_VERIFY_CLIENT_ONCE;
		}
	}

	constexpr int get_file_format(context_base::file_format f)
	{
		switch(f)
		{
			case context_base::asn1:
				return SSL_FILETYPE_ASN1;
			case context_base::pem:
				return SSL_FILETYPE_PEM;
			default:
				return SSL_FILETYPE_PEM;
		}
	}
} // namespace network::ssl::native

#endif // NETWORK_NATIVE_HPP
