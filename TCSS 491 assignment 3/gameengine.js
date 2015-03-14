window.requestAnimFrame = (function () {
    return window.requestAnimationFrame ||
            window.webkitRequestAnimationFrame ||
            window.mozRequestAnimationFrame ||
            window.oRequestAnimationFrame ||
            window.msRequestAnimationFrame ||
            function (/* function */ callback, /* DOMElement */ element) {
                window.setTimeout(callback, 1000 / 60);
            };
})();

function GameEngine() {
    this.entities = [];
    this.ctx = null;
    this.surfaceWidth = null;
    this.surfaceHeight = null;
	this.mouseCurrentX = -500;
	this.mouseCurrentY = -500;
	this.debug = false;
	//this.stopped = true;
}

GameEngine.prototype.init = function (ctx) {
    this.ctx = ctx;
    this.surfaceWidth = this.ctx.canvas.width;
    this.surfaceHeight = this.ctx.canvas.height;
    this.timer = new Timer();
    console.log('game initialized');
}

GameEngine.prototype.initControls = function () {
	var that = this;
    this.ctx.canvas.addEventListener("mousemove", function (e) {
        e.preventDefault();
	    that.mouseCurrentX = e.layerX;
		that.mouseCurrentY = e.layerY;
		//console.log(this.mouseCurrentX);
	});
	
	//var start = document.getElementById("startButton");
	//var stop = document.getElementById("stopButton");
	//var that = this;
	//start.addEventListener("click", function(e) {
	//	e.preventDefault();
	//	that.stopped = false;
	//}, false);
	//stop.addEventListener("click", function(e) {
	//	e.preventDefault();
	//	that.stopped = true;
	//}, false);
}

GameEngine.prototype.start = function () {
    console.log("starting game");
    var that = this;
    (function gameLoop() {
        that.loop();
        requestAnimFrame(gameLoop, that.ctx.canvas);
    })();
}

GameEngine.prototype.addEntity = function (entity) {
    console.log('added entity');
    this.entities.push(entity);
}

GameEngine.prototype.draw = function () {
    this.ctx.clearRect(0, 0, this.surfaceWidth, this.surfaceHeight);
    this.ctx.save();
    for (var i = 0; i < this.entities.length; i++) {
        this.entities[i].draw(this.ctx);
		if (this.entities[i].constructor === terrainObject && this.debug) {
			var entity = this.entities[i];
			this.ctx.beginPath();
			this.ctx.moveTo(entity.left - 20, 600 - entity.bottom);
			this.ctx.lineTo(entity.right + 20, 600 - entity.bottom);
			this.ctx.stroke();
			this.ctx.beginPath();
			this.ctx.moveTo(entity.left - 20, 600 - entity.top);
			this.ctx.lineTo(entity.right + 20, 600 - entity.top);
			this.ctx.stroke();
		}
    }
    this.ctx.restore();
}

GameEngine.prototype.update = function () {
    var entitiesCount = this.entities.length;
    for (var i = 0; i < entitiesCount; i++) {
        var entity = this.entities[i];
		entity.update();
    }
	
	for (var i = 0; i < entitiesCount; i++) {
        var entity = this.entities[i];
		if(entity.constructor === mario) {
			if (entity.dead) {
				this.entities.splice(i, 1);
				entitiesCount--;
			}
		}
    }
}

GameEngine.prototype.loop = function () {
	if (!this.stopped) {
		this.clockTick = this.timer.tick();
		this.update();
		this.draw();
	}
	
}

function Timer() {
    this.gameTime = 0;
    this.maxStep = 0.05;
    this.wallLastTimestamp = 0;
}

Timer.prototype.tick = function () {
    var wallCurrent = Date.now();
    var wallDelta = (wallCurrent - this.wallLastTimestamp) / 1000;
    this.wallLastTimestamp = wallCurrent;

    var gameDelta = Math.min(wallDelta, this.maxStep);
    this.gameTime += gameDelta;
    return gameDelta;
}