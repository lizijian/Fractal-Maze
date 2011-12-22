<map version="0.9.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1324540328656" ID="ID_325787633" MODIFIED="1324540407000" TEXT="AnalyzeMaze">
<node CREATED="1324540343250" ID="ID_480974237" MODIFIED="1324540441265" POSITION="right" TEXT="1, detect main chip and sub chip">
<node CREATED="1324540519593" ID="ID_760340955" MODIFIED="1324547284625" TEXT="find conours">
<node CREATED="1324547284625" FOLDED="true" ID="ID_740961101" MODIFIED="1324550613281" TEXT="findContours">
<node CREATED="1324540752218" ID="ID_1352693709" MODIFIED="1324550424890">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/1.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1324540540765" ID="ID_1969245796" MODIFIED="1324547301281" TEXT="polygon approx">
<node CREATED="1324547301281" ID="ID_757344626" MODIFIED="1324550360265" TEXT="approxPolyDP">
<node CREATED="1324540763906" ID="ID_210706598" MODIFIED="1324550346734">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/2.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1324540705921" ID="ID_1716810574" MODIFIED="1324540736015" TEXT="judge: is a chip contour?">
<node CREATED="1324540775421" ID="ID_1514278277" MODIFIED="1324540871593" TEXT="4 edges"/>
<node CREATED="1324540875593" ID="ID_566008476" MODIFIED="1324540888828" TEXT="convex"/>
<node CREATED="1324541031859" ID="ID_147713644" MODIFIED="1324541036625" TEXT="square">
<node CREATED="1324540889734" ID="ID_735401233" MODIFIED="1324541018453" TEXT="orthometric"/>
<node CREATED="1324540931796" ID="ID_928863546" MODIFIED="1324541018453" TEXT="regular"/>
</node>
</node>
<node CREATED="1324546011656" FOLDED="true" ID="ID_95877615" MODIFIED="1324550607859" TEXT="result: refer to result of AnalyzeMaze -f FILE -d">
<node CREATED="1324548656859" ID="ID_1460508464" MODIFIED="1324550411203">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/9.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1324540378187" ID="ID_1713455032" MODIFIED="1324540448140" POSITION="right" TEXT="2, detect pins">
<node CREATED="1324541073546" ID="ID_1289067056" MODIFIED="1324541121828" TEXT="contract contour appropriately">
<node CREATED="1324541351953" ID="ID_70382553" MODIFIED="1324541369125" TEXT="fix 4 points of contour and get contracted contour"/>
</node>
<node CREATED="1324541173218" ID="ID_926614532" MODIFIED="1324541251218" TEXT="get cross points between new contour and pins">
<node CREATED="1324541530500" ID="ID_1096358932" MODIFIED="1324541559421" TEXT="iterate contour lines"/>
<node CREATED="1324541379093" ID="ID_778162642" MODIFIED="1324541653406" TEXT="find out left/right cross point of each pin">
<node CREATED="1324541608671" ID="ID_1946747335" MODIFIED="1324541611406" TEXT="color break points"/>
</node>
</node>
<node CREATED="1324541258515" ID="ID_478383963" MODIFIED="1324547255609" TEXT="calculate pin points">
<node CREATED="1324541407312" ID="ID_1760733483" MODIFIED="1324550190734" TEXT="midpoint between left and right point">
<node CREATED="1324547273109" ID="ID_704831210" MODIFIED="1324550370843">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/3.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1324547330812" FOLDED="true" ID="ID_286256231" MODIFIED="1324550604671" TEXT="result: refer to result of AnalyzeMaze -f FILE -d">
<node CREATED="1324548698562" ID="ID_1363843050" MODIFIED="1324550399531">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/10.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1324540396187" ID="ID_1887339288" MODIFIED="1324540453015" POSITION="left" TEXT="3, detect poles">
<node CREATED="1324541742312" ID="ID_74660164" MODIFIED="1324541761109" TEXT="erode wire">
<node CREATED="1324541729031" ID="ID_1635375726" MODIFIED="1324541740296" TEXT="calculate wire width"/>
<node CREATED="1324541881703" ID="ID_1992412396" MODIFIED="1324547521718" TEXT="erode wireWidth/2"/>
<node CREATED="1324541907156" ID="ID_1810376251" MODIFIED="1324547523781" TEXT="dilate wireWidth/2"/>
</node>
<node CREATED="1324541765484" ID="ID_1298446797" MODIFIED="1324541820359" TEXT="maximum 2 contour">
<node CREATED="1324542029000" FOLDED="true" ID="ID_784467371" MODIFIED="1324550594515" TEXT="contourArea">
<node CREATED="1324547532937" ID="ID_543591330" MODIFIED="1324550445359">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/4.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1324541848578" ID="ID_1740794074" MODIFIED="1324541876546" TEXT="cathode or anode">
<node CREATED="1324542047125" ID="ID_1563758315" MODIFIED="1324542197890" TEXT="mark potential anode sign">
<node CREATED="1324542292578" FOLDED="true" ID="ID_1320107023" MODIFIED="1324550590078" TEXT="contour:12edges,orthometric">
<node CREATED="1324547688109" ID="ID_1449310961" MODIFIED="1324550468953">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/5.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1324542097640" ID="ID_1648558670" MODIFIED="1324542202062" TEXT="mark potential cathode sign">
<node CREATED="1324542354375" ID="ID_1713568769" MODIFIED="1324547816218" TEXT="contour:4edges,orthometric"/>
<node CREATED="1324542397625" ID="ID_550752675" MODIFIED="1324542415625" TEXT="small area than chip contour">
<node CREATED="1324542416703" ID="ID_1929073673" MODIFIED="1324542441531" TEXT="suppose threshold 100"/>
</node>
<node CREATED="1324547812343" FOLDED="true" ID="ID_819392288" MODIFIED="1324550587859" TEXT="eg">
<node CREATED="1324547757484" ID="ID_947615430" MODIFIED="1324550457218">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/6.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1324542189140" ID="ID_1278451262" MODIFIED="1324542229328" TEXT="is anode">
<node CREATED="1324542230953" ID="ID_1258632621" MODIFIED="1324548429390" TEXT="contain a potential anode sign">
<node CREATED="1324548379984" ID="ID_699473187" MODIFIED="1324550479343">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/8.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1324542261171" ID="ID_1706037487" MODIFIED="1324542263828" TEXT="is cathode">
<node CREATED="1324542265718" ID="ID_1403353754" MODIFIED="1324542280562" TEXT="contain a potential cathode sign">
<node CREATED="1324548414093" ID="ID_750473406" MODIFIED="1324550488453">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/7.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1324548839109" FOLDED="true" ID="ID_1978745886" MODIFIED="1324550583234" TEXT="result: refer to result of AnalyzeMaze -f FILE -d">
<node CREATED="1324548866593" ID="ID_1035547594" MODIFIED="1324550498906">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/11.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
</node>
<node CREATED="1324540407359" ID="ID_1643109166" MODIFIED="1324540457734" POSITION="left" TEXT="4, detect connections">
<node CREATED="1324542459156" ID="ID_654843334" MODIFIED="1324542498109" TEXT="detect form each pin point">
<node CREATED="1324542666406" ID="ID_159050647" MODIFIED="1324542675421" TEXT="start point = pin point"/>
<node CREATED="1324542676312" ID="ID_261798482" MODIFIED="1324542693781" TEXT="direction">
<node CREATED="1324542695734" ID="ID_750693194" MODIFIED="1324542788859" TEXT="orthometric direction"/>
<node CREATED="1324542790921" ID="ID_1506427065" MODIFIED="1324542809390" TEXT="main chip =&gt; inside"/>
<node CREATED="1324542810375" ID="ID_629949739" MODIFIED="1324542824265" TEXT="sub maze =&gt;outside"/>
</node>
</node>
<node CREATED="1324542504609" ID="ID_1383166473" MODIFIED="1324542530171" TEXT="track wire">
<node CREATED="1324542837765" ID="ID_787240227" MODIFIED="1324542843421" TEXT="color image">
<node CREATED="1324542919953" ID="ID_1394264550" MODIFIED="1324542967296" TEXT="no cross point sign">
<node CREATED="1324542980375" ID="ID_1290770139" MODIFIED="1324542989765" TEXT="step by step">
<node CREATED="1324543069546" ID="ID_187443434" MODIFIED="1324543095140" TEXT="step = line width">
<node CREATED="1324548928609" ID="ID_845296027" MODIFIED="1324550507984">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/12.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1324543026687" ID="ID_1871866825" MODIFIED="1324543059500" TEXT="cross point test on each step">
<node CREATED="1324543101281" ID="ID_1599373203" MODIFIED="1324543346078" TEXT="test 2 orthometric directions"/>
<node CREATED="1324543131937" ID="ID_1304931876" MODIFIED="1324543333562" TEXT="color break = break out of line = no cross line in this direction"/>
<node CREATED="1324543181250" ID="ID_465576308" MODIFIED="1324543287234" TEXT="no color break = there is a cross line in this direction"/>
<node CREATED="1324548943031" ID="ID_1492827159" MODIFIED="1324550515265">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/13.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
</node>
<node CREATED="1324542827812" ID="ID_1190656996" MODIFIED="1324542836562" TEXT="binary image">
<node CREATED="1324543357703" ID="ID_261040908" MODIFIED="1324543375328" TEXT="cross sign or noncross sign">
<node CREATED="1324543376531" ID="ID_1583013978" MODIFIED="1324543408781" TEXT="move forward until color break">
<node CREATED="1324543413843" ID="ID_1206919344" MODIFIED="1324543474531" TEXT="corner">
<node CREATED="1324543503968" ID="ID_152058159" MODIFIED="1324543554515" TEXT="1break in neighborhood(forward)">
<node CREATED="1324549085578" ID="ID_95861811" MODIFIED="1324550522921">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/14.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
<node CREATED="1324543744468" ID="ID_256200400" MODIFIED="1324543752328" TEXT="test left and right"/>
</node>
<node CREATED="1324543475656" ID="ID_218045449" MODIFIED="1324543480375" TEXT="cross point">
<node CREATED="1324543558265" ID="ID_273531792" MODIFIED="1324543569375" TEXT="2breaks in neighborhood">
<node CREATED="1324549124078" ID="ID_1234975531" MODIFIED="1324550529218">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/15.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
<node CREATED="1324543754984" ID="ID_1163858819" MODIFIED="1324543779859" TEXT="test l/r and front"/>
</node>
<node CREATED="1324543481234" ID="ID_656087304" MODIFIED="1324543487312" TEXT="noncross point">
<node CREATED="1324543574609" ID="ID_491123010" MODIFIED="1324549207781" TEXT="4breaks in neighborhood">
<node CREATED="1324549156390" ID="ID_449346070" MODIFIED="1324550536734">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/16.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
<node CREATED="1324543781734" ID="ID_1787912507" MODIFIED="1324543802781" TEXT="skip breaks and test front"/>
</node>
<node CREATED="1324543488328" ID="ID_371324960" MODIFIED="1324543499843" TEXT="quatin point">
<node CREATED="1324543587000" ID="ID_777595647" MODIFIED="1324543591640" TEXT="none of above">
<node CREATED="1324549308671" ID="ID_152927701" MODIFIED="1324550554125">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/17.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
<node CREATED="1324543711546" ID="ID_420434739" MODIFIED="1324543726375" TEXT="action = corner"/>
</node>
</node>
</node>
</node>
</node>
<node CREATED="1324542542375" ID="ID_1972061971" MODIFIED="1324542565265" TEXT="reach pin/pole">
<node CREATED="1324543822281" ID="ID_139604296" MODIFIED="1324543836703" TEXT="color break point"/>
<node CREATED="1324543838015" ID="ID_1519706907" MODIFIED="1324544011828" TEXT="distance to chip contour &lt; threshold"/>
<node CREATED="1324543966046" ID="ID_219063915" MODIFIED="1324544024484" TEXT="minimum distance to pin point =&gt; reach pin"/>
</node>
<node CREATED="1324549374062" ID="ID_1908099880" MODIFIED="1324550147656" TEXT="result: refer to result of AnalyzeMaze -f FILE -d">
<node CREATED="1324549418515" ID="ID_1622368453" MODIFIED="1324550556000" TEXT="color image">
<node CREATED="1324549425078" ID="ID_966259538" MODIFIED="1324550563609">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/18.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
<node CREATED="1324549432703" ID="ID_605749538" MODIFIED="1324550566515" TEXT="binary image">
<node CREATED="1324549997015" ID="ID_142961218" MODIFIED="1324550573500">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      <img src="AnalyzeMaze-images/19.jpg" />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
</node>
</node>
</map>
