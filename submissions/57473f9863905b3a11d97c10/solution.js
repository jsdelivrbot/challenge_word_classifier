var S={},F={},N=5;function i(c){var f=[],a=0,d,b=0,e=[""];d=2*(256*c[a]+c[a+1])+2;for(a=2;a<d;a+=2)b+=256*c[a]+c[a+1],F[b]=1;a++;f[26]="'";for(b=0;26>b;b++)f[b]=String.fromCharCode(97+b);for(d=[];a<c.length;a++){for(b=0;b<c[a];b++)d.push(0);d.push(1)}for(a=c=0;a<e.length;a++){for(b=0;27>b;b++)1==d[c++]&&e.push(e[a]+f[b]);e[a].length==N&&(S[e[a]]=1)}}
function f1(c,f){var a,d,b=0,e=0,k=c.length,h=0,g=0;for(a=0;a<k;a++)d=c.substr(a,1),/[aeiouy]/.test(d)?(b++,h+=d.charCodeAt(0)-97):/[bcdfghjklmnpqrstvwxyz]/.test(d)&&e++;a=25;g=((g*a+b)*a+e)*a+(h/b*5|0);return f[g]?!0:!1}function t(c){return f1(c,F)?S[c.substr(0,N)]?!0:!1:!1}exports.init=i;exports.test=t;