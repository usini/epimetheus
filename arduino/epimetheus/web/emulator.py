from bottle import route, post, get, run, template, static_file, request
from bottle.ext.websocket import GeventWebSocketServer, websocket
import json
import time
import random
import os.path
import os
#http://bottlepy.org/docs/dev/tutorial.html#generating-content

# To implement
simulate_random_sensor_change = False
settings = {}
name = ""
flash = False

def is_json(x):
    try:
        json.loads(x)
        return True
    except:
        return False

if os.path.isfile("settings.json"):
    print("Settings exists")
    f = open("settings.json","r")
    settings = json.loads(f.read())
    print(settings)
else:
    print("Generate default settings")
    f = open("settings.json", "w")
    settings["wifi1_name"] = ""
    settings["wifi1_pass"] = ""
    settings["wifi2_name"] = ""
    settings["wifi2_pass"] = ""
    f.write(json.dumps(settings))
    f.close()

if os.path.isfile("name.txt"):
    print("name exists")
    f = open("name.txt", "r")
    name = f.read()
else:
    print("Generate default name")
    f = open("name.txt", "w")
    f.write("EPIM43E1F4")

if os.path.isfile("flash"):
    flash = True

sensors_list = []

sensors_list.append({
    "sensor":"BME680-A",
    "text":"Température",
    "unit":"°C",
    "color":"red",
    "type":"temp"
})

sensors_list.append({
    "sensor":"BME680-A",
    "text":"Humidité",
    "unit":"%",
    "color":"blue",
    "type":"humidity"
})


sensors_list.append({
    "sensor":"BME680-A",
    "text":"Pression Atmosphérique",
    "unit":"hPA",
    "color":"blue",
    "type":"pressure"
})

sensors_list.append({
    "sensor":"BME680-A",
    "text":"Gaz",
    "unit":"Kohm",
    "color":"brown",
    "type":"gaz"
})

sensors_list.append({
    "sensor":"TSL2561",
    "text":"Luminosité",
    "unit":"lux",
    "color":"yellow",
    "type":"light"
})

@route('/')
def index_page():
    return static_file("index.html","./")

@route('/settings')
def settings_page():
    return static_file("settings.html","./")

@route('/save.svg')
def svg_save():
    return static_file("save.svg","./")

@route('/radio.svg')
def svg_radio():
    return static_file("radio.svg","./")

@route('/labsud.svg')
def svg_labsud():
    return static_file("labsud.svg","./")

@route('/script.js')
def script_js():
    return static_file("script.js","./")

@route('/settings.js')
def settings_js():
    return static_file("settings.js","./")

@route('/charts.js')
def charts_js():
    return static_file("charts.js","./")

@route('/hammerjs.js')
def hammer_js():
    return static_file("/hammerjs.js","./")

@route('/chartjs-plugin-zoom.js')
def charts_js_zoom():
    return static_file("chartjs-plugin-zoom.js","./")

@route('/lang.js')
def lang_js():
    return static_file("lang.js","./")

@route('/charts.css')
def charts_css():
    return static_file("charts.css","./")

@route('/style.css')
def style_css():
    return static_file("style.css","./")

@route('/slider.css')
def slider_css():
    return static_file("slider.css","./")

@route('/download')
def data_csv():
    return static_file("data.csv","./")

@route('/toast.min.js')
def toast():
    return static_file("toast.min.js","./")

@get('/websocket', apply=[websocket])
def echo(ws):
    global settings, flash, name
    while True:
        data = ws.receive()
        if data is not None:
            if(is_json(data)):
                json_data = json.loads(data)
                print(json_data)
                if(json_data["msg"] == "list"):
                    id = 0
                    for sensor in sensors_list:
                        sensor["msg"] = "list"
                        sensor["result"] = True
                        sensor["id"] = id
                        id = id + 1
                        ws.send(json.dumps(sensor))
                    print(sensors_list)
                elif(json_data["msg"] == "update"):
                    #ws.send(str(random.randrange(0,30)))
                    ws.send(str(random.randrange(0,30)) + ";" + str(random.randrange(0,100)) + ";" + str(random.randrange(2000,3000)) + ";" + str(random.randrange(0,1000)) + ";" + str(random.randrange(0,60000)))
                elif(json_data["msg"] == "wifi_scan"):
                    ssids = {}
                    ssids["msg"] = "wifi_scan"
                    ssids["value"] = ["livebox","freebox","bobox"]
                    ssids["result"] = True
                    ws.send(json.dumps(ssids))
                elif(json_data["msg"] == "delete"):
                    delete = {}
                    delete["msg"] = "delete"
                    delete["result"] = True
                    ws.send(json.dumps(delete))
                    f = open("data.csv", "w")
                    f.write("")
                    f.close()
                elif(json_data["msg"] == "save_settings"):
                    settings_save = {}
                    settings_save["wifi1_name"] = json_data["wifi1_name"]
                    settings_save["wifi2_name"] = json_data["wifi2_name"]
                    f = open("settings.json", "w")
                    f.write(json.dumps(settings_save))
                    f.close()
                    settings = settings_save
                    response = {}
                    response["msg"] = "save_settings"
                    response["result"] = True
                    ws.send(json.dumps(response))
                elif(json_data["msg"] == "open_settings"):
                    settings_load = settings
                    settings_load["msg"] = "open_settings"
                    settings_load["result"] = True
                    ws.send(json.dumps(settings))
                elif(json_data["msg"] == "change_name"):
                    name = json_data["value"]
                    f = open("name.txt", "w")
                    f.write(name)
                    f.close()
                    response = {}
                    response["msg"] = "change_name"
                    response["result"] = True
                    ws.send(json.dumps(response))
                elif(json_data["msg"] == "name"):
                    response = {}
                    response["msg"] = "name"
                    response["value"] = name
                    ws.send(json.dumps(response))
                elif(json_data["msg"] == "save_flash"):
                    print("Réponse de la sauvegarde flash")
                    print(json_data)
                    if(json_data["value"]):
                        f = open("flash", "w")
                        f.write("")
                        f.close()
                        flash = True
                    else:
                        if os.path.isfile("flash"):
                            os.remove("flash")
                            flash = False
                    response = {}
                    response["msg"] = "save_flash"
                    response["result"] = True
                    ws.send(json.dumps(response))
                elif(json_data["msg"] == "flash"):
                    response = {}
                    response["msg"] = "flash"
                    response["value"] = flash
                    response["result"] = True
                    ws.send(json.dumps(response))
                elif(json_data["msg"] == "get_clock"):
                    response = {}
                    response["msg"] = "get_clock"
                    response["result"] = True
                    response["value"] = "2000/1/14 3:41:4"
                    ws.send(json.dumps(response))
                elif(json_data["msg"] == "set_clock"):
                    response = {}
                    response["msg"] = "set_clock"
                    response["result"] = True
                    print(json_data)
                    ws.send(json.dumps(response))
                else:
                    print("Incorrect JSON")
                    print(json_data)
            else:
                print("Non JSON")
                print(data)

run(host='0.0.0.0', port=8080, server=GeventWebSocketServer)
