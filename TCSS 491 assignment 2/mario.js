function mario(game) {
	this.x = 440;
	this.y = 490;
	this.width = 40;
	this.height = 40;
	this.game = game;
	this.ctx = game.ctx;
	this.upwardVelocity = 8;

	this.idleLeftAnimation = new Animation(AM.getAsset("./img/sprite-sheet-mario.png"), 40, 40, .05, 1, 0, 4, true, false);
	this.idleRightAnimation = new Animation(AM.getAsset("./img/sprite-sheet-mario.png"), 40, 40, .05, 1, 0, 5, true, false);
	this.jumpRightAnimation = new Animation(AM.getAsset("./img/sprite-sheet-mario.png"), 40, 40, .05, 1, 1, 5, true, false);
	this.jumpleftAnimation = new Animation(AM.getAsset("./img/sprite-sheet-mario.png"), 40, 40, .05, 1, 0, 4, true, false);

	this.currentAnimation = this.jumpRightAnimation;
}

mario.prototype.translateCoords = function () {
	return [this.x - (this.width / 2), this.y + this.height];
}

mario.prototype.update = function () {
	var dest;
	if (this.currentAnimation.isDone()) {
		switch(this.currentAnimation) {
			case this.idleRightAnimation:
				this.y = FLOOR;
				break;
			case this.idleLeftAnimation:
				break;
			case this.jumpRightAnimation:
				dest = this.jumpDecision();
				break;
			case this.jumpleftAnimation:
				break;
			default:
				this.currentAnimation = this.idleRightAnimation;
		}
	}
	

}

mario.prototype.jumpDecision = function() {
	var entities = this.game.entities;
	var length = entities.length;
	
	var dest = [this.x, this.y];
	
	dest[1] -= this.upwardVelocity;
	
	if (Math.abs(dest[0] - this.game.mouseCurrentX) <= 100) {
		if (dest[0] > this.game.mouseCurrentX) {
			dest[0] += 2;
		} else {
			dest[0] -= 2;
		}
	}
	
	for (var i = 0; i < length; i++) {
		var entity = entities[i];
		if (entity.constructor === terrainObject && !entity.canPass(dest[0], dest[1], 40, 40)) {
			if (this.x > entity.right && dest[0] < entity.right) {//collision right
			//	dest[0] = entity.right;
			} else if (this.x < entity.left && dest[0] > entity.left) {//collision left
			//	dest[0] = entity.left - 40;
			} 
			if (this.y < entity.top && dest[1] > entity.top) {//collision top
				console.log("collision top");
				dest[1] = entity.top;
				this.upwardVelocity = 8;
			} else if (this.y > entity.bottom + 40 && dest[1] < entity.bottom + 40) {//collision bottom
			//	console.log("collision bottom");
			//	dest[1] = entity.bottom + 40;
			//	upwardVelocity = -1;
			}
		}
	}
	
	this.upwardVelocity -= .25;
	if (this.y >= FLOOR) {
		this.upwardVelocity = 8;
	}
	this.x = dest[0];
	this.y = dest[1];
}




mario.prototype.draw = function (){
	this.currentAnimation.drawFrame(this.game.clockTick, this.ctx, this.x, this.y);
}





























