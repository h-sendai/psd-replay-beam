名前

psd_replay_beam - NEUNETエミュレータ

使用方法

usage: psd_replay_beam [-d] [-H hz] [-F] [-h ip_address] [-n data_size] [-p port] [-s usleep] [-v] data_file

Options:
    -d            debug
    -H hz         beam Hz (1 - 30) (default 25 Hz)
    -F            forever mode.  Read data file again when reach EOF.
    -h ip_address listen IP address
    -n data_size  data bytes size per one beam shot (default 100000 bytes)
    -s usleep     sleep usleep usec just before sending data
    -v            verbose

説明

NEUNETのプロトコルでデータを送信するエミュレータです。データ
は、自前で作るわけではなく、datafileを読んでそれをそのまま送
り出します。

返すデータ長はビーム運転のときをまねるようにしました。ビーム
1ショットで何イベントのデータが生成するかを -n オプションで
指定します。ビーム周期を-HでHz単位で指定します。-Hで指定でき
る範囲は1から30Hzまでで、整数のみ指定できます。

detafileの最後の部分を読んだときにリクエストされた長さだけ
detafileに残りデータがなかった場合は読み取れた分だけ返します。

datafileはどこかで実際に取得したデータファイルを利用するのが
簡単です。T0データはこのエミュレータでは発生させることができ
ません。T0データが必要ならT0データはdatafileに入っている必要
があります。

NEUNETはport 23を使用しますが、一般のUnixではport 23を使用
するにはroot権限が必要になるので、port 23456でlistenするように
しました。-p portでlistenするポートを変更することが可能です。
例えば -p 23 を付けて起動するとNEUNETモジュールのようにport 23
でlisten()しますが、通常のUnixではport 23を使用するにはroot権限
が必要です。

-Fオプションを指定しなかった場合はdatafileを読み終わったらlength 0
をクライアントに返し続けます。

オプション

-d        デバッグ出力を標準エラー出力に出す。

-F        foreverモード。datafileを読み終わったらもう一度読み直す。
          このオプションを指定しなかった場合はdatafileを読み終わ
          ったらlength 0を返し続ける。

-h ip_address
          このサーバーがlisten()するIPアドレスを指定する。指定
          されなかった場合は全てのネットワークインターフェイス
          でlisten()する。

-H Hz     ビーム運転周期をHzで指定する。整数のみ指定可。1から30
          Hzまで。その他の値が指定された場合はエラーとなる。
          
-n イベントバイトサイズ
          ビーム1ショットあたり発生するイベントサイズをバイトで
          指定する。

-p port   ポート番号portでlisten()する。指定しなかった場合の
          デフォルトは23456。

-s usleep データをソケットにwrite()する前にusleepマイクロ秒
          スリープする。転送速度を遅くするためのはなはだ適当
          な方法。マイクロ秒で指定できるが現在のLinuxの実装
          では1usを指定しても1ms程度はsleepしてしまうことに
          注意。

診断

psd_replay: (client exit?): Connection reset by peer

このサーバーが長さリクエストの受信を待っているときにクライアント側
からTCP RESETが送られてくると(クライアントがC-cで停止した場合など)
サーバーがこのメッセージを出します。

バグ

データファイルがないとなにもできない。イベントデータの生成は
どうにかなるかもしれないが、T0データの挿入はむずかしそう。

プログラムのバグではありませんが付属のMakefileは作者の趣味
でBSD makeの文法で書いてあります。

ファイルを読み終わったあとの動作。今はフラグを使ってEOFに
なったあとはread()しないようにしているが、EOFに達したファイル
を何度read()しても0が返ってくるだけでブロックなどしないので
read()させてその戻り値0をlengthとしてクライアントに送るほうが
フラグを使わなくてすむのでコードがすっきりするかもしれない。
が無意味にread()させるとシステムコール代が高くつくかもしれない。

想定されている利用目的

すでに性質がわかっているデータを利用してオンラインモニターの
使用感のテストなどに利用する。

ソースの出どころ

ネットワーク部分についてはStevensらの教科書Unix Network Programming
第3版に載っていたものをほぼそのまま使いました。

sicatで読み取らせたときの例

psd_replay_beam -h 130.87.234.118 -H 25 -n 128000 -p 5555 /home/sendai/src/psd_replay_beam/test.dat

として25Hz、ビーム1ショットで128000バイトのデータが生成する
としてこのエミュレータを走らせて、sicatで読み取ったときの例
を以下に示します。最初のカラムは接続してからの経過時間。
次のカラムはその直前のカラムとの時間差を示します。
(中略)のところは0イベントが返ってきています。概ね40msec間隔
で0以外のデータが返ってきているのがわかります。

