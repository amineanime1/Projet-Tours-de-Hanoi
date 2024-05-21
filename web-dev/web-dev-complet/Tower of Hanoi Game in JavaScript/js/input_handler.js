function InputHandler(ctx, tower_manager) {
  this.ctx = ctx;
  this.tower_manager = tower_manager;
  this.canvas = ctx.canvas;
  this.coordinate_finder = new ElementCoordinateFinder(this.canvas);
  this.add_event_listeners();
  this.enable_input();
}
// mettre des listeners pour le mouvement de la souris
InputHandler.prototype.add_event_listeners = function() {
  debug.msg('Adding event listeners');
   var self = this;
  this.canvas.addEventListener('mousedown', function(event) { self.on_canvas_mousedown(event); }, false);
  this.canvas.addEventListener('mousemove', function(event) { self.on_canvas_mousemove(event); }, false);
  this.canvas.addEventListener('mouseup',   function(event) { self.on_canvas_mouseup(event); },   false);
}

InputHandler.prototype.on_canvas_mousedown = function(event) {
  if(!this.allow_input) return;
  var coords = this.coordinate_finder.get_mouse_coordinates(event);
  this.disk = this.tower_manager.get_clicked_disk(coords);
  if(!this.disk || !this.disk.is_top_disk()) return;

  this.mouse_delta = coords.subtract(this.disk.position);
  this.dragging = true;
}

InputHandler.prototype.on_canvas_mousemove = function(event) {
  if(!this.dragging) return;
  var coords = this.coordinate_finder.get_mouse_coordinates(event);
  this.disk.move_to(coords.subtract(this.mouse_delta));
  this.tower_manager.draw();
  this.show_distance_to_each_tower();
}

InputHandler.prototype.show_distance_to_each_tower = function() {
  debug.clear();
  debug.msg('Distance to tower 1: ' + this.disk.centre.distance_to(this.tower_manager.towers[0].top));
  debug.msg('Distance to tower 2: ' + this.disk.centre.distance_to(this.tower_manager.towers[1].top));
  debug.msg('Distance to tower 3: ' + this.disk.centre.distance_to(this.tower_manager.towers[2].top));
}

// fonction quand on fait monter la souris
InputHandler.prototype.on_canvas_mouseup = function(event) {
  if(!this.dragging) return;
  this.dragging = false;
  var closest_tower = this.tower_manager.find_closest_tower(this.disk.centre);
  this.disk.transfer_to_tower(closest_tower);
 
  this.tower_manager.draw();
}
// fonction pour desactiver l'input
InputHandler.prototype.disable_input = function() {
  debug.msg('Input disabled');
  this.allow_input = false;
}
// fonction pour activer l'input
InputHandler.prototype.enable_input = function() {
  debug.msg('Input enabled');
  this.allow_input = true;
}
