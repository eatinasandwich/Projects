var AM = new AssetManager();

var FLOOR = 50;

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



AM.queueDownload("./img/sprite-sheet-mario.png");

AM.downloadAll(function () {
    var canvas = document.getElementById("gameWorld");
    var ctx = canvas.getContext("2d");


    var gameEngine = new GameEngine();
    gameEngine.init(ctx);
    //gameEngine.initControls();
    gameEngine.start();
    gameEngine.addEntity(new mario(gameEngine));
    

    console.log("All Done!");
});
















