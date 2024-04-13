function Colour(rgb) {
  this.rgb = rgb;
}

Colour.prototype.toString = function() {
  return 'rgb(' + this.rgb.join() + ')';
}

Colour.random = function() {
  // Si toutes les couleurs ont été utilisées, réinitialisez la liste des couleurs utilisées
  if (Colour.usedColors.length === colors.length) {
    Colour.usedColors = [];
  }

  var randomIndex;
  var selectedColor;
  do {
    // Choisissez un index de couleur aléatoire
    randomIndex = random_int(0, colors.length - 1);
    selectedColor = colors[randomIndex];
  } while (Colour.usedColors.includes(randomIndex)); // Vérifiez si la couleur a déjà été utilisée

  // Ajoutez l'index de la couleur sélectionnée à la liste des couleurs utilisées
  Colour.usedColors.push(randomIndex);

  // Créez un nouvel objet Colour avec les composantes R, G et B de la couleur sélectionnée
  return new Colour([selectedColor.r, selectedColor.g, selectedColor.b]);
}

// Tableau des couleurs disponibles
var colors = [
  { r: 255, g: 138, b: 0 }, // Disque 1
  { r: 255, g: 92, b: 0 },  // Disque 2
  { r: 255, g: 0, b: 0 },   // Disque 3
  { r: 165, g: 0, b: 119 }, // Disque 4
  { r: 97, g: 0, b: 77 },   // Disque 5
  { r: 37, g: 0, b: 51 },   // Disque 6
  { r: 9, g: 0, b: 107 }    // Disque 7
];

// Méthode pour générer un entier aléatoire dans une plage donnée
function random_int(min, max) {
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

// Propriété statique pour stocker les index des couleurs déjà utilisées
Colour.usedColors = [];
