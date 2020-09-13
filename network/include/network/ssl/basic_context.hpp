#ifndef NETWORK_CONTEXT_BASE_HPP
#define NETWORK_CONTEXT_BASE_HPP

namespace network::ssl
{
	class basic_context
	{
	  public:
		enum method { tls, tls_client, tls_server, dtls, dtls_client, dtls_server };

		enum file_format { asn1, pem };

		enum verify_mode { none, peer, verify_client_fail, verify_client_once };

		enum handshake_type { client, server };

	  protected:
		basic_context() = default;
	};
} // namespace network::ssl

#endif // NETWORK_CONTEXT_BASE_HPP
