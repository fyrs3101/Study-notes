h = {
    "X-GitHub-Api-Version": "2022-11-28",
    'Authorization': 'Bearer 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',
    'user-agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:47.0) Gecko/20100101 Firefox/47.0'
}
let resContent = "";
$task.get('https://api.github.com/users/luoxin971/repos', { headers: h }, (response) => {
    let todo = '';

    // called when a data chunk is received.
    response.on('data', (chunk) => {
        todo += chunk;
        resContent += chunk;
    });

    // called when the complete response is received.
    response.on('end', () => {
        let a = JSON.parse(todo);
        a.map(element => {
            console.log(element.url + " " + element.name);
        });
    });

}).on("error", (error) => {
    console.log("Error: " + error.message);
});

const myStatus = "HTTP/1.1 200 OK";
const myHeaders = { "Connection": "Close" };

const myResponse = {
    status: myStatus,
    headers: myHeaders,
    body: resContent
};

$done(myResponse)
