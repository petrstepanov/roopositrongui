/*
 * Images.cpp
 *
 *  Created on: Apr 16, 2019
 *      Author: petrstepanov
 */

// Suppress warnings https://stackoverflow.com/questions/1867065/how-to-suppress-gcc-warnings-from-library-headers
#pragma GCC diagnostic ignored "-Wwrite-strings"

#include "../resources/Images.h"
#include <TGClient.h>
#include <TGPicture.h>

const TGPicture* Images::makeTGPicture(char **xpmData) {
  TGPicturePool *picturePool = gClient->GetPicturePool();
  return picturePool->GetPicture("picture", xpmData);
}

char *Images::applicationIcon[] = { "48 48 17 1", " 	c None", ".	c #AFEEFF",
    "+	c #6EE1FF", "@	c #F0FCFF", "#	c #08BCEA", "$	c #D6F7FF", "%	c #49DAFF",
    "&	c #C9F4FF", "*	c #9EECFF", "=	c #18C5F2", "-	c #32D4FD", ";	c #87E7FF",
    ">	c #23CCF7", ",	c #34D6FF", "'	c #00B7E6", ")	c #FFFFFF", "!	c #000000",
    "        ))))))))))))))))))))))))))))))))        ",
    "      ))))))))))))))))))))))))))))))))))))      ",
    "    ))))))))))))))))))))))))))))))))))))))))    ",
    "   ))))))))))))))))))))))))))))))))))))))))))   ",
    "  ))))))))))))))))))))))))))))))))))))))))))))  ",
    "  ))))))))))))))))))))))))))))))))))))))))))))  ",
    " )))))))))))))))))))))))))))))))))))))))))))))) ",
    " )))))))))))&;%,%+$)))))))))))))))))))))))))))) ",
    "))))))))))$+,,,,,,,*))))))))))))))))))))))))))))",
    "))))))))).,,,,,,,,,,;)))))))))))))))))))))))))))",
    "))))))))*,,,,,,,,,,,,;))))))))))))))))))))))))))",
    "))))))).,,,,,,,,,,,,,,*)))))))))))))))))))))))))",
    "))))))&,,,,,,,,,,,,,,,,$))))))))))))))))))))))))",
    ")))))@%,,,,,,,,,,,,,,,,%@)))))))))))))))))))))))",
    ")))))+,,,,,,,,,,,,,,,,,,+)))))))))))))))))))))))",
    ")))).,,,,,,,,,,,,,,,,,,,,*))))))))))))))))))))))",
    ")))@%,,,,,,,,,,,,,,,,,,,,,$)))))))))))))))))))))",
    ")));,,,,,,,,,,,,,,,,,,,,,,%)))))))))))))))))))))",
    "))$,,,,,,,,,,,,,,,,,,,,,,,,;))))))))))))))))))))",
    "))+,,,,,,,,,,,,,,,,,,,,,,,,,&)))))))))))))))))))",
    ")$,,,,,,,,,,,,,,,,,,,,,,,,,,%@))))))))))))))))))",
    ")+,,,,,,,,,,,,,,,,,,,,,,,,,,,+))))))))))))))))))",
    "$,,,,,,,,,,,,,,,,,,,,,,,,,,,,,*)))))))))))))))))",
    "+-,,,,,,,,,,,,,,,,,,,,,,,,,,,,,$))))))))))))))))",
    ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,%@)))))))))))))))",
    ",,,,,,,,->==##'''##>--,,,,,,,,,,+@))))))))))))))",
    ",,,,,,>='''''''''''''#>,,,,,,,,-,;))))))))))))))",
    ",,,,>#'''''''''''''''''#>-,,,,,,,,*)))))))))))))",
    ",,>#'''''''''''''''''''''#=-,,,,,,,*))))))))))))",
    ">#'''''''''''''''''''''''''#=,,,,,,,*)))))))))))",
    "'''''''''''''''''''''''''''''#=-,,,,,;))))))))))",
    "''''''''''''''''''''''''''''''''=-,,,,+@))))))))",
    "''''''''''''''''''''''''''''''''''=>-,,%&)))))))",
    "'''''''''''''''''''''''''''''''''''''=>-,+&)))))",
    "''''''''''''''''''''''''''''''''''''''''#==-;.$)",
    "''''''''''''''''''''''''''''''''''''''''''''''''",
    "''''''''''''''''''''''''''''''''''''''''''''''''",
    "''''''''''''''''''''''''''''''''''''''''''''''''",
    "''''''''''''''''''''''''''''''''''''''''''''''''",
    "''''''''''''''''''''''''''''''''''''''''''''''''",
    " '''''''''''''''''''''''''''''''''''''''''''''' ",
    " '''''''''''''''''''''''''''''''''''''''''''''' ",
    "  ''''''''''''''''''''''''''''''''''''''''''''  ",
    "  ''''''''''''''''''''''''''''''''''''''''''''  ",
    "   ''''''''''''''''''''''''''''''''''''''''''   ",
    "    ''''''''''''''''''''''''''''''''''''''''    ",
    "      ''''''''''''''''''''''''''''''''''''      ",
    "        ''''''''''''''''''''''''''''''''        " };

