import React, { useState } from 'react';

function App() {
  const [status, setStatus] = useState("");
  const [results, setResults] = useState([]);

  const startPoll = async () => {
    const res = await fetch('http://localhost:8080/poll/start', { method: 'POST' });
    const data = await res.json();
    setStatus(data.status);
  };
  const stopPoll = async () => {
    const res = await fetch('http://localhost:8080/poll/stop', { method: 'POST' });
    const data = await res.json();
    setStatus(data.status);
  };
  const getResults = async () => {
    const res = await fetch('http://localhost:8080/poll/results');
    const data = await res.json();
    setResults(data.results);
  };

  return (
    <div style={{padding: 40}}>
      <h1>Smart Response Poll</h1>
      <button onClick={startPoll}>Start Poll</button>
      <button onClick={stopPoll}>Stop Poll</button>
      <button onClick={getResults}>Get Results</button>
      <div>Status: {status}</div>
      <div>
        <h2>Results</h2>
        <pre>{JSON.stringify(results, null, 2)}</pre>
      </div>
    </div>
  );
}

export default App;
