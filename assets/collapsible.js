/* -------afterload--------------*/
var debug=false;

// fix png for IE <6
function correctPNG(){
    for(var i=0; i<document.images.length; i++){
	var img = document.images[i];
	var imgName = img.src.toUpperCase();
	if (imgName.substring(imgName.length-3, imgName.length) == "PNG"){
	    var imgID = (img.id) ? "id='" + img.id + "' " : "";
	    var imgClass = (img.className) ? "class='" + img.className + "' " : "";
	    var imgTitle = (img.title) ? "title='" + img.title + "' " : "title='" + img.alt + "' ";
	    var imgStyle = "display:inline-block;" + img.style.cssText;
	    if (img.align == "left") 
		imgStyle = "float:left;" + imgStyle;
	    if (img.align == "right") imgStyle = "float:right;" + imgStyle;
	    if (img.parentElement.href) imgStyle = "cursor:hand;" + imgStyle;
	    var strNewHTML = "<span " + imgID + imgClass + imgTitle
		+ " style=\"" + "width:" + img.width + "px; height:" + img.height + "px;" + imgStyle + ";"
		+ "filter:progid:DXImageTransform.Microsoft.AlphaImageLoader"
		+ "(src=\'" + img.src + "\', sizingMethod='scale');\"></span>";
	    img.outerHTML = strNewHTML;
	    i = i-1;
	}
    }
}

function myAlert(msg){
    if(debug){
	alert(msg);
    }
}

function afterload(){
    myAlert("alert");
    
    //correct PNG Background
    if(navigator.appName=="Microsoft Internet Explorer" 
       && parseInt(navigator.appVersion) < 7){
	 correctPNG();
    }

    expandTopic();
    expandNew();
    setCollapsible();

}





function setCollapsible(){
    
    var collapsible=
	document.getElementById("collapsible");
    var content=
	document.getElementById("muse-content");
    
    //attache the event handler
    if(collapsible.addEventListenner){
	collapsible.addEventListener('mouseover', showArrow, false);
	collapsible.addEventListener('mouseout', hideArrow, false);
	collapsible.addEventListener('click', collapse, false);
	collapsible.addEventListener('mousemove',moveArrow, false);
	window.addEventListener('resize',resizeWindow, false);
    } else if (collapsible.attachEvent) {
	collapsible.attachEvent('onmouseover', showArrow);
	collapsible.attachEvent('onmouseout', hideArrow);
	collapsible.attachEvent('onclick', collapse);
	collapsible.attachEvent('onmousemove',moveArrow);
	window.attachEvent('onresize', resizeWindow);
    } else {
	collapsible.onmouseover=showArrow;
	collapsible.onmouseout=hideArrow;
	collapsible.onclick=collapse;
	collapsible.onmousemove=moveArrow;
	window.onresize=resizeWindow;
    }
	
    adjustCollapsibleHeight();
}

function resizeWindow() {
    
    adjustCollapsibleHeight();
}
    

function moveArrow(e){
    var arrow=
	document.getElementById("collapsible-arrow");
    myAlert("move");
    //set the Arrow position
    var posx = 0;
    var posy = 0;
    if (!e) var e = window.event;
    if (e.pageX || e.pageY) 	{
	//alert("h1");
	posx = e.pageX;
	posy = e.pageY;
    }
   else 
    if (e.clientX || e.clientY) 	{
	//alert("h2");
	posx = e.clientX + document.body.scrollLeft
	    + document.documentElement.scrollLeft;
	posy = e.clientY + document.body.scrollTop
	    + document.documentElement.scrollTop;
    }
    // posx and posy contain the mouse position relative to the document
    // Do something with this information

    //set the absolute pixel position
    //arrow.style.position="absolute";
    arrow.style.top=posy+"px";
    //arrow.style.left=posx+"px";
    if(isCollapsed()){
	arrow.style.left="0px";
    } else {
	//arrow.style.left="181px";
	arrow.style.left="250px";
    }
	
    //alert("("+posx+", "+posy+")");
	  
}

//when move into the mouse
function showArrow(e){
    myAlert("showArrow");

    var collapsible=
	document.getElementById("collapsible");
    var arrow=
	document.getElementById("collapsible-arrow");

    collapsible.className="hover";
    adjustCollapsiblePos();

    //show the Arrow
    moveArrow(arrow, e);
    arrow.style.display="block";    
}


//when move out the mouse
function hideArrow(){
    myAlert("hideArrow");
    
    var collapsible=
	document.getElementById("collapsible");
    var arrow=
	document.getElementById("collapsible-arrow");

    collapsible.className="";
    adjustCollapsiblePos();

    //hide the Arrow
    arrow.style.display="none";
}
    

function collapse(){
    myAlert("collapse");

    var content=
	document.getElementById("muse-content");

    var topic=
	document.getElementById("topic");

    var collapsible=
	document.getElementById("collapsible");
    var arrow=
	document.getElementById("collapsible-arrow");
      
    if(isCollapsed()){
	topic.style.display="block";
	//content.style.marginLeft="181px";
	content.style.marginLeft="250px";
	arrow.className="";
// 	collapsible.style.height=content.offsetHeight+"px";
	
    } else {
	topic.style.display="none";
	content.style.marginLeft="0px";
	arrow.className="collapsed";
      // 	collapsible.style.height=content.offsetHeight+"px";
    }
    adjustCollapsiblePos();
    adjustCollapsibleHeight();
    
}
function adjustCollapsiblePos(){
    var topic=
	document.getElementById("topic");
    var collapsible=
	document.getElementById("collapsible");

    if(topic.style.display=="none"){
	if(collapsible.className=="hover"){
	    collapsible.style.left="-3px";
	} else {
	    collapsible.style.left="-5px";
	}

    }else {
	collapsible.style.left="-5px";
    }
}
	


