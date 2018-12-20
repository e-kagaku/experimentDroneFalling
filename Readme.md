# Experiment Drone Falling
### ドローンからの落下実験 データ収集Arduino
written on 2018/12/19, by Yuta Nakamoto

![body_arduino](img/body_arduino2.jpg)

## 観測内容
以下の項目をArduinoで観測している。
- 緯度、経度(GPS)
- 高度、気圧、気温(BME280)
- 気温(MLX90614)
- (今回は開発途中で使用していない)姿勢(MPU9250)

## 注意点
1. 9Dコンパスは使えない。
今回9Dコンパスにて姿勢を観測するつもりだったが、3.3V - 5V変換モジュールが壊れて、I2C通信用コネクタは3.3Vで設計したためである。
1. GPSを付けるコネクタの位置に注意する。I2C通信ではないので、(一応コネクタにGPSと名前をつけている。下の回路図参照)
1. 落下させた際、衝撃の影響でArduinoのリセットがかかることを確認しているが、データは取れていてArduinoもすぐに再スタートしているようなので今回は気にしないことにする。
1. SDカードに保存するファイル名は8文字以内にする。
(8文字以上にすると、SD.open()がエラーとなり、SDに書き込めない。)
1. SEALEVELPRESSURE_HPA(その日の海面の気圧) を変える。

## 使用部品
以下に使用した部品をまとめる。
- Arduino Uno R3  
https://www.switch-science.com/catalog/789/
- SDカードシールドV4 SEEED-103030005 (SeedStudio製)  
https://www.switch-science.com/catalog/1292/
- Arduino R3 互換 プロトシールド キット （プロトタイプシールド キット）  
https://www.amazon.co.jp/Arduino-プロトシールド-キット-（プロトタイプシールド-キット）/dp/B00LP9CT22
- BME280使用 温湿度・気圧センサーモジュールキット
http://akizukidenshi.com/catalog/g/gK-09421/
- GPS受信機キット 1pps出力付き 「みちびき」対応  
http://akizukidenshi.com/catalog/g/gK-09991/
- 赤外線温度センサーMLX90614  
https://strawberry-linux.com/catalog/items?code=18120
- (開発中) MPU9250 9軸センサーモジュール
https://strawberry-linux.com/catalog/items?code=12250
<!-- - (開発中) DSR1603 コンパスモジュール 9軸デジタルコンパス
http://daisen-netstore.com/shopdetail/000000000196/
http://www.daisendenshi.com/download/DSR1603_manual-160615.pdf
- (開発中) I2Cバス用双方向電圧レベル変換モジュール(PCA9306)
http://akizukidenshi.com/catalog/g/gM-05452/ -->



## 使用ライブラリ

#### 追加ライブラリ
- Adafruit_Sensor：Adafruit製センサー用
https://github.com/adafruit/Adafruit_Sensor
- Adafruit_BME280：BME280温湿度・気圧センサー用
https://github.com/adafruit/Adafruit_BME280_Library
- SparkFun_MLX90614：MLX90614製赤外線温度センサー用
https://github.com/sparkfun/SparkFun_MLX90614_Arduino_Library
- TinyGPSPlus：GPS受信機キットのGPSデータを緯度、経度情報に整理する
https://github.com/mikalhart/TinyGPSPlus

#### Buit-inライブラリ(追加の必要なし)
- SoftwareSerial：ハードウェアシリアル(D0,D1)以外のピンでシリアル通信を行う
- SPI：SPI通信を行う
- SD：SDカードへの読み書きを行う


## センサーの概要
下図のような繋ぎ方をしている。
- I2C通信：BME280, MLX90614, MPU9250
- Serial通信：GPS
- SPI通信：SDカードシールド
![outline_arduino](img/outline_arduino.jpg)

## 回路図
上の概要を回路に直したものが下の回路図である。
![circuit](img/circuit_arduino_shield.png)

上の１つのコネクタがシリアル通信用(GPS)で、
下の3つのコネクタがI2C通信用(3.3V)(BME280,MLX90614,MPU9250)である。

## パラシュート作成方法
パラシュートは下記URLを参考に作成します。
http://fusenucyu.com/5611
