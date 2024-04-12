function init() {
  debug = new Debug(); // TODO: convert to singleton to eliminate global variable.
  new Game(3);
 
}
window.addEventListener('load', init, false);


const button = document.getElementById('hamburger-btn');

button.addEventListener('click', function() {
  document.getElementById('hamburger-menu').classList.toggle('open');
}); 

