function Canvas(canvas_id) {
  this.canvas_id = canvas_id;
  this.recreate();
}
// Declaration de la classe canvas et ces 


// method pour demarer le canvas
Canvas.prototype.load_canvas = function() {
  this.canvas = document.getElementById(this.canvas_id);
  this.ctx = this.canvas.getContext('2d');
}
// methode pour mettre une largeur au canvas
Canvas.prototype.set_width = function(width) {
  this.canvas.width = this.width = biggest(window.innerWidth, width); // this.width can be queried by external agents.
}
// methode pour mettre une hauteur au canvas
Canvas.prototype.set_height = function(height) {
  this.canvas.height = this.height = 1900; // this.height can be queried by external agents.
}
// methode pour nettoyer le canvas des dessins
Canvas.prototype.clear = function() {
  this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
}
// methode pour recrée le  canvas
Canvas.prototype.recreate = function() {
  this.load_canvas();
  var canvas_prime = this.canvas.cloneNode(false);
  this.canvas.parentNode.replaceChild(canvas_prime, this.canvas);
  this.load_canvas();
}
