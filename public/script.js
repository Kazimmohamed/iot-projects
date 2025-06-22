function updateSensorData() {
  fetch('/esp32data')  // ✅ This calls your Node server
    .then(response => response.json())
    .then(data => {
      console.log("📥 Received from server:", data);
      document.getElementById('temp').textContent = data.temp?.toFixed(1) ?? '--';
      document.getElementById('hum').textContent = data.hum?.toFixed(1) ?? '--';
    })
    .catch(error => {
      console.error('❌ Error fetching data:', error);
    });
}

setInterval(updateSensorData, 1000);
