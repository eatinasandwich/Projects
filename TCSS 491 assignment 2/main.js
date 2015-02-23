var AM = new AssetManager();

var FLOOR = 490;

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
    this.done = false;
}

Animation.prototype.drawFrame = function (tick, ctx, x, y) {
    this.elapsedTime += tick;
    if (this.isDone()) {
        if (this.loop) this.elapsedTime = 0;
    }
    var frame = this.currentFrame();
    
    var xindex = frame % 10 + this.columnOffset;
    var yindex = Math.floor(frame / 10) + this.rowOffset;

    var sx = xindex * 40;
    var sy = yindex * 40;
    ctx.drawImage(this.spriteSheet, //image
                 sx, sy,  // source location
                 this.frameWidth, this.frameHeight, //source dim
                 x, y, // destination location
                 this.frameWidth, // destination dim
                 this.frameHeight);
    if (frame === this.frames) {
        this.done = true;
    }
}

Animation.prototype.currentFrame = function () {
    return Math.floor(this.elapsedTime / this.frameDuration);
}

Animation.prototype.isDone = function () {
    return this.done;
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

AM.downloadAll(function () {
    var canvas = document.getElementById("gameWorld");
    var ctx = canvas.getContext("2d");


    var gameEngine = new GameEngine();
    gameEngine.init(ctx);
    gameEngine.initControls();
    gameEngine.start();
	gameEngine.addEntity(new Background(ctx));
	gameEngine.addEntity(new mario(gameEngine));
    gameEngine.addEntity(new terrainObject());

    console.log("All Done!");
});
















