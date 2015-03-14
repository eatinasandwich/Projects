var FOOT = 31; 
var HEAD = 3;
var LEFT = 6;
var RIGHT = 21;

function mario(game, initX, initY, initDirection, terminalVelocity) {
	this.x = 440;
	this.x = initX;
	this.y = 80;
	this.y = initY;
	this.width = 40;
	this.height = 28;
	this.game = game;
	this.ctx = game.ctx;
	this.terminalVelocity = terminalVelocity;
	this.upwardVelocity = -this.terminalVelocity;
	this.dead = false;

	this.idleLeftAnimation = new Animation(AM.getAsset("./img/sprite-sheet-mario.png"), 40, 40, .05, 1, 0, 4, true, false);
	this.idleRightAnimation = new Animation(AM.getAsset("./img/sprite-sheet-mario.png"), 40, 40, .05, 1, 0, 5, true, false);
	this.jumpRightAnimation = new Animation(AM.getAsset("./img/sprite-sheet-mario.png"), 40, 40, .05, 1, 1, 5, true, false);
	this.jumpLeftAnimation = new Animation(AM.getAsset("./img/sprite-sheet-mario.png"), 40, 40, .05, 1, 1, 4, true, false);
	this.walkLeftAnimation = new Animation(AM.getAsset("./img/sprite-sheet-mario.png"), 40, 40, .25, 2, 0, 0, true, false);
	this.walkRightAnimation = new Animation(AM.getAsset("./img/sprite-sheet-mario.png"), 40, 40, .25, 2, 0, 8, true, false);

	if (initDirection === 0) {
		this.currentAnimation = this.jumpLeftAnimation;
	} else {
		this.currentAnimation = this.jumpRightAnimation;
	}
	
}

mario.prototype.translateCoords = function () {
	return [this.x - (this.width / 2), this.y + this.height];
}

mario.prototype.update = function () {
	switch(this.currentAnimation) {
		case this.idleRightAnimation:
			break;
		case this.idleLeftAnimation:
			break;
		case this.jumpRightAnimation:
			this.jumpDecision();
			break;
		case this.jumpLeftAnimation:
			this.jumpDecision();
			break;
		case this.walkRightAnimation:
			this.walkDecision();
			break;
		case this.walkLeftAnimation:
			this.walkDecision();
			break;
		default:
			this.currentAnimation = this.idleRightAnimation;
	}
	
	var entities = this.game.entities;
	var center = {x: this.x + 20, y: this.y + 20};
	for (var i = 0; i < entities.length; i++) {
		if (entities[i].constructor === mario && entities[i] != this) {
			var other = entities[i];
			var otherCenter = {x: other.x + 20, y: other.y + 20};
			var distance = Math.sqrt(Math.pow(center.x - otherCenter.x, 2) + Math.pow(center.y - otherCenter.y, 2));
			if (distance <= 20) {
				this.dead = true;
				console.log("dead");
				other.terminalVelocity -= Math.random() * 2;
			}
		}
	}
}

mario.prototype.jumpDecision = function() {
	var entities = this.game.entities;
	var length = entities.length;
	
	var dest = [this.x, this.y];
	
	dest[1] += this.upwardVelocity;

	//if (Math.abs(dest[0] - this.game.mouseCurrentX) <= 100) {
	//	if (dest[0] > this.game.mouseCurrentX) {
	//		dest[0] += 2;
	//	} else {
	//		dest[0] -= 2;
	//	}
	//}
	if (this.currentAnimation === this.jumpRightAnimation) {
		dest[0] += 2;
	} else {
		dest[0] -= 2;
	}
	
	for (var i = 0; i < length; i++) {
		var entity = entities[i];
		if (entity.constructor === terrainObject) {
			if (dest[0] + LEFT < entity.right && dest[0] + RIGHT > entity.left) {
				if (dest[1] < entity.top && dest[1] + (FOOT - HEAD) > entity.bottom &&
					!(this.x + LEFT < entity.right && this.x + RIGHT > entity.left)) {//entering from the side
					if (this.currentAnimation === this.jumpLeftAnimation) {
						this.currentAnimation = this.jumpRightAnimation;
					} else {
						this.currentAnimation = this.jumpLeftAnimation;
					}
					
				}
					
				
				if (this.y >= entity.top && dest[1] < entity.top) {
					dest[1] = entity.top;
					this.upwardVelocity = -this.terminalVelocity;
				} else if (this.y + (FOOT - HEAD) < entity.bottom && dest[1] + (FOOT - HEAD) > entity.bottom) {
					this.upwardVelocity = 0;
					dest[1] = entity.bottom - FOOT;
				}
			}
		}
	}
	if (this.currentAnimation === this.jumpRightAnimation || this.currentAnimation === this.jumpLeftAnimation) {
		this.upwardVelocity -= .25;
	}
	if (this.y < FLOOR) {
		this.upwardVelocity = -this.terminalVelocity;
		dest[1] = FLOOR;
	} else if (this.upwardVelocity < this.terminalVelocity) {
		this.upwardVelocity = this.terminalVelocity;
	}
	
	if (dest[0] <= 0) {
		dest[0] = 0;
		this.currentAnimation = this.jumpRightAnimation;
	} else if(dest[0] > 800 - RIGHT) {
		dest[0] = 800 - RIGHT;
		this.currentAnimation = this.jumpLeftAnimation;
	}
	
	this.x = dest[0];
	this.y = dest[1];
}

mario.prototype.walkDecision = function() {
	if (this.currentAnimation === this.walkLeftAnimation) {
		this.x -= 2;
	} else {
		this.x += 2;
	}
	
	if (this.x < 0) {
		this.x = 0;
		this.currentAnimation = this.walkRightAnimation;
	} else if (this.x > 800 - RIGHT) {
		this.x = 800 - RIGHT;
		this.currentAnimation = this.walkLeftAnimation;
	}
}



mario.prototype.draw = function (){
	this.currentAnimation.drawFrame(this.game.clockTick, this.ctx, this.x, 600 - this.y - FOOT);
}





