char *Images::projectNewXpm[] =
    { "105 32 24 1", " 	c None", ".	c #E8E8E8", "+	c #CBCBCB", "@	c #828282",
        "#	c #747474", "$	c #0E0E0E", "%	c #000000", "&	c #0F0F0F",
        "*	c #2C2C2C", "=	c #2B2B2B", "-	c #1D1D1D", ";	c #9F9F9F",
        ">	c #AEAEAE", ",	c #D9D9D9", "'	c #575757", ")	c #DADADA",
        "!	c #3A3A3A", "~	c #919191", "{	c #A0A0A0", "]	c #BCBCBC",
        "^	c #666666", "/	c #656565", "(	c #494949", "_	c #BDBDBD",
        ".........................................................................................................",
        ".........................................................................................................",
        ".........................................................................................................",
        ".........................................................................................................",
        ".........................................................................................................",
        "......+@#################+...............................................................................",
        ".....+$%%%%%%%%%%%%%%%%%%&+..............................................................................",
        ".....#%+................+%@..............................................................................",
        ".....#%..................%#..............................................................................",
        ".....#%..................%#..............................................................................",
        ".....#%........*=........%#..............................................................................",
        ".....#%........--........%#........#+...;>...................,####>.............').......................",
        ".....#%........--........%#........%!...'#...................+%~~@-@............#+..............-+.......",
        ".....#%........--........%#........%-@..'#..)@~+.;+..{..]>...+%...>&.;]@].+@~+..;)..>#>...+@~+,~%@)......",
        ".....#%........--........%#........%{&+.'#.+-^'-)/@.>%).(~...+%..._%.!-'>{$^'-).->.#*#-@.>-#'-+#%^+......",
        ".....#%...*----%%----*...%#........%+/!.'#.'~..!~>!.'!@.-+...+%>>{*'.!@..*~..'#.->+&+.+&.!~..(;.%+.......",
        ".....#%...*----%%----*...%#........%+,-@'#.-=!!$#,-)*>!_=....+%'''@..!~..%+..~!.->>&!!!%.$+.....%+.......",
        ".....#%........--........%#........%+.>&!#.-;+++).!#'.*@^....+%......!~..$+..@!.->>=++++.-+.....%+.......",
        ".....#%........--........%#........%+../%#.//..~+.@%~./%>....+%......!~..!/..*~.->,$>.)@.'/..*;.%+.......",
        ".....#%........--........%#........%+..,-#.,(-*!+.+%).>&.....+%......!~..+-*$^..->.;-!-@.+-*$#..!$]......",
        ".....#%........--........%#..................))............................))...->...+)....))....+.......",
        ".....#%........*=........%#...................................................,~%+.......................",
        ".....#%..................%#...................................................,#>........................",
        ".....#%..................%#..............................................................................",
        ".....@%+................+%#..............................................................................",
        ".....+$%%%%%%%%%%%%%%%%%%$+..............................................................................",
        "......+#################@+...............................................................................",
        ".........................................................................................................",
        ".........................................................................................................",
        ".........................................................................................................",
        ".........................................................................................................",
        "........................................................................................................." };

