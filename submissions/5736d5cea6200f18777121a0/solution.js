for(var c=Array(2048),e=2097152,f=0;f<c.length;f++){for(var k=0;32>k;k++)e^=e<<21,e^=e>>>35,e^=e<<4;c[f]=e}var l;function m(a){this.data=a;this.b=524287;this.c=1;this.get=function(b){var a=b%8;return this.data[(b-a)/8]>>a&1};this.contains=function(a){for(var d=0;d<this.c;d++)if(!this.get(this.a(a,d)&this.b))return!1;return!0};this.a=function(a,d){for(var g=43840,n=256*d,h=0;h<a.length;h++)g=7664345*g^c[n+(a.charCodeAt(h)&255)];return g}}exports.init=function(a){l=new m(a)};
function p(a,b){return a.endsWith(b[0])&&a!=b[0]?a.slice(0,void 0===b[1]?-b[0].length:-b[1])+(void 0===b[2]?"":b[2]):a}function q(a,b){return a.startsWith(b)&&a!=b?a.slice(b.length):a}
var r="non semi anti thorough arithmo counter dinitro quarter genito pseudo after chemo eigen ethno femto ferro forth micro micro multi other photo pseud quasi radio super super supra ultra under yotta zepto zetta deka demi down fore gibi half kilo nano naso over pico ribo mis out ovo un ur chemico hinder psycho audio full gain kuli like many post same self inter hyper pre sub".split(" "),t=[["'s"],["'s"],["as",1],["bs",1],["cs",1],["fs",1],["gs",1],["hs",1],["js",1],["ks",1],["ls",1],["ms",1],["ns",
1],["os",1],["ps",1],["rs",1],["qs",1],["ts",1],["ws",1],["vs",1],["xs",1],["ys",1],["iness",5,"y"],["ness"],["inesses",7,"y"],["nesses"],["virile"],["worthy"],["scape"],["speak"],["wards"],["ds",1],["zilla"],["dale"],["fold"],["hood"],["land"],["less"],["less"],["like"],["mire"],["most"],["punk"],["some"],["ward"],["ware"],["ways"],["wear"],["wide"],["wise"],["iful",3,"y"],["ful"],["n't"],["ies",3,"y"],["ily",3,"y"],["ily",3,"y"],["ied",3,"y"],["iest",4,"y"],["yed",2],["bly",1,"e"],["ly"],["shes",
2],["ches",2],["xes",2],["ied",3,"y"],["iest",4,"y"],["yed",2],["ed",2,"ing"],["athon"],["log"],["log"],["isation",6,"se"],["bility",5,"le"],["ment"],["ship"],["aholic"],["script"],["bot"],["dom"],["sys"],["men",2,"an"],["kind"],["kind"],["fish"],["field"],["ying",3],["aes",1],["bes",1],["ces",1],["ees",1],["fes",1],["ges",1],["nes",1],["oes",1],["pes",1],["tes",1],["ves",1],["aing",3],["cing",3,"e"],["fing",3],["ging",3,"e"],["hing",3],["king",3],["oing",3],["sing",3,"e"],["uing",3,"e"],["ving",
3,"e"],["wing",3,"e"],["xing",3],["cer",2,"e"],["xer",2],["wood"],["ning",3],["sman"],["man"],["maker"],["maker"],["ds",1],["os",1],["ys",1],["aling",3],["eling",3],["iling",3],["oling",3],["bling",3,"e"],["cling",3,"e"],["dling",3,"e"],["fling",3,"e"],["kling",3,"e"],["pling",3,"e"],["hling",4],["lling",4],["rling",4],["wling",4],["bing",4],["bing",3,"e"],["pping",4],["ping",3],["ring",3],["tting",4]];exports.test=function(a){a=t.reduce(p,r.reduce(q,a));return l.contains(a)};