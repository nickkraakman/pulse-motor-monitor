const ctx = document.getElementById('chart').getContext('2d');

// Fetch the data from the server
const data = await fetch('/data').then((response) => response.json());

// Create the chart using the fetched data
const chart = new Chart(ctx, {
  type: 'line',
  data: {
    labels: data.map((d) => d.timestamp), // Use the timestamps as labels
    datasets: [
      {
        label: 'Voltage 1',
        data: data.map((d) => d.voltage1), // Use the voltage1 values as data
        borderColor: 'rgba(255, 99, 132, 0.2)',
        backgroundColor: 'rgba(255, 99, 132, 0.2)',
      },
      {
        label: 'Voltage 2',
        data: data.map((d) => d.voltage2), // Use the voltage2 values as data
        borderColor: 'rgba(54, 162, 235, 0.2)',
        backgroundColor: 'rgba(54, 162, 235, 0.2)',
      },
    ],
  },
  options: {
    // Add options to customize the appearance of the chart
    scales: {
      yAxes: [
        {
          ticks: {
            beginAtZero: true,
          },
        },
      ],
    },
  },
});