function isCollapsed(){
    var topic=
	document.getElementById("topic");
    return (topic.style.display=="none");
}


function adjustCollapsibleHeight(){
    var collapsible=
	document.getElementById("collapsible");
    var muse_content=
 	document.getElementById("muse-content");
    var topic=
	document.getElementById("topic");
    var container=
	document.getElementById("container");
    var maxHeight=Math.max(
			   Math.max(muse_content.offsetHeight, topic.offsetHeight),
			   container.offsetHeight);
			   
    //alert(maxHeight);
    collapsible.style.height=maxHeight+"px";
}


function hideContents(){
    var show=
	document.getElementById("show");    
    var hide=
	document.getElementById("hide");
    var contentList=
	document.getElementById("content-list");

    show.style.display="inline";
    hide.style.display="none";
    contentList.style.display="none";
    adjustCollapsibleHeight();
}


function showContents(){
    var show=
	document.getElementById("show");    
    var hide=
	document.getElementById("hide");
    var contentList=
	document.getElementById("content-list");

    show.style.display="none";
    hide.style.display="inline";
    contentList.style.display="block";
    adjustCollapsibleHeight();
}

function toggle(control){
    var ul=control.parentNode.parentNode.getElementsByTagName("ul")[0];
    var img=control.getElementsByTagName("img")[0];

    if(ul.style.display=="block") {
	//toggle to none
	ul.style.display="none";
	img.className="tgl-control tgl-plus";
    } else {
	ul.style.display="block";
	img.className="tgl-control tgl-minus";
    }

    adjustCollapsibleHeight();
}

function expandTopic(){
    var topic=document.getElementById("topic");
    var divs=topic.getElementsByTagName("div");
    var current=null;

    for(i=0;i<divs.length;i++){
	if(divs[i].className=="current"){
	    current=divs[i];
	    break;
	}
    }

    var toggles=new Array();

    if(current!=null){
	var tmp=current;
	while(tmp!=null && tmp!=topic){
	    if(tmp.tagName.toLowerCase()=="li") {
		if(tmp.getElementsByTagName("ul").length>0){
		    toggles.unshift(tmp.getElementsByTagName("div")[0]);
		}
	    }
	    tmp=tmp.parentNode;
	}
    } else {
	var tgl=topic.getElementsByTagName("div")[0];
	if(div.parentNode.getElementsByTagName("ul").length>0){
	    toggles.push(tgl);
	}
    }

    for(i=0;i<toggles.length;i++){
	toggle(toggles[i].getElementsByTagName("a")[0]);
    }
}

function expandNew(){
    var topic=document.getElementById("topic");
    var spans=topic.getElementsByTagName("span");
    var news=new Array();
    
    for(i=0;i<spans.length;i++){
	if(spans[i].className=="newentry"){
	    news.push(spans[i].parentNode);
	}
    }

    for(j=0;j<news.length;j++){
	showNew(topic, news[j]);
    }
}

function showNew(topic, current){
    var toggles=new Array();

    if(current!=null){
	var tmp=current;
	while(tmp!=null && tmp!=topic){
	    if(tmp.tagName.toLowerCase()=="li") {
		if(tmp.getElementsByTagName("ul").length>0){
		    toggles.unshift(tmp.getElementsByTagName("div")[0]);
		}
	    }
	    tmp=tmp.parentNode;
	}
    } else {
	var tgl=topic.getElementsByTagName("div")[0];
	if(div.parentNode.getElementsByTagName("ul").length>0){
	    toggles.push(tgl);
	}
    }

    for(i=0;i<toggles.length;i++){
	showtoggle(toggles[i].getElementsByTagName("a")[0]);
    }

}

function showtoggle(control){
    var ul=control.parentNode.parentNode.getElementsByTagName("ul")[0];
    var img=control.getElementsByTagName("img")[0];

    ul.style.display="block";
    img.className="tgl-control tgl-minus";


    // if(ul.style.display=="block") {
    // 	//toggle to none
    // 	ul.style.display="none";
    // 	img.className="tgl-control tgl-plus";
    // } else {
    // 	ul.style.display="block";
    // 	img.className="tgl-control tgl-minus";
    // }

    adjustCollapsibleHeight();
}


//-------------------------
// get contents
//-------------------------

function markCurrent(currentid){
    var current_div = document.getElementById(currentid);
    current_div.className="current";
}

function getContent(src, currentid){
    var iframe = document.createElement("iframe");
    
    var onload_func = function() {
	var outer = document.getElementById("outer");
	outer.innerHTML = iframe.contentWindow.document.getElementById("inner").innerHTML;
	document.body.removeChild(iframe);
	markCurrent(currentid);
	afterload();
    }

    //set event handler
    if(navigator.appName=="Microsoft Internet Explorer"){
	iframe.attachEvent("onload", onload_func);
    } else {
    	iframe.onload = onload_func;
    }
    
    iframe.style.display = "none";
    iframe.src = src;
    document.body.appendChild(iframe);
}
