#ifndef __QYZK_OHNO_BOT_H__
#define __QYZK_OHNO_BOT_H__

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <nlohmann/json.hpp>

#include "./gateway.h"

namespace qyzk::ohno
{

class bot
{
public:
    using websocket_stream_type = boost::beast::websocket::stream<
        boost::beast::ssl_stream<
            boost::beast::tcp_stream >>;

    bot(boost::asio::io_context& context_io, ohno::config& config);
    auto connect(void) -> void;
    auto disconnect(void) -> void;
    auto async_start_heartbeat(boost::system::error_code const& error) -> void;
    auto beat(void) -> void;
    auto async_listen_event(void) -> void;
    auto get_heartbeat_timer(void) noexcept -> boost::asio::steady_timer&;
    auto get_heartbeat_interval(void) const noexcept -> uint32_t;
    auto set_heartbeat_interval(uint32_t const interval) noexcept -> void;
    auto is_running(void) const noexcept -> bool;
    auto stop(void) noexcept -> void;
    auto get_websocket_buffer(void) noexcept -> boost::beast::flat_buffer&;
    auto get_websocket(void) noexcept -> websocket_stream_type&;
    auto get_config(void) const noexcept -> ohno::config const&;
    auto get_config(void) noexcept -> ohno::config&;
    auto set_event_sequence(uint32_t const sequence) noexcept -> void;
    auto set_session_id(std::string const& session_id) -> void;
    auto is_resuming(void) const noexcept -> bool;
    auto start_resuming(void) noexcept -> void;
    auto stop_resuming(void) noexcept -> void;

private:
    ohno::config& m_config;
    boost::asio::io_context& m_context_io;
    boost::asio::ssl::context m_context_ssl;
    ohno::gateway const m_gateway;
    websocket_stream_type m_websocket;
    uint32_t m_heartbeat_interval;
    boost::beast::flat_buffer m_buffer;
    boost::asio::steady_timer m_timer_heartbeat;
    uint32_t m_sequence_event;
    bool m_is_running;
    bool m_is_resuming;
};

} // namespace qyzk::ohno

#endif