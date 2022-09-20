/*
Sleep cycle 会员

***************************
QuantumultX:

[rewrite_local]
^https:\/\/ch\.sleepcycle\.com\/api\/v1\/subscription\/get url script-response-body https://raw.githubusercontent.com/luoxin971/Study-notes/master/sleepcycle.js

[mitm]
hostname = *.sleepcycle.com

**************************/

var obj = JSON.parse($response.body);
obj.subscription.expire_date = 1734221588
// abc = obj.subscription.features_rich
for (x of obj.subscription.features_rich) {
    x.expire_date = 1734221586
}
$done({body: JSON.stringify(obj)}); 
