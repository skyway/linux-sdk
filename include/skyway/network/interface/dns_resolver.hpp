//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_NETWORK_INTERFACE_DNS_RESOLVER_HPP
#define SKYWAY_NETWORK_INTERFACE_DNS_RESOLVER_HPP

#include <boost/asio.hpp>

namespace skyway {
namespace network {
namespace interface {

template <typename InternetProtocol>
class DnsResolver {
public:
    virtual ~DnsResolver() = default;
    /**
     * @brief タイムアウト付きでDNS解決を行います。
     * @details
     * configで設定されたタイムアウトを利用して`Resolve`します。
     *
     * この関数は`basic_resolver`の`resolve`中にスイッチとルータ間で抜線すると40秒以上かかることがあるため実装しています。
     *
     * 原因は`resolve`関数内部でglibcの`getaddrinfo`を呼び出しているためです。
     *
     * タイムアウトした場合は別スレッドで`getaddrinfo`を実行し続け、結果が得られた場合は次回の`Resolve`でその結果を返します。
     *
     * @throw boost::system::system_error
     * タイムアウトやResolveエラーが発生した場合にスローされます。
     * @param host ホスト名
     * @param port ポート番号
     * @return boost::asio::ip::basic_resolver_results<InternetProtocol>
     */
    virtual boost::asio::ip::basic_resolver_results<InternetProtocol> Resolve(
        const std::string& host, const std::string& port) = 0;
};

}  // namespace interface
}  // namespace network
}  // namespace skyway

#endif /* SKYWAY_NETWORK_INTERFACE_DNS_RESOLVER_HPP */
