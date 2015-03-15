var socket = io.connect("http://76.28.150.193:8888");
//console.log(socket);
var AM = new AssetManager();
var MARIO_COUNT = 10;
var FLOOR = 80;

window.onload = function() {
	
	AM.downloadAll(function () {
    var canvas = document.getElementById("gameWorld");
    var ctx = canvas.getContext("2d");
	var marioButton = document.getElementById("mariosButton");
	var numMariosField = document.getElementById("numMarios");

    var gameEngine = new GameEngine();
    gameEngine.init(ctx);
    gameEngine.initControls();
    gameEngine.start();
	gameEngine.addEntity(new Background(ctx));
    gameEngine.addEntity(new terrainObject(296, 267, 293, 319));//top block
	gameEngine.addEntity(new terrainObject(187, 160, 239, 373));//platform
	gameEngine.addEntity(new terrainObject(187, 160, 133, 159));//left block
	gameEngine.addEntity(new terrainObject(134, 0, 453, 506));//left pipe
	gameEngine.addEntity(new terrainObject(160, 0, 720, 773));//right pipe
	
	marioButton.addEventListener("click", function(e) {
		e.preventDefault();
		for (var i = 0; i < numMariosField.value; i++) {
			var x = Math.floor(Math.random() * 800);
			var direction = Math.floor(Math.random() * 1.999);
			var terminalVelocity = -(8 + 2 * Math.random());
			gameEngine.addEntity(new mario(gameEngine, x, 80, direction, terminalVelocity));		
		}
	}, false);
	
	socket.on("load", function(data) {
		var entities = data.gameState;
		console.log(data.gameState);
		gameEngine.entities = [];
		gameEngine.addEntity(new Background(ctx));
		gameEngine.addEntity(new terrainObject(296, 267, 293, 319));//top block
		gameEngine.addEntity(new terrainObject(187, 160, 239, 373));//platform
		gameEngine.addEntity(new terrainObject(187, 160, 133, 159));//left block
		gameEngine.addEntity(new terrainObject(134, 0, 453, 506));//left pipe
		gameEngine.addEntity(new terrainObject(160, 0, 720, 773));//right pipe
		for (var i = 0; i < entities.length; i++) {
			var newMario = new mario(gameEngine, entities[i].x, entities[i].y, 
												entities[i].direction, entities[i].terminalVelocity);
			newMario.upwardVelocity = entities[i].upwardVelocity;
			gameEngine.entities.push(newMario);
		}
	});
	
	document.getElementById("save").onclick = function(e) {
		e.preventDefault();
		console.log("Attempting to save");
		var entities = gameEngine.entities;
		var saveState = {studentname: "JaredHelm", statename: "entityData", gameState: []};
		for (var i = 0; i < gameEngine.entities.length; i++) {
			if (gameEngine.entities[i].hasOwnProperty("terminalVelocity")) {
				var mario = gameEngine.entities[i];
				saveState.gameState.push({x: mario.x, y: mario.y, 
										direction: mario.currentAnimation === mario.jumpLeftAnimation ? 0 : 1, 
										terminalVelocity: mario.terminalVelocity,
										upwardVelocity: mario.upwardVelocity});
				console.log("pushing mario");
			}
			
		}
		socket.emit("save", saveState);
		
	}
	
	document.getElementById("load").onclick = function(e) {
		e.preventDefault();
		console.log("Attempting to load");
		socket.emit("load", {studentname: "JaredHelm", statename: "entityData"});
	}
	
});
}

function Animation(spriteSheet, frameWidth, frameHeight, frameDuration, frames, rowOffset, columnOffset, loop, reverse) {
    this.spriteSheet = spriteSheet;
    this.frameWidth = frameWidth;
    this.frameDuration = frameDuration;
    this.frameHeight = frameHeight;
    this.frames = frames;
    this.totalTime = frameDuration * frames;
    this.elapsedTime = 0;
    this.loop = loop;
    this.reverse = reverse;
    this.rowOffset = rowOffset;
    this.columnOffset = columnOffset;
}

Animation.prototype.drawFrame = function (tick, ctx, x, y) {
    this.elapsedTime += tick;
    var frame = -1;
    if (this.isDone()) {
        if (this.loop) this.elapsedTime = 0;
        else frame = this.frames - 1;
    }
    if (frame === -1) {
        var frame = this.currentFrame();
    }
    var xindex = frame % 10 + this.columnOffset;
    var yindex = this.rowOffset;
	
	ctx.drawImage(this.spriteSheet,
                    xindex * this.frameWidth, yindex * this.frameHeight,
                    this.frameWidth, this.frameHeight,
                    x, y,
                    this.frameWidth,
                    this.frameHeight);
}

Animation.prototype.currentFrame = function () {
    return Math.floor(this.elapsedTime / this.frameDuration);
}

Animation.prototype.isDone = function () {
    return (this.elapsedTime >= this.totalTime);
}

function Background(ctx) {
	this.img = AM.getAsset("./img/super_mario_background.jpg");
	this.ctx = ctx;
}

Background.prototype.draw = function() {
	this.ctx.drawImage(this.img, 0, 0);
}

Background.prototype.update = function() {
	//do nothing, your a background
}

AM.queueDownload("./img/sprite-sheet-mario.png");
AM.queueDownload("./img/super_mario_background.jpg");


















