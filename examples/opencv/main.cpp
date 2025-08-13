//
//  main.cpp
//  skyway
//
//  Created by ogura on 2024/12/13.
//  Copyright © 2024 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#include <iostream>

#include "example_room.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "opencv.out <room_name>" << std::endl;
        return -1;
    }

    // SkyWayのAppIdとSecretKeyを環境変数から取得します。
    const char* app_id     = getenv("SKYWAY_APP_ID");
    const char* secret_key = getenv("SKYWAY_SECRET_KEY");
    if (!app_id || !secret_key) {
        std::cerr << "Please set SKYWAY_APP_ID and SKYWAY_SECRET_KEY environment variables."
                  << std::endl;
        return -1;
    }

    std::string room_name = argv[1];

    auto example_room = ExampleRoom();
    if (!example_room.Setup(app_id, secret_key)) {
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
