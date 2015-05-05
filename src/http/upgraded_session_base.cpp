// 这个文件是 Poseidon 服务器应用程序框架的一部分。
// Copyleft 2014 - 2015, LH_Mouse. All wrongs reserved.

#include "../precompiled.hpp"
#include "upgraded_session_base.hpp"
#include "session.hpp"

namespace Poseidon {

namespace Http {
	UpgradedSessionBase::UpgradedSessionBase(const boost::shared_ptr<Session> &parent, std::string uri)
		: m_parent(parent), m_uri(STD_MOVE(uri))
	{
	}

	void UpgradedSessionBase::onReadHup() NOEXCEPT {
	}
	void UpgradedSessionBase::onWriteHup() NOEXCEPT {
	}
	void UpgradedSessionBase::onClose(int errCode) NOEXCEPT {
		(void)errCode;
	}

	void UpgradedSessionBase::onInit(RequestHeaders requestHeaders, StreamBuffer entity){
		(void)requestHeaders;
		(void)entity;
	}

	bool UpgradedSessionBase::send(StreamBuffer buffer){
		const AUTO(parent, getParent());
		if(!parent){
			return false;
		}
		return static_cast<TcpSessionBase &>(*parent).send(STD_MOVE(buffer));
	}

	bool UpgradedSessionBase::hasBeenShutdownRead() const NOEXCEPT {
		const AUTO(parent, getParent());
		if(!parent){
			return true;
		}
		return static_cast<const TcpSessionBase &>(*parent).hasBeenShutdownRead();
	}
	bool UpgradedSessionBase::shutdownRead() NOEXCEPT {
		const AUTO(parent, getParent());
		if(!parent){
			return false;
		}
		return static_cast<TcpSessionBase &>(*parent).shutdownRead();
	}
	bool UpgradedSessionBase::hasBeenShutdownWrite() const NOEXCEPT {
		const AUTO(parent, getParent());
		if(!parent){
			return true;
		}
		return static_cast<const TcpSessionBase &>(*parent).hasBeenShutdownWrite();
	}
	bool UpgradedSessionBase::shutdownWrite() NOEXCEPT {
		const AUTO(parent, getParent());
		if(!parent){
			return false;
		}
		return static_cast<TcpSessionBase &>(*parent).shutdownWrite();
	}
	void UpgradedSessionBase::forceShutdown() NOEXCEPT {
		const AUTO(parent, getParent());
		if(!parent){
			return;
		}
		static_cast<TcpSessionBase &>(*parent).forceShutdown();
	}

	void UpgradedSessionBase::setTimeout(boost::uint64_t timeout){
		getSafeParent()->setTimeout(timeout);
	}
}

}