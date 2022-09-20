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
l = list.filter(x => x.ad_info == undefined)
obj.data.items = l
$done({body: JSON.stringify(obj)}); 
