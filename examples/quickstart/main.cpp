//
//  main.cpp
//  skyway
//
//  Created by ogura on 2024/2/2.
//  Copyright © 2024 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#include <iostream>

#include "example_room.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        std::cerr << "app.out <room_name> [renderer_device_name]" << std::endl;
        return -1;
    }

    // SkyWayのAuthTokenを環境変数から取得します。
    const char* token = getenv("SKYWAY_AUTH_TOKEN");
    if (!token) {
        std::cerr << "Please set SKYWAY_AUTH_TOKEN environment variable." << std::endl;
        return -1;
    }

    std::string room_name           = argv[1];
    std::string video_output_device = "";
    if (argc == 3) {
        video_output_device = argv[2];
    }

    // イベント関連のログを出力が不要であれば第二引数をfalseにしてください。
    auto example_room = ExampleRoom(video_output_device, true);
    if (!example_room.Setup(token)) {
        return -1;
    }
    if (!example_room.JoinRoom(room_name)) {
        return -1;
    }
    example_room.SubscribeAll();
    example_room.Publish();

    // キー入力を待ちます。
    std::cout << "- Press ENTER key to close..." << std::endl;
    std::cin.ignore();
    std::cin.get();

    example_room.LeaveRoom();
    example_room.Dispose();
    return 0;
}
