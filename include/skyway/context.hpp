//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CONTEXT_HPP_
#define SKYWAY_CONTEXT_HPP_

#include <mutex>

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
class Context {
public:
    static const unsigned int kVersionMajor = 4;
    static const unsigned int kVersionMinor = 1;
    static const unsigned int kVersionPatch = 0;

    /// @brief Contextのイベントリスナ
    class EventListener {
    public:
        virtual ~EventListener() = default;

        /// @brief 再接続処理が開始した時にコールされます。
        virtual void OnReconnectStart() = 0;

        /// @brief 再接続が成功した時にコールされます。
        virtual void OnReconnectSuccess() = 0;

        /// @brief 回復不能なエラーが発生した時にコールされます。
        /// @details インターネット接続状況を確認した上で再度Context::Setupをコールしてください。
        /// @param error エラー
        virtual void OnFatalError(const global::Error& error) = 0;
    };

    /// @brief AuthTokenのイベントリスナ
    class AuthTokenListener {
    public:
        virtual ~AuthTokenListener() = default;

        /// @brief 設定したリマインド時間に応じてコールされるリマインダコールバック関数
        virtual void OnTokenRefreshingNeeded() {}

        /// @brief トークンが失効した時にコールされるコールバック関数
        virtual void OnTokenExpired() {}
    };

    /// @brief SkyWayの利用に関する設定
    struct SkyWayOptions {
        /// @cond INTERNAL_SECTION

        /// @brief RTCAPIサーバーへの接続に関する設定
        struct RtcApi {
            std::optional<std::string> domain;
            std::optional<bool> secure;
        };

        /// @brief ICEサーバーへの接続に関する設定
        struct IceParams {
            std::optional<std::string> domain;
            std::optional<int> version;
            std::optional<bool> secure;
            webrtc::PeerConnectionInterface::IceServers custom_ice_servers;
        };

        /// @brief Signalingサーバーへの接続に関する設定
        struct Signaling {
            std::optional<std::string> domain;
            std::optional<bool> secure;
        };

        /// @brief Analyticsサーバーへの接続に関する設定
        struct Analytics {
            std::optional<std::string> domain;
            std::optional<bool> secure;
        };

        /// @brief RTCサーバーへの接続に関する設定
        struct RtcConfig {
            std::optional<int> timeout;
            std::optional<domain::TurnPolicy> policy;
        };

        /// @endcond

        /// @brief トークンに関する設定
        struct Token {
            [[deprecated]] std::optional<int> remind_time_sec;
            std::optional<int> update_remind_sec;
            AuthTokenListener* listener = nullptr;
        };

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
        domain::LogLevel log_level = domain::LogLevel::kInfo;

        /// @cond INTERNAL_SECTION
        RtcApi rtc_api;
        IceParams ice_params;
        Signaling signaling;
        Analytics analytics;
        RtcConfig rtc_config;
        Token token;
        /// @endcond

        /// @brief WebRTCのログを有効にします
        bool enable_webrtc_log = false;

        /// @brief オーディオバックエンドを指定します
        skyway::media::AudioBackendType audio_backend =
            skyway::media::AudioBackendType::kPulseAudio;

        /// @brief 音声処理に関する設定
        /// @details
        /// エコーキャンセラー等の音声処理は、Context全体で共有される1つの音声処理エンジンに対して
        /// 適用されるため、Context単位の設定となります。
        skyway::media::AudioProcessingOptions audio_processing;

        /// @brief RTPに関する設定
        Rtp rtp;

        /// @cond INTERNAL_SECTION
        /// @brief SFUサーバーの接続に関する設定
        struct SFU {
            std::optional<std::string> domain;
            std::optional<int> version;
            std::optional<bool> secure;
        };
        SFU sfu;
        /// @endcond
    };

    /// @brief Contextを初期化します。
    /// @details SkyWayを利用するためには必ずこのメソッドを最初にコールする必要があります。
    /// @param token JWT形式のAuthトークン
    /// @param listener イベントリスナ
    /// @param options オプション
    static bool Setup(const std::string& token,
                      EventListener* listener,
                      const SkyWayOptions& options);

    /// @brief Contextを初期化します。このメソッドは動作確認用です。
    /// @details 認証情報の漏洩を防ぐため、このメソッドをリリース版で利用することは控えてください。
    /// @param app_id アプリケーションID
    /// @param secret_key アプリケーションのシークレットキー
    /// @param listener イベントリスナ
    /// @param options オプション
    static bool SetupForDev(const std::string& app_id,
                            const std::string& secret_key,
                            EventListener* listener,
                            const SkyWayOptions& options);

    /// @brief SkyWayを終了し、Contextを破棄します。
    /// @details
    /// コンテキストを破棄し、全ての接続を切断します。
    /// SkyWayの利用が不要になった時にコールしてください。
    /// Dispose完了後にSDKで生成されたリソースにアクセスしないでください。
    /// skyway::Context::Setup()を再度コールすることで利用可能になります。
    static void Dispose();

    /// @brief AuthTokenを更新します。
    static bool UpdateAuthToken(const std::string& token);

    /// @brief SkyWay Linux SDKのバージョンを取得します。
    static std::string GetVersionString();

    /// @cond INTERNAL_SECTION
    /// @brief
    /// RTP入力が有効かどうかを検証して有効ならばコーデックを返し、無効ならばnullptrを返します。
    static std::shared_ptr<media::codec::VideoCodec> GetRtpVideoInputCodecWithValidate();
    /// @endcond

private:
    class CoreEventListenerAdapter : public core::Context::EventListener {
    public:
        CoreEventListenerAdapter();
        void SetListener(Context::EventListener* listener);
        void OnReconnectStart() override;
        void OnReconnectSuccess() override;
        void OnFatalError(const global::Error& error) override;

    private:
        Context::EventListener* listener_;
    };

    class CoreAuthTokenListenerAdapter : public token::interface::AuthTokenManager::Listener {
    public:
        CoreAuthTokenListenerAdapter();
        void SetListener(Context::AuthTokenListener* listener);
        void OnTokenRefreshingNeeded() override;
        void OnTokenExpired() override;

    private:
        Context::AuthTokenListener* listener_;
    };

    static core::TurnPolicy ConvertToCoreTurnPolicy(domain::TurnPolicy policy);
    static core::ContextOptions ConvertToCoreContextOptions(const SkyWayOptions& options);

    inline static SkyWayOptions::Rtp rtp_;
    static std::mutex core_event_listener_mutex_;
    static CoreEventListenerAdapter core_event_listener_adapter_;
    static std::mutex core_auth_token_listener_mutex_;
    static CoreAuthTokenListenerAdapter core_auth_token_listener_adapter_;

public:
    /// @cond INTERNAL_SECTION
    friend class media::rtp::PassthroughVideoEncoderFactoryTest;
    /// @endcond
};
}  // namespace skyway

#endif /* SKYWAY_CONTEXT_HPP_ */
