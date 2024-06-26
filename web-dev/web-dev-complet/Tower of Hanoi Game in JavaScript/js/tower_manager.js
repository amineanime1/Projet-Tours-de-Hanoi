function TowerManager(canvas, disks_count) {
  this.canvas = canvas;
  this.disks_count = parseInt(disks_count, 10);
  this.towers_count = 3;
  this.create_towers();
  this.add_initial_disks();
}
// ajouter les disques initiaux dans la tour
TowerManager.prototype.add_initial_disks = function() {
  var disk_widths = this.calculate_disk_widths();
  while(width = disk_widths.pop()) new Disk(this.towers[0], width, Colour.random().toString());
}
// dessiner la tour
TowerManager.prototype.draw = function() {
  this.canvas.clear();
  for(i in this.towers) {
    this.towers[i].draw();
  }
}
// creation des tour avec leur hauteur , largeur , coulleur
TowerManager.prototype.create_towers = function() {
  this.towers = [];
  var base_width = this.calculate_disk_widths().pop() + 30;
  var stem_height = this.disks_count*Disk.height + 40;
  var base_horizontal_separation = biggest(16, base_width/10);
  var horizontal_padding = 42;
  var vertical_padding = 80;

  var towers_width = base_width*this.towers_count + base_horizontal_separation*(this.towers_count - 1);
 
  this.canvas.set_width(towers_width + 2*horizontal_padding);
  var x = (this.canvas.width - towers_width)/2;

  for(var i = 0; i < this.towers_count; i++) {

    var tower = new Tower(new Point(x, vertical_padding), base_width, stem_height, this.canvas.ctx);
    this.towers.push(tower);
    x += base_width + base_horizontal_separation;
  }
  this.canvas.set_height(this.towers[0].height + 2*vertical_padding);
}
// calcul de la largeur des disques
TowerManager.prototype.calculate_disk_widths = function() {
  var disk_widths = [];
  var width = 40;
  for(var i = 0; i < this.disks_count; i++) {
    disk_widths.push(width += 20);
  }
  return disk_widths;
}
// recuperer le disque cliqué
TowerManager.prototype.get_clicked_disk = function(point) {
  var disks = this.get_all_disks();
  for(i in disks) {
    if(disks[i].is_clicked_on(point)) return disks[i];
  }
}
// recuperer tout les disques
TowerManager.prototype.get_all_disks = function() {
  var disks = [];
  for(i in this.towers) disks = disks.concat(this.towers[i].disks);
  return disks;
}
// trouver la tour la plus proche
TowerManager.prototype.find_closest_tower = function(point) {
  var distances = [];
  for(i in this.towers) {
    distances.push({'tower':    this.towers[i],
                    'distance': this.towers[i].top.distance_to(point)});
  }
  distances.sort(function(a, b) { return a.distance - b.distance; });
  return distances[0]['tower'];
}

// return la chaine de caractere des tours
TowerManager.prototype.toString = function() {
  return 'TowerManager( ' + this.towers + ' )';
}
