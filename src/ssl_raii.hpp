// 这个文件是 Poseidon 服务器应用程序框架的一部分。
// Copyleft 2014 - 2018, LH_Mouse. All wrongs reserved.

#ifndef POSEIDON_SSL_RAII_HPP_
#define POSEIDON_SSL_RAII_HPP_

#include "cxx_ver.hpp"
#include "raii.hpp"
#include <openssl/ssl.h>

namespace Poseidon {

struct SslDeleter {
	CONSTEXPR ::SSL *operator()() NOEXCEPT {
		return NULLPTR;
	}
	void operator()(::SSL *ssl) NOEXCEPT;
};

typedef UniqueHandle<SslDeleter> UniqueSsl;

struct SslCtxDeleter {
	CONSTEXPR ::SSL_CTX *operator()() NOEXCEPT {
		return NULLPTR;
	}
	void operator()(::SSL_CTX *ssl_ctx) NOEXCEPT;
};

typedef UniqueHandle<SslCtxDeleter> UniqueSslCtx;

}

#endif
