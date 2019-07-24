const custom = require('bindings')('hello');

console.log(custom.hello());
console.log(custom.getInstalledCount());
