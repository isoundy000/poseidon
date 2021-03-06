// 这个文件是 Poseidon 服务器应用程序框架的一部分。
// Copyleft 2014 - 2018, LH_Mouse. All wrongs reserved.

#ifndef POSEIDON_HTTP_SESSION_HPP_
#define POSEIDON_HTTP_SESSION_HPP_

#include "low_level_session.hpp"

namespace Poseidon {
namespace Http {

class Session : public LowLevelSession {
private:
	class SyncJobBase;
	class ReadHupJob;
	class ExpectJob;
	class RequestJob;
	class ErrorJob;

private:
	volatile boost::uint64_t m_max_request_length;
	boost::uint64_t m_size_total;
	RequestHeaders m_request_headers;
	StreamBuffer m_entity;

public:
	explicit Session(Move<UniqueFile> socket);
	~Session();

protected:
	boost::uint64_t get_low_level_size_total() const {
		return m_size_total;
	}
	const RequestHeaders &get_low_level_request_headers() const {
		return m_request_headers;
	}
	const StreamBuffer &get_low_level_entity() const {
		return m_entity;
	}

	// TcpSessionBase
	void on_read_hup() OVERRIDE;

	// LowLevelSession
	void on_low_level_request_headers(RequestHeaders request_headers, boost::uint64_t content_length) OVERRIDE;
	void on_low_level_request_entity(boost::uint64_t entity_offset, StreamBuffer entity) OVERRIDE;
	boost::shared_ptr<UpgradedSessionBase> on_low_level_request_end(boost::uint64_t content_length, OptionalMap headers) OVERRIDE;

	// 可覆写。
	virtual void on_sync_expect(RequestHeaders request_headers);
	virtual void on_sync_request(RequestHeaders request_headers, StreamBuffer entity) = 0;

public:
	boost::uint64_t get_max_request_length() const;
	void set_max_request_length(boost::uint64_t max_request_length);
};

}
}

#endif
