// 这个文件是 Poseidon 服务器应用程序框架的一部分。
// Copyleft 2014 - 2018, LH_Mouse. All wrongs reserved.

#ifndef POSEIDON_CBPP_CLIENT_HPP_
#define POSEIDON_CBPP_CLIENT_HPP_

#include "low_level_client.hpp"

namespace Poseidon {
namespace Cbpp {

class Client : public LowLevelClient {
private:
	class SyncJobBase;
	class ConnectJob;
	class ReadHupJob;
	class DataMessageJob;
	class ControlMessageJob;

private:
	unsigned m_message_id;
	StreamBuffer m_payload;

public:
	explicit Client(const SockAddr &addr, bool use_ssl = false, bool verify_peer = true);
	~Client();

protected:
	unsigned get_low_level_message_id() const {
		return m_message_id;
	}
	const StreamBuffer &get_low_level_payload() const {
		return m_payload;
	}

	// TcpSessionBase
	void on_connect() OVERRIDE;
	void on_read_hup() OVERRIDE;

	// LowLevelClient
	void on_low_level_data_message_header(boost::uint16_t message_id, boost::uint64_t payload_size) OVERRIDE;
	void on_low_level_data_message_payload(boost::uint64_t payload_offset, StreamBuffer payload) OVERRIDE;
	bool on_low_level_data_message_end(boost::uint64_t payload_size) OVERRIDE;

	bool on_low_level_control_message(StatusCode status_code, StreamBuffer param) OVERRIDE;

	// 可覆写。
	virtual void on_sync_connect();

	virtual void on_sync_data_message(boost::uint16_t message_id, StreamBuffer payload) = 0;
	virtual void on_sync_control_message(StatusCode status_code, StreamBuffer param);
};

}
}

#endif