0.000000 0.000000 request #    1  4096 events ( 32768 bytes )
0.005208 0.005208 request #    2  4096 events ( 32768 bytes )
0.008980 0.003772 request #    3  4096 events ( 32768 bytes )
0.013309 0.004329 request #    4  3712 events ( 29696 bytes )
0.014676 0.001367 request #    5     0 events (     0 bytes )
0.015995 0.001319 request #    6     0 events (     0 bytes )
(中略)
0.033002 0.000251 request #   27     0 events (     0 bytes )
0.034315 0.001313 request #   28     0 events (     0 bytes )
0.039000 0.004685 request #   29  4096 events ( 32768 bytes )
0.042763 0.003763 request #   30  4096 events ( 32768 bytes )
0.047124 0.004361 request #   31  4096 events ( 32768 bytes )
0.051333 0.004209 request #   32  3712 events ( 29696 bytes )
0.052688 0.001355 request #   33     0 events (     0 bytes )
0.054004 0.001316 request #   34     0 events (     0 bytes )
(中略)
0.070999 0.000251 request #   55     0 events (     0 bytes )
0.072310 0.001311 request #   56     0 events (     0 bytes )
0.077082 0.004772 request #   57  4096 events ( 32768 bytes )
0.080836 0.003754 request #   58  4096 events ( 32768 bytes )
0.085203 0.004367 request #   59  4096 events ( 32768 bytes )
0.089433 0.004230 request #   60  3712 events ( 29696 bytes )
0.090777 0.001344 request #   61     0 events (     0 bytes )
0.092093 0.001316 request #   62     0 events (     0 bytes )
(中略)
0.112028 0.001311 request #   86     0 events (     0 bytes )
0.112278 0.000250 request #   87     0 events (     0 bytes )
0.116850 0.004572 request #   88  4096 events ( 32768 bytes )
0.120604 0.003754 request #   89  4096 events ( 32768 bytes )
0.124990 0.004386 request #   90  4096 events ( 32768 bytes )
0.129200 0.004210 request #   91  3712 events ( 29696 bytes )
0.130552 0.001352 request #   92     0 events (     0 bytes )
0.131883 0.001331 request #   93     0 events (     0 bytes )
(中略)
0.152002 0.000252 request #  118     0 events (     0 bytes )
0.153314 0.001312 request #  119     0 events (     0 bytes )
0.157996 0.004682 request #  120  4096 events ( 32768 bytes )
0.161750 0.003754 request #  121  4096 events ( 32768 bytes )
0.166117 0.004367 request #  122  4096 events ( 32768 bytes )
0.170325 0.004208 request #  123  3712 events ( 29696 bytes )
0.171675 0.001350 request #  124     0 events (     0 bytes )
0.172990 0.001315 request #  125     0 events (     0 bytes )
(中略)
0.191621 0.000265 request #  148     0 events (     0 bytes )
0.192933 0.001312 request #  149     0 events (     0 bytes )
0.197627 0.004694 request #  150  4096 events ( 32768 bytes )
0.201380 0.003753 request #  151  4096 events ( 32768 bytes )
0.205745 0.004365 request #  152  4096 events ( 32768 bytes )
0.209949 0.004204 request #  153  3712 events ( 29696 bytes )
0.211313 0.001364 request #  154     0 events (     0 bytes )
0.212633 0.001320 request #  155     0 events (     0 bytes )
(以下略)

作者

千代浩司

変更履歴

* 2008-08-25
    - 接続直後のリクエストでデータを送るように変更した。
      以降 -H オプションで指定された間隔(あるいはデフォルトの25Hz)で
      でデータを送る。
    - 1イベントで発生するデータサイズのデフォルトを100000バイト(100kB)に
      した(以前は0バイトであった)。

* 2008-06-14
    - ビーム運転時をまねるように変更したブランチpsd_replay_beam
      を作成。

* 2008-06-04
    - -cオプション(データを返す回を指定)を追加。

* 2008-05-12
    - -zオプション(常にイベント長として0を返す)を追加。
    - -Pオプション(確率)を追加。

* 2008-04-12
    - -Fオプション(foreverモード)追加。

* 2008-04-07
    - 大バグfix(クライアントから送られてくるリクエストイベントデータサイズの
      解釈を間違っていたので直した)。

* 2008-04-05
    - 第1版。とりあえず書いてみた。
    - lengthとdataで2回write()していたのをwritev()で1回にした。
    - 反復サーバーだったのをコンカレントサーバーに書き換えた。
    - ソケット関連(socket(), bind(), listen(), accept())の部分は
      他の用途でもできるだけそのまま使えるようにするために
      ファイルを読んでソケットに書く関数を分離して別ファイルにした。
    - 転送速度を遅くするためにwritev()の直前でusleep()するオプションを
      追加した。
