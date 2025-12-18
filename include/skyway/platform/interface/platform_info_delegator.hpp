//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLATFORM_INTERFACE_PLATFORM_INFO_DELEGATOR_HPP_
#define SKYWAY_PLATFORM_INTERFACE_PLATFORM_INFO_DELEGATOR_HPP_

#include <memory>
#include <string>

namespace skyway {
namespace platform {
namespace interface {

/// @brief デバイス情報デリゲーター
/// @details Platformにてこのインターフェースを実装して、Context::Setupに渡してください。
class PlatformInfoDelegator {
public:
    /// @brief デストラクタ
    virtual ~PlatformInfoDelegator() = default;

    /// @brief プラットフォーム名を取得します。
    /// @details 例として以下の文字列が返ります。
    /// - Android: "android"
    /// - iOS: "ios"
    virtual std::string GetPlatform() const = 0;

    /// @brief OS情報を取得します。
    /// @details 例として以下の文字列が返ります。
    /// - Android: "Android 18"
    /// - iOS: "iOS 13.4.1"
    virtual std::string GetOsInfo() const = 0;

    /// @brief モデル名を取得します。
    /// @details 例として以下の文字列が返ります。
    /// - Android: "google Nexus One"
    /// - iOS: "iPhone14,7"
    virtual std::string GetModelName() const = 0;

    /// @brief SDKのバージョンを取得します。
    /// @details 例として以下の文字列が返ります。
    /// - Android: "1.2.2"
    /// - iOS: "1.2.2"
    virtual std::string GetSdkVersion() const = 0;

    /// @brief デバイス情報デリゲーターをセットします。
    /// @details `Context::Setup()`内でセットします。
    /// @param delegator デリゲーター
    static void SetSharedInstance(std::unique_ptr<PlatformInfoDelegator> delegator);

    /// @brief デバイス情報デリゲーターを取得します。
    static const PlatformInfoDelegator* const Shared();

private:
    static std::unique_ptr<PlatformInfoDelegator> shared_;
};

}  // namespace interface
}  // namespace platform
}  // namespace skyway

#endif /* SKYWAY_PLATFORM_INTERFACE_PLATFORM_INFO_DELEGATOR_HPP_ */
