const express = require('express');
const path = require('path');
const axios = require('axios');

const app = express();
const port = 3000;

// ✅ MUST BE A STRING, in quotes
const ESP32_IP = 'http://192.168.1.14';

app.use(express.static(path.join(__dirname, 'public')));

app.get('/esp32data', async (req, res) => {
  try {
    console.log('🔁 Trying to contact ESP32 at:', `${ESP32_IP}/data`);
    const response = await axios.get(`${ESP32_IP}/data`);
    console.log('✅ ESP32 replied:', response.data);
    res.json(response.data);
  } catch (err) {
    console.error('❌ ESP32 fetch error:', err.message);
    res.status(500).json({ error: 'Failed to fetch data from ESP32' });
  }
});

app.listen(port, () => {
  console.log(`🚀 Server running at http://localhost:${port}`);
});
