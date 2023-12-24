#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
const int h(48), w(45);
sf::String TileMap[h] = {
	"b!]glg])bbbbbbb!##l####]####l##g##]###l###i#)",
	"b@[   [$bbbbbbb@c-tttt-[----d---tt[t-----sss$",
	"b@tt   ])bbbbbb@-----tt   _###+###]--tt]###_~",
	"b@ ppt [$bbbbbb*ii########~bbb@3--[----[tt-$b",
	"b@ txt  )bbbbbbbbbbbbbbbbbbbbb@ -_#+- _#+c-$b",
	"b@ttpppp##g#l##]ii]#)bbbbbbbbb@st$b@t-$b@--$b",
	"b@     p   t   [  [ $bbbbbbbbb@s-$b@tc$b@dc$b",
	"b@c    t    ttt     $bbbbbbbbb@t-$b@--$b@--$b",
	"b@ c    e           $bbbbbbbbb@-c$b@c-$b@s-$b",
	"b@c            tt 33$bbbbbbbbb@--$b@-t$b@t-$b",
	"b@   tt  _##########~bbbbbbbbb*i##b#ii#b##i~b",
	"b@  tt   $bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
	"b@   t   $bbbbbbbbbbbbbbbbbbbbbbb!#]ii]#)bbbb",
	"b@       $bbbbbbbbbbbbbbbbbbbbbb!g-[-t[-#)bbb",
	"b@       $bbbbbbbbbbbbbbbbbbbbb!#-tt--s--#)bb",
	"b@t      $bbbbbbbbbbbbbbbbbbbb!ls--ppxp-t3l)b",
	"b@    xp $bbbbbbbbbbbbbbbbbbbb@ss-pp  pt-tt$b",
	"b@     p $bbbbbbbbbbbbbbbbbbbb@d-tp    px- $b",
	"b@e      $bbbbbbbbbbbbbbbbbbbb@d-pp    xp--$b",
	"b@       $bbbbbbbbbbbbbbbbbbbb@-dpx    px-d$b",
	"b@tt     $bbbbbbbbbbbbbbbbbbbb@--xp    pp--$b",
	"b@ tt    #]#l#######)bbbbbbbbb@ --xp  pp--d$b",
	"b@ t      [    ttt 3$bbbbbbbbb*+ -pxxpxe- _~b",
	"b@          e  x _##~bbbbbbbbbb*+-tt---- _~bb",
	"b@               $bbbbbbbbbbbbbb*+--ttt-_~bbb",
	"b@  _#+   _######~bbbbbbbbbbbbbbb*##ii##~bbbb",
	"b@  $b@   $bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
	"b@  $b@   $bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
	"!#  #l#   $bbbbbbbbbbbbbbbbbbbbbbb!]ii])bbbbb",
	"@     e  d$bbbbbbbb!l######l##g##]l[--[l]###)",
	"@  p      $bbbbbbbb@-pp----tpptt-[--ppp-[dt-$",
	"@   tt    $bbbbbbbb@t-_+######l####_+s--sss-$",
	"@         #]l##g#l]#--$@3-ddd----h-$@--cc-cc$",
	"@          [  tt  [---$@--ppss--tt-$@p-cspcc$",
	"@    tt        tc  --t$@pp---s--_##~@-p_####$",
	"@   tt             -tt$@s-tt-sss$!###p-$bbbb$",
	"@  ttt             -tt$@s----sss$!-tt--$bbbb$",
	"@   t        _####+tt-$@--s--t--$@--_##~@l#l$",
	"@         e  $bbbb@-d-$@-pppps--$@t-$b!##ccc$",
	"@3           $bbbb@-d-$@--------$@tp$b@ssss-$",
	"*############~bbbb@--d#]l##l]--]##--]#]-p--p$",
	"bbbbbbbbbbbbbbbbbb@s---[--s-[tt[-s--[-[-sse-$",
	"bbbbbbbbbbbbbbbbbb@oo--sooo--s-dttpp----pp--$",
	"bbbbbbbbbbbbbbbbbb*################+t-_#####~",
	"bbbbb!##l)bbbbbbbbbbbbbbbbbbbbbbbbb@t-$bbbbbb",
	"bbb!##p--###]###l###]###l###]###l###-t$bbbbbb",
	"bbb@d--pp---[----t--[----t-t[tt---t---$bbbbbb",
	"bbb*##################################~bbbbbb",
};

