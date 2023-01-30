const headers = {
    "X-GitHub-Api-Version": "2022-11-28",
    'Authorization': 'Bearer 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',
    'user-agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:47.0) Gecko/20100101 Firefox/47.0'
}
cosnt url = 'https://api.github.com/users/luoxin971/repos';
cosnt method = 'GET';
const myRequest = {
    url: url,
    method: method, // Optional, default GET.
    headers: headers
}
let resContent = "";
$task.fetch(myRequest).then(response => {
    resContent = response.body;
    $notify("Success", "Subtitle", response.body); // Success!

}, reason => {
    $notify("Error", "Subtitle", reason.error); // Error!
    console.log("Error: " + reason.error);
});

const myStatus = "HTTP/1.1 200 OK";
const myHeaders = { "Connection": "Close" };

const myResponse = {
    status: myStatus,
    headers: myHeaders,
    body: resContent
};

$done(myResponse)
