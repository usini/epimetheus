var ws = new WebSocket("ws://" + location.host + "/websocket");
websocket_status = false;
var chart_0_ctx = document.getElementById("chart_0").getContext('2d');

// https://www.chartjs.org/docs/latest/getting-started/usage.html
 chart_0 = new Chart(chart_0_ctx, {
    // The type of chart we want to create
    type: 'line',
    
    // The data for our dataset
    data: {
        datasets: []
    },
    // Configuration options go here
    options: {
        scales: {
            xAxes: [{
                type: 'time',
                time: {
                    displayFormats: {
                        second: "h:mm:ss a"
                    },
                },
                distribution: "linear"
            }]
        },
        plugins: {
            zoom: {
                zoom: {
                    enabled: true,
                    drag: true,
                    mode: 'x',
        
                    rangeMin: {
                        x: null,
                        y: null
                    },
                    rangeMax: {
                        x: null,
                        y: null
                    },
        
                    speed: 0.1,
                    threshold: 2,
                    sensitivity: 3,
                    onZoom: function({chart}) { console.log(`I'm zooming!!!`); },
                    onZoomComplete: function({chart}) { console.log(`I was zoomed!!!`); }
                }
            }
        }
    }
});

time = "";

function currentTime() {
    var t = setTimeout(currentTime, 1000);
    var date = new Date();
    var hour = updateTime(date.getHours());
    var min = updateTime(date.getMinutes());
    var sec = updateTime(date.getSeconds());
    time = hour + ":" + min + ":" + sec;
    document.getElementById("clock").innerHTML = time;
}

function updateData() {
    var t = setTimeout(updateData, 1000);
    if(websocket_status){
        msg = {};
        msg.msg = "update";
        ws.send(JSON.stringify(msg));
    }
}

function updateTime(k) {
    if (k < 10) {
        return "0" + k;
    }
    else {
        return k;
    }
}

function update_clock() {
    var date = new Date();
    message = {};
    message.msg = "set_clock";
    message.year = date.getFullYear();
    message.month = date.getMonth() + 1;
    message.day = date.getDay();
    message.hour = date.getHours();
    message.minute = date.getMinutes();
    message.second = date.getSeconds();
    ws.send(JSON.stringify(message));
}

currentTime();
updateData();

nb_sensors = 0;

ws.onopen = function (event) {
    console.log(LANG_WEBSOCKET_OPEN);
    websocket_status = true;
    msg = {};
    msg.msg = "list";
    //console.log(JSON.stringify(msg));
    ws.send(JSON.stringify(msg));
    msg = {};
    msg.msg = "flash";
    ws.send(JSON.stringify(msg));
    msg = {};
    msg.msg = "name";
    ws.send(JSON.stringify(msg));
    msg.msg = "get_clock"
    ws.send(JSON.stringify(msg));
};

ws.onmessage=function(event) {
    // Fix for integer report as valid JSON
    if(!isNaN(event.data)){
        json_parsed = false;
    } else {
        try {
            data = JSON.parse(event.data);
            //console.log(data)
            json_parsed = true;
        } catch(e) {
            json_parsed = false;
        }
    }

    if(json_parsed){
        if(data.msg == "list") {
            generate_sensors(JSON.parse(event.data));
        }
        if(data.msg == "name") {
            document.getElementById("esp_name").value = data.value;
        }
        if(data.msg == "flash") {
            if(!data.value) {
                document.getElementById("save_flash_icon").style.display = "none";
            }
        }
        if(data.msg == "change_name") {
            if(data.result){
                show_ok(LANG_NAME_SAVED_OK);
            } else {
                show_error(LANG_NAME_SAVED_ERROR);
            }
        }
        if(data.msg == "get_clock") {
            var date_local = new Date();
            var date_remote = data["value"];
            var diff = Math.abs(Date.parse(date_local) - Date.parse(data["value"]))
            if(diff >= 5) {
                update_clock();
            }
        }
    } else {
        //console.log("Parsing data...");
        chart_0.data.labels.push(new Date());
        //console.log(event.data);
        data = event.data.split(';');
        //console.log(data.length);
        data.forEach(function(item, index, array) {
            document.getElementById("sensor_value_" + index).innerHTML = item;
            chart_0.data.datasets[index].data.push(item);           
        });
        chart_0.update();
        mean_chart();
    }
}

ws.onclose = function (event) {
    console.log(LANG_WEBSOCKET_CLOSED);
}      

ws.onerror = function (event) {
    console.log(LANG_WEBSOCKET_ERROR);
    show_error(LANG_WEBSOCKET_ERROR);
    websocket_status = false;
};

function generate_sensors(data) {
    //console.log(data)
    if(data.result) {
        data.value = "...";

        const widget = ` 
        <tr class="theme_widget_background margin center">
        <td>${data.text}</td>
        <td id="sensor_${data.id}" style="color:${data.color};">
        <span id="sensor_value_${data.id}">${data.value}</span>${data.unit}
        </td>
        <td class="right">${data.sensor}</td>
        </tr>
        `;
        //console.log(widget);
        widgets_code = document.getElementById("widgets").innerHTML
        document.getElementById("widgets").innerHTML += widget;
        nb_sensors++;
        chart_0.data.datasets.push({
            label: data.text,
            borderColor: data.color,
            borderWidth: 1,
            data: []
        })
        chart_0.update();
    }
}

const name_input = document.getElementById("esp_name");
name_input.addEventListener("keydown", function(event){
    if(event.key === "Enter") {
        event.preventDefault();
        response = {};
        response.msg = "change_name";
        response.value = name_input.value;
        ws.send(JSON.stringify(response));
    }
});

function mean_chart() {
    mean_each = 10;
    mean_data_until = 50;
    mean_at = 100;
    if(chart_0.data.labels.length > mean_at) {
        
        //Réduction de l'échelle de temps
        //Gardez l'heure pour mean_at valeur puis a keep_last_data garder toutes les temps
        time_labels = mean_time(chart_0.data.labels, mean_data_until, mean_each);
        
        chart_0.chart.data.datasets.forEach(function(dataset,dataset_index) {
            chart_0.chart.data.datasets[dataset_index].data = mean_data(dataset.data, mean_data_until, mean_each);
        });

        chart_0.data.labels = time_labels;
        console.log("TIME LABELS :" + time_labels.length);
        console.log("CHART DATA:" + chart_0.chart.data.datasets[0].data.length);
    } else {
        console.log("Pas assez de valeurs pour faire une moyenne");
        console.log(chart_0.data.labels.length);
    }
}

function mean_time(time_array, mean_data_until, mean_each) {
    time_labels = [];
    time_value = 0;
    time_labels.push(time_array[0]);
    do_not_mean_at = (time_array.length - mean_data_until);
    for (const [index, value] of time_array.entries()) {
        if(index < do_not_mean_at) {
            if(time_value == mean_each) {
                time_labels.push(value);
                time_value = 0;
            }
            time_value++;
        } else {
            time_labels.push(value);
        }
    }
    return time_labels;
}

function mean_data(data_array, mean_data_until, mean_each) {
    temp_array = [];
    mean_array = [];
    for (const [index, value] of data_array.entries()) {
        //Keep last 50 data points
        if(index >= (data_array.length - mean_data_until)) {
            mean_array.push(value);
        } else {
            temp_array.push(value);
            if(temp_array.length == mean_each) { // We get 10 value
                sum = (temp_array.reduce(function(a, b) { return parseFloat(a) + parseFloat(b); }, 0) / temp_array.length).toFixed(2)
                mean_array.push(sum); // Add value to mean array
                temp_array.length = 0; 
            }
        }
    }
    return mean_array;
}