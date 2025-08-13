# OpenCV Example
- SkyWay Linux®︎ SDKのOpenCVサンプルです。
- 内容については[QuickStart](https://skyway.ntt.com/ja/docs/user-guide/linux-sdk/quickstart/)を実施済みの方を対象としております。

## サンプル概要
- 任意のルームに入室し、OpenCVを利用して作成したVideoをPublishします。また、他のメンバーがPublishしたVideoをSubscribeし、cv::imshowを利用して表示します。

## ビルド/実行方法
- 本サンプルでは追加のパッケージが必要となります。aptを利用してインストールしてください。
```
apt update 
apt install libswscale-dev 
```
利用するOpenCVのバージョンは4.6.0を想定しています。
`Ubuntu24.04`の場合はaptを利用してinstallしてください。
```
apt install libopencv-dev 
```
それ以外のOSの場合は下記のOpenCV公式チュートリアルを参考に`OpenCV 4.6.0`をインストールしてください。
https://docs.opencv.org/4.6.0/d7/d9f/tutorial_linux_install.html

以下は`OpenCV 4.6.0`のビルド例です。
```
sudo apt update && sudo apt install -y cmake g++ wget unzip libgtk2.0-dev
 
# Download and unpack sources
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.6.0.zip
unzip opencv.zip
 
# Create build directory
mkdir -p build && cd build
 
# Configure
cmake  ../opencv-4.6.0
 
# Build
cmake --build .

# Install
sudo make install
```

- examples直下でビルドします。
```
cmake -DENABLE_OPENCV_EXAMPLE=true -B build
cd build
make -j
```

- 環境変数の`SKYWAY_AUTH_TOKEN`に生成したトークンを設定します。
    - トークンの設定方法などは[QuickStart](https://skyway.ntt.com/ja/docs/user-guide/linux-sdk/quickstart/)の「トークンの準備」をご覧ください。

- 引数に入室したいルーム名を指定して実行します。
```
opencv.out test_room
```

- 映像の送受信を行うために、別途QuickStartのアプリケーションを実行するか、別途`opencv.out`を実行していただく必要があります。

## 商標
Linux®︎は、米国およびその他の国における Linus Torvalds の登録商標です。