char *Images::projectOpenXpm[] = { "68 32 24 1", " 	c None", ".	c #E8E8E8",
    "+	c #9F9F9F", "@	c #747474", "#	c #BCBCBC", "$	c #000000", "%	c #0F0F0F",
    "&	c #CBCBCB", "*	c #1D1D1D", "=	c #484848", "-	c #AEAEAE", ";	c #0E0E0E",
    ">	c #919191", ",	c #2C2C2C", "'	c #DADADA", ")	c #3A3A3A", "!	c #D9D9D9",
    "~	c #575757", "{	c #828282", "]	c #494949", "^	c #A0A0A0", "/	c #666666",
    "(	c #656565", "_	c #838383",
    "....................................................................",
    "....................................................................",
    "....................................................................",
    "....................................................................",
    "....................................................................",
    ".....+@@@@@@#.......................................................",
    "....@$$$$$$$%&......................................................",
    "....*=-----+;*&.....................................................",
    "....$@......>$,'....................................................",
    "....$@.......@$$$$$$$$@.............................................",
    "....$@........@))))))*$-............................................",
    "....$@...............!$@............-~~>............................",
    "....$@................$@...........{*{>*~...........................",
    "....$@................$@...........*#..!;-.>&{>'...-@#..+&>{&.......",
    "....$@....>]))))))))))$*))~'......-%....~{.$,@=,..~=@*^.**/~*.......",
    "....$@...@$$$$$$$$$$$$$$$$$]......+)....~@.$#..;--*..+).*-..$&......",
    "....$@..-$/'..............~%......+*....~@.$&..~>@*)),*.*-..$&......",
    "....$@..)*................~*......&%'...)>.$&..)>{]&&&&.*-..$&......",
    "....$@.>$>...............&$~.......)(..>*'.$-.&$&-%&.&>.*-..$&......",
    "....$@.**................)*&.......&~;*,#..$=);@..@;,*>.*-..$&......",
    "....$@>$>...............-$@..........'&....$&''.....&...............",
    "....$@*)................)*&................$&.......................",
    "....$*$-...............+$@.................>'.......................",
    "....$$)................**...........................................",
    "....;$_--------------^=$>...........................................",
    "...._$$$$$$$$$$$$$$$$$$~............................................",
    ".....>@@@@@@@@@@@@@@@@-.............................................",
    "....................................................................",
    "....................................................................",
    "....................................................................",
    "....................................................................",
    "...................................................................." };

char *Images::projectSaveXpm[] = { "66 32 25 1", " 	c None", ".	c #E8E8E8",
    "+	c #CBCBCB", "@	c #828282", "#	c #747474", "$	c #0E0E0E", "%	c #000000",
    "&	c #0F0F0F", "*	c #BCBCBC", "=	c #575757", "-	c #1D1D1D", ";	c #DADADA",
    ">	c #666666", ",	c #AEAEAE", "'	c #A0A0A0", ")	c #9F9F9F", "!	c #919191",
    "~	c #D9D9D9", "{	c #2C2C2C", "]	c #484848", "^	c #3A3A3A", "/	c #656565",
    "(	c #494949", "_	c #2B2B2B", ":	c #BDBDBD",
    "..................................................................",
    "..................................................................",
    "..................................................................",
    "..................................................................",
    "..................................................................",
    "......+@#############+............................................",
    ".....+$%%%%%%%%%%%%%%&*...........................................",
    ".....#%+#%.........%=-&*..........................................",
    ".....#%.#%.........%#+-&*.........................................",
    ".....#%.#%.........%#.+-&*........................................",
    ".....#%.#%.........%#..+-&*.......................................",
    ".....#%.#%#########%#...+%#........;#=>+..........................",
    ".....#%.,%%%%%%%%%%$'....%#........->)!-*.........................",
    ".....#%..................%#.......,&...#>..)#'.~'...!;.,@'........",
    ".....#%........+;........%#.......~$@.....{=@-@.$+.,-.@-#]=.......",
    ".....#%......,{%%-'......%#........)--=+.~!..!^./#.=@.-+.~$;......",
    ".....#%.....'%{@@-%,.....%#..........*=%,.,(--^.,^.-++%^^^%*......",
    ".....#%.....--;..~{_.....%#.......,'.../=+&*.!^..-)^.+&++++;......",
    ".....#%....~%@....@%+....%#.......,-+..=>:&;./^..#&!..-!..!.......",
    ".....#%....+%@....@%;....%#........#--$^+./$-]-..~%+..+-^$#.......",
    ".....#%.....{{;..;--.....%#..........+;....;;...........+;........",
    ".....#%.....,%-@@{%'.....%#.......................................",
    ".....#%......)-%%{,......%#.......................................",
    ".....#%........;+........%#.......................................",
    ".....@%+................+%#.......................................",
    ".....+$%%%%%%%%%%%%%%%%%%$+.......................................",
    "......+#################@+........................................",
    "..................................................................",
    "..................................................................",
    "..................................................................",
    "..................................................................",
    ".................................................................." };

