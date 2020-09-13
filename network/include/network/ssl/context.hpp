#ifndef NETWORK_SSL_CONTEXT_HPP
#define NETWORK_SSL_CONTEXT_HPP

#include <stdexcept>
#include <string_view>

#if defined(FILESYSTEM_SUPPORT)
#include <filesystem>
#endif

#include "native.hpp"

namespace network::ssl
{
	class context : public basic_context
	{
	  public:
		using native_handle_type = SSL_CTX;

		explicit context(method m) : ctx(SSL_CTX_new(native::get_method(m)))
		{
			if(ctx == nullptr)
				throw std::runtime_error(native::get_last_error());
		}

		context(const context& other)		 = delete;
		context(context&& other) noexcept = default;

		~context() noexcept { SSL_CTX_free(ctx); }

		context& operator=(const context& other) = delete;
		context& operator=(context&& other) noexcept = default;

		native_handle_type* native_handler() const noexcept { return ctx; }

		void set_verify_mode(verify_mode v) { ::SSL_CTX_set_verify(ctx, native::get_verify_mode(v), nullptr); }

		void set_verify_depth(int depth) { ::SSL_CTX_set_verify_depth(ctx, depth); }

		void load_verify_file(const std::string& filename)
		{
			if(!::SSL_CTX_load_verify_locations(ctx, filename.c_str(), nullptr))
				throw std::runtime_error(native::get_last_error());
		}

#if defined(FILESYSTEM_SUPPORT)
		void load_verify_file(const std::filesystem::path& filename) { load_verify_file(filename.native()); }
#endif

		void add_certificate_authority(const std::string& ca)
		{
			STACK_OF(X509_NAME)* list = ::SSL_load_client_CA_file(ca.c_str());
			if(!list)
				throw std::runtime_error(native::get_last_error());

			::SSL_CTX_set_client_CA_list(ctx, list);
		}

#if defined(FILESYSTEM_SUPPORT)
		void add_certificate_authority(const std::filesystem::path& ca) { add_certificate_authority(ca.native()); }
#endif

		void set_default_verify_paths()
		{
			if(!::SSL_CTX_set_default_verify_paths(ctx))
				throw std::runtime_error(native::get_last_error());
		}

		void set_default_verify_dir()
		{
			if(!::SSL_CTX_set_default_verify_dir(ctx))
				throw std::runtime_error(native::get_last_error());
		}

		void set_default_verify_file()
		{
			if(!::SSL_CTX_set_default_verify_dir(ctx))
				throw std::runtime_error(native::get_last_error());
		}

		void set_verify_path(const std::string& path)
		{
			if(!::SSL_CTX_load_verify_locations(ctx, nullptr, path.c_str()))
				throw std::runtime_error(native::get_last_error());
		}

#if defined(FILESYSTEM_SUPPORT)
		void set_verify_path(const std::filesystem::path& path) { set_verify_path(path.native()); }
#endif

		void use_certificate_file(const std::string& filename, file_format format)
		{
			if(!::SSL_CTX_use_certificate_file(ctx, filename.c_str(), native::get_file_format(format)))
				throw std::runtime_error(native::get_last_error());
		}

		void use_certificate(const immutable_buffer& certificate)
		{
			if(!::SSL_CTX_use_certificate_ASN1(ctx, certificate.size(), certificate.data()))
				throw std::runtime_error(native::get_last_error());
		}

#if defined(FILESYSTEM_SUPPORT)
		void use_certificate_file(const std::filesystem::path& filename, file_format format)
		{
			use_certificate_file(filename.native(), format);
		}
#endif

		void use_private_key_file(const std::string& filename, file_format format)
		{
			if(!::SSL_CTX_use_PrivateKey_file(ctx, filename.c_str(), native::get_file_format(format)))
				throw std::runtime_error(native::get_last_error());
		}

		void use_private_key(const immutable_buffer& key)
		{
			if(!::SSL_CTX_use_PrivateKey_ASN1(ctx, key.data(), key.size()))
				throw std::runtime_error(native::get_last_error());
		}

#if defined(FILESYSTEM_SUPPORT)
		void use_private_key_file(const std::filesystem::path& filename, file_format format)
		{
			use_private_key_file(filename.native(), format);
		}
#endif

		void use_rsa_private_key_file(const std::string& filename, file_format format)
		{
			if(!::SSL_CTX_use_RSAPrivateKey_file(ctx, filename.c_str(), native::get_file_format(format)))
				throw std::runtime_error(native::get_last_error());
		}

		void use_rsa_private_key(const immutable_buffer& key)
		{
			if(!::SSL_CTX_use_RSAPrivateKey_ASN1(ctx, key.data(), key.size()))
				throw std::runtime_error(native::get_last_error());
		}

#if defined(FILESYSTEM_SUPPORT)
		void use_rsa_private_key_file(const std::filesystem::path& filename, file_format format)
		{
			use_rsa_private_key_file(filename.native(), format);
		}
#endif

		void verify_private_key()
		{
			if(!::SSL_CTX_check_private_key(ctx))
				throw std::runtime_error(native::get_last_error());
		}

		void use_dh_file(const std::string& filename)
		{
			if(!::SSL_CTX_set_tmp_dh(ctx, filename.c_str()))
				throw std::runtime_error(native::get_last_error());
		}

#if defined(FILESYSTEM_SUPPORT)
		void use_dh_file(const std::filesystem::path& filename) { use_dh_file(filename.native()); }
#endif

	  private:
		static native::openssl_init init;

		SSL_CTX* ctx;
	};
} // namespace network::ssl

#endif // NETWORK_SSL_CONTEXT_HPP
