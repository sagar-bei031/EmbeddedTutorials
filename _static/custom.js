document.addEventListener("DOMContentLoaded", function () {
    document.querySelectorAll('a.extlink-newtab').forEach(link => {
        link.setAttribute('target', '_blank');
        link.setAttribute('rel', 'noopener noreferrer');
    });
});