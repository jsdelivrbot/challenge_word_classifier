var d = {
    rs: "jz'''xvq'zqzqxxjjq'qjxqjzx'jvjwxgxhxqhqg'ywqqpzjkxqyvbvw'wpxqfxzvxqvqcfqjvqkxkkz'kfx'gcxcjqbkq'fjb'bqn'ugqqd'psxpqjgjwqwqmjffzbxqlfvqqmxvftxqtvzdxqo'mwjpz'hzqjtyqjmbqjj'v'rqrzfmqqe'ojhxqjlvhxgjpvpxxbzfjjk'nxr'c'itqvgjyjcvmqsdq'llx'eq'xnjdxvzgyjwvxdhqmzcvzpyyrxjrgzgvhj".match(/../g),
    az: ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',"'"],
    primes: [3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101]
};

function getHash(w){
    var ch = w.substr(0, 6),
        ret = 0;

    ch.split('').forEach( function(l, i) {
        var p_code = d.primes[i],
            l_code = d.az.indexOf(l) < 25 ? d.primes[d.az.indexOf(l)] : d.primes[d.az.indexOf(l) - 5] - 1;

        ret += Math.round( Math.pow(p_code, 3.35) * l_code);
    });

    ret = Math.round( ret / 3.9 );

    return ret;
}

var checks = {
    longWords: function(w){
        return w.length > 14 ? -1 : 0;
    },
    rareSylls: function(w){
        return d.rs.some( function(a){ return ~w.indexOf(a) }) ? -1 : 0;
    },
    hashes: function(w){
        var hash;

        if ( w.substr(-2) == "'s" ) hash = getHash( w.substr(0, w.length - 2) );
        else hash = getHash(w);

        if ( hash > d.h.length || d.h.substr(hash, 1) === '0' ) return -1;

        return 0;
    }
}

function test(w) {
    var a = checks.rareSylls(w);

    if (!a) a = checks.longWords(w);
    if (!a) a = checks.hashes(w);

    return a < 0 ? false : true;
}

function init(data) {
    d.h = data.toString();
}

module.exports = {
    init: init,
    test: test
}