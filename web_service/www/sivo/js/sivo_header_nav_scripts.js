/* Toggle between showing and hiding the navigation menu links when the user clicks on the hamburger menu / bar icon */
function mobileMenu()
{
	let x = document.getElementById("sivoLinks");
	if (x.style.display === "block")
	{
		x.style.display = "none";
	}
	else
	{
		x.setAttribute("style","display: block;margin-top:" + (document.getElementById("navbar").clientHeight) + "px");
	}
}
function showStaticMenu()
{
	let x = document.getElementById("sivoLinks");
	if (x.style.display === "block")
	{
		x.style.display = "none";
	}
	else
	{
		x.setAttribute("style","display: block;");
	}
}
function isPhoneLandscape()
{
	return ((window.matchMedia("(orientation: landscape)").matches) && (/Mobi|Android/i.test(navigator.userAgent)));
}
function sizeDownLogo()
{
	let logo = document.getElementById("logoInHeader");
	logo.style.width = "64px";
	logo.style.height = "auto";
	document.getElementById("menuBtn").style.fontSize = "43px";
}
function createSpacerLegacy()
{
	document.getElementById("headerSpacerID").setAttribute("style","height:" + (document.getElementById("navbar").clientHeight + 16) + "px");
}
function createSpacer()
{
	document.querySelector("main").style.paddingTop = (document.getElementById("navbar").clientHeight + 16) + "px";
}
function fullHeightMain()
{
	let footer = document.querySelector("footer");
	let header = document.querySelector("header");
	let page = document.querySelector("body");
	document.querySelector("main").style.height = page.clientHeight - Math.abs(header.clientHeight - document.querySelector("main").style.paddingTop - footer.clientHeight) + "px";
}
function centerMain()
{
	let main = document.querySelector("main");
	let footer = document.querySelector("footer");
	let header = document.querySelector("header");
	let page = document.querySelector("body");
	
	let pageCenter = (page.clientHeight  / 2) - main.clientHeight / 2;
	//window.alert(pageCenter + header.clientHeight);
	//main.style.paddingTop = pageCenter + header.clientHeight;
	document.querySelector("main").style.paddingTop = pageCenter - Math.abs(header.clientHeight- footer.clientHeight)/2 + "px";
}
function centerMainContent()
{
	let main = document.querySelector("main");
	let page = document.querySelector("body");
	
	let pageCenter = (page.clientHeight  / 2) - main.clientHeight / 2;
	document.querySelector("main").style.paddingTop = pageCenter + "px";
}
