function VictoryCelebrator(input_handler) {
  this.input_handler = input_handler;
}

VictoryCelebrator.prototype.on_victory = function() {
  this.input_handler.disable_input();

  
  var duration = 3 * 1000;
  var animationEnd = Date.now() + duration;
  var defaults = { startVelocity: 30, spread: 360, ticks: 60, zIndex: 0 };
  
  function randomInRange(min, max) {
    return Math.random() * (max - min) + min;
  }
  
  var interval = setInterval(function() {
    var timeLeft = animationEnd - Date.now();
  
    if (timeLeft <= 0) {
      return clearInterval(interval);
    }
  
    var particleCount = 50 * (timeLeft / duration);
    // since particles fall down, start a bit higher than random
    confetti({ ...defaults, particleCount, origin: { x: randomInRange(0.1, 0.3), y: Math.random() - 0.2 } });
    confetti({ ...defaults, particleCount, origin: { x: randomInRange(0.7, 0.9), y: Math.random() - 0.2 } });
  }, 250);
  
  var victory_notification = document.getElementById('victory-notification');
  victory_notification.style.display = 'block';
  document.getElementById('play-again').addEventListener('click', function() {

      victory_notification.style.display = 'none';
      new Game(document.getElementById('disks-count').value);
  }, false);
}


const restart = document.getElementById("restart-game");

restart.addEventListener("click" , () =>{
  confetti.reset();

  var disksCountInput = document.getElementById('disks-count-input').value;
  Colour.nextColorIndex = 0;
  new Game(disksCountInput);
})


