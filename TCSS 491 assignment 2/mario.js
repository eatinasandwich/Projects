function mario(game) {
	this.x = 10;
	this.y = 50;
	this.width = 40;
	this.height = 40;
	this.game = game;
	this.ctx = game.ctx;

	this.idleRightAnimation = new Animation(AM.getAsset("./img/sprite-sheet-mario.png"), 40, 40, .05, 1, 0, 4, true, false);
	this.idleLeftAnimation = new Animation(AM.getAsset("./img/sprite-sheet-mario.png"), 40, 40, .05, 1, 0, 5, true, false);
	this.jumpRightAnimation = new Animation(AM.getAsset("./img/sprite-sheet-mario.png"), 40, 40, .05, 1, 1, 5, true, false);
	this.jumpleftAnimation = new Animation(AM.getAsset("./img/sprite-sheet-mario.png"), 40, 40, .05, 1, 0, 4, true, false);

	this.currentAnimation = this.idleRightAnimation;
}

mario.prototype.translateCoords = function () {
	return [this.x - (this.width / 2), this.y + this.height];
}

mario.prototype.update = function () {
	if (this.currentAnimation.isDone()) {
		switch(this.currentAnimation) {
			case this.idleRightAnimation:
				this.currentAnimation = this.jumpRightAnimation;
				this.y += 1;
				break;
			case this.idleLeftAnimation:
				break;
			case this.jumpRightAnimation:

				break;
			case this.jumpleftAnimation:
				break;
			case default:
				this.currentAnimation = this.idleRightAnimation;
		}
	}

}

mario.prototype.draw = function (ctx){
	this.currentAnimation.drawFrame(this.game.clockTick, this.ctx, this.x, this.y);
}