char *Images::projectSaveAsXpm[] =
    { "91 32 25 1", " 	c None", ".	c #E8E8E8", "+	c #CBCBCB", "@	c #828282",
        "#	c #747474", "$	c #0E0E0E", "%	c #000000", "&	c #0F0F0F",
        "*	c #BCBCBC", "=	c #575757", "-	c #1D1D1D", ";	c #DADADA",
        ">	c #666666", ",	c #AEAEAE", "'	c #A0A0A0", ")	c #9F9F9F",
        "!	c #919191", "~	c #D9D9D9", "{	c #3A3A3A", "]	c #2C2C2C",
        "^	c #484848", "/	c #494949", "(	c #656565", "_	c #BDBDBD",
        ":	c #2B2B2B",
        "...........................................................................................",
        "...........................................................................................",
        "...........................................................................................",
        "...........................................................................................",
        "...........................................................................................",
        "......+@#############+.....................................................................",
        ".....+$%%%%%%%%%%%%%%&*....................................................................",
        ".....#%+#%.........%=-&*...................................................................",
        ".....#%.#%.........%#+-&*..................................................................",
        ".....#%.#%.........%#.+-&*.................................................................",
        ".....#%.#%.........%#..+-&*................................................................",
        ".....#%.#%#########%#...+%#........;#=>+..........................#;.......................",
        ".....#%.,%%%%%%%%%%$'....%#........->)!-*........................!%@.......................",
        ".....#%..................%#.......,&...#>..)#'.~'...!;.,@'.......{>{....,#'................",
        ".....#%...........+;.....%#.......~$@.....]=@-@.$+.,-.@-#^=.....+-.-,..#]#^=...............",
        ".....#%......#/...]/.....%#........)--=+.~!..!{.(#.=@.-+.~$;....@=.#>../!.~#...............",
        ".....#%.....+%%;..%@.....%#..........*=%,.,/--{.,{.-++%{{{%*....-!+*&;.,-{!+...............",
        ".....#%.....=]%,._%{-(...%#.......,'...(=+&*.!{..-){.+&++++;...,${{{-)...,=-...............",
        ".....#%....,%,$@.)%>(%*..%#.......,-+..=>_&;.({..#&!..-!..!....=@...@{.$,.+%.;+..;..*......",
        ".....#%....-{.]=.#&._%,..%#........#--${+.($-^-..~%+..+-{$#...+%+...~$;)-{-@.@:.,$._%;.....",
        ".....#%...!%%%%-./{.,%*..%#..........+;....;;...........+;...............+;................",
        ".....#%...-],,(%;]-!--...%#................................................................",
        ".....#%..,{*..,{+{#]{+...%#................................................................",
        ".....#%..................%#................................................................",
        ".....@%+................+%#................................................................",
        ".....+$%%%%%%%%%%%%%%%%%%$+................................................................",
        "......+#################@+.................................................................",
        "...........................................................................................",
        "...........................................................................................",
        "...........................................................................................",
        "...........................................................................................",
        "..........................................................................................." };

char *Images::projectCloseXpm[] = { "32 32 8 1", " 	c None", ".	c #E8E8E8",
    "+	c #BCBCBC", "@	c #CBCBCB", "#	c #0E0E0E", "$	c #1D1D1D", "%	c #0F0F0F",
    "&	c #000000", "................................",
    "................................", "................................",
    "................................", "................................",
    "................................", "................................",
    "................................", ".........+@..........@+.........",
    "........+#$@........@$%+........", "........@$&$@......@$&$@........",
    ".........@$&$@....@$&$@.........", "..........@$&$@..@$&$@..........",
    "...........@$&$@@$&$@...........", "............@$&$$&$@............",
    ".............@$&&$@.............", ".............@$&&$@.............",
    "............@$&$$&$@............", "...........@$&$@@$&$@...........",
    "..........@$&$@..@$&$@..........", ".........@$&$@....@$&$@.........",
    "........@$&$@......@$&$@........", "........+#$@........@$#+........",
    ".........+@..........@+.........", "................................",
    "................................", "................................",
    "................................", "................................",
    "................................", "................................",
    "................................" };

