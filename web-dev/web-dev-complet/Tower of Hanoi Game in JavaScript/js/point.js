function Point(x, y) {
  this.x = x;
  this.y = y;
}
//  methode pour les coordonnée des Point


// soustraire deux point
Point.prototype.subtract = function(point) {
  return new Point(this.x - point.x, this.y - point.y);
}
// calculer la distance entre deux point
Point.prototype.distance_to = function(other) {
  return Math.sqrt(Math.pow(other.x - this.x, 2) + Math.pow(other.y - this.y, 2));
}
// return la chaine de caractere des coordonnée
Point.prototype.toString = function() {
  return '(' + this.x + ', ' + this.y + ')';
}
