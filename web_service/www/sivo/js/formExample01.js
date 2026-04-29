function prepareFormDownload(formID)
{
	const form = document.getElementById(formID);
	form.addEventListener("submit", function (e)
	{
		e.preventDefault(); // Prevent the form from submitting traditionally
		const formData = new FormData(form);
		// Convert form data to a JavaScript object
		const formDataObject = {};
		formData.forEach((value, key) => {
			formDataObject[key] = value;
		});
		// Convert the data to JSON
		const jsonData = JSON.stringify(formDataObject);
		// Create a Blob object with the JSON data
		const blob = new Blob([jsonData], { type: "application/json" });
		// CSV
		/*let csvData = '';
		formData.forEach((value, key) => { csvData += `${key}; ${value}\n`; });
		const blob2 = new Blob([csvData], { type: "text/csv" }); // Create a Blob object with the CSV data
		*/
		// Create a download link for the JSON file
		const url = URL.createObjectURL(blob);
		const a = document.createElement("a");
		a.href = url;
		a.download = "userInput.json";
		a.click();
	});
}