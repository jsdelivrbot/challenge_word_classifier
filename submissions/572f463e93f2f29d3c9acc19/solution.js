function hash(t){for(var r=31,o=1000000009,e=0,i=0;i<t.length;i++){var n=t[i].toUpperCase();-1!=="ABCDEFGHIJKLMNOPQRSTUVWXYZ".indexOf(n)&&(e=(e*r+(n.charCodeAt(0)-"A".charCodeAt(0)))%o)}return e}function BitArray(t,r){if(this.size=Math.ceil(t/BIT_COUNT),r){this.buckets=[];for(var o=0;o<r.length;o++)this.buckets[o]=r[o]}else{this.buckets=[];for(var o=0;o<this.size;o++)this.buckets[o]=0}}function BloomFilter(t){this.bitArray=new BitArray(bloomFilterConfig.SIZE,t)}var bloomFilterConfig={N:662003,P:.01,SIZE:496e3,K:1,INITIAL_SEED:11},INT_SIZE=4,HashFunc=hash,BIT_COUNT=8*INT_SIZE;BitArray.prototype={set:function(t){var r=Math.floor(t/BIT_COUNT),o=t%BIT_COUNT,e=1<<o;this.buckets[r]=this.buckets[r]|e},test:function(t){var r=Math.floor(t/BIT_COUNT),o=t%BIT_COUNT,e=1<<o;return 0!==(this.buckets[r]&e)},get:function(){return this.buckets}},BloomFilter.prototype={add:function(t){for(var r,o=0;o<bloomFilterConfig.K;o++)r=HashFunc(t,bloomFilterConfig.INITIAL_SEED+o)%bloomFilterConfig.SIZE,this.bitArray.set(r)},get:function(){return this.bitArray.get()},test:function(t){for(var r,o=0;o<bloomFilterConfig.K;o++)if(r=HashFunc(t,bloomFilterConfig.INITIAL_SEED+o)%bloomFilterConfig.SIZE,this.bitArray.test(r)===!1)return!1;return!0}};var bufferToArray=function(t){for(var r=[],o=0;o<t.length;)r.push(t.readIntBE(o,INT_SIZE)),o+=INT_SIZE;return r},bloomFilter;exports.init=function(t){var r=bufferToArray(t);bloomFilter=new BloomFilter(r)},exports.test=function(t){return console.log(t),bloomFilter.test(t)};