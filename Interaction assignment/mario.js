function mario(game, animation) {
	this.animation = animation;
	this.x = 10;
	this.y = 50;
	this.width = 40;
	this.height = 40;
	this.game = game;
	this.ctx = game.ctx;
}

mario.prototype.translateCoords() {
	return [this.x - (this.width / 2), this.y + this.height];
}