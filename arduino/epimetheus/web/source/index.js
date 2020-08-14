var ctx = document.getElementById('temp_chart').getContext('2d');
var ctx2 = document.getElementById('humidity_chart').getContext('2d');
var ctx3 = document.getElementById('light_chart').getContext('2d');

var temp_chart = new Chart(ctx, {
    // The type of chart we want to create
    type: 'line',
    
    // The data for our dataset
    data: {
        datasets: [{
            label: "Température",
            backgroundColor: 'rgb(36, 138, 80)',
            borderColor: 'rgb(36, 138, 80)',
            data: []
        }]
    },

    // Configuration options go here
    options: {}
});

var humidity_chart = new Chart(ctx2, {
    // The type of chart we want to create
    type: 'line',
   
    // The data for our dataset
    data: {
        datasets: [{
            label: "Humidité",
            backgroundColor: 'rgb(58, 69, 188)',
            borderColor: 'rgb(58, 69, 188)',
            data: []
        }]
    },

    // Configuration options go here
    options: {}
});

var light_chart = new Chart(ctx3, {
    // The type of chart we want to create
    type: 'line',
   
    // The data for our dataset
    data: {
        datasets: [{
            label: "Luminosité",
            backgroundColor: 'rgb(227, 230, 77)',
            borderColor: 'rgb(227, 230, 77)',
            data: []
        }]
    },

    // Configuration options go here
    options: {}
});

function addData(chart, label, data) {
    chart.data.labels.push(label);
    chart.data.datasets.forEach((dataset) => {
        dataset.data.push(data);
    });
    chart.update();
}

var ws = new WebSocket("ws://" + location.host + ":81");
ws.onmessage = function (event) {
    console.log(event.data);
    data = JSON.parse(event.data);
    document.getElementById("temp").innerHTML = data.temp + " °C";
    document.getElementById("humidity").innerHTML = data.hum + " %";
    document.getElementById("light").innerHTML = data.lux + " lux";
    addData(temp_chart, "", data.temp)
    addData(humidity_chart, "", data.hum);
    addData(light_chart, "", data.lux);
}