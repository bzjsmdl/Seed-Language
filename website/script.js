const path = ["/404.html", "/", "/index.html", "/qs.html"];
window.addEventListener("DOMContentLoaded", function(){
    if (!document.getElementById("head-SEEDLANG") || !document.getElementById("end-SEED")) {
        window.location.href = "/404.html"
        alert("Sorry, the wibesite was hijacked. So you have been to 404.html");
    }
});
const currentpath = window.location.pathname;
if (!path.some(p => currentpath.startsWith(p))) {
    window.location.href = "/404.html";
}

function plan() {
    alert("Alpha version! Are you joking with me?");
}