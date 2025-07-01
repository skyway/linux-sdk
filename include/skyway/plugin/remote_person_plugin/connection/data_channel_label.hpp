//
//  data_channel_label.hpp
//  skyway
//
//  Created by sandabu on 2022/01/27.
//  Copyright © 2022 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_DATA_CHANNEL_LABEL_HPP_
#define SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_DATA_CHANNEL_LABEL_HPP_

#include <json.hpp>

namespace skyway {
namespace plugin {
namespace remote_person {
namespace connection {

struct DataChannelLabel {
    std::string publication_id;
    std::string stream_id;
};

void from_json(const nlohmann::json& j, DataChannelLabel& label);

void to_json(nlohmann::json& j, const DataChannelLabel& label);

}  // namespace connection
}  // namespace remote_person
}  // namespace plugin
}  // namespace skyway
#endif /* SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_DATA_CHANNEL_LABEL_HPP_ */