void randomgen() {
	int randomx = 0;
	int randomy = 0;
	srand(time(0));
	int CoinsPerTime = 1;
	int SpikesPerTime = 1;
	while (CoinsPerTime > 0) {
		randomx = 1 + rand() % (w - 1);
		randomy = 1 + rand() % (h - 1);
		if (TileMap[randomy][randomx] == ' ') {
			(TileMap[randomy][randomx] = 'c');
			CoinsPerTime--;
		}
	}
	while (SpikesPerTime > 0) {
		randomx = 1 + rand() % (w - 1);
		randomy = 1 + rand() % (h - 1);
		if (TileMap[randomy][randomx] == ' ') {
			TileMap[randomy][randomx] = 's';
			SpikesPerTime--;
		}
	}
}
/*sf::String TileMap[h] = {
* "b!]###])bbbbbbb!############################)",
	"b@[   [$bbbbbbb@--tttt------d---tttt--------$",
	"b@tt   ])bbbbbb@-   -tt---_###+####--tt####_~",
	"b@ ppt [$bbbbbb*ii########~bbb@--------ttt-$b",
	"b@ txt  )bbbbbbbbbbbbbbbbbbbbb@c-_#+-c_#+c-$b",
	"b@ttpppp########ii##)bbbbbbbbb@ct$b@t-$b@--$b",
	"b@     p   t        $bbbbbbbbb@c-$b@tc$b@dc$b",
	"b@     t    ttt     $bbbbbbbbb@t-$b@--$b@--$b",
	"b@  c      ccc      $bbbbbbbbb@-c$b@c-$b@c-$b",
	"b@             tt   $bbbbbbbbb@--$b@-t$b@t-$b",
	"b@   tt  _##########~bbbbbbbbb*i##b#ii#b##i~b",
	"b@  tt   $bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
	"b@   t   $bbbbbbbbbbbbbbbbbbbbbbb!#]ii]#)bbbb",
	"b@       $bbbbbbbbbbbbbbbbbbbbbb!#-[-t[-#)bbb",
	"b@       $bbbbbbbbbbbbbbbbbbbbb!#-tt-----#)bb",
	"b@t      $bbbbbbbbbbbbbbbbbbbb!# --ppxp-tt#)b",
	"b@    xp $bbbbbbbbbbbbbbbbbbbb@ --pp  pt-tt$b",
	"b@     p $bbbbbbbbbbbbbbbbbbbb@d-tp    px- $b",
	"b@       $bbbbbbbbbbbbbbbbbbbb@d-pp    xp--$b",
	"b@       $bbbbbbbbbbbbbbbbbbbb@-dpx    px-d$b",
	"b@tt     $bbbbbbbbbbbbbbbbbbbb@--xp    pp--$b",
	"b@ tt    #]#########)bbbbbbbbb@ --xp  pp--d$b",
	"b@ t      [    ttt  $bbbbbbbbb*+ -pxxpx-- _~b",
	"b@             x _##~bbbbbbbbbb*+-tt---- _~bb",
	"b@               $bbbbbbbbbbbbbb*+--ttt-_~bbb",
	"b@  _#+   _######~bbbbbbbbbbbbbbb*##ii##~bbbb",
	"b@  $b@   $bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
	"b@  $b@   $bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
	"!#  ###   $bbbbbbbbbbbbbbbbbbbbbbb!]ii])bbbbb",
	"@        d$bbbbbbbb!#############]#[--[#]###)",
	"@  p      $bbbbbbbb@-pp----tpptt-[--ppp-[dt-$",
	"@   tt    $bbbbbbbb@t-_+###########_+s--sss-$",
	"@         ##########--$@--ddd----h-$@--cc-cc$",
	"@             tt   ---$@--ppss--tt-$@p-cspcc$",
	"@    tt        tc  --t$@pp---s--_##~@-p_####$",
	"@   tt             -tt$@s-tt-sss$!###p-$bbbb$",
	"@  ttt             -tt$@s----sss$!-tt--$bbbb$",
	"@   t        _####+tt-$@--s--t--$@--_##~@###$",
	"@            $bbbb@-d-$@-pppps--$@t-$b!##ccc$",
	"@            $bbbb@-d-$@--------$@tp$b@ssss-$",
	"*###########~bbbb@--d#]####]--]##--]#]-p--p$",
	"bbbbbbbbbbbbbbbbbb@s---[--s-[tt[-s--[-[-ss--$",
	"bbbbbbbbbbbbbbbbbb@oo--sooo--s-dttpp----pp--$",
	"bbbbbbbbbbbbbbbbbb*################+t-_#####~",
	"bbbbb!###)bbbbbbbbbbbbbbbbbbbbbbbbb@t-$bbbbbb",
	"bbb!##---###########################-t$bbbbbb",
	"bbb@d------------t-------tttttt-------$bbbbbb",
	"bbb*##################################~bbbbbb",
*/