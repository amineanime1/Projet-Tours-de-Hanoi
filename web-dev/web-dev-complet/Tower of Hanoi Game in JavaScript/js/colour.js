




// Propriété statique pour stocker les index des couleurs déjà utilisées
Colour.usedColors = [];

function Colour(rgb) {
  this.rgb = rgb;
}

Colour.prototype.toString = function() {
  return 'rgb(' + this.rgb.join() + ')';
}

Colour.nextColorIndex = 0; // Index de la prochaine couleur à utiliser

Colour.random = function() {
  // Si toutes les couleurs ont été utilisées, réinitialisez l'index à zéro
  if (Colour.nextColorIndex === colors.length) {
    Colour.nextColorIndex = 0;
  }
  
  // Sélectionnez la couleur suivante dans l'ordre du tableau colors
  var selectedColor = colors[Colour.nextColorIndex];
  
  // Incrémentez l'index pour la prochaine couleur
  Colour.nextColorIndex++;
  
  // Créez un nouvel objet Colour avec les composantes R, G et B de la couleur sélectionnée
  return new Colour([selectedColor.r, selectedColor.g, selectedColor.b]);
}

// Tableau des couleurs disponibles
var colors = [
  { r: 9, g: 0, b: 107 } ,
  { r: 37, g: 0, b: 51 },  
  { r: 97, g: 0, b: 77 },
  { r: 165, g: 0, b: 119 },
  { r: 255, g: 0, b: 0 }, // Disque 2 
  { r: 255, g: 138, b: 0 }, 
  
];

