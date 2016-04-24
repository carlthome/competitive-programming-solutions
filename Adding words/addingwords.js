var s = '';
var toNumber = {};
var toWord = {};
while ((s = readline())) {
  var ss = s.split(' ');
  var op = ss.shift();
  switch (op) {
    case 'def':
      var w = ss[0];
      var i = parseInt(ss[1]);
      delete toWord[toNumber[w]]
      toNumber[w] = i;
      toWord[i] = w;
      break;
    case 'calc':
      var s = ss.join(' ');
      ss.pop();
      var w = 'unknown';
      try {
        for (var i = 0; i < ss.length; ++i) {
          if (ss[i] in toNumber) {
            ss[i] = toNumber[ss[i]];
          }
        }
        var v = eval(ss.join(' '));
        if (v in toWord) {
          w = toWord[v];
        }
      } catch(e) {
        // LULZ
      } finally {
        print(s + ' ' + w);
      }
      break;
    case 'clear':
      toNumber = {};
      toWord = {};
      break;
    }
}
