// Class Tour
function Tower(position, base_width, stem_height, ctx) {
  this.position = position;
  this.ctx = ctx;
  this.disks = [];

  this.base = {'width': base_width, 'height': 1000};
  this.stem = {'width': 20, 'height': stem_height };
  this.height = this.base.height + this.stem.height;
  this.base.position = new Point(this.position.x, this.position.y + this.stem.height);
  this.stem.position = new Point(this.position.x + (this.base.width/2 - this.stem.width/2), this.position.y);

  this.top = new Point(this.stem.position.x + this.stem.width/2, this.stem.position.y);
  this.disks_top = this.base.position.y;
}

Tower.prototype.toString = function() {
  return 'Tower(x=' + this.position.x + ', y=' + this.position.y + ')';
}
// methode pour ajouter un disque dans la tour
Tower.prototype.add_disk = function(disk) {
  this.disks.push(disk);
  this.disks_top -= disk.height;
}
// methode pour enlever le disque de la tour
Tower.prototype.remove_disk = function(disk) {
  this.disks.splice(this.disks.indexOf(disk), 1);
  this.disks_top += disk.height;
}
// methode pour dessiner la tour
Tower.prototype.draw = function() {
  this.draw_self();
  this.draw_disks();
}

Tower.prototype.draw_self = function() {
  this.ctx.save();
  this.ctx.fillStyle = '#460000';
  this.ctx.globalCompositeOperation = 'destination-over';
  
  // Dessiner la base avec des coins arrondis
  var baseX = this.base.position.x - 300; // Position x de la base
  var baseY = this.base.position.y; // Position y de la base
  var baseWidth = this.base.width + 600; // Largeur de la base
  var baseHeight = this.base.height; // Hauteur de la base
  var cornerRadius = 20; // Rayon des coins arrondis
  
  this.ctx.beginPath();
  this.ctx.moveTo(baseX + cornerRadius, baseY);
  this.ctx.arcTo(baseX + baseWidth, baseY, baseX + baseWidth, baseY + baseHeight, cornerRadius);
  this.ctx.arcTo(baseX + baseWidth, baseY + baseHeight, baseX, baseY + baseHeight, cornerRadius);
  this.ctx.arcTo(baseX, baseY + baseHeight, baseX, baseY, cornerRadius);
  this.ctx.arcTo(baseX, baseY, baseX + baseWidth, baseY, cornerRadius);
  this.ctx.closePath();
  this.ctx.fill();
  
  // Dessiner la tige avec un haut arrondi
  var stemX = this.stem.position.x; // Position x de la tige
  var stemY = this.stem.position.y; // Position y de la tige
  var stemWidth = this.stem.width; // Largeur de la tige
  var stemHeight = this.stem.height +20; // Hauteur de la tige
  var stemCornerRadius = 10; // Rayon du haut arrondi de la tige
  
  this.ctx.beginPath();
  this.ctx.moveTo(stemX + stemCornerRadius, stemY);
  this.ctx.arcTo(stemX + stemWidth, stemY, stemX + stemWidth, stemY + stemHeight, stemCornerRadius);
  this.ctx.arcTo(stemX + stemWidth, stemY + stemHeight, stemX, stemY + stemHeight, stemCornerRadius);
  this.ctx.arcTo(stemX, stemY + stemHeight , stemX, stemY, stemCornerRadius);
  this.ctx.arcTo(stemX, stemY, stemX + stemWidth, stemY, stemCornerRadius);
  this.ctx.closePath();
  this.ctx.fill();
  
  this.ctx.restore();
}

Tower.prototype.draw_disks = function() {
  for(i in this.disks)
    this.disks[i].draw();
}

Tower.prototype.get_top_disk = function() {
  return this.disks[this.disks.length - 1];
}
