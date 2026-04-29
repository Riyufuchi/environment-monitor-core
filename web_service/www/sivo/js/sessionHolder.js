let checkerID = setInterval(checkSession, 60000);
function checkSession()
{
	let xmlhttp = new XMLHttpRequest();
	xmlhttp.onreadystatechange = function()
	{
		if (this.readyState == 4 && this.status == 200)
		{
			let response = this.responseText;
			if (response.trim() === "expired")
			{
				clearInterval(checkerID);
				alert("Session expired. Redirecting to login page.");
				window.location.href = "../simitrut/html/login.html";
			}
		}
	};
	xmlhttp.open("GET", "sivo/php/session.php?check=CHECK", true);
	xmlhttp.send();
}
