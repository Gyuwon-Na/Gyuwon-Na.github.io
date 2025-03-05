const navToggle = document.querySelector(".nav-toggle");
const navLinks = document.querySelectorAll(".nav__link");

navToggle.addEventListener("click", () => {
    document.body.classList.toggle("nav-open");
});

navLinks.forEach((link) => {
    link.addEventListener("click", () => {
        document.body.classList.remove('nav-open');
    });
});

// Help iframe of webgl demos get access to the keyboard by giving them focus when clicked
document.addEventListener("DOMContentLoaded", function () {
    const iframe = document.getElementById("demo");
    if (!iframe) {
        return;
    }
    iframe.addEventListener("load", function () {
        try {
            const iframeDoc = iframe.contentWindow.document;
            iframeDoc.addEventListener("mousedown", function () {
                iframe.contentWindow.Module.canvas.focus();
            });
        } catch (e) {
            console.error(e);
        }
    });
});

window.addEventListener("message", function(event) {
    const iframe = document.getElementById("interaction");
    if (!iframe) {
        return;
    }
    
    if (event.data && event.data.type === 'data-on') {
        const dataOnValue = event.data.value;

        // data-on 값에 따른 처리
        if (dataOnValue === "true") {
            document.documentElement.setAttribute('data-on', 'true');
        } else {
            document.documentElement.setAttribute('data-on', 'false');
        }
    }
});
