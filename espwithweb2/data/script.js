const webSocket = new WebSocket('ws://' + window.location.hostname + ':81/');

webSocket.onopen = function () {
    console.log('WebSocket connection established.');

    // Request initial sensor data
    webSocket.send('get_data');
};

webSocket.onmessage = function (event) {
    const data = JSON.parse(event.data);

    if (data.type === 'sensor_data') {
        if (data.sensor === 'humidity') {
          console.log('Received Humidity:', data.value);
          document.getElementById('humidity-value').textContent = data.value + '%';
        } else if (data.sensor === 'temperature') {
          console.log('Received Temperature:', data.value);
          document.getElementById('temperature-value').textContent = data.value + 'C';
        } else if (data.sensor === 'co') {
          console.log('Received CO Value:', data.value);
          document.getElementById('co-value').textContent = data.value + ' ppm';
        }
      }
      
};

webSocket.onclose = function () {
    console.log('WebSocket connection closed.');
};

webSocket.onerror = function (error) {
    console.error('WebSocket error:', error);
};