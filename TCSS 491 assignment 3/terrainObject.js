function terrainObject(top, bottom, left, right) {
	this.solid = true;
	this.top = top;
	this.right = right;
	this.bottom = bottom;
	this.left = left;
	this.dead = false;
}

terrainObject.prototype.update = function() {
	//do nothing
}

terrainObject.prototype.draw = function() {
	//do nothing
}