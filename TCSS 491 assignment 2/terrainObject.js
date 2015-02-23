function terrainObject() {
	this.solid = true;
	this.top = 412;
	this.right = 373;
	this.bottom = 440;
	this.left = 239;
	
}

terrainObject.prototype.canPass = function(sourceX, sourceY, destX, destY, width, height) {
	if (destX > this.left - width && destX < this.right	&& 
		destY < this.bottom + height && destY > this.top) {
		return false;
	} else {
		return true;
	}
}

terrainObject.prototype.update = function() {
	//do nothing
}

terrainObject.prototype.draw = function() {
	//do nothing
}