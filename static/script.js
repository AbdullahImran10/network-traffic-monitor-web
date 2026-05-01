function start(){
    fetch('/start');
}

function stop(){
    fetch('/stop');
}

function loadData(){
    let p = document.getElementById("protocol").value;
    let s = document.getElementById("src").value;
    let d = document.getElementById("dst").value;

    fetch(`/data?protocol=${p}&src=${s}&dst=${d}`)
    .then(res => res.json())
    .then(data => {
        let body = document.getElementById("tableBody");
        body.innerHTML = "";

        data.slice(-50).forEach(row => {
            body.innerHTML += `
            <tr>
                <td>${row.SrcIP}</td>
                <td>${row.DstIP}</td>
                <td>${row.Protocol}</td>
                <td>${row.Size}</td>
                <td>${row.Service}</td>
            </tr>`;
        });
    });

    loadStats();
}

function loadStats(){
    fetch('/stats')
    .then(res => res.json())
    .then(s => {
        document.getElementById("stats").innerHTML =
        `Total: ${s.total} | TCP: ${s.tcp} | UDP: ${s.udp} | ICMP: ${s.icmp} | Avg Size: ${s.avg}`;
    });
}

function reset(){
    document.getElementById("protocol").value="";
    document.getElementById("src").value="";
    document.getElementById("dst").value="";
    loadData();
}

// AUTO REFRESH EVERY 2 SEC
setInterval(loadData, 2000);