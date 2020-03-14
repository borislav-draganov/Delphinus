<div class="mdl-grid main-container">
	<div class="mdl-cell mdl-cell--5-col mdl-cell--1-col-tablet mdl-cell--hide-phone"></div>

	<div class="mdl-cell mdl-cell--2-col mdl-cell--6-col-tablet mdl-cell--12-col-phone">
		<h1 class="center mdl-color-text--primary header">Delphinus</h1>

		<ul class="mdl-list">
			{#each sensors as sensor}
				<li class="mdl-list__item {sensor.color}-underline">
					<span class="mdl-list__item-primary-content">
						<span class="circle {sensor.color}-bg"></span>
						{sensor.name}
					</span>

					<span class="mdl-list__item-secondary-content">{sensor.value} {sensor.unitSign}</span>
				</li>
			{/each}
		</ul>

		<div class="mdl-tabs mdl-js-tabs mdl-js-ripple-effect">
			<div class="mdl-tabs__tab-bar">
				<a href="#sensor-panel" class="mdl-tabs__tab is-active">Sensor</a>
				<a href="#wifi-panel" class="mdl-tabs__tab">WiFi</a>
			</div>
			
			<div class="mdl-tabs__panel is-active" id="sensor-panel">
				<div class="center">
					{#each sensors as sensor}
						<div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
							<input class="mdl-textfield__input" type="text" id="{sensor.color}-sensor-name-input" bind:value={sensor.name}>
							<label class="mdl-textfield__label" for="{sensor.color}-sensor-name-input"><span class="{sensor.color}-color capitalize">{sensor.color}</span> Sensor Name</label>
						</div>
					{/each}
					
					<button class="mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect mdl-button--colored" on:click="{submitSensorConfig}">
						Save
					</button>
				</div>
			</div>

			<div class="mdl-tabs__panel" id="wifi-panel">
				<div class="center">
					<div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
						<input class="mdl-textfield__input" type="text" id="ssid" bind:value={ssid}>
						<label class="mdl-textfield__label" for="ssid">SSID</label>
					</div>
					
					<div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
						<input class="mdl-textfield__input" type="password" id="password" bind:value={password}>
						<label class="mdl-textfield__label" for="password">Password</label>
					</div>
					
					<button class="mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect mdl-button--colored" on:click="{submitWiFiConfig}">
						Save
					</button>
				</div>
			</div>
		</div>
	</div>
</div>

<footer class="mdl-mini-footer">
	<div class="mdl-mini-footer__left-section">
		Copyright &copy; 2019 Borislav Draganov
	</div>
</footer>

<div id="toast" class="mdl-js-snackbar mdl-snackbar">
	<div class="mdl-snackbar__text"></div>
	<button class="mdl-snackbar__action" type="button"></button>
</div>

<script>
	const sensorConfigEndpoint = '/config/sensors';
	const temperatureSign = '°C';

	const sensors = [{
		name: 'Red',
		color: 'red',
		value: 0,
		unitSign: temperatureSign,
	}, {
		name: 'Yellow',
		color: 'yellow',
		value: 0,
		unitSign: temperatureSign,
	}, {
		name: 'Blue',
		color: 'blue',
		value: 0,
		unitSign: temperatureSign,
	}, {
		name: 'Green',
		color: 'green',
		value: 0,
		unitSign: temperatureSign,
	}, {
		name: 'Power',
		color: 'black',
		value: 0,
		unitSign: 'A',
	}];

	let ssid = '';  
	let password = '';

	const showToast = (message) => {
		const notification = document.querySelector('.mdl-js-snackbar');
		const data = {
			message,
			timeout: 2000,
		};

		notification.MaterialSnackbar.showSnackbar(data);
	};

	const getSensorData = async() => {
		if (isDev) {
			return {"redSensor":21.5625,"yellowSensor":21.4375,"blueSensor":21.3125,"greenSensor":21,"powerSensor":0.0453};
		}

		const response = await fetch('/sensors', {
			method: 'GET',
		});

		return response.json();
	};

	const getSensorConfig = async () => {
		if (isDev) {
			return {"redSensorName":"Red","yellowSensorName":"Yellow","blueSensorName":"Blue","greenSensorName":"Green","powerSensor":"Power"};
		}

		const response = await fetch(sensorConfigEndpoint, {
			method: 'GET',
		});

		return response.json();
	};

	const refreshSensorData = async () => {
		const {
			redSensor,
			yellowSensor,
			blueSensor,
			greenSensor,
			powerSensor,
		} = await getSensorData();

		const [red, yellow, blue, green, power] = sensors;

		red.value = redSensor.toFixed(2);
		yellow.value = yellowSensor.toFixed(2);
		blue.value = blueSensor.toFixed(2);
		green.value = greenSensor.toFixed(2);
		power.value = powerSensor.toFixed(3);

		sensors = sensors;
	};

	const refreshSensorConfig = async () => {
		const {
			redSensorName,
			yellowSensorName,
			blueSensorName,
			greenSensorName,
		} = await getSensorConfig();

		const [red, yellow, blue, green] = sensors;

		red.name = redSensorName;
		yellow.name = yellowSensorName;
		blue.name = blueSensorName;
		green.name = greenSensorName;

		sensors = sensors;
	} ;

	const submitWiFiConfig = async () => {
		if (!ssid) {
			showToast('SSID is required');
			return;
		}

		const response = await fetch('/config/wifi', {
			method: 'POST',
			body: JSON.stringify({
				ssid,
				password,
			}),
			headers: {
				'Content-Type': 'application/json',
			},
		});

		showToast('Saved');
	};

	const submitSensorConfig = async () => {
		const [red, yellow, blue, green] = sensors;

		const response = await fetch(sensorConfigEndpoint, {
			method: 'POST',
				body: JSON.stringify({
					redSensorName: red.name,
					yellowSensorName: yellow.name,
					blueSensorName: blue.name,
					greenSensorName: green.name,
				}),
				headers: {
					'Content-Type': 'application/json',
				},
			});

		showToast('Saved');
	};

	// Main
	(async () => {
		refreshSensorConfig();

		refreshSensorData();

		setInterval(refreshSensorData, 2000);
	})();
</script>