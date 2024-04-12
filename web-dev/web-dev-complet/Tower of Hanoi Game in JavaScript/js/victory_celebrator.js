function VictoryCelebrator(input_handler) {
  this.input_handler = input_handler;
}

VictoryCelebrator.prototype.on_victory = function() {
  this.input_handler.disable_input();

  var victory_notification = document.getElementById('victory-notification');
  victory_notification.style.display = 'block';
  document.getElementById('play-again').addEventListener('click', function() {
      victory_notification.style.display = 'none';
      new Game(document.getElementById('disks-count').value);
  }, false);
}


const restart = document.getElementById("restart-game");

restart.addEventListener("click" , () =>{
  var disksCountInput = document.getElementById('disks-count-input').value;
  new Game(disksCountInput);
})