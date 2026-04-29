const hrefs = ["index.html", "../index.html#aboutme", "../index.html#what_i_do_id", "../index.html#contact"];
const hrefTexts = ["Home", "About me", "What I do", "Social"];
const htmlRootFolder = "sivoWeb/";

function createMenu()
{
	menuBar();
	footer();
}

function menuBar()
{
    let tbl = document.getElementById("sivoLinks");
    tbl.innerHTML = "";

    for (let i = 0; i < hrefs.length; i++)
    {
        const a = document.createElement("a");
        a.className = "sivoNavButton";
        a.href = i === 0 ? hrefs[i] : htmlRootFolder + hrefs[i];
        a.textContent = hrefTexts[i];
        a.onclick = closeMenu;

        tbl.appendChild(a);
    }

}
function closeMenu()
{
	document.getElementById("sivoLinks").style.display = "none";
    
}
function footer()
{
	document.getElementById("footer").innerHTML =
	'<a href="https://ko-fi.com/riyufuchi" target="blank"><img src="https://storage.ko-fi.com/cdn/logomarkLogo.png" alt="KoFi-logo" class="footerLogo"></a>' +
	'<a href="https://github.com/Riyufuchi" target="blank"><img src="pictures/logos/github-mark-white.svg" alt="github-logo" class="footerLogo"></a>';
}
