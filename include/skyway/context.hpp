//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CONTEXT_HPP_
#define SKYWAY_CONTEXT_HPP_

#include <skyway/core/context.hpp>
#include <skyway/core/interface/remote_member_plugin.hpp>
#include <skyway/global/error.hpp>
#include <skyway/global/logger.hpp>
#include <skyway/network/interface/http_client.hpp>
#include <skyway/network/interface/websocket_client.hpp>
#include "skyway/media/codec/video_codec.hpp"
#include "skyway/media/device_manager.hpp"

namespace skyway {
namespace media {
namespace rtp {

class PassthroughVideoEncoderFactoryTest;

}  // namespace rtp
}  // namespace media

/// @brief アプリケーションでSkyWay全体の設定、取得を行うStaticなコンテキスト
/// @details 特別な理由がない場合はcore::Contextでなく、こちらを利用してください。
class Context : public core::Context {
public:
    static const unsigned int kVersionMajor = 3;
    static const unsigned int kVersionMinor = 3;
    static const unsigned int kVersionPatch = 0;

    /// @brief SkyWayの利用に関する設定
    struct SkyWayOptions : core::ContextOptions {
        /**
         * @brief SkyWayのRTPに関する設定
         */
        struct Rtp {
            /// @brief RTP入力に関する設定
            struct Input {
                /// @brief RTP映像入力に関する設定
                struct Video {
                    /**
                     * @brief RTP映像入力を有効にするかどうか
                     * @details
                     * この値が`true`かつ`codec`が設定されている場合、RTP映像入力モードとなります。
                     *
                     * RTP映像入力モードでは、`RtpCapturerVideoSource`以外のVideoSourceは利用できません。
                     */
                    bool enabled;
                    /**
                     * @brief RTP映像入力のコーデック
                     * @details
                     * `enabled`が`true`の場合、必ず設定する必要があります。
                     *
                     * Linux SDK
                     * では現在H.264のデコードに対応していないため、H.264を利用したPublicationをSubscribeすることはできません。
                     *
                     * 各SDKが対応するコーデックについては[こちら](https://skyway.ntt.com/en/docs/user-guide/commons/codecs/)に記載しております。
                     */
                    std::shared_ptr<media::codec::VideoCodec> codec;
                    Video() : enabled(false), codec(nullptr) {}
                };
                /// @brief RTP映像入力に関する設定
                Video video;
            };
            /// @brief RTP入力に関する設定
            Input input;
        };
        /// @brief ログレベル
        global::interface::Logger::Level log_level = global::interface::Logger::kInfo;

        /// @brief WebRTCのログを有効にします
        bool enable_webrtc_log = false;

        /// @brief オーディオバックエンドを指定します
        skyway::media::AudioBackendType audio_backend =
            skyway::media::AudioBackendType::kPulseAudio;

        /// @brief RTPに関する設定
        Rtp rtp;

        /// @brief SFUサーバーの接続に関する設定
        struct SFU {
            std::optional<std::string> domain;
            std::optional<int> version;
            std::optional<bool> secure;
        };
        SFU sfu;
    };

    /// @brief Contextを初期化します。
    /// @details SkyWayを利用するためには必ずこのメソッドを最初にコールする必要があります。
    /// @param token JWT形式のAuthトークン
    /// @param listener イベントリスナ
    /// @param options オプション
    static bool Setup(const std::string& token,
                      core::Context::EventListener* listener,
                      const SkyWayOptions& options);

    /// @brief Contextを初期化します。このメソッドは動作確認用です。
    /// @details 認証情報の漏洩を防ぐため、このメソッドをリリース版で利用することは控えてください。
    /// @param app_id アプリケーションID
    /// @param secret_key アプリケーションのシークレットキー
    /// @param listener イベントリスナ
    /// @param options オプション
    static bool SetupForDev(const std::string& app_id,
                            const std::string& secret_key,
                            core::Context::EventListener* listener,
                            const SkyWayOptions& options);

    /// @brief SkyWayを終了し、Contextを破棄します。
    /// @details
    /// コンテキストを破棄し、全ての接続を切断します。
    /// SkyWayの利用が不要になった時にコールしてください。
    /// Dispose完了後にSDKで生成されたリソースにアクセスしないでください。
    /// skyway::Context::Setup()を再度コールすることで利用可能になります。
    static void Dispose();

    /// @brief SkyWay Linux SDKのバージョンを取得します。
    static std::string GetVersionString();

    /// @cond INTERNAL_SECTION
    /// @brief
    /// RTP入力が有効かどうかを検証して有効ならばコーデックを返し、無効ならばnullptrを返します。
    static std::shared_ptr<media::codec::VideoCodec> GetRtpVideoInputCodecWithValidate();
    /// @endcond

private:
    inline static SkyWayOptions::Rtp rtp_;

public:
    /// @cond INTERNAL_SECTION
    friend class media::rtp::PassthroughVideoEncoderFactoryTest;
    /// @endcond
};
}  // namespace skyway

#endif /* SKYWAY_CONTEXT_HPP_ */
