



function VictoryCelebrator(input_handler) {
  this.input_handler = input_handler;
}
// methode a lancer lors de la victoire
VictoryCelebrator.prototype.on_victory = function() {
  

  
  var victory_notification = document.getElementById('victory-notification');
  victory_notification.style.display = 'block';
  document.getElementById('play-again').addEventListener('click', function() {

      victory_notification.style.display = 'none';
      new Game(document.getElementById('disks-count').value);
  }, false);
}

// declaration du button restart dans javascript
const restart = document.getElementById("restart-game");
// ajouter un listener pour le button restart
restart.addEventListener("click" , () =>{
// lancement de la methode new Game et recuperation de la valeur du nombre de disque
  var disksCountInput = document.getElementById('disks-count-input').value;
  Colour.nextColorIndex = 0;
  new Game(disksCountInput);
})

