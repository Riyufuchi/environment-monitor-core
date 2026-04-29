let index = 0;
const maxImg = 5; // num of imgs - 1
const numOfImg = 6; // num of imgs on the page
let imgIndex = [];
// Utils
function insert(newElement, existingElement)
{
	existingElement.parentNode.insertBefore(newElement, existingElement.nextSibling);
}
function changeSrc(elementID, newSrc)
{
	let img = document.getElementById(String(elementID));
	img.src = newSrc;
	img.onclick = (function(id) {
        return function() {
            displayImage(id);
        };
    })(newSrc);
}
function displayImage(imageUrl)
{
	//window.open(imageUrl,'Image','width=largeImage.stylewidth,height=largeImage.style.height,resizable=1');
	window.open(imageUrl);
	//window.alert(id);
	//var newTab = window.open();
	// Write the image to the new tab
	//newTab.document.write('<html><head><title>Gallery</title><base href="../" /></head><body><img src="' + imageUrl + '"></body></html>');
	// Close the document to prevent further writing
	//newTab.document.close();
}
//
function setIndexArray()
{
	let maxIndex = maxImg + 2; // +2 because index for arr starts at one and that one img
	for(i = 1; i < maxIndex; i++)
	{
		imgIndex[i] = i;
	}
	let mod = maxImg % numOfImg;
	if(mod !== 0)
	{
		maxIndex = (numOfImg - mod) + maxImg + 1;
		mod = 0;
		for(y = imgIndex.length; y < maxIndex; y++)
		{
			mod++;
			imgIndex[y] = mod;
		}
	}
}
function loadPictures()
{
	var a;
	for(let i = numOfImg; i > 1; i--)
	{
		a = document.createElement("img");
		a.setAttribute("id", i);
		a.setAttribute("class", "galleryFrame");
		//a.style.width = "100%";
		//a.style.height = "100%";
		a.setAttribute("alt", "picture" + i);
		insert(a, document.getElementById("1"));
	}
	setIndexArray();
	loadNext();
	document.getElementById("back").disabled = true;
}
function loadNext()
{
	let numOfImgs = numOfImg + 1;
	for(i = 1; i < numOfImgs; i++)
	{
		index++;
		if(index < imgIndex.length - 1)
		{
			//document.getElementById(String(i)).src = 'pictures/autoload/' + imgIndex[index] + '.png';
			 changeSrc(i, 'pictures/autoload/' + imgIndex[index] + '.png')
		}
		else
		{
			changeSrc(i, 'pictures/autoload/' + imgIndex[index] + '.png')
			//document.getElementById(String(i)).src = "pictures/autoload/" + imgIndex[index] + ".png";
			document.getElementById("next").disabled = true;
			break;
		}
	}
	scroll(0,0);
	document.getElementById("back").disabled = false;
}
function loadPrev()
{
	index = index - numOfImg*2;
	if(index < 0)
	{
		index = 0;
	}
	let numOfImgs = numOfImg + 1;
	for(i = 1; i < numOfImgs; i++)
	{
		index++;
		changeSrc(i, 'pictures/autoload/' + imgIndex[index] + '.png')
	}
	if(index === numOfImgs-1)
	{
		document.getElementById("back").disabled = true;
	}
	scroll(0,0);
	document.getElementById("next").disabled = false;
}
