/*
Sleep cycle 会员

***************************
QuantumultX:

[rewrite_local]
^https:\/\/app\.bilibili\.com\/x\/v2\/feed\/index url script-response-body https://raw.githubusercontent.com/luoxin971/Study-notes/master/bilibili.js

[mitm]
hostname = app.bilibili.com

**************************/

var obj = JSON.parse($response.body);
list = obj.data.items
console.log("originLength: ", list.length)
filter = list.filter(x => x.ad_info == undefined)
console.log("filterLength: ", filter.length)
ad = list.filter(x => !filter.includes(x))
console.log(ad)
obj.data.items = filter
$done({body: JSON.stringify(obj)}); 
