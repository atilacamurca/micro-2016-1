const five = require("johnny-five");
const rp = require('request-promise');
// const url = 'http://wireless-monitor.provisorio.ws';
const url = 'http://localhost:8000';

const auth = {
    method: 'POST',
    uri: url + '/api/authenticate',
    body: {
        api_key: '',
        monitor_key: ''
    },
    json: true
};

const Monitor = function (token) {
    this.token = token;
    this.med = [];
    this.api = {
        method: 'POST',
        uri: url + '/api/send',
        headers: {
            'Authorization': 'Bearer ' + this.token
        },
        body: {
            data: null
        },
        json: true
    };
};

Monitor.prototype.pushValue = function (value) {
    this.med.push(value);
};

Monitor.prototype.send = function () {
    let len = this.med.length;
    if (len < 50) {
        return;
    }
    let result = this.calcMed();
    console.log('result', result);
    this.api.body.data = JSON.stringify({value: result});
    this.med = [];
    rp(this.api)
        .then(function (json) {
            console.log('response', json);
        })
        .catch(function (err) {
            console.log(err);
        });
};

Monitor.prototype.calcMed = function () {
    let result = 0;
    for (let value of this.med) {
        result += value;
    }
    return result / this.med.length;
};

rp(auth)
    .then(function(result) {
        var token = result.token;
        console.log('token:', token);
        var monitor = new Monitor(token);

        five.Board().on("ready", function() {
            var temperature = new five.Thermometer({
                controller: "LM35",
                pin: "A0"
            });

            temperature.on("change", function() {
                monitor.pushValue(this.celsius);
                monitor.send();
            });
        });
    })
    .catch(function(err) {
        console.log(err);
    });
