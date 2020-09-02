$BL>A0(B

psd_replay_beam - NEUNET$B%(%_%e%l!<%?(B

$B;HMQJ}K!(B

usage: psd_replay_beam [-d] [-H hz] [-F] [-h ip_address] [-n data_size] [-p port] [-s usleep] [-v] data_file

Options:
    -d            debug
    -H hz         beam Hz (1 - 30) (default 25 Hz)
    -F            forever mode.  Read data file again when reach EOF.
    -h ip_address listen IP address
    -n data_size  data bytes size per one beam shot (default 100000 bytes)
    -s usleep     sleep usleep usec just before sending data
    -v            verbose

$B@bL@(B

NEUNET$B$N%W%m%H%3%k$G%G!<%?$rAw?.$9$k%(%_%e%l!<%?$G$9!#%G!<%?(B
$B$O!"<+A0$G:n$k$o$1$G$O$J$/!"(Bdatafile$B$rFI$s$G$=$l$r$=$N$^$^Aw(B
$B$j=P$7$^$9!#(B

$BJV$9%G!<%?D9$O%S!<%`1?E>$N$H$-$r$^$M$k$h$&$K$7$^$7$?!#%S!<%`(B
1$B%7%g%C%H$G2?%$%Y%s%H$N%G!<%?$,@8@.$9$k$+$r(B -n $B%*%W%7%g%s$G(B
$B;XDj$7$^$9!#%S!<%`<~4|$r(B-H$B$G(BHz$BC10L$G;XDj$7$^$9!#(B-H$B$G;XDj$G$-(B
$B$kHO0O$O(B1$B$+$i(B30Hz$B$^$G$G!"@0?t$N$_;XDj$G$-$^$9!#(B

detafile$B$N:G8e$NItJ,$rFI$s$@$H$-$K%j%/%(%9%H$5$l$?D9$5$@$1(B
detafile$B$K;D$j%G!<%?$,$J$+$C$?>l9g$OFI$_<h$l$?J,$@$1JV$7$^$9!#(B

datafile$B$O$I$3$+$G<B:]$K<hF@$7$?%G!<%?%U%!%$%k$rMxMQ$9$k$N$,(B
$B4JC1$G$9!#(BT0$B%G!<%?$O$3$N%(%_%e%l!<%?$G$OH/@8$5$;$k$3$H$,$G$-(B
$B$^$;$s!#(BT0$B%G!<%?$,I,MW$J$i(BT0$B%G!<%?$O(Bdatafile$B$KF~$C$F$$$kI,MW(B
$B$,$"$j$^$9!#(B

NEUNET$B$O(Bport 23$B$r;HMQ$7$^$9$,!"0lHL$N(BUnix$B$G$O(Bport 23$B$r;HMQ(B
$B$9$k$K$O(Broot$B8"8B$,I,MW$K$J$k$N$G!"(Bport 23456$B$G(Blisten$B$9$k$h$&$K(B
$B$7$^$7$?!#(B-p port$B$G(Blisten$B$9$k%]!<%H$rJQ99$9$k$3$H$,2DG=$G$9!#(B
$BNc$($P(B -p 23 $B$rIU$1$F5/F0$9$k$H(BNEUNET$B%b%8%e!<%k$N$h$&$K(Bport 23
$B$G(Blisten()$B$7$^$9$,!"DL>o$N(BUnix$B$G$O(Bport 23$B$r;HMQ$9$k$K$O(Broot$B8"8B(B
$B$,I,MW$G$9!#(B

-F$B%*%W%7%g%s$r;XDj$7$J$+$C$?>l9g$O(Bdatafile$B$rFI$_=*$o$C$?$i(Blength 0
$B$r%/%i%$%"%s%H$KJV$7B3$1$^$9!#(B

$B%*%W%7%g%s(B

-d        $B%G%P%C%0=PNO$rI8=`%(%i!<=PNO$K=P$9!#(B

-F        forever$B%b!<%I!#(Bdatafile$B$rFI$_=*$o$C$?$i$b$&0lEYFI$_D>$9!#(B
          $B$3$N%*%W%7%g%s$r;XDj$7$J$+$C$?>l9g$O(Bdatafile$B$rFI$_=*$o(B
          $B$C$?$i(Blength 0$B$rJV$7B3$1$k!#(B

-h ip_address
          $B$3$N%5!<%P!<$,(Blisten()$B$9$k(BIP$B%"%I%l%9$r;XDj$9$k!#;XDj(B
          $B$5$l$J$+$C$?>l9g$OA4$F$N%M%C%H%o!<%/%$%s%?!<%U%'%$%9(B
          $B$G(Blisten()$B$9$k!#(B

-H Hz     $B%S!<%`1?E><~4|$r(BHz$B$G;XDj$9$k!#@0?t$N$_;XDj2D!#(B1$B$+$i(B30
          Hz$B$^$G!#$=$NB>$NCM$,;XDj$5$l$?>l9g$O%(%i!<$H$J$k!#(B
          
-n $B%$%Y%s%H%P%$%H%5%$%:(B
          $B%S!<%`(B1$B%7%g%C%H$"$?$jH/@8$9$k%$%Y%s%H%5%$%:$r%P%$%H$G(B
          $B;XDj$9$k!#(B

-p port   $B%]!<%HHV9f(Bport$B$G(Blisten()$B$9$k!#;XDj$7$J$+$C$?>l9g$N(B
          $B%G%U%)%k%H$O(B23456$B!#(B

-s usleep $B%G!<%?$r%=%1%C%H$K(Bwrite()$B$9$kA0$K(Busleep$B%^%$%/%mIC(B
          $B%9%j!<%W$9$k!#E>AwB.EY$rCY$/$9$k$?$a$N$O$J$O$@E,Ev(B
          $B$JJ}K!!#%^%$%/%mIC$G;XDj$G$-$k$,8=:_$N(BLinux$B$N<BAu(B
          $B$G$O(B1us$B$r;XDj$7$F$b(B1ms$BDxEY$O(Bsleep$B$7$F$7$^$&$3$H$K(B
          $BCm0U!#(B

$B?GCG(B

psd_replay: (client exit?): Connection reset by peer

$B$3$N%5!<%P!<$,D9$5%j%/%(%9%H$N<u?.$rBT$C$F$$$k$H$-$K%/%i%$%"%s%HB&(B
$B$+$i(BTCP RESET$B$,Aw$i$l$F$/$k$H(B($B%/%i%$%"%s%H$,(BC-c$B$GDd;_$7$?>l9g$J$I(B)
$B%5!<%P!<$,$3$N%a%C%;!<%8$r=P$7$^$9!#(B

$B%P%0(B

$B%G!<%?%U%!%$%k$,$J$$$H$J$K$b$G$-$J$$!#%$%Y%s%H%G!<%?$N@8@.$O(B
$B$I$&$K$+$J$k$+$b$7$l$J$$$,!"(BT0$B%G!<%?$NA^F~$O$`$:$+$7$=$&!#(B

$B%W%m%0%i%`$N%P%0$G$O$"$j$^$;$s$,IUB0$N(BMakefile$B$O:n<T$N<qL#(B
$B$G(BBSD make$B$NJ8K!$G=q$$$F$"$j$^$9!#(B

$B%U%!%$%k$rFI$_=*$o$C$?$"$H$NF0:n!#:#$O%U%i%0$r;H$C$F(BEOF$B$K(B
$B$J$C$?$"$H$O(Bread()$B$7$J$$$h$&$K$7$F$$$k$,!"(BEOF$B$KC#$7$?%U%!%$%k(B
$B$r2?EY(Bread()$B$7$F$b(B0$B$,JV$C$F$/$k$@$1$G%V%m%C%/$J$I$7$J$$$N$G(B
read()$B$5$;$F$=$NLa$jCM(B0$B$r(Blength$B$H$7$F%/%i%$%"%s%H$KAw$k$[$&$,(B
$B%U%i%0$r;H$o$J$/$F$9$`$N$G%3!<%I$,$9$C$-$j$9$k$+$b$7$l$J$$!#(B
$B$,L50UL#$K(Bread()$B$5$;$k$H%7%9%F%`%3!<%kBe$,9b$/$D$/$+$b$7$l$J$$!#(B

$BA[Dj$5$l$F$$$kMxMQL\E*(B

$B$9$G$K@-<A$,$o$+$C$F$$$k%G!<%?$rMxMQ$7$F%*%s%i%$%s%b%K%?!<$N(B
$B;HMQ46$N%F%9%H$J$I$KMxMQ$9$k!#(B

$B%=!<%9$N=P$I$3$m(B

$B%M%C%H%o!<%/ItJ,$K$D$$$F$O(BStevens$B$i$N652J=q(BUnix Network Programming
$BBh(B3$BHG$K:\$C$F$$$?$b$N$r$[$\$=$N$^$^;H$$$^$7$?!#(B

sicat$B$GFI$_<h$i$;$?$H$-$NNc(B

psd_replay_beam -h 130.87.234.118 -H 25 -n 128000 -p 5555 /home/sendai/src/psd_replay_beam/test.dat

$B$H$7$F(B25Hz$B!"%S!<%`(B1$B%7%g%C%H$G(B128000$B%P%$%H$N%G!<%?$,@8@.$9$k(B
$B$H$7$F$3$N%(%_%e%l!<%?$rAv$i$;$F!"(Bsicat$B$GFI$_<h$C$?$H$-$NNc(B
$B$r0J2<$K<($7$^$9!#:G=i$N%+%i%`$O@\B3$7$F$+$i$N7P2a;~4V!#(B
$B<!$N%+%i%`$O$=$ND>A0$N%+%i%`$H$N;~4V:9$r<($7$^$9!#(B
($BCfN,(B)$B$N$H$3$m$O(B0$B%$%Y%s%H$,JV$C$F$-$F$$$^$9!#35$M(B40msec$B4V3V(B
$B$G(B0$B0J30$N%G!<%?$,JV$C$F$-$F$$$k$N$,$o$+$j$^$9!#(B

0.000000 0.000000 request #    1  4096 events ( 32768 bytes )
0.005208 0.005208 request #    2  4096 events ( 32768 bytes )
0.008980 0.003772 request #    3  4096 events ( 32768 bytes )
0.013309 0.004329 request #    4  3712 events ( 29696 bytes )
0.014676 0.001367 request #    5     0 events (     0 bytes )
0.015995 0.001319 request #    6     0 events (     0 bytes )
($BCfN,(B)
0.033002 0.000251 request #   27     0 events (     0 bytes )
0.034315 0.001313 request #   28     0 events (     0 bytes )
0.039000 0.004685 request #   29  4096 events ( 32768 bytes )
0.042763 0.003763 request #   30  4096 events ( 32768 bytes )
0.047124 0.004361 request #   31  4096 events ( 32768 bytes )
0.051333 0.004209 request #   32  3712 events ( 29696 bytes )
0.052688 0.001355 request #   33     0 events (     0 bytes )
0.054004 0.001316 request #   34     0 events (     0 bytes )
($BCfN,(B)
0.070999 0.000251 request #   55     0 events (     0 bytes )
0.072310 0.001311 request #   56     0 events (     0 bytes )
0.077082 0.004772 request #   57  4096 events ( 32768 bytes )
0.080836 0.003754 request #   58  4096 events ( 32768 bytes )
0.085203 0.004367 request #   59  4096 events ( 32768 bytes )
0.089433 0.004230 request #   60  3712 events ( 29696 bytes )
0.090777 0.001344 request #   61     0 events (     0 bytes )
0.092093 0.001316 request #   62     0 events (     0 bytes )
($BCfN,(B)
0.112028 0.001311 request #   86     0 events (     0 bytes )
0.112278 0.000250 request #   87     0 events (     0 bytes )
0.116850 0.004572 request #   88  4096 events ( 32768 bytes )
0.120604 0.003754 request #   89  4096 events ( 32768 bytes )
0.124990 0.004386 request #   90  4096 events ( 32768 bytes )
0.129200 0.004210 request #   91  3712 events ( 29696 bytes )
0.130552 0.001352 request #   92     0 events (     0 bytes )
0.131883 0.001331 request #   93     0 events (     0 bytes )
($BCfN,(B)
0.152002 0.000252 request #  118     0 events (     0 bytes )
0.153314 0.001312 request #  119     0 events (     0 bytes )
0.157996 0.004682 request #  120  4096 events ( 32768 bytes )
0.161750 0.003754 request #  121  4096 events ( 32768 bytes )
0.166117 0.004367 request #  122  4096 events ( 32768 bytes )
0.170325 0.004208 request #  123  3712 events ( 29696 bytes )
0.171675 0.001350 request #  124     0 events (     0 bytes )
0.172990 0.001315 request #  125     0 events (     0 bytes )
($BCfN,(B)
0.191621 0.000265 request #  148     0 events (     0 bytes )
0.192933 0.001312 request #  149     0 events (     0 bytes )
0.197627 0.004694 request #  150  4096 events ( 32768 bytes )
0.201380 0.003753 request #  151  4096 events ( 32768 bytes )
0.205745 0.004365 request #  152  4096 events ( 32768 bytes )
0.209949 0.004204 request #  153  3712 events ( 29696 bytes )
0.211313 0.001364 request #  154     0 events (     0 bytes )
0.212633 0.001320 request #  155     0 events (     0 bytes )
($B0J2<N,(B)

$B:n<T(B

$B@iBe9@;J(B

$BJQ99MzNr(B

* 2008-08-25
    - $B@\B3D>8e$N%j%/%(%9%H$G%G!<%?$rAw$k$h$&$KJQ99$7$?!#(B
      $B0J9_(B -H $B%*%W%7%g%s$G;XDj$5$l$?4V3V(B($B$"$k$$$O%G%U%)%k%H$N(B25Hz)$B$G(B
      $B$G%G!<%?$rAw$k!#(B
    - 1$B%$%Y%s%H$GH/@8$9$k%G!<%?%5%$%:$N%G%U%)%k%H$r(B100000$B%P%$%H(B(100kB)$B$K(B
      $B$7$?(B($B0JA0$O(B0$B%P%$%H$G$"$C$?(B)$B!#(B

* 2008-06-14
    - $B%S!<%`1?E>;~$r$^$M$k$h$&$KJQ99$7$?%V%i%s%A(Bpsd_replay_beam
      $B$r:n@.!#(B

* 2008-06-04
    - -c$B%*%W%7%g%s(B($B%G!<%?$rJV$92s$r;XDj(B)$B$rDI2C!#(B

* 2008-05-12
    - -z$B%*%W%7%g%s(B($B>o$K%$%Y%s%HD9$H$7$F(B0$B$rJV$9(B)$B$rDI2C!#(B
    - -P$B%*%W%7%g%s(B($B3NN((B)$B$rDI2C!#(B

* 2008-04-12
    - -F$B%*%W%7%g%s(B(forever$B%b!<%I(B)$BDI2C!#(B

* 2008-04-07
    - $BBg%P%0(Bfix($B%/%i%$%"%s%H$+$iAw$i$l$F$/$k%j%/%(%9%H%$%Y%s%H%G!<%?%5%$%:$N(B
      $B2r<a$r4V0c$C$F$$$?$N$GD>$7$?(B)$B!#(B

* 2008-04-05
    - $BBh(B1$BHG!#$H$j$"$($:=q$$$F$_$?!#(B
    - length$B$H(Bdata$B$G(B2$B2s(Bwrite()$B$7$F$$$?$N$r(Bwritev()$B$G(B1$B2s$K$7$?!#(B
    - $BH?I|%5!<%P!<$@$C$?$N$r%3%s%+%l%s%H%5!<%P!<$K=q$-49$($?!#(B
    - $B%=%1%C%H4XO"(B(socket(), bind(), listen(), accept())$B$NItJ,$O(B
      $BB>$NMQES$G$b$G$-$k$@$1$=$N$^$^;H$($k$h$&$K$9$k$?$a$K(B
      $B%U%!%$%k$rFI$s$G%=%1%C%H$K=q$/4X?t$rJ,N%$7$FJL%U%!%$%k$K$7$?!#(B
    - $BE>AwB.EY$rCY$/$9$k$?$a$K(Bwritev()$B$ND>A0$G(Busleep()$B$9$k%*%W%7%g%s$r(B
      $BDI2C$7$?!#(B
