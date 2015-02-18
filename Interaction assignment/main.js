var AM = new AssetManager();

var FLOOR = 50;

function Animation(spriteSheet, frameWidth, frameHeight, frameDuration, frames, rowOffset, loop, reverse) {
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
}

Animation.prototype.drawFrame = function (tick, ctx, x, y) {
    this.elapsedTime += tick;
    if (this.isDone()) {
        if (this.loop) this.elapsedTime = 0;
    }
    var frame = this.currentFrame();
    
    var xindex = frame % 5;
    var yindex = Math.floor(frame / 5) + this.rowOffset;

    var sx = 3 + (xindex * (this.frameWidth + 17));
    var sy = 3 + (yindex * (this.frameHeight+ 17));
    ctx.drawImage(this.spriteSheet, //image
                 sx, sy,  // source location
                 this.frameWidth, this.frameHeight, //source dim
                 x, y, // destination location
                 this.frameWidth, // destination dim
                 this.frameHeight);
}

Animation.prototype.currentFrame = function () {
    return Math.floor(this.elapsedTime / this.frameDuration);
}

Animation.prototype.isDone = function () {
    return (this.elapsedTime >= this.totalTime);
}



AM.queueDownload("./img/sheet 4a.png");

AM.downloadAll(function () {
    var canvas = document.getElementById("gameWorld");
    var ctx = canvas.getContext("2d");


    var gameEngine = new GameEngine();
    gameEngine.init(ctx);
    gameEngine.initControls();
    gameEngine.start();

    

    console.log("All Done!");
});
















