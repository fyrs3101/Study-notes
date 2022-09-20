/*
Sleep cycle 会员

***************************
QuantumultX:

[rewrite_local]
^https:\/\/ch\.sleepcycle\.com\/api\/v1\/subscription\/get url script-response-body abc.js

[mitm]
hostname = mp.weixin.qq.com

**************************/

var obj = JSON.parse($response.body);
obj.subscription.expire_date = 1734221586
abc = obj.subscription.features_rich
for (x in abc) {
    x.expire_date = 1734221586
}
$done({body: JSON.stringify(obj)}); 