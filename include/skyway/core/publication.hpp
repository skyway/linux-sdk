//
//  publication.hpp
//  skyway
//
//  Created by sandabu on 2022/01/12.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_PUBLICATION_HPP_
#define SKYWAY_CORE_PUBLICATION_HPP_

#include "skyway/core/interface/channel.hpp"
#include "skyway/core/interface/local_stream.hpp"

namespace skyway {
namespace core {

/// @brief Publicationの実装クラス
class Publication : public interface::Publication {
public:
    /// @cond INTERNAL_SECTION
    Publication(interface::Channel* channel, const model::Publication& initial_dto);
    /// @endcond
    ~Publication();

    void AddEventListener(interface::Publication::EventListener* listener) override;
    void RemoveEventListener(interface::Publication::EventListener* listener) override;

    /// @cond INTERNAL_SECTION
    void AddInternalListener(InternalListener* listener) override;
    void RemoveInternalListener(InternalListener* listener) override;
    /// @endcond

    std::string Id() const override;
    interface::Member* Publisher() const override;
    std::vector<interface::Subscription*> Subscriptions() const override;
    model::ContentType ContentType() const override;
    boost::optional<std::string> Metadata() const override;
    interface::Publication* Origin() const override;
    std::vector<model::Codec> CodecCapabilities() const override;
    std::vector<model::Encoding> Encodings() const override;
    interface::PublicationState State() override;

    std::shared_ptr<interface::LocalStream> Stream() const override;

    bool UpdateMetadata(const std::string& metadata) override;
    void UpdateEncodings(std::vector<model::Encoding> encodings) override;
    bool ReplaceStream(std::shared_ptr<interface::LocalStream> stream) override;
    bool Cancel() const override;
    bool Enable() override;
    bool Disable() const override;

    boost::optional<model::WebRTCStats> GetStats(const std::string& selector) override;
    /// @cond INTERNAL_SECTION
    void AddGetStatsCallback(const std::string& remote_member_id, Callback* callback) override;
    void RemoveGetStatsCallback(const std::string& remote_member_id) override;

    void SetCodecCapabilities(std::vector<model::Codec> codec_capabilities) override;
    void SetEncodings(std::vector<model::Encoding> encodings) override;
    void SetStream(std::shared_ptr<interface::LocalStream> stream) override;
    bool IsEnabling() override;
    void Dispose() override;

    void OnUnpublished() override;
    void OnSubscribed(interface::Subscription* subscription) override;
    void OnUnsubscribed(interface::Subscription* subscription) override;
    void OnMetadataUpdated(const std::string& metadata) override;
    void OnEnabled() override;
    void OnDisabled() override;
    void OnConnectionStateChanged(const ConnectionState new_state) override;
    /// @endcond

private:
    interface::Channel* channel_;
    model::Publication initial_dto_;
    std::atomic<interface::PublicationState> state_;
    std::vector<model::Codec> codec_capabilities_;
    std::vector<model::Encoding> encodings_;

    std::shared_ptr<interface::LocalStream> stream_;

    std::mutex listeners_mtx_;
    std::mutex internal_listeners_mtx_;
    std::unordered_set<interface::Publication::EventListener*> listeners_;
    std::unordered_set<interface::Publication::InternalListener*> internal_listeners_;
    std::atomic<bool> metadata_updated_;
    bool is_enabling_;
    std::mutex get_stats_callback_mutex_;
    std::unordered_map<std::string, Callback*> get_stats_callbacks_;
};

}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_PUBLICATION_HPP_ */
