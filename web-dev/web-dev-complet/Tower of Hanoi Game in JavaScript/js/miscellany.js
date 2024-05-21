// methode pour la generation de random number pour les coulleurs du disque
function random_int(min, max) {
  return Math.floor(Math.random() * (max - min + 1) + min);
}


function shuffle(arr) {
  arr.sort(function(a, b) { return Math.random() - 0.5; });
}

function biggest(a, b) {
  return a > b ? a : b;
}
