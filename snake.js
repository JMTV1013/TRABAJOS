const readline = require("readline");

readline.emitKeypressEvents(process.stdin);
process.stdin.setRawMode(true);

let width = 20;
let height = 15;

// posicion inicial de la serpiente
function crearSerpienteInicial() {
    snake = [
        { x: 5, y: 5 },
        { x: 4, y: 5 },
        { x: 3, y: 5 },
        { x: 2, y: 5 },
        { x: 1, y: 5 }
    ];
}

let snake = [];
crearSerpienteInicial();

let dx = 1;
let dy = 0;

let comidas = [];
let trampas = [];

let level = 1;
let velocidad = 200;

let gameOver = false;

//verufica si una posicion esta ocupada por la serpiente
function posicionEnSnake(pos) {
    return snake.some(p => p.x === pos.x && p.y === pos.y);
}

// funcion para verificar si una casilla esta ocupada
function posicionOcupada(pos) {
    if (posicionEnSnake(pos)) return true;
    if (comidas.some(c => c.x === pos.x && c.y === pos.y)) return true;
    if (trampas.some(t => t.x === pos.x && t.y === pos.y)) return true;
    return false;
}

// aqui se genera la comida en posiciones libres
function crearComida() {
    let pos;
    do {
        pos = { x: Math.floor(Math.random() * width), y: Math.floor(Math.random() * height) };
    } while (posicionOcupada(pos));
    comidas.push(pos);
}

// funcion para crear trampas en una posicion libre
function crearTrampa() {
    let pos;
    do {
        pos = { x: Math.floor(Math.random() * width), y: Math.floor(Math.random() * height) };
    } while (posicionOcupada(pos));
    trampas.push(pos);
}

crearComida();
crearTrampa();

// esta funcion sube eel nivel
function subirNivel() {
    level++;

    crearSerpienteInicial();

    dx = 1;
    dy = 0;

    velocidad = Math.max(50, velocidad - 15);

    crearComida();

    crearTrampa();
    crearTrampa();

    clearInterval(juego);
    juego = setInterval(tick, velocidad);
}

// aqui dibujo el tablero, nivel y progreso hacia el siguiente nivel
function dibujar() {
    console.clear();

    console.log(`=== NIVEL: ${level} ===`);
    console.log(`Sig Nivel: ${snake.length}/15`);

    let tablero = Array.from({ length: height }, () => Array(width).fill(" "));

    comidas.forEach(c => tablero[c.y][c.x] = "*");
    trampas.forEach(t => tablero[t.y][t.x] = "X");

    snake.forEach((p, i) => {
        tablero[p.y][p.x] = i === 0 ? "O" : "o";
    });

    console.log(".".repeat(width + 2));
    for (let y = 0; y < height; y++) {
        console.log("." + tablero[y].join("") + ".");
    }
    console.log(".".repeat(width + 2));

    console.log("\nO = cabeza");
    console.log("o = cuerpo");
    console.log("* = comida");
    console.log("X = trampa");
    console.log("Mover: W A S D");
}

// esta funcion detecta las colisiones y define el tamaño de la serpiente
function mover() {
    let nuevaCabeza = {
        x: snake[0].x + dx,
        y: snake[0].y + dy
    };

    if (nuevaCabeza.x < 0) nuevaCabeza.x = width - 1;
    if (nuevaCabeza.x >= width) nuevaCabeza.x = 0;
    if (nuevaCabeza.y < 0) nuevaCabeza.y = height - 1;
    if (nuevaCabeza.y >= height) nuevaCabeza.y = 0;

    if (posicionEnSnake(nuevaCabeza)) {
        gameOver = true;
        return;
    }

    snake.unshift(nuevaCabeza);

    let comida = comidas.findIndex(c => c.x === nuevaCabeza.x && c.y === nuevaCabeza.y);
    if (comida !== -1) {
        comidas.splice(comida, 1);
        crearComida();
    } 
    else {
        let trampa = trampas.findIndex(t => t.x === nuevaCabeza.x && t.y === nuevaCabeza.y);
        if (trampa !== -1) {
            trampas.splice(trampa, 1);
            crearTrampa();

            if (snake.length <= 2) {
                gameOver = true;
                return;
            }

            snake.pop();
            snake.pop();
        } 
        else {
            snake.pop();
        }
    }

    if (snake.length >= 15) {
        subirNivel();
    }
}

process.stdin.on("keypress", (str, key) => {
    if (key.sequence === "w" && dy !== 1) { dy = -1; dx = 0; }
    if (key.sequence === "s" && dy !== -1) { dy = 1; dx = 0; }
    if (key.sequence === "a" && dx !== 1) { dx = -1; dy = 0; }
    if (key.sequence === "d" && dx !== -1) { dx = 1; dy = 0; }

    if (key.sequence === "\u0003") process.exit();
});

function tick() {
    if (gameOver) {
        console.clear();
        console.log("¡Juego terminado!");
        console.log("\nO = cabeza");
        console.log("o = cuerpo");
        console.log("* = comida");
        console.log("X = trampa");
        console.log("Mover: W A S D");
        clearInterval(juego);
        process.exit();
    }

    mover();
    dibujar();
}

let juego = setInterval(tick, velocidad);
