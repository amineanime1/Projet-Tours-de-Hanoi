function GameState(tower_manager) {
  this.tower_manager = tower_manager;
  this.connect_to_disks();
  this.last_complete_tower = this.find_complete_tower();
}

// method quand on change la position du disque
GameState.prototype.on_disk_transferred = function() {
  var complete_tower = this.find_complete_tower();
  if(complete_tower && complete_tower != this.last_complete_tower) {
    this.last_complete_tower = complete_tower;
    this.on_victory();
  }
}
// method pour trouver la tour complete
GameState.prototype.find_complete_tower = function() {
  var towers = this.tower_manager.towers;
  for(var i in towers) {
    if(towers[i].disks.length == this.count_total_disks()) return towers[i];
  }
}
// calcul du total des disques
GameState.prototype.count_total_disks = function() {
  return this.tower_manager.get_all_disks().length;
}

GameState.prototype.connect_to_disks = function() {
  var disks = this.tower_manager.get_all_disks();
  var self = this;
  for(var i in disks) {
       disks[i].on_disk_transferred = function() { self.on_disk_transferred(); }
  }
}

// method pour la victoire
GameState.prototype.on_victory = function() { }